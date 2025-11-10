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
#include "../include/GXPublicKey.h"

CGXPublicKey::CGXPublicKey() : m_pkey(nullptr)
{
    m_Scheme = ECC_P256;
}

CGXPublicKey::CGXPublicKey(EVP_PKEY* pkey) : m_pkey(pkey)
{
    m_Scheme = ECC_P256;
}

CGXPublicKey::~CGXPublicKey()
{
    if (m_pkey)
    {
        EVP_PKEY_free(m_pkey);
    }
}

CGXPublicKey& CGXPublicKey::operator=(const CGXPublicKey& value)
{
    m_Scheme = value.m_Scheme;
    m_RawValue = value.m_RawValue;
    m_SystemTitle = value.m_SystemTitle;
    return *this;
}

ECC CGXPublicKey::GetScheme()
{
    return m_Scheme;
}

CGXByteArray& CGXPublicKey::GetRawValue()
{
    if (m_pkey != nullptr && m_RawValue.GetSize() == 0)
    {
        EC_KEY* ec_key = EVP_PKEY_get1_EC_KEY(m_pkey);
        if (ec_key != nullptr)
        {
            const EC_POINT* pub_key = EC_KEY_get0_public_key(ec_key);
            if (pub_key != nullptr)
            {
                BIGNUM* x = BN_new();
                BIGNUM* y = BN_new();
                if (EC_POINT_get_affine_coordinates_GFp(EC_KEY_get0_group(ec_key), pub_key, x, y, NULL))
                {
                    unsigned char buffer[256];
                    int len = BN_bn2bin(x, buffer);
                    CGXByteArray new_raw_value;
                    new_raw_value.Set(buffer, len);
                    int x_len = len;
                    len = BN_bn2bin(y, buffer);
                    unsigned char* tmp = new unsigned char[x_len + len];
                    memcpy(tmp, new_raw_value.GetData(), x_len);
                    memcpy(tmp + x_len, buffer, len);
                    m_RawValue.Set(tmp, x_len + len);
                    delete[] tmp;
                }
                BN_free(x);
                BN_free(y);
            }
            EC_KEY_free(ec_key);
        }
    }
    return m_RawValue;
}

CGXByteArray& CGXPublicKey::GetSystemTitle()
{
    return m_SystemTitle;
}

void CGXPublicKey::SetSystemTitle(CGXByteBuffer& value)
{
    m_SystemTitle = value;
}

int CGXPublicKey::FromRawBytes(CGXByteBuffer& key,
    CGXPublicKey& value)
{
    if (key.GetSize() == 65)
    {
        value.m_Scheme = ECC_P256;
        value.m_RawValue = key;
    }
    else if (key.GetSize() == 97)
    {
        value.m_Scheme = ECC_P384;
        value.m_RawValue = key;
    }
    else if (key.GetSize() == 64)
    {
        //Compression tag is not send in DLMS messages.
        value.m_Scheme = ECC_P256;
        value.m_RawValue.SetUInt8(4);
        value.m_RawValue.Set(&key);
    }
    else if (key.GetSize() == 96)
    {
        //Compression tag is not send in DLMS messages.
        value.m_Scheme = ECC_P384;
        value.m_RawValue.SetUInt8(4);
        value.m_RawValue.Set(&key);
    }
    else
    {
        //Invalid key.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

int CGXPublicKey::FromDer(std::string der,
    CGXPublicKey& key)
{
    CGXByteBuffer bb;
    bb.FromBase64(der);
    const unsigned char* p = bb.GetData();
    EVP_PKEY* pkey = d2i_PUBKEY(NULL, &p, bb.GetSize());
    if (pkey == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    key.m_pkey = pkey;
    return 0;
}

int CGXPublicKey::FromPem(
    std::string pem,
    CGXPublicKey& key)
{
    BIO* bio = BIO_new_mem_buf((void*)pem.c_str(), -1);
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (pkey == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    key.m_pkey = pkey;
    return 0;
}

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)

int CGXPublicKey::Load(std::string& path,
    CGXPublicKey& value)
{
    std::string text;
    int ret = GXHelpers::Load(path, text);
    if (ret != 0)
    {
        return ret;
    }
    return FromPem(text, value);
}

int CGXPublicKey::Save(std::string& path)
{
    std::string text;
    int ret = ToPem(text);
    if (ret != 0)
    {
        return ret;
    }
    return GXHelpers::Save(path, text);
    return 0;
}
#endif //defined(_WIN32) || defined(_WIN64) || defined(__linux__)

std::string CGXPublicKey::ToHex()
{
    return m_RawValue.ToHexString();
}

int CGXPublicKey::ToDer(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = i2d_PUBKEY_bio(bio, m_pkey);
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

int CGXPublicKey::GetEncoded(
    CGXByteBuffer& value)
{
    //Subject Key Info.
    CGXAsn1Sequence d;
    CGXAsn1Sequence* d1 = new CGXAsn1Sequence();
    d1->GetValues()->push_back(new CGXAsn1ObjectIdentifier("1.2.840.10045.2.1"));
    if (m_Scheme == ECC_P256)
    {
        d1->GetValues()->push_back(new CGXAsn1ObjectIdentifier("1.2.840.10045.3.1.7"));
    }
    else if (m_Scheme == ECC_P384)
    {
        d1->GetValues()->push_back(new CGXAsn1ObjectIdentifier("1.3.132.0.34"));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    d.GetValues()->push_back(d1);
    d.GetValues()->push_back(new CGXAsn1BitString(m_RawValue, 0));
    return CGXAsn1Converter::ToByteArray(&d, value);
}

int CGXPublicKey::ToPem(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = PEM_write_bio_PUBKEY(bio, m_pkey);
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

CGXByteArray CGXPublicKey::GetX()
{
    CGXByteArray bb;
    GetRawValue();
    int size = m_RawValue.GetSize() / 2;
    m_RawValue.SubArray(0, size, bb);
    return bb;
}

CGXByteArray CGXPublicKey::GetY()
{
    CGXByteArray bb;
    GetRawValue();
    int size = m_RawValue.GetSize() / 2;
    m_RawValue.SubArray(size, size, bb);
    return bb;
}

std::string CGXPublicKey::ToString()
{
    std::string sb;
    if (m_Scheme == ECC_P256)
    {
        sb += "NIST P-256\n";
    }
    else if (m_Scheme == ECC_P384)
    {
        sb += "NIST P-384\n";
    }
    CGXByteBuffer pk;
    int size = m_RawValue.GetSize() / 2;
    sb += " x coord: ";
    m_RawValue.SubArray(1, size, pk);
    sb += CGXBigInteger(pk).ToString();
    sb += " y coord: ";
    pk.SetSize(0);
    m_RawValue.SubArray(1 + size, size, pk);
    sb += CGXBigInteger(pk).ToString();
    return sb;
}