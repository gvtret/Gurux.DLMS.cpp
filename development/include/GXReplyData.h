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

#ifndef GXREPLYDATA_H
#define GXREPLYDATA_H

#include "GXDLMSConverter.h"
#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"
#include "GXDLMSTranslatorStructure.h"
#include <memory>

class CGXReplyData {
private:
    /*
     * Is more data available.
     */
    DLMS_DATA_REQUEST_TYPES m_MoreData = DLMS_DATA_REQUEST_TYPES_NONE;
    /*
     * Received command.
     */
    DLMS_COMMAND m_Command = DLMS_COMMAND_NONE;

    /*
    * Received command type.
    */
    unsigned char m_CommandType = 0;

    /*
     * Received data.
     */
    CGXByteBuffer m_Data;
    CGXByteBuffer* m_pData = &m_Data;
    /*
     * Is frame complete.
     */
    bool m_Complete = false;

    /*
     * Read value.
     */
    CGXDLMSVariant m_DataValue;

    /*
     * Expected count of element in the array.
     */
    int m_TotalCount = 0;

    /*
     * Last read position. This is used in peek to solve how far data is read.
     */
    unsigned long m_ReadPosition = 0;

    /*
     * Packet Length.
     */
    int m_PacketLength = 0;

    /*
     * Try Get value.
     */
    bool m_Peek = false;

    DLMS_DATA_TYPE m_DataType = DLMS_DATA_TYPE_NONE;

    /*
     * Cipher index is position where data is decrypted.
     */
    unsigned long m_CipherIndex = 0;

    /*
     * Data notification date time.
     */
    std::unique_ptr<struct tm> m_Time;

#ifndef DLMS_IGNORE_XML_TRANSLATOR
    CGXDLMSTranslatorStructure* m_pXml = nullptr;
#endif  //DLMS_IGNORE_XML_TRANSLATOR

    /*
    * Invoke ID.
    */
    long m_InvokeId = 0;

    /*
     * GBT block number.
     */
    int m_BlockNumber = 0;
    /*
     * GBT block number ACK.
     */
    int m_BlockNumberAck = 0;
    /*
     * Is GBT streaming in use.
     */
    bool m_Streaming = false;
    /*
     * GBT Window size. This is for internal use.
     */
    unsigned char m_GbtWindowSize = 0;

    /*
     * Client address of the notification message. Notification message sets
     * this.
     */
    unsigned short m_ClientAddress = 0;

    /*
     * Server address of the notification message. Notification message sets
     * this.
     */
    int m_ServerAddress = 0;

    unsigned char m_CipheredCommand = 0;

public:
    /*
     * Constructor.
     */
    CGXReplyData();


    CGXReplyData(const CGXReplyData& other);
    CGXReplyData(CGXReplyData&& other) noexcept;
    CGXReplyData& operator=(const CGXReplyData& other);
    CGXReplyData& operator=(CGXReplyData&& other) noexcept;

    DLMS_DATA_TYPE GetValueType() const;

    void SetValueType(DLMS_DATA_TYPE value);

    const CGXDLMSVariant &GetValue() const;
    CGXDLMSVariant &GetValue();


    void SetValue(const CGXDLMSVariant &value);

    unsigned long GetReadPosition() const;

    void SetReadPosition(unsigned long value);

    int GetPacketLength() const;

    void SetPacketLength(int value);

    void SetCommand(DLMS_COMMAND value);

    void SetCommandType(unsigned char value);

    unsigned char GetCommandType() const;


    void SetData(const CGXByteBuffer &value);

    void SetComplete(bool value);

    void SetTotalCount(int value);

    /*
     * Reset data values to default.
     */
    void Clear();

    /*
     * @return Is more data available.
     */
    bool IsMoreData() const;

    /*
     * Is more data available.
     *
     * @return Return None if more data is not available or Frame or Block type.
     */
    DLMS_DATA_REQUEST_TYPES GetMoreData() const;

    void SetMoreData(DLMS_DATA_REQUEST_TYPES value);


    /*
     * Get received command.
     *
     * @return Received command.
     */
    DLMS_COMMAND GetCommand() const;

    /*
     * Get received data.
     *
     * @return Received data.
     */
    const CGXByteBuffer &GetData() const;
    CGXByteBuffer &GetData();

    /*
     * Is frame complete.
     *
     * @return Returns true if frame is complete or false if bytes is missing.
     */
    bool IsComplete() const;

    /*
     * Get total count of element in the array. If this method is used peek must
     * be Set true.
     *
     * @return Count of element in the array.
     * @see peek
     * @see GetCount
     */
    int GetTotalCount() const;

    /*
     * Get count of read elements. If this method is used peek must be Set true.
     *
     * @return Count of read elements.
     * @see peek
     * @see GetTotalCount
     */
    int GetCount() const;

    /*
     * Get is value try to peek.
     *
     * @return Is value try to peek.
     * @see GetCount
     * @see GetTotalCount
     */
    bool GetPeek() const;

    /*
     * Set is value try to peek.
     *
     * @param value
     *            Is value try to peek.
     */
    void SetPeek(bool value);

    /*
     * @return Cipher index is position where data is decrypted.
     */
    unsigned long GetCipherIndex() const;

    /*
     * @param cipherIndex
     *            Cipher index is position where data is decrypted.
     */
    void SetCipherIndex(unsigned long value);

    /*
     * @return Data notification date time.
     */
    struct tm *GetTime() const;


    /*
     * @param time
     *            Data notification date time.
     */
    void SetTime(const struct tm *value);

#ifndef DLMS_IGNORE_XML_TRANSLATOR
    /*
     * @return Data notification date time.
     */
    CGXDLMSTranslatorStructure *GetXml() const;


    /*
     * @param time
     *            Data notification date time.
     */
    void SetXml(CGXDLMSTranslatorStructure *value);
#endif  //DLMS_IGNORE_XML_TRANSLATOR

    /**
    * Invoke ID.
    */
    long GetInvokeId() const;

    /**
     * Invoke ID.
     */
    void SetInvokeId(long value);

    /*
     * GBT block number.
     */
    int GetBlockNumber() const;

    /*
     * GBT block number.
     */
    void SetBlockNumber(int value);

    /**
     * GBT block number ACK.
     */
    int GetBlockNumberAck() const;

    /**
     * @param value
     *            GBT block number ACK.
     */
    void SetBlockNumberAck(int value);

    /**
     * @return Is GBT streaming in use.
     */
    bool GetStreaming() const;

    /**
     * Is GBT streaming in use.
     */
    void SetStreaming(bool value);

    /**
     * GBT Window size. This is for internal use.
     */
    unsigned char GetGbtWindowSize() const;

    /**
     * GBT Window size. This is for internal use.
     */
    void SetGbtWindowSize(unsigned char value);

    /**
     * Is GBT streaming.
     */
    bool IsStreaming() const;

    /**
     * Client address of the notification message. Notification message
     * sets this.
     */
    unsigned short GetClientAddress() const;

    /**
     *            Client address of the notification message. Notification
     *            message sets this.
     */
    void SetClientAddress(unsigned short value);

    /*
     * Server address of the notification message. Notification message
     *         sets this.
     */
    int GetServerAddress() const;

    /*
     *            Server address of the notification message. Notification
     *            message sets this.
     */
    void SetServerAddress(int value);

    /*
     * returns Received ciphered command.
     */
    unsigned char GetCipheredCommand() const;

    /*
     * value: Received ciphered command.
     */
    void SetCipheredCommand(unsigned char value);
};

#endif  //GXREPLYDATA_H