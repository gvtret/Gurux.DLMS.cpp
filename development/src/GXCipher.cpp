//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "../include/GXCipher.h"
#include "../include/chipperingenums.h"
#include "../include/GXHelpers.h"

void CGXCipher::Init(
    unsigned char* systemTitle,
    unsigned char count)
{
    const unsigned char BLOCKCIPHERKEY[] =
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    const unsigned char AUTHENTICATIONKEY[] =
    {
        0xD0,  0xD1,  0xD2, 0xD3,  0xD4,  0xD5,  0xD6,  0xD7,
        0xD8,  0xD9,  0xDA,  0xDB,  0xDC, 0xDD,  0xDE,  0xDF
    };
    m_FrameCounter = 0;
    m_Security = DLMS_SECURITY_NONE;
    m_SystemTitle.Set(systemTitle, count);
    m_BlockCipherKey.Set(BLOCKCIPHERKEY, sizeof(BLOCKCIPHERKEY));
    m_AuthenticationKey.Set(AUTHENTICATIONKEY, sizeof(AUTHENTICATIONKEY));
    m_SecuritySuite = DLMS_SECURITY_SUITE_V0;
}

CGXCipher::CGXCipher(CGXByteBuffer& systemTitle)
{
    Init((unsigned char*)systemTitle.m_Data, (unsigned char)systemTitle.m_Size);
}

CGXCipher::CGXCipher(const char* systemTitle)
{
    Init((unsigned char*)systemTitle, (unsigned char)strlen(systemTitle));
}

CGXCipher::CGXCipher(unsigned char* systemTitle, unsigned char count)
{
    Init(systemTitle, count);
}

CGXCipher::~CGXCipher()
{
}

/**
* Get nonse from frame counter and system title.
*
* @param frameCounter
*            Frame counter.
* @param systemTitle
*            System title.
* @return
*/
static int GetNonse(
    unsigned long frameCounter,
    CGXByteBuffer& systemTitle,
    CGXByteBuffer& nonce)
{
    if (systemTitle.GetSize() != 8)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    nonce.SetSize(0);
    nonce.Capacity(12);
    nonce.Set(systemTitle.GetData(), systemTitle.GetSize());
    nonce.SetUInt32(frameCounter);
    return 0;
}


int CGXCipher::Encrypt(
    DLMS_SECURITY_SUITE suite,
    DLMS_SECURITY security,
    DLMS_COUNT_TYPE type,
    unsigned long frameCounter,
    unsigned char tag,
    CGXByteBuffer& systemTitle,
    CGXByteBuffer& key,
    CGXByteBuffer& input,
    bool encrypt)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    unsigned char ciphertext[128];
    unsigned char aad[33];
    unsigned char iv[12];
    unsigned char tag_buf[16];

    // Create and initialise the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
        return DLMS_ERROR_CODE_INVALID_PARAMETER;

    if (encrypt)
    {
        // Initialise the encryption operation.
        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Set IV length
        if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Initialise key and IV
        CGXByteBuffer nonce;
        nonce.Set(iv, 12);
        GetNonse(frameCounter, systemTitle, nonce);
        if(1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key.m_Data, iv))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Provide AAD data
        CGXByteBuffer bb;
        bb.Set(aad, sizeof(aad));
        bb.SetUInt8(security | suite);
        bb.Set(m_AuthenticationKey.m_Data, m_AuthenticationKey.GetSize());

        if(1 != EVP_EncryptUpdate(ctx, NULL, &len, aad, bb.GetSize()))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Provide the message to be encrypted, and obtain the encrypted output.
        if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, input.m_Data, input.GetSize()))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        ciphertext_len = len;

        // Finalise the encryption.
        if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        ciphertext_len += len;

        // Get the tag
        if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag_buf))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        input.Clear();
        input.Set(ciphertext, ciphertext_len);
        input.Set(tag_buf, 16);
    }
    else
    {
        // Initialise the decryption operation.
        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Set IV length
        if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Initialise key and IV
        CGXByteBuffer nonce;
        nonce.Set(iv, 12);
        GetNonse(frameCounter, systemTitle, nonce);
        if(1 != EVP_DecryptInit_ex(ctx, NULL, NULL, key.m_Data, iv))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Provide AAD data
        CGXByteBuffer bb;
        bb.Set(aad, sizeof(aad));
        bb.SetUInt8(security | suite);
        bb.Set(m_AuthenticationKey.m_Data, m_AuthenticationKey.GetSize());

        if(1 != EVP_DecryptUpdate(ctx, NULL, &len, aad, bb.GetSize()))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Provide the message to be decrypted, and obtain the plaintext output.
        if(1 != EVP_DecryptUpdate(ctx, ciphertext, &len, input.m_Data, input.GetSize() - 16))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        ciphertext_len = len;

        // Set expected tag value.
        memcpy(tag_buf, input.m_Data + input.GetSize() - 16, 16);
        if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag_buf))
            return DLMS_ERROR_CODE_INVALID_PARAMETER;

        // Finalise the decryption. A positive return value indicates success, anything else is a failure - the plaintext is not trustworthy.
        if(EVP_DecryptFinal_ex(ctx, ciphertext + len, &len) <= 0)
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        ciphertext_len += len;

        input.Clear();
        input.Set(ciphertext, ciphertext_len);
    }
    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    if (encrypt)
    {
        ++m_FrameCounter;
    }
    if (encrypt && type == DLMS_COUNT_TYPE_PACKET)
    {
        CGXByteBuffer bb;
        bb.SetUInt8(tag);
        if (tag == DLMS_COMMAND_GENERAL_GLO_CIPHERING ||
            tag == DLMS_COMMAND_GENERAL_DED_CIPHERING)
        {
            GXHelpers::SetObjectCount(8, bb);
            bb.Set(systemTitle.GetData(), 8);
        }
        GXHelpers::SetObjectCount(5 + input.GetSize(), bb);
        bb.SetUInt8(security | suite);
        bb.SetUInt32(frameCounter);
        bb.Set(input.GetData(), input.GetSize());
        input = bb;
    }
    return 0;
}

int CGXCipher::Decrypt(
    CGXByteBuffer& title,
    CGXByteBuffer& key,
    CGXByteBuffer& data,
    DLMS_SECURITY& security,
    DLMS_SECURITY_SUITE& suite,
    uint64_t& InvocationCounter)
{
    unsigned long length;
    int ret;
    unsigned char ch;
    unsigned long frameCounter;
    DLMS_COMMAND cmd;
    CGXByteBuffer* pTitle = &title;
    CGXByteBuffer systemTitle, countTag;
    if (data.GetSize() - data.GetPosition() < 2)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    cmd = (DLMS_COMMAND)ch;
    switch (cmd)
    {
    case DLMS_COMMAND_GENERAL_GLO_CIPHERING:
    case DLMS_COMMAND_GENERAL_DED_CIPHERING:
        if ((ret = GXHelpers::GetObjectCount(data, length)) != 0)
        {
            return ret;
        }
        if (length != 0)
        {
            systemTitle.Set(&data, data.m_Position, length);
            pTitle = &systemTitle;
        }
        break;
    case DLMS_COMMAND_GLO_INITIATE_REQUEST:
    case DLMS_COMMAND_GLO_INITIATE_RESPONSE:
    case DLMS_COMMAND_GLO_READ_REQUEST:
    case DLMS_COMMAND_GLO_READ_RESPONSE:
    case DLMS_COMMAND_GLO_WRITE_REQUEST:
    case DLMS_COMMAND_GLO_WRITE_RESPONSE:
    case DLMS_COMMAND_GLO_GET_REQUEST:
    case DLMS_COMMAND_GLO_GET_RESPONSE:
    case DLMS_COMMAND_GLO_SET_REQUEST:
    case DLMS_COMMAND_GLO_SET_RESPONSE:
    case DLMS_COMMAND_GLO_METHOD_REQUEST:
    case DLMS_COMMAND_GLO_METHOD_RESPONSE:
    case DLMS_COMMAND_GLO_EVENT_NOTIFICATION_REQUEST:
    case DLMS_COMMAND_DED_GET_REQUEST:
    case DLMS_COMMAND_DED_GET_RESPONSE:
    case DLMS_COMMAND_DED_SET_REQUEST:
    case DLMS_COMMAND_DED_SET_RESPONSE:
    case DLMS_COMMAND_DED_METHOD_REQUEST:
    case DLMS_COMMAND_DED_METHOD_RESPONSE:
    case DLMS_COMMAND_DED_EVENT_NOTIFICATION:
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if ((ret = GXHelpers::GetObjectCount(data, length)) != 0)
    {
        return ret;
    }
    if (data.Available() < length)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    security = (DLMS_SECURITY)(ch & 0x30);
    suite = (DLMS_SECURITY_SUITE)(ch & 0x3);
    if ((ret = data.GetUInt32(&frameCounter)) != 0)
    {
        return ret;
    }
    InvocationCounter = frameCounter;
    return Encrypt(
        suite,
        security,
        DLMS_COUNT_TYPE_DATA,
        frameCounter,
        0,
        *pTitle,
        key,
        data,
        false);
}


int CGXCipher::Aes1Encrypt(
    CGXByteBuffer& buff,
    unsigned short offset,
    CGXByteBuffer& secret)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    unsigned char ciphertext[16];

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, secret.m_Data, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, buff.m_Data + offset, 16)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    if (ciphertext_len == 16) {
        memcpy(buff.m_Data + offset, ciphertext, 16);
        return 0;
    }

    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXCipher::Aes1Decrypt(
    CGXByteBuffer& buff,
    CGXByteBuffer& secret)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    unsigned char plaintext[16];

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, secret.m_Data, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, buff.m_Data, 16)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    if (plaintext_len == 16) {
        memcpy(buff.m_Data, plaintext, 16);
        return 0;
    }

    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

bool CGXCipher::IsCiphered()
{
    return m_Security != DLMS_SECURITY_NONE;
}

DLMS_SECURITY CGXCipher::GetSecurity()
{
    return m_Security;
}

void CGXCipher::SetSecurity(DLMS_SECURITY value)
{
    m_Security = value;
}

/**
    * @return Used security suite.
    */
DLMS_SECURITY_SUITE CGXCipher::GetSecuritySuite()
{
    return m_SecuritySuite;
}

/**
 * @param value
 *            Used security suite.
 */
void CGXCipher::SetSecuritySuite(DLMS_SECURITY_SUITE value)
{
    m_SecuritySuite = value;
}

CGXByteBuffer& CGXCipher::GetSystemTitle()
{
    return m_SystemTitle;
}

int CGXCipher::SetSystemTitle(CGXByteBuffer& value)
{
    if (value.GetSize() != 8)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    m_SystemTitle.Clear();
    m_SystemTitle.Set(value.m_Data, value.m_Size - value.m_Position);
    return 0;
}

CGXByteBuffer& CGXCipher::GetBlockCipherKey()
{
    return m_BlockCipherKey;
}

int CGXCipher::SetBlockCipherKey(CGXByteBuffer& value)
{
    if ((m_SecuritySuite == DLMS_SECURITY_SUITE_V2 && value.GetSize() != 32) ||
        ((m_SecuritySuite == DLMS_SECURITY_SUITE_V0 ||
            m_SecuritySuite == DLMS_SECURITY_SUITE_V1) && value.GetSize() != 16))
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    m_BlockCipherKey.Clear();
    m_BlockCipherKey.Set(value.m_Data, value.m_Size - value.m_Position);
    return 0;
}

CGXByteBuffer& CGXCipher::GetAuthenticationKey()
{
    return m_AuthenticationKey;
}

int CGXCipher::SetAuthenticationKey(CGXByteBuffer& value)
{
    if ((m_SecuritySuite == DLMS_SECURITY_SUITE_V2 && value.GetSize() != 32) ||
        ((m_SecuritySuite == DLMS_SECURITY_SUITE_V0 ||
            m_SecuritySuite == DLMS_SECURITY_SUITE_V1) && value.GetSize() != 16))
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    m_AuthenticationKey.Clear();
    m_AuthenticationKey.Set(value.m_Data, value.m_Size - value.m_Position);
    return 0;
}

unsigned long CGXCipher::GetFrameCounter()
{
    return m_FrameCounter;
}

void CGXCipher::SetFrameCounter(unsigned long value)
{
    m_FrameCounter = value;
}

unsigned long CGXCipher::GetInvocationCounter()
{
    return m_FrameCounter;
}

void CGXCipher::SetInvocationCounter(unsigned long value)
{
    m_FrameCounter = value;
}

void CGXCipher::Reset()
{

}

CGXByteBuffer& CGXCipher::GetDedicatedKey()
{
    return m_DedicatedKey;
}

void CGXCipher::SetDedicatedKey(CGXByteBuffer& value)
{
    m_DedicatedKey = value;
}

std::pair<CGXPublicKey, CGXPrivateKey>& CGXCipher::GetKeyAgreementKeyPair()
{
    return m_KeyAgreementKeyPair;
}

void CGXCipher::SetKeyAgreementKeyPair(
    std::pair<CGXPublicKey, CGXPrivateKey>& value)
{
    m_KeyAgreementKeyPair = value;
}


std::pair<CGXPublicKey, CGXPrivateKey>& CGXCipher::GetSigningKeyPair()
{
    return m_SigningKeyPair;
}

void CGXCipher::SetSigningKeyPair(
    std::pair<CGXPublicKey, CGXPrivateKey>& value)
{
    m_SigningKeyPair = value;
}

std::vector<CGXx509Certificate>& CGXCipher::GetCertificates()
{
    return m_Certificates;
}

void CGXCipher::SetCertificates(
    std::vector<CGXx509Certificate>& value)
{
    m_Certificates = value;
}
