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

#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509v3.h>
#include "../include/GXx509Certificate.h"
#include "../include/GXEcdsa.h"

CGXx509Certificate::CGXx509Certificate() : m_x509(nullptr)
{
    m_BasicConstraints = false;
    m_Version = DLMS_CERTIFICATE_VERSION_3;
    m_SignatureAlgorithm = DLMS_HASH_ALGORITHM_NONE;
    m_PublicKeyAlgorithm = DLMS_HASH_ALGORITHM_NONE;
    m_KeyUsage = DLMS_KEY_USAGE_NONE;
    m_ExtendedKeyUsage = DLMS_EXTENDED_KEY_USAGE_NONE;
}

CGXx509Certificate::~CGXx509Certificate()
{
    if (m_x509)
    {
        X509_free(m_x509);
    }
}

int CGXx509Certificate::GetFilePath(
    CGXx509Certificate& cert,
    std::string& path)
{
    if ((cert.m_KeyUsage & (DLMS_KEY_USAGE_DIGITAL_SIGNATURE | DLMS_KEY_USAGE_KEY_AGREEMENT)) == (DLMS_KEY_USAGE_DIGITAL_SIGNATURE | DLMS_KEY_USAGE_KEY_AGREEMENT))
    {
        path = "T";
    }
    else if ((cert.m_KeyUsage & DLMS_KEY_USAGE_DIGITAL_SIGNATURE) != 0)
    {
        path = "D";
    }
    else if ((cert.m_KeyUsage & DLMS_KEY_USAGE_KEY_AGREEMENT) != 0)
    {
        path = "A";
    }
    else
    {
        printf("Unknown certificate type.");
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    std::string tmp;
    CGXAsn1Converter::HexSystemTitleFromSubject(cert.GetSubject(), tmp);
    path += tmp;
    path += ".pem";
    CGXByteBuffer bb;
    cert.m_PublicKey.GetEncoded(bb);
    if (bb.GetSize() < 100)
    {
        path = "Certificates/" + path;
    }
    else
    {
        path = "Certificates384/" + path;
    }
    return 0;
}

int CGXx509Certificate::GetFilePath(
    ECC ecc,
    DLMS_KEY_USAGE usage,
    std::string& systemTitle,
    std::string& path)
{
    if ((usage & (DLMS_KEY_USAGE_DIGITAL_SIGNATURE | DLMS_KEY_USAGE_KEY_AGREEMENT)) ==
        (DLMS_KEY_USAGE_DIGITAL_SIGNATURE | DLMS_KEY_USAGE_KEY_AGREEMENT))
    {
        path = "T";
    }
    else if ((usage & DLMS_KEY_USAGE_DIGITAL_SIGNATURE) != 0)
    {
        path = "D";
    }
    else if ((usage & DLMS_KEY_USAGE_KEY_AGREEMENT) != 0)
    {
        path = "A";
    }
    else
    {
        printf("Unknown certificate type.");
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    path += systemTitle;
    path += ".pem";
    if (ecc == ECC_P256)
    {
        path = "Certificates/" + path;
    }
    else if (ecc == ECC_P384)
    {
        path = "Certificates384/" + path;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

int CGXx509Certificate::FromHexString(
    std::string& data,
    CGXx509Certificate& cert)
{
    CGXByteBuffer bb;
    GXHelpers::HexToBytes(data, bb);
    cert.Init(bb);
    return 0;
}

int CGXx509Certificate::FromPem(
    std::string data,
    CGXx509Certificate& cert)
{
    BIO* bio = BIO_new_mem_buf((void*)data.c_str(), -1);
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    X509* x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (x509 == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    cert.m_x509 = x509;
    return 0;
}

int CGXx509Certificate::FromDer(
    std::string& data,
    CGXx509Certificate& cert)
{
    CGXByteBuffer bb;
    bb.FromBase64(data);
    const unsigned char* p = bb.GetData();
    X509* x509 = d2i_X509(NULL, &p, bb.GetSize());
    if (x509 == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    cert.m_x509 = x509;
    return 0;
}

int CGXx509Certificate::FromByteArray(
    CGXByteBuffer& data,
    CGXx509Certificate& cert)
{
    return cert.Init(data);
}

int CGXx509Certificate::FromByteArray(
    const unsigned char* data,
    uint16_t length,
    CGXx509Certificate& cert)
{
    CGXByteBuffer bb;
    bb.Set(data, length);
    return cert.Init(bb);
}

int CGXx509Certificate::GetAlgorithm(
    std::string& algorithm,
    std::string& value)
{
    if (GXHelpers::EndsWith(algorithm, "RSA"))
    {
        value = "RSA";
    }
    else if (GXHelpers::EndsWith(algorithm, "ECDSA"))
    {
        value = "EC";
    }
    else
    {
        printf("Unknown algorithm: %s", algorithm.c_str());
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}


int CGXx509Certificate::GetCertificateInfo()
{
    // A.2.1 Version
    m_Version = (DLMS_CERTIFICATE_VERSION)X509_get_version(m_x509);

    // A.2.2 Serial number
    ASN1_INTEGER* serial = X509_get_serialNumber(m_x509);
    BIGNUM* bn = ASN1_INTEGER_to_BN(serial, NULL);
    char* hex = BN_bn2hex(bn);
    m_SerialNumber = CGXBigInteger((unsigned char*)hex, strlen(hex));
    BN_free(bn);
    OPENSSL_free(hex);

    // A.2.3 Signature
    const X509_ALGOR* sig_alg = X509_get0_tbs_sigalg(m_x509);
    char buf[128];
    OBJ_obj2txt(buf, sizeof(buf), sig_alg->algorithm, 0);
    m_SignatureAlgorithm = CGXDLMSConverter::ValueOfHashAlgorithm(buf);

    // A.2.4 Issuer
    X509_NAME* issuer = X509_get_issuer_name(m_x509);
    m_Issuer = X509_NAME_oneline(issuer, NULL, 0);

    // A.2.5 Validity
    ASN1_TIME* not_before = X509_get_notBefore(m_x509);
    GXHelpers::ASN1_TIME_to_tm(not_before, &m_ValidFrom);
    ASN1_TIME* not_after = X509_get_notAfter(m_x509);
    GXHelpers::ASN1_TIME_to_tm(not_after, &m_ValidTo);

    // A.2.6 Subject
    X509_NAME* subject = X509_get_subject_name(m_x509);
    m_Subject = X509_NAME_oneline(subject, NULL, 0);

    // A.2.7 Subject public key info
    EVP_PKEY* pkey = X509_get_pubkey(m_x509);
    m_PublicKey = CGXPublicKey(pkey);
    m_PublicKeyAlgorithm = (DLMS_HASH_ALGORITHM)EVP_PKEY_id(pkey);

    // A.2.8 Standard extensions
    ASN1_BIT_STRING* key_usage = (ASN1_BIT_STRING*)X509_get_ext_d2i(m_x509, NID_key_usage, NULL, NULL);
    if (key_usage)
    {
        m_KeyUsage = (DLMS_KEY_USAGE)key_usage->data[0];
        ASN1_BIT_STRING_free(key_usage);
    }

    EXTENDED_KEY_USAGE* ext_key_usage = (EXTENDED_KEY_USAGE*)X509_get_ext_d2i(m_x509, NID_ext_key_usage, NULL, NULL);
    if (ext_key_usage)
    {
        for (int i = 0; i < sk_ASN1_OBJECT_num(ext_key_usage); i++)
        {
            ASN1_OBJECT* obj = sk_ASN1_OBJECT_value(ext_key_usage, i);
            int nid = OBJ_obj2nid(obj);
            if (nid == NID_server_auth)
            {
                m_ExtendedKeyUsage = (DLMS_EXTENDED_KEY_USAGE)(m_ExtendedKeyUsage | DLMS_EXTENDED_KEY_USAGE_SERVER_AUTH);
            }
            else if (nid == NID_client_auth)
            {
                m_ExtendedKeyUsage = (DLMS_EXTENDED_KEY_USAGE)(m_ExtendedKeyUsage | DLMS_EXTENDED_KEY_USAGE_CLIENT_AUTH);
            }
        }
        EXTENDED_KEY_USAGE_free(ext_key_usage);
    }

    BASIC_CONSTRAINTS* bc = (BASIC_CONSTRAINTS*)X509_get_ext_d2i(m_x509, NID_basic_constraints, NULL, NULL);
    if (bc)
    {
        m_BasicConstraints = bc->ca != 0;
        BASIC_CONSTRAINTS_free(bc);
    }

    ASN1_OCTET_STRING* subj_key_id = (ASN1_OCTET_STRING*)X509_get_ext_d2i(m_x509, NID_subject_key_identifier, NULL, NULL);
    if (subj_key_id)
    {
        m_SubjectKeyIdentifier.Set(subj_key_id->data, subj_key_id->length);
        ASN1_OCTET_STRING_free(subj_key_id);
    }

    AUTHORITY_KEYID* auth_key_id = (AUTHORITY_KEYID*)X509_get_ext_d2i(m_x509, NID_authority_key_identifier, NULL, NULL);
    if (auth_key_id)
    {
        if (auth_key_id->keyid)
        {
            m_AuthorityKeyIdentifier.Set(auth_key_id->keyid->data, auth_key_id->keyid->length);
        }
        AUTHORITY_KEYID_free(auth_key_id);
    }

    return 0;
}

int CGXx509Certificate::Init(CGXByteBuffer& data)
{
    m_RawData = data;
    const unsigned char* p = data.GetData();
    m_x509 = d2i_X509(NULL, &p, data.GetSize());
    if (m_x509 == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return GetCertificateInfo();
}

std::string& CGXx509Certificate::GetSubject()
{
    return m_Subject;
}

void CGXx509Certificate::SetSubject(std::string& value)
{
    m_Subject = value;
}

std::string& CGXx509Certificate::GetIssuer()
{
    return m_Issuer;
}

void CGXx509Certificate::SetIssuer(std::string& value)
{
    m_Issuer = value;
}

CGXBigInteger& CGXx509Certificate::GetSerialNumber()
{
    return m_SerialNumber;
}

void CGXx509Certificate::SetSerialNumber(CGXBigInteger& value)
{
    m_SerialNumber = value;
}

DLMS_CERTIFICATE_VERSION CGXx509Certificate::GetVersion()
{
    return m_Version;
}

void CGXx509Certificate::SetVersion(DLMS_CERTIFICATE_VERSION value)
{
    m_Version = value;
}

struct tm& CGXx509Certificate::GetValidFrom()
{
    return m_ValidFrom;
}

void CGXx509Certificate::SetValidFrom(struct tm& value)
{
    m_ValidFrom = value;
}

struct tm& CGXx509Certificate::GetValidTo()
{
    return m_ValidTo;
}

void CGXx509Certificate::SetValidTo(struct tm& value)
{
    m_ValidTo = value;
}

DLMS_HASH_ALGORITHM CGXx509Certificate::GetSignatureAlgorithm()
{
    return m_SignatureAlgorithm;
}

void CGXx509Certificate::SetSignatureAlgorithm(DLMS_HASH_ALGORITHM value)
{
    m_SignatureAlgorithm = value;
}

CGXAsn1Base& CGXx509Certificate::GetParameters()
{
    return m_Parameters;
}

CGXPublicKey& CGXx509Certificate::GetPublicKey()
{
    return m_PublicKey;
}

void CGXx509Certificate::SetPublicKey(CGXPublicKey& value)
{
    m_PublicKey = value;
}

CGXByteBuffer& CGXx509Certificate::GetSignature()
{
    return m_Signature;
}

void CGXx509Certificate::SetSignature(CGXByteBuffer& value)
{
    m_Signature = value;
}

/**
 * Returns Encoded x509 certificate.
 */
int CGXx509Certificate::GetEncoded(
    CGXByteBuffer& value)
{
    if (m_RawData.GetSize() != 0)
    {
        value = m_RawData;
        return 0;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

std::string CGXx509Certificate::ToString()
{
    int ret;
    char buff[50];
    std::string bb;
    bb += "Version: ";
    bb += (int)m_Version;
    bb += "\n";
    bb += "Serial Number: ";
    bb += m_SerialNumber.ToString();
    bb += "\n";
    bb += "Signature Algorithm: ";
    bb += CGXDLMSConverter::ToString(m_SignatureAlgorithm);
    bb += ", OID = ";
    bb += CGXDLMSConverter::ToString(m_SignatureAlgorithm);
    bb += "\n";
    bb += "Issuer: ";
    bb += m_Issuer;
    bb += "\n";
    bb += "Validity: [From: ";
    ret = (int)strftime(buff, 50, "%x %X", &m_ValidFrom);
    bb.append(buff, ret);
    bb += ", \n";
    bb += "To: ";
    ret = (int)strftime(buff, 50, "%x %X", &m_ValidTo);
    bb.append(buff, ret);
    bb += "]\n";
    bb += "Subject Public Key Info:\n";
    bb += "Public Key Algorythm: ";
    bb += CGXDLMSConverter::ToString(m_PublicKeyAlgorithm);
    bb += "\n";
    bb += m_PublicKey.ToString();
    bb += "\n";
    if (m_SubjectKeyIdentifier.GetSize() != 0)
    {
        bb += "X509v3 Subject Key Identifier:\n";
        bb += m_SubjectKeyIdentifier.ToHexString();
        bb += "\n";
    }
    if (m_AuthorityKeyIdentifier.GetSize() != 0)
    {
        bb += "X509v3 Authority Key Identifier:\n";
        bb += m_AuthorityKeyIdentifier.ToHexString();
        bb += "\n";
    }
    bb += "Signature Algorithm: ";
    bb += CGXDLMSConverter::ToString(m_SignatureAlgorithm);
    bb += "\n";
    bb += m_Signature.ToHexString();
    bb += "\n";
    return bb;
}

DLMS_KEY_USAGE CGXx509Certificate::GetKeyUsage()
{
    return m_KeyUsage;
}

void CGXx509Certificate::SetKeyUsage(DLMS_KEY_USAGE value)
{
    m_KeyUsage = value;
}

DLMS_EXTENDED_KEY_USAGE CGXx509Certificate::GetExtendedKeyUsage()
{
    return m_ExtendedKeyUsage;
}

void CGXx509Certificate::SetExtendedKeyUsage(DLMS_EXTENDED_KEY_USAGE value) {
    m_ExtendedKeyUsage = value;
}

CGXByteBuffer& CGXx509Certificate::GetSubjectKeyIdentifier()
{
    return m_SubjectKeyIdentifier;
}

void CGXx509Certificate::SetSubjectKeyIdentifier(CGXByteBuffer& value)
{
    m_SubjectKeyIdentifier = value;
}

CGXByteBuffer& CGXx509Certificate::GetAuthorityKeyIdentifier()
{
    return m_AuthorityKeyIdentifier;
}

void CGXx509Certificate::SetAuthorityKeyIdentifier(CGXByteBuffer& value)
{
    m_AuthorityKeyIdentifier = value;
}

bool CGXx509Certificate::IsBasicConstraints()
{
    return m_BasicConstraints;
}

void CGXx509Certificate::SetBasicConstraints(bool value)
{
    m_BasicConstraints = value;
}

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)

int CGXx509Certificate::Load(
    std::string& path,
    CGXx509Certificate& cert)
{
    std::string text;
    int ret = GXHelpers::Load(path, text);
    if (ret != 0)
    {
        return ret;
    }
    return FromPem(text, cert);
}

int CGXx509Certificate::Save(std::string& path)
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

int CGXx509Certificate::ToPem(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = PEM_write_bio_X509(bio, m_x509);
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

int CGXx509Certificate::ToDer(std::string& value)
{
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret = i2d_X509_bio(bio, m_x509);
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

CGXByteBuffer& CGXx509Certificate::GetIssuerRaw()
{
    return m_IssuerRaw;
}

bool CGXx509Certificate::Equals(CGXx509Certificate& cert)
{
    return m_SerialNumber.Compare(cert.m_SerialNumber) == 0;
}

int CGXx509Certificate::GetSystemTitle(CGXByteBuffer& value)
{
    value.Clear();
    if (m_Subject.empty())
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    std::string tmp;
    int ret = CGXAsn1Converter::HexSystemTitleFromSubject(m_Subject, tmp);
    if (ret == 0)
    {
        GXHelpers::HexToBytes(tmp, value);
        if (value.GetSize() != 8)
        {
            ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    return ret;
}