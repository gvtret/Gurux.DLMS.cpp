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
// This code is licensed under the GNU General Public License v2//
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "../include/GXReplyData.h"

#include <utility>

CGXReplyData::CGXReplyData() {
    Clear();
}

CGXReplyData::CGXReplyData(const CGXReplyData& other) :
    m_MoreData(other.m_MoreData),
    m_Command(other.m_Command),
    m_CommandType(other.m_CommandType),
    m_Data(*other.m_pData),
    m_pData(&m_Data),
    m_Complete(other.m_Complete),
    m_DataValue(other.m_DataValue),
    m_TotalCount(other.m_TotalCount),
    m_ReadPosition(other.m_ReadPosition),
    m_PacketLength(other.m_PacketLength),
    m_Peek(other.m_Peek),
    m_DataType(other.m_DataType),
    m_CipherIndex(other.m_CipherIndex),
    m_InvokeId(other.m_InvokeId),
    m_BlockNumber(other.m_BlockNumber),
    m_BlockNumberAck(other.m_BlockNumberAck),
    m_Streaming(other.m_Streaming),
    m_GbtWindowSize(other.m_GbtWindowSize),
    m_ClientAddress(other.m_ClientAddress),
    m_ServerAddress(other.m_ServerAddress),
    m_CipheredCommand(other.m_CipheredCommand)
{
    if (other.m_Time) {
        m_Time = std::unique_ptr<struct tm>(new struct tm(*other.m_Time));
    }
#ifndef DLMS_IGNORE_XML_TRANSLATOR
    m_pXml = other.m_pXml;
#endif
}
CGXReplyData::CGXReplyData(CGXReplyData&& other) noexcept :
    m_MoreData(other.m_MoreData),
    m_Command(other.m_Command),
    m_CommandType(other.m_CommandType),
    m_Data(std::move(other.m_Data)),
    m_pData(other.m_pData == &other.m_Data ? &m_Data : other.m_pData),
    m_Complete(other.m_Complete),
    m_DataValue(std::move(other.m_DataValue)),
    m_TotalCount(other.m_TotalCount),
    m_ReadPosition(other.m_ReadPosition),
    m_PacketLength(other.m_PacketLength),
    m_Peek(other.m_Peek),
    m_DataType(other.m_DataType),
    m_CipherIndex(other.m_CipherIndex),
    m_Time(std::move(other.m_Time)),
#ifndef DLMS_IGNORE_XML_TRANSLATOR
    m_pXml(other.m_pXml),
#endif
    m_InvokeId(other.m_InvokeId),
    m_BlockNumber(other.m_BlockNumber),
    m_BlockNumberAck(other.m_BlockNumberAck),
    m_Streaming(other.m_Streaming),
    m_GbtWindowSize(other.m_GbtWindowSize),
    m_ClientAddress(other.m_ClientAddress),
    m_ServerAddress(other.m_ServerAddress),
    m_CipheredCommand(other.m_CipheredCommand)
{
    other.m_pData = &other.m_Data;
#ifndef DLMS_IGNORE_XML_TRANSLATOR
    other.m_pXml = nullptr;
#endif
}
CGXReplyData& CGXReplyData::operator=(const CGXReplyData& other)
{
    if (this != &other) {
        m_MoreData = other.m_MoreData;
        m_Command = other.m_Command;
        m_CommandType = other.m_CommandType;
        m_Data = *other.m_pData;
        m_pData = &m_Data;
        m_Complete = other.m_Complete;
        m_DataValue = other.m_DataValue;
        m_TotalCount = other.m_TotalCount;
        m_ReadPosition = other.m_ReadPosition;
        m_PacketLength = other.m_PacketLength;
        m_Peek = other.m_Peek;
        m_DataType = other.m_DataType;
        m_CipherIndex = other.m_CipherIndex;
        if (other.m_Time) {
            m_Time = std::unique_ptr<struct tm>(new struct tm(*other.m_Time));
        }
        else {
            m_Time.reset();
        }
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        m_pXml = other.m_pXml;
#endif
        m_InvokeId = other.m_InvokeId;
        m_BlockNumber = other.m_BlockNumber;
        m_BlockNumberAck = other.m_BlockNumberAck;
        m_Streaming = other.m_Streaming;
        m_GbtWindowSize = other.m_GbtWindowSize;
        m_ClientAddress = other.m_ClientAddress;
        m_ServerAddress = other.m_ServerAddress;
        m_CipheredCommand = other.m_CipheredCommand;
    }
    return *this;
}
CGXReplyData& CGXReplyData::operator=(CGXReplyData&& other) noexcept
{
    if (this != &other) {
        m_MoreData = other.m_MoreData;
        m_Command = other.m_Command;
        m_CommandType = other.m_CommandType;
        m_Data = std::move(other.m_Data);
        m_pData = other.m_pData == &other.m_Data ? &m_Data : other.m_pData;
        m_Complete = other.m_Complete;
        m_DataValue = std::move(other.m_DataValue);
        m_TotalCount = other.m_TotalCount;
        m_ReadPosition = other.m_ReadPosition;
        m_PacketLength = other.m_PacketLength;
        m_Peek = other.m_Peek;
        m_DataType = other.m_DataType;
        m_CipherIndex = other.m_CipherIndex;
        m_Time = std::move(other.m_Time);
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        m_pXml = other.m_pXml;
#endif
        m_InvokeId = other.m_InvokeId;
        m_BlockNumber = other.m_BlockNumber;
        m_BlockNumberAck = other.m_BlockNumberAck;
        m_Streaming = other.m_Streaming;
        m_GbtWindowSize = other.m_GbtWindowSize;
        m_ClientAddress = other.m_ClientAddress;
        m_ServerAddress = other.m_ServerAddress;
        m_CipheredCommand = other.m_CipheredCommand;

        other.m_pData = &other.m_Data;
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        other.m_pXml = nullptr;
#endif
    }
    return *this;
}

DLMS_DATA_TYPE CGXReplyData::GetValueType() const {
    return m_DataType;
}

void CGXReplyData::SetValueType(DLMS_DATA_TYPE value) {
    m_DataType = value;
}

const CGXDLMSVariant& CGXReplyData::GetValue() const {
    return m_DataValue;
}

CGXDLMSVariant& CGXReplyData::GetValue() {
    return m_DataValue;
}

void CGXReplyData::SetValue(const CGXDLMSVariant& value) {
    m_DataValue = value;
}

unsigned long CGXReplyData::GetReadPosition() const {
    return m_ReadPosition;
}

void CGXReplyData::SetReadPosition(unsigned long value) {
    m_ReadPosition = value;
}

int CGXReplyData::GetPacketLength() const {
    return m_PacketLength;
}

void CGXReplyData::SetPacketLength(int value) {
    m_PacketLength = value;
}

void CGXReplyData::SetCommand(DLMS_COMMAND value) {
    m_Command = value;
}

void CGXReplyData::SetData(const CGXByteBuffer& value) {
    m_Data = value;
    m_pData = &m_Data;
}

void CGXReplyData::SetComplete(bool value) {
    m_Complete = value;
}

void CGXReplyData::SetTotalCount(int value) {
    m_TotalCount = value;
}

void CGXReplyData::Clear() {
    m_Data.Clear();
    m_pData = &m_Data;
    m_Time.reset();
    m_MoreData = DLMS_DATA_REQUEST_TYPES_NONE;
    m_Command = DLMS_COMMAND_NONE;
    m_Complete = false;
    m_Peek = false;
    m_TotalCount = 0;
    m_DataValue.Clear();
    m_ReadPosition = 0;
    m_PacketLength = 0;
    m_DataType = DLMS_DATA_TYPE_NONE;
    m_CipherIndex = 0;
#ifndef DLMS_IGNORE_XML_TRANSLATOR
    m_pXml = nullptr;
#endif
    m_InvokeId = 0;
    m_BlockNumber = 0;
    m_BlockNumberAck = 0;
    m_Streaming = false;
    m_GbtWindowSize = 0;
    m_ClientAddress = 0;
    m_ServerAddress = 0;
    m_CommandType = 0;
    m_CipheredCommand = 0;
    m_ReadPosition = 0;
    m_CipherIndex = 0;
}

bool CGXReplyData::IsMoreData() const {
    return m_MoreData != DLMS_DATA_REQUEST_TYPES_NONE;
}

DLMS_DATA_REQUEST_TYPES CGXReplyData::GetMoreData() const {
    return m_MoreData;
}

void CGXReplyData::SetMoreData(DLMS_DATA_REQUEST_TYPES value) {
    m_MoreData = value;
}

DLMS_COMMAND CGXReplyData::GetCommand() const {
    return m_Command;
}

void CGXReplyData::SetCommandType(unsigned char value) {
    m_CommandType = value;
}

unsigned char CGXReplyData::GetCommandType() const {
    return m_CommandType;
}

const CGXByteBuffer& CGXReplyData::GetData() const {
    return *m_pData;
}

CGXByteBuffer& CGXReplyData::GetData() {
    return *m_pData;
}

bool CGXReplyData::IsComplete() const {
    return m_Complete;
}

int CGXReplyData::GetTotalCount() const {
    return m_TotalCount;
}

int CGXReplyData::GetCount() const {
    if (m_DataValue.vt == DLMS_DATA_TYPE_ARRAY) {
        return (int)m_DataValue.Arr.size();
    }
    return 0;
}

bool CGXReplyData::GetPeek() const {
    return m_Peek;
}

void CGXReplyData::SetPeek(bool value) {
    m_Peek = value;
}

unsigned long CGXReplyData::GetCipherIndex() const {
    return m_CipherIndex;
}

void CGXReplyData::SetCipherIndex(unsigned long value) {
    m_CipherIndex = value;
}

struct tm* CGXReplyData::GetTime() const {
    return m_Time.get();
}

void CGXReplyData::SetTime(const struct tm* value) {
    if (value == nullptr) {
        m_Time.reset();
    }
    else {
        m_Time = std::unique_ptr<struct tm>(new struct tm(*value));
    }
}

#ifndef DLMS_IGNORE_XML_TRANSLATOR
CGXDLMSTranslatorStructure* CGXReplyData::GetXml() const {
    return m_pXml;
}

void CGXReplyData::SetXml(CGXDLMSTranslatorStructure* value) {
    m_pXml = value;
}
#endif  //DLMS_IGNORE_XML_TRANSLATOR

long CGXReplyData::GetInvokeId() const {
    return m_InvokeId;
}

void CGXReplyData::SetInvokeId(long value) {
    m_InvokeId = value;
}

int CGXReplyData::GetBlockNumber() const {
    return m_BlockNumber;
}

void CGXReplyData::SetBlockNumber(int value) {
    m_BlockNumber = value;
}

int CGXReplyData::GetBlockNumberAck() const {
    return m_BlockNumberAck;
}

void CGXReplyData::SetBlockNumberAck(int value) {
    m_BlockNumberAck = value;
}

bool CGXReplyData::GetStreaming() const {
    return m_Streaming;
}

void CGXReplyData::SetStreaming(bool value) {
    m_Streaming = value;
}

unsigned char CGXReplyData::GetGbtWindowSize() const {
    return m_GbtWindowSize;
}

void CGXReplyData::SetGbtWindowSize(unsigned char value) {
    m_GbtWindowSize = value;
}

bool CGXReplyData::IsStreaming() const {
    return (m_MoreData & DLMS_DATA_REQUEST_TYPES_FRAME) == 0 && m_Streaming &&
        (m_BlockNumberAck * m_GbtWindowSize) + 1 > m_BlockNumber;
}

unsigned short CGXReplyData::GetClientAddress() const {
    return m_ClientAddress;
}

void CGXReplyData::SetClientAddress(unsigned short value) {
    m_ClientAddress = value;
}

int CGXReplyData::GetServerAddress() const {
    return m_ServerAddress;
}

void CGXReplyData::SetServerAddress(int value) {
    m_ServerAddress = value;
}

unsigned char CGXReplyData::GetCipheredCommand() const {
    return m_CipheredCommand;
}

void CGXReplyData::SetCipheredCommand(unsigned char value) {
    m_CipheredCommand = value;
}
