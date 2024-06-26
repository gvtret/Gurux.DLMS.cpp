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

#include "../include/GXDLMSCommunicationPortProtection.h"
#include "../include/GXDLMSClient.h"

#ifndef DLMS_IGNORE_COMMUNICATION_PORT_PROTECTION

//Constructor.
CGXDLMSCommunicationPortProtection::CGXDLMSCommunicationPortProtection() :
    CGXDLMSCommunicationPortProtection("0.0.44.2.0.255", 0)
{
}

//SN Constructor.
CGXDLMSCommunicationPortProtection::CGXDLMSCommunicationPortProtection(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_COMMUNICATION_PORT_PROTECTION, ln, sn)
{
    m_Port = NULL;
}

//LN Constructor.
CGXDLMSCommunicationPortProtection::CGXDLMSCommunicationPortProtection(std::string ln) :
    CGXDLMSCommunicationPortProtection(ln, 0)
{

}

DLMS_PROTECTION_MODE CGXDLMSCommunicationPortProtection::GetProtectionMode()
{
    return m_ProtectionMode;
}

void CGXDLMSCommunicationPortProtection::SetProtectionMode(DLMS_PROTECTION_MODE value)
{
    m_ProtectionMode = value;
}

uint16_t CGXDLMSCommunicationPortProtection::GetAllowedFailedAttempts()
{
    return m_AllowedFailedAttempts;
}

void CGXDLMSCommunicationPortProtection::SetAllowedFailedAttempts(uint16_t value)
{
    m_AllowedFailedAttempts = value;
}

uint32_t CGXDLMSCommunicationPortProtection::GetInitialLockoutTime() 
{
    return m_InitialLockoutTime;
}

void CGXDLMSCommunicationPortProtection::SetInitialLockoutTime(uint32_t value)
{
    m_InitialLockoutTime = value;
}

unsigned char CGXDLMSCommunicationPortProtection::GetSteepnessFactor()
{
    return m_SteepnessFactor;
}

void CGXDLMSCommunicationPortProtection::SetSteepnessFactor(unsigned char value)
{
    m_SteepnessFactor = value;
}

uint32_t CGXDLMSCommunicationPortProtection::GetMaxLockoutTime()
{
    return m_MaxLockoutTime;
}

void CGXDLMSCommunicationPortProtection::SetMaxLockoutTime(uint32_t value)
{
    m_MaxLockoutTime = value;
}

CGXDLMSObject* CGXDLMSCommunicationPortProtection::GetPort()
{
    return m_Port;
}

void CGXDLMSCommunicationPortProtection::SetPort(CGXDLMSObject* value)
{
    m_Port = value;
}

DLMS_PROTECTION_STATUS CGXDLMSCommunicationPortProtection::GetProtectionStatus() 
{
    return m_ProtectionStatus;
}

void CGXDLMSCommunicationPortProtection::SetProtectionStatus(DLMS_PROTECTION_STATUS value)
{
    m_ProtectionStatus = value;
}

uint32_t CGXDLMSCommunicationPortProtection::GetFailedAttempts()
{
    return m_FailedAttempts;
}

void CGXDLMSCommunicationPortProtection::SetFailedAttempts(uint32_t value)
{
    m_FailedAttempts = value;
}

uint32_t CGXDLMSCommunicationPortProtection::GetCumulativeFailedAttempts()
{
    return m_CumulativeFailedAttempts;
}

void CGXDLMSCommunicationPortProtection::SetCumulativeFailedAttempts(uint32_t value)
{
    m_CumulativeFailedAttempts = value;
}

int CGXDLMSCommunicationPortProtection::Reset(CGXDLMSClient* client,
    std::vector<CGXByteBuffer>& reply)
{
    CGXDLMSVariant data((char)0);
    return client->Method(this, 1, data, reply);
}

// Returns amount of attributes.
int CGXDLMSCommunicationPortProtection::GetAttributeCount()
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSCommunicationPortProtection::GetMethodCount()
{
    return 1;
}

void CGXDLMSCommunicationPortProtection::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(std::to_string(m_ProtectionMode));

    values.push_back(std::to_string(m_AllowedFailedAttempts));
    values.push_back(std::to_string(m_InitialLockoutTime));
    values.push_back(std::to_string(m_SteepnessFactor));
    values.push_back(std::to_string(m_MaxLockoutTime));
    if (m_Port == NULL)
    {
        values.push_back("");
    }
    else
    {
        std::string ln;
        m_Port->GetLogicalName(ln);
        values.push_back(ln);
    }
    values.push_back(std::to_string(m_ProtectionStatus));
    values.push_back(std::to_string(m_FailedAttempts));
    values.push_back(std::to_string(m_CumulativeFailedAttempts));
}

void CGXDLMSCommunicationPortProtection::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //ProtectionMode
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    // AllowedFailedAttempts
    if (all || CanRead(3)) {
        attributes.push_back(3);
    }
    // InitialLockoutTime
    if (all || CanRead(4)) {
        attributes.push_back(4);
    }
    // SteepnessFactor
    if (all || CanRead(5)) {
        attributes.push_back(5);
    }
    // MaxLockoutTime
    if (all || CanRead(6)) {
        attributes.push_back(6);
    }
    // Port
    if (all || CanRead(7)) {
        attributes.push_back(7);
    }
    // ProtectionStatus
    if (all || CanRead(8)) {
        attributes.push_back(8);
    }
    // FailedAttempts
    if (all || CanRead(9)) {
        attributes.push_back(9);
    }
    // CumulativeFailedAttempts
    if (all || CanRead(10)) {
        attributes.push_back(10);
    }
}

int CGXDLMSCommunicationPortProtection::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index) {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
        type = DLMS_DATA_TYPE_ENUM;
        break;
    case 3:
        type = DLMS_DATA_TYPE_UINT16;
        break;
    case 4:
        type = DLMS_DATA_TYPE_UINT32;
        break;
    case 5:
        type = DLMS_DATA_TYPE_UINT8;
        break;
    case 6:
        type = DLMS_DATA_TYPE_UINT32;
        break;
    case 7:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 8:
        type = DLMS_DATA_TYPE_ENUM;
        break;
    case 9:
        type = DLMS_DATA_TYPE_UINT32;
        break;
    case 10:
        type = DLMS_DATA_TYPE_UINT32;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSCommunicationPortProtection::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
    {
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) == 0)
        {
            e.SetValue(tmp);
        }
        break;
    }
    case 2:
        e.SetValue(m_ProtectionMode);
        break;
    case 3:
        e.SetValue(m_AllowedFailedAttempts);
        break;
    case 4:
        e.SetValue(m_InitialLockoutTime);
        break;
    case 5:
        e.SetValue(m_SteepnessFactor);
        break;
    case 6:
        e.SetValue(m_MaxLockoutTime);
        break;
    case 7:
    {
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(m_Port, tmp)) == 0)
        {
            e.SetValue(tmp);
        }
        break;
    }
    case 8:
        e.SetValue(m_ProtectionStatus);
        break;
    case 9:
        e.SetValue(m_FailedAttempts);
        break;
    case 10:
        e.SetValue(m_CumulativeFailedAttempts);
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSCommunicationPortProtection::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex()) {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
        m_ProtectionMode = (DLMS_PROTECTION_MODE) e.GetValue().ToInteger();
        break;
    case 3:
        m_AllowedFailedAttempts = e.GetValue().ToInteger();
        break;
    case 4:
        m_InitialLockoutTime = e.GetValue().ToInteger();
        break;
    case 5:
        m_SteepnessFactor = e.GetValue().ToInteger();
        break;
    case 6:
        m_MaxLockoutTime = e.GetValue().ToInteger();
        break;
    case 7:
    {
        std::string ln;
        GXHelpers::GetLogicalName(e.GetValue().byteArr, ln);
        m_Port = settings.GetObjects().FindByLN(DLMS_OBJECT_TYPE_NONE, ln);
        break;
    }
    case 8:
        m_ProtectionStatus = (DLMS_PROTECTION_STATUS) e.GetValue().ToInteger();
        break;
    case 9:
        m_FailedAttempts = e.GetValue().ToInteger();
        break;
    case 10:
        m_CumulativeFailedAttempts = e.GetValue().ToInteger();
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}
#endif //DLMS_IGNORE_COMMUNICATION_PORT_PROTECTION