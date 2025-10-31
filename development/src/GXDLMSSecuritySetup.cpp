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

#include <memory>
#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSSecuritySetup.h"
#include "../include/GXDLMSConverter.h"
#include "../include/GXDLMSSecureClient.h"

#ifndef DLMS_IGNORE_SECURITY_SETUP

//Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup() :
    CGXDLMSSecuritySetup("0.0.43.0.0.255", 0)
{
}

//SN Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_SECURITY_SETUP, ln, sn)
{
    m_Version = 1;
}

CGXDLMSSecuritySetup::CGXDLMSSecuritySetup(const CGXDLMSSecuritySetup& other) :
    CGXDLMSObject(other),
    m_SecurityPolicy(other.m_SecurityPolicy),
    m_SecuritySuite(other.m_SecuritySuite),
    m_ServerSystemTitle(other.m_ServerSystemTitle),
    m_ClientSystemTitle(other.m_ClientSystemTitle)
{
    for (const auto& cert : other.m_Certificates)
    {
        m_Certificates.emplace_back(std::unique_ptr<CGXDLMSCertificateInfo>(new CGXDLMSCertificateInfo(*cert)));
    }
}

CGXDLMSSecuritySetup& CGXDLMSSecuritySetup::operator=(const CGXDLMSSecuritySetup& other)
{
    if (this != &other)
    {
        CGXDLMSObject::operator=(other);
        m_SecurityPolicy = other.m_SecurityPolicy;
        m_SecuritySuite = other.m_SecuritySuite;
        m_ServerSystemTitle = other.m_ServerSystemTitle;
        m_ClientSystemTitle = other.m_ClientSystemTitle;
        m_Certificates.clear();
        for (const auto& cert : other.m_Certificates)
        {
            m_Certificates.emplace_back(std::unique_ptr<CGXDLMSCertificateInfo>(new CGXDLMSCertificateInfo(*cert)));
        }
    }
    return *this;
}

//LN Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup(std::string ln): CGXDLMSSecuritySetup(ln, 0) {
}

DLMS_SECURITY_POLICY CGXDLMSSecuritySetup::GetSecurityPolicy() const
{
    return m_SecurityPolicy;
}

void CGXDLMSSecuritySetup::SetSecurityPolicy(DLMS_SECURITY_POLICY value)
{
    m_SecurityPolicy = value;
}

DLMS_SECURITY_SUITE CGXDLMSSecuritySetup::GetSecuritySuite() const
{
    return m_SecuritySuite;
}

void CGXDLMSSecuritySetup::SetSecuritySuite(DLMS_SECURITY_SUITE value)
{
    m_SecuritySuite = value;
}

const CGXByteBuffer& CGXDLMSSecuritySetup::GetClientSystemTitle() const
{
    return m_ClientSystemTitle;
}

void CGXDLMSSecuritySetup::SetClientSystemTitle(const CGXByteBuffer& value)
{
    m_ClientSystemTitle = value;
}

const CGXByteBuffer& CGXDLMSSecuritySetup::GetServerSystemTitle() const
{
    return m_ServerSystemTitle;
}

void CGXDLMSSecuritySetup::SetServerSystemTitle(const CGXByteBuffer& value)
{
    m_ServerSystemTitle = value;
}

// Returns amount of attributes.
int CGXDLMSSecuritySetup::GetAttributeCount() {
    if (GetVersion() == 0) {
        return 5;
    }
    return 6;
}

// Returns amount of methods.
int CGXDLMSSecuritySetup::GetMethodCount() {
    if (GetVersion() == 0) {
        return 2;
    }
    return 8;
}

int CGXDLMSSecuritySetup::Activate(CGXDLMSClient *client, DLMS_SECURITY security, std::vector<CGXByteBuffer> &reply) {
    CGXDLMSVariant data((char)security);
    return client->Method(this, 1, data, reply);
}

int CGXDLMSSecuritySetup::GlobalKeyTransfer(
    CGXDLMSClient *client, CGXByteBuffer &kek, std::vector<std::pair<DLMS_GLOBAL_KEY_TYPE, CGXByteBuffer &>> &list,
    std::vector<CGXByteBuffer> &reply
) {
    int ret = 0;
    CGXDLMSVariant data;
    CGXByteBuffer bb, tmp;
    if (list.size() == 0) {
        //Invalid list. It is empty.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    bb.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    bb.SetUInt8((unsigned char)list.size());
    for (std::vector<std::pair<DLMS_GLOBAL_KEY_TYPE, CGXByteBuffer &>>::iterator it = list.begin(); it != list.end();
         ++it) {
        bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        bb.SetUInt8(2);
        data = (char)it->first;
        if ((ret = GXHelpers::SetData(NULL, bb, DLMS_DATA_TYPE_ENUM, data)) != 0 ||
            (ret = CGXDLMSSecureClient::Encrypt(kek, it->second, tmp)) != 0) {
            break;
        }
        data = tmp;
        if ((ret = GXHelpers::SetData(NULL, bb, DLMS_DATA_TYPE_OCTET_STRING, data)) != 0) {
            break;
        }
    }
    if (ret == 0) {
        data = bb;
        ret = client->Method(this, 2, data, DLMS_DATA_TYPE_ARRAY, reply);
    }
    return ret;
}

/*
* Agree on one or more symmetric keys using the key agreement algorithm.
* client: DLMS client that is used to generate action.
* list: List of keys.
* Returns Generated action
*/
int CGXDLMSSecuritySetup::KeyAgreement(
    CGXDLMSSecureClient *client, std::vector<std::pair<DLMS_GLOBAL_KEY_TYPE, CGXByteBuffer>> list,
    std::vector<CGXByteBuffer> &reply
) {
    if (list.size() == 0) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    CGXByteBuffer bb;
    bb.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    bb.SetUInt8((unsigned char)list.size());
    for (std::vector<std::pair<DLMS_GLOBAL_KEY_TYPE, CGXByteBuffer>>::iterator it = list.begin(); it != list.end();
         ++it) {
        bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        bb.SetUInt8(2);
        CGXDLMSVariant data = it->first;
        GXHelpers::SetData(NULL, bb, DLMS_DATA_TYPE_ENUM, data);
        data = it->second;
        GXHelpers::SetData(NULL, bb, DLMS_DATA_TYPE_OCTET_STRING, data);
    }
    CGXDLMSVariant data = bb;
    return client->Method(this, 3, data, DLMS_DATA_TYPE_ARRAY, reply);
}

int CGXDLMSSecuritySetup::GenerateKeyPair(
    CGXDLMSSecureClient *client, DLMS_CERTIFICATE_TYPE type, std::vector<CGXByteBuffer> &reply
) {
    CGXDLMSVariant data = type;
    return client->Method(this, 4, data, DLMS_DATA_TYPE_ENUM, reply);
}

int CGXDLMSSecuritySetup::GenerateCertificate(
    CGXDLMSSecureClient *client, DLMS_CERTIFICATE_TYPE type, std::vector<CGXByteBuffer> &reply
) {
    CGXDLMSVariant data = type;
    return client->Method(this, 5, data, DLMS_DATA_TYPE_ENUM, reply);
}

int CGXDLMSSecuritySetup::ImportCertificate(
    CGXDLMSClient *client, CGXx509Certificate &certificate, std::vector<CGXByteBuffer> &reply
) {
    CGXByteBuffer bb;
    int ret = certificate.GetEncoded(bb);
    if (ret == 0) {
        CGXDLMSVariant data = bb;
        reply.clear();
        ret = client->Method(this, 6, data, reply);
    }
    return ret;
}

int CGXDLMSSecuritySetup::ExportCertificateByEntity(
    CGXDLMSClient *client, DLMS_CERTIFICATE_ENTITY entity, DLMS_CERTIFICATE_TYPE type, CGXByteBuffer &systemTitle,
    std::vector<CGXByteBuffer> &reply
) {
    int ret;
    CGXDLMSVariant data;
    CGXByteBuffer bb;
    reply.clear();
    if ((ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //Add enum
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(0)) == 0 &&
        //Add certificate_identification_by_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(3)) == 0 &&
        //Add certificate_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(entity)) == 0 &&
        //Add certificate_type
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(type)) == 0 &&
        //system_title
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)systemTitle.GetSize(), bb)) == 0 &&
        (ret = bb.Set(&systemTitle, 0, systemTitle.GetSize())) == 0) {
        data = bb;
        ret = client->Method(this, 7, data, DLMS_DATA_TYPE_ARRAY, reply);
    }
    return ret;
}

int CGXDLMSSecuritySetup::ExportCertificateBySerial(
    CGXDLMSClient *client, const CGXBigInteger &serialNumber, CGXByteBuffer &issuer, std::vector<CGXByteBuffer> &reply
) {
    int ret;
    CGXDLMSVariant data;
    CGXByteBuffer bb;
    reply.clear();
    CGXByteBuffer sn;
    serialNumber.ToArray(sn);
    if ((ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //Add enum
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(1)) == 0 &&
        //Add certificate_identification_by_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //serialNumber
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)sn.GetSize(), bb)) == 0 &&
        (ret = bb.Set(sn.GetData(), sn.GetSize())) == 0 &&
        //issuer
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)issuer.GetSize(), bb)) == 0 &&
        (ret = bb.Set(issuer.GetData(), issuer.GetSize())) == 0) {
        data = bb;
        ret = client->Method(this, 7, data, DLMS_DATA_TYPE_ARRAY, reply);
    }
    return ret;
}

int CGXDLMSSecuritySetup::RemoveCertificateByEntity(
    CGXDLMSClient *client, DLMS_CERTIFICATE_ENTITY entity, DLMS_CERTIFICATE_TYPE type, CGXByteBuffer &systemTitle,
    std::vector<CGXByteBuffer> &reply
) {
    int ret;
    CGXDLMSVariant data;
    CGXByteBuffer bb;
    reply.clear();
    if ((ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //Add enum
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(0)) == 0 &&
        //Add certificate_identification_by_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(3)) == 0 &&
        //Add certificate_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(entity)) == 0 &&
        //Add certificate_type
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(type)) == 0 &&
        //system_title
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)systemTitle.GetSize(), bb)) == 0 &&
        (ret = bb.Set(&systemTitle, 0, systemTitle.GetSize())) == 0) {
        data = bb;
        ret = client->Method(this, 8, data, DLMS_DATA_TYPE_ARRAY, reply);
    }
    return ret;
}

int CGXDLMSSecuritySetup::RemoveCertificateBySerial(
    CGXDLMSClient *client, CGXByteBuffer &serialNumber, CGXByteBuffer &issuer, std::vector<CGXByteBuffer> &reply
) {
    int ret;
    CGXDLMSVariant data;
    CGXByteBuffer bb;
    reply.clear();
    if ((ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //Add enum
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_ENUM)) == 0 && (ret = bb.SetUInt8(1)) == 0 &&
        //Add certificate_identification_by_entity
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 && (ret = bb.SetUInt8(2)) == 0 &&
        //serialNumber
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)serialNumber.GetSize(), bb)) == 0 &&
        (ret = bb.Set(&serialNumber, 0, serialNumber.GetSize())) == 0 &&
        //issuer
        (ret = bb.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
        (ret = GXHelpers::SetObjectCount((unsigned long)issuer.GetSize(), bb)) == 0 &&
        (ret = bb.Set(&issuer, 0, issuer.GetSize())) == 0) {
        data = bb;
        ret = client->Method(this, 8, data, DLMS_DATA_TYPE_ARRAY, reply);
    }
    return ret;
}

int CGXDLMSSecuritySetup::Invoke(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e) {
    if (e.GetIndex() == 1) {
        m_SecurityPolicy = (DLMS_SECURITY_POLICY)e.GetParameters().ToInteger();
    } else if (e.GetIndex() == 2) {
        for (std::vector<CGXDLMSVariant>::iterator it = e.GetParameters().Arr.begin();
             it != e.GetParameters().Arr.end(); ++it) {
            DLMS_GLOBAL_KEY_TYPE type = (DLMS_GLOBAL_KEY_TYPE)it->Arr[0].ToInteger();
            CGXByteBuffer data, reply;
            CGXByteBuffer kek = settings.GetKek();
            data.Set(it->Arr[1].byteArr, it->Arr[1].GetSize());
            if (CGXDLMSSecureClient::Decrypt(kek, data, reply) != 0 || reply.GetSize() != 16) {
                e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
                break;
            }
            //Keys are take in action after reply is generated.
            switch (type) {
                case DLMS_GLOBAL_KEY_TYPE_UNICAST_ENCRYPTION:
                    break;
                case DLMS_GLOBAL_KEY_TYPE_BROADCAST_ENCRYPTION:
                    // Invalid type
                    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
                    break;
                case DLMS_GLOBAL_KEY_TYPE_AUTHENTICATION:
                    break;
                case DLMS_GLOBAL_KEY_TYPE_KEK:
                    break;
                default:
                    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
            }
        }
    } else {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSSecuritySetup::ApplyKeys(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e) {
    for (std::vector<CGXDLMSVariant>::iterator it = e.GetParameters().Arr.begin(); it != e.GetParameters().Arr.end();
         ++it) {
        DLMS_GLOBAL_KEY_TYPE type = (DLMS_GLOBAL_KEY_TYPE)it->Arr[0].ToInteger();
        CGXByteBuffer data, reply;
        CGXByteBuffer kek = settings.GetKek();
        data.Set(it->Arr[1].byteArr, it->Arr[1].GetSize());
        if (CGXDLMSSecureClient::Decrypt(kek, data, reply) != 0 || reply.GetSize() != 16) {
            e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
            break;
        }
        switch (type) {
            case DLMS_GLOBAL_KEY_TYPE_UNICAST_ENCRYPTION:
                settings.GetCipher()->SetBlockCipherKey(reply);
                break;
            case DLMS_GLOBAL_KEY_TYPE_BROADCAST_ENCRYPTION:
                // Invalid type
                e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
                break;
            case DLMS_GLOBAL_KEY_TYPE_AUTHENTICATION:
                // if settings.Cipher is NULL non secure server is used.
                settings.GetCipher()->SetAuthenticationKey(reply);
                break;
            case DLMS_GLOBAL_KEY_TYPE_KEK:
                settings.SetKek(reply);
                break;
            default:
                e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSSecuritySetup::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(CGXDLMSConverter::ToString(m_SecurityPolicy));
    values.push_back(CGXDLMSConverter::ToString(m_SecuritySuite));
    values.push_back(m_ClientSystemTitle.ToHexString());
    values.push_back(m_ServerSystemTitle.ToHexString());
    if (GetVersion() > 0)
    {
        std::stringstream sb;
        bool empty = true;
        for (const auto& it : m_Certificates)
        {
            if (empty)
            {
                empty = false;
            }
            else
            {
                sb << ',';
            }
            sb << '[';
            sb << static_cast<int>(it->GetEntity());
            sb << ' ';
            sb << static_cast<int>(it->GetType());
            sb << ' ';
            sb << it->GetSerialNumber().ToString();
            sb << ' ';
            sb << it->GetIssuer();
            sb << ' ';
            sb << it->GetSubject();
            sb << ' ';
            sb << it->GetSubjectAltName();
            sb << ']';
        }
        values.push_back(sb.str());
    }
}

void CGXDLMSSecuritySetup::GetAttributeIndexToRead(bool all, std::vector<int> &attributes) {
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN)) {
        attributes.push_back(1);
    }
    //SecurityPolicy
    if (all || CanRead(2)) {
        attributes.push_back(2);
    }
    //SecuritySuite
    if (all || CanRead(3)) {
        attributes.push_back(3);
    }
    //ClientSystemTitle
    if (all || CanRead(4)) {
        attributes.push_back(4);
    }
    //ServerSystemTitle
    if (all || CanRead(5)) {
        attributes.push_back(5);
    }
    if (GetVersion() > 0) {
        //Certificates
        if (all || CanRead(6)) {
            attributes.push_back(6);
        }
    }
}

int CGXDLMSSecuritySetup::GetDataType(int index, DLMS_DATA_TYPE &type) {
    if (index == 1) {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    } else if (index == 2) {
        type = DLMS_DATA_TYPE_ENUM;
    } else if (index == 3) {
        type = DLMS_DATA_TYPE_ENUM;
    } else if (index == 4) {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    } else if (index == 5) {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    } else if (index == 6 && GetVersion() > 0) {
        type = DLMS_DATA_TYPE_ARRAY;
    } else {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSSecuritySetup::GetValue(CGXDLMSSettings&, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        int ret;
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) != 0)
        {
            return ret;
        }
        e.SetValue(tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        e.SetValue(m_SecurityPolicy);
    }
    else if (e.GetIndex() == 3)
    {
        e.SetValue(m_SecuritySuite);
    }
    else if (e.GetIndex() == 4)
    {
        e.GetValue().Add(m_ClientSystemTitle.GetData(), m_ClientSystemTitle.GetSize());
    }
    else if (e.GetIndex() == 5)
    {
        e.GetValue().Add(m_ServerSystemTitle.GetData(), m_ServerSystemTitle.GetSize());
    }
    else if (e.GetIndex() == 6)
    {
        CGXByteBuffer bb;
        bb.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount(static_cast<unsigned long>(m_Certificates.size()), bb);
        for (const auto& it : m_Certificates)
        {
            bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
            GXHelpers::SetObjectCount(6, bb);
            bb.SetUInt8(DLMS_DATA_TYPE_ENUM);
            bb.SetUInt8(it->GetEntity());
            bb.SetUInt8(DLMS_DATA_TYPE_ENUM);
            bb.SetUInt8(it->GetType());
            it->GetSerialNumber().ToArray(bb);
            bb.AddString(it->GetIssuer());
            bb.AddString(it->GetSubject());
            bb.AddString(it->GetSubjectAltName());
        }
        e.SetValue(bb);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSSecuritySetup::SetValue(CGXDLMSSettings&, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    if (e.GetIndex() == 2)
    {
        m_SecurityPolicy = static_cast<DLMS_SECURITY_POLICY>(e.GetValue().ToInteger());
    }
    else if (e.GetIndex() == 3)
    {
        m_SecuritySuite = static_cast<DLMS_SECURITY_SUITE>(e.GetValue().ToInteger());
    }
    else if (e.GetIndex() == 4)
    {
        m_ClientSystemTitle.Clear();
        m_ClientSystemTitle.Set(e.GetValue().byteArr, e.GetValue().size);
    }
    else if (e.GetIndex() == 5)
    {
        m_ServerSystemTitle.Clear();
        m_ServerSystemTitle.Set(e.GetValue().byteArr, e.GetValue().size);
    }
    else if (e.GetIndex() == 6)
    {
        m_Certificates.clear();
        if (e.GetValue().vt != DLMS_DATA_TYPE_NONE)
        {
            CGXByteBuffer bb;
            for (const auto& it : e.GetValue().Arr)
            {
                auto info = std::unique_ptr<CGXDLMSCertificateInfo>(new CGXDLMSCertificateInfo());
                info->SetEntity(static_cast<DLMS_CERTIFICATE_ENTITY>(it.Arr[0].ToInteger()));
                info->SetType(static_cast<DLMS_CERTIFICATE_TYPE>(it.Arr[1].ToInteger()));
                bb.Clear();
                bb.Set(it.Arr[2].byteArr, it.Arr[2].size);
                std::unique_ptr<CGXAsn1Base> value(new CGXAsn1Base());
                int ret;
                CGXAsn1Base* tmp = value.get();
                if ((ret = CGXAsn1Converter::FromByteArray(bb, tmp)) != 0)
                {
                    return ret;
                }
                if (auto* asn1Int = dynamic_cast<CGXAsn1Integer*>(value.get()))
                {
                    asn1Int->GetValue().Reverse(0, asn1Int->GetValue().GetSize());
                    info->SetSerialNumber(asn1Int->ToBigInteger());
                }
                else if (auto* asn1Var = dynamic_cast<CGXAsn1Variant*>(value.get()))
                {
                    bb.Clear();
                    bb.Set(asn1Var->GetValue().byteArr, asn1Var->GetValue().size);
                    CGXBigInteger bi(bb);
                    info->SetSerialNumber(bi);
                }
                else
                {
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                info->m_IssuerRaw.Set(it.Arr[3].byteArr, it.Arr[3].size);
                info->SetIssuer(it.Arr[3].ToString());
                info->SetSubject(it.Arr[4].ToString());
                info->SetSubjectAltName(it.Arr[5].ToString());
                m_Certificates.push_back(std::move(info));
            }
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

std::vector<std::unique_ptr<CGXDLMSCertificateInfo>> const& CGXDLMSSecuritySetup::GetCertificates() const
{
    return m_Certificates;
}
#endif  //DLMS_IGNORE_SECURITY_SETUP