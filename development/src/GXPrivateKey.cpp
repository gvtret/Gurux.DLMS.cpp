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

#include <openssl/evp.h>
#include <openssl/pem.h>
#include "../include/GXPrivateKey.h"
#include "../include/GXCurve.h"
#include "../include/GXEcdsa.h"
#include "../include/GXShamirs.h"

CGXPrivateKey::CGXPrivateKey() : m_pkey(nullptr)
{
    m_Scheme = ECC_P256;
}

CGXPrivateKey::CGXPrivateKey(EVP_PKEY* pkey) : m_pkey(pkey)
{
    m_Scheme = ECC_P256;
}

CGXPrivateKey::~CGXPrivateKey()
{
    if (m_pkey)
    {
        EVP_PKEY_free(m_pkey);
    }
}

CGXPrivateKey& CGXPrivateKey::operator=(const CGXPrivateKey& value)
{
    m_Scheme = value.m_Scheme;
    m_RawValue = value.m_RawValue;
    m_PublicKey = value.m_PublicKey;
    return *this;
}

ECC CGXPrivateKey::GetScheme()
{
    return m_Scheme;
}

CGXByteArray& CGXPrivateKey::GetRawValue()
{
    if (m_pkey != nullptr && m_RawValue.GetSize() == 0)
    {
        EC_KEY* ec_key = EVP_PKEY_get1_EC_KEY(m_pkey);
        if (ec_key != nullptr)
        {
            const BIGNUM* priv_key = EC_KEY_get0_private_key(ec_key);
            if (priv_key != nullptr)
            {
                unsigned char buffer[256];
                int len = BN_bn2bin(priv_key, buffer);
                m_RawValue.Set(buffer, len);
            }
            EC_KEY_free(ec_key);
        }
    }
    return m_RawValue;
}

CGXByteArray& CGXPrivateKey::GetSystemTitle()
{
    return m_SystemTitle;
}

void CGXPrivateKey::SetSystemTitle(
    CGXByteBuffer& value)
{
    m_SystemTitle = value;
}

int CGXPrivateKey::FromRawBytes(
    CGXByteBuffer& value,
    CGXPrivateKey& key)
{
    //If private key is given
    if (value.GetSize() == 32)
    {
        key.m_Scheme = ECC_P256;
        key.m_RawValue = value;
    }
    else if (value.GetSize() == 48)
    {
        key.m_Scheme = ECC_P384;
        key.m_RawValue = value;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

int CGXPrivateKey::UpdateSchema(
    CGXAsn1Sequence* seq,
    CGXPrivateKey& key)
{
    int ret = 0;
    if (CGXAsn1Sequence* tmp = dynamic_cast<CGXAsn1Sequence*>(seq->GetValues()->at(2)))
    {
        DLMS_X9_OBJECT_IDENTIFIER id = CGXDLMSConverter::ValueOfX9Identifier(tmp->GetValues()->at(0)->ToString().c_str());
        switch (id)
        {
        case DLMS_X9_OBJECT_IDENTIFIER_PRIME_256_V1:
            key.m_Scheme = ECC_P256;
            break;
        case DLMS_X9_OBJECT_IDENTIFIER_SECP_384_R1:
            key.m_Scheme = ECC_P384;
            break;
        default:
#ifdef _DEBUG
            printf("Invalid private key.\n");
#endif //_DEBUG
            ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

int CGXPrivateKey::UpdatePublicKey(
    CGXAsn1Sequence* seq,
    CGXPrivateKey& key)
{
    int ret = 0;
    if (CGXAsn1Variant* tmp = dynamic_cast<CGXAsn1Variant*>(seq->GetValues()->at(1)))
    {
        key.m_RawValue.Clear();
        key.m_RawValue.Set(tmp->GetValue().byteArr, tmp->GetValue().size);
        if (CGXAsn1Variant* tmp = dynamic_cast<CGXAsn1Variant*>(seq->GetValues()->at(3)))
        {
            CGXByteBuffer bb;
            bb.Set(tmp->GetValue().byteArr, tmp->GetValue().size);
            ret = CGXPublicKey::FromRawBytes(bb, key.m_PublicKey);
        }
        else if (CGXAsn1BitString* tmp = dynamic_cast<CGXAsn1BitString*>(seq->GetValues()->at(3)))
        {
            ret = CGXPublicKey::FromRawBytes(tmp->GetValue(), key.m_PublicKey);
        }
        else if (CGXAsn1Context* tmp = dynamic_cast<CGXAsn1Context*>(seq->GetValues()->at(3)))
        {
            if (CGXAsn1BitString* bs = dynamic_cast<CGXAsn1BitString*>(tmp->GetValues()->at(0)))
            {
                ret = CGXPublicKey::FromRawBytes(bs->GetValue(), key.m_PublicKey);
            }
        }
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

int CGXPrivateKey::FromDer(
    std::string der,
    CGXPrivateKey& key)
{
    CGXByteBuffer bb;
    bb.FromBase64(der);
    const unsigned char* p = bb.GetData();
    EVP_PKEY* pkey = d2i_PrivateKey(EVP_PKEY_EC, NULL, &p, bb.GetSize());
    if (pkey == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    key.m_pkey = pkey;
    return 0;
}

int CGXPrivateKey::FromPem(std::string pem,
    CGXPrivateKey& value)
{
    BIO* bio = BIO_new_mem_buf((void*)pem.c_str(), -1);
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (pkey == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    value.m_pkey = pkey;
    return 0;
}

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)

int CGXPrivateKey::Load(std::string& path,
    CGXPrivateKey& value)
{
    std::string text;
    int ret = GXHelpers::Load(path, text);
    if (ret != 0)
    {
        return ret;
    }
    return FromPem(text, value);
}

int CGXPrivateKey::Save(std::string& path)
{
    std::string text;
    int ret = ToPem(text);
    if (ret != 0)
    {
        return ret;
    }
    return GXHelpers::Save(path, text);
}
#endif //defined(_WIN32) || defined(_WIN64) || defined(__linux__)

int CGXPrivateKey::ToDer(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = i2d_PrivateKey_bio(bio, m_pkey);
    if (ret != 1)
    {
        BIO_free(bio);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    BUF_MEM *buf;
    BIO_get_mem_ptr(bio, &buf);
    CGXByteBuffer bb;
    bb.Set(buf->data, buf->length);
    bb.ToBase64(value);
    BIO_free(bio);
    return 0;
}

int CGXPrivateKey::ToPem(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = PEM_write_bio_PrivateKey(bio, m_pkey, NULL, NULL, 0, NULL, NULL);
    if (ret != 1)
    {
        BIO_free(bio);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    BUF_MEM *buf;
    BIO_get_mem_ptr(bio, &buf);
    value.assign(buf->data, buf->length);
    BIO_free(bio);
    return 0;
}

int CGXPrivateKey::GetPublicKey(CGXPublicKey& value)
{
    if (m_pkey != nullptr && m_PublicKey.GetRawValue().GetSize() == 0)
    {
        EC_KEY* ec_key = EVP_PKEY_get1_EC_KEY(m_pkey);
        if (ec_key != nullptr)
        {
            const EC_POINT* pub_key_point = EC_KEY_get0_public_key(ec_key);
            if (pub_key_point != nullptr)
            {
                EVP_PKEY* pub_pkey = EVP_PKEY_new();
                EC_KEY* pub_ec_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
                EC_KEY_set_public_key(pub_ec_key, pub_key_point);
                EVP_PKEY_set1_EC_KEY(pub_pkey, pub_ec_key);
                m_PublicKey = CGXPublicKey(pub_pkey);
                EC_KEY_free(pub_ec_key);
            }
            EC_KEY_free(ec_key);
        }
    }
    value = m_PublicKey;
    return 0;
}

std::string CGXPrivateKey::ToHex()
{
    return ToHex(true);
}

std::string CGXPrivateKey::ToHex(bool addSpace)
{
    return m_RawValue.ToHexString(addSpace);
}

std::string CGXPrivateKey::ToString()
{
    return ToHex(true);
}