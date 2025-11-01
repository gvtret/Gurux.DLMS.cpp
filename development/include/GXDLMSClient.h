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

#ifndef GXDLMSCLIENT_H
#define GXDLMSCLIENT_H

#include "GXDLMS.h"
#include "GXDLMSProfileGeneric.h"
#include "GXSecure.h"
#include "GXDateTime.h"
#include "GXDLMSAccessItem.h"

/**
 * @brief Represents a DLMS/COSEM client.
 */
class CGXDLMSClient {
protected:
    friend class CGXDLMSSchedule;
    CGXDLMSSettings m_Settings;
    char m_ManufacturerId[3];

private:
    /**
     * @brief Initialize PDU size that is restored after the connection is closed.
     */
    uint16_t m_InitializePduSize;

    /**
     * @brief Initialize Max HDLC transmission size that is restored after the connection is closed.
     */
    uint16_t m_InitializeMaxInfoTX;

    /**
     * @brief Initialize Max HDLC receive size that is restored after the connection is closed.
     */
    uint16_t m_InitializeMaxInfoRX;

    /**
     * @brief Initialize max HDLC window size in transmission that is restored after the connection is closed.
     */
    unsigned char m_InitializeWindowSizeTX;

    /**
     * @brief Initialize max HDLC window size in receive that is restored after the connection is closed.
     */
    unsigned char m_InitializeWindowSizeRX;

    /**
     * @brief If protected release is used release is including a ciphered xDLMS Initiate request.
     */
    bool m_UseProtectedRelease;
    bool m_IsAuthenticationRequired;

    int ParseSNObjects(CGXByteBuffer &buff, bool onlyKnownObjects, bool ignoreInactiveObjects);

    int ParseSNObjectItem(CGXDLMSVariant &value, bool ignoreInactiveObjects);
    int ParseLNObjectItem(CGXDLMSVariant &value, bool ignoreInactiveObjects);

    /**
     * @brief Parses LN objects.
     * @param buff Byte stream where objects are parsed.
     * @param onlyKnownObjects Only known objects are parsed.
     * @return Collection of COSEM objects.
     */
    int ParseLNObjects(CGXByteBuffer &buff, bool onlyKnownObjects, bool ignoreInactiveObjects);

    /**
     * @brief Generates a read message.
     * @param name Short or Logical Name.
     * @param objectType COSEM object type.
     * @param attributeOrdinal Attribute index of the object.
     * @param data Read selective access parameter.
     * @param reply Generated read message(s).
     * @return Error status.
     */
    int Read(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int attributeOrdinal, CGXByteBuffer *parameters,
        std::vector<CGXByteBuffer> &reply
    );

public:
    /**
     * @brief Constructor.
     * @param UseLogicalNameReferencing True to use logical name referencing, false otherwise.
     * @param ClientAddress The client's address.
     * @param ServerAddress The server's address.
     * @param authentication The authentication type.
     * @param password The password for authentication.
     * @param intefaceType The interface type.
     */
    CGXDLMSClient(
        bool UseLogicalNameReferencing = true, int ClientAddress = 16, int ServerAddress = 1,
        DLMS_AUTHENTICATION authentication = DLMS_AUTHENTICATION_NONE,
        const char *password = NULL, DLMS_INTERFACE_TYPE intefaceType = DLMS_INTERFACE_TYPE_HDLC
    );

    /**
     * @brief Destructor.
     */
    ~CGXDLMSClient();

    /**
     * @brief Gets whether logical name referencing is used.
     * @return True if logical name referencing is used, false otherwise.
     */
    bool GetUseLogicalNameReferencing();

    /**
     * @brief Gets the interface type.
     * @return The interface type.
     */
    DLMS_INTERFACE_TYPE GetInterfaceType();

    /**
     * @brief Gets the used priority.
     * @return The priority.
     */
    DLMS_PRIORITY GetPriority();

    /**
     * @brief Sets the used priority.
     * @param value The priority to set.
     */
    void SetPriority(DLMS_PRIORITY value);

    /**
     * @brief Gets the used service class.
     * @return The service class.
     */
    DLMS_SERVICE_CLASS GetServiceClass();

    /**
     * @brief Sets the used service class.
     * @param value The service class to set.
     */
    void SetServiceClass(DLMS_SERVICE_CLASS value);

    /**
     * @brief Gets the Invoke ID.
     * @return The Invoke ID.
     */
    unsigned char GetInvokeID();

    /**
     * @brief Sets the Invoke ID.
     * @param value The Invoke ID to set.
     */
    void SetInvokeID(unsigned char value);

    /**
     * @brief Gets whether to auto-increase the Invoke ID.
     * @return True to auto-increase the Invoke ID, false otherwise.
     */
    bool GetAutoIncreaseInvokeID();

    /**
     * @brief Sets whether to auto-increase the Invoke ID.
     * @param value True to auto-increase the Invoke ID, false otherwise.
     */
    void SetAutoIncreaseInvokeID(bool value);

    /**
     * @brief Gets the used authentication.
     * @return The authentication type.
     */
    DLMS_AUTHENTICATION GetAuthentication();

    /**
     * @brief Sets the used authentication.
     * @param value The authentication type to set.
     */
    void SetAuthentication(DLMS_AUTHENTICATION value);

    /**
     * @brief Gets the client address.
     * @return The client address.
     */
    unsigned long GetClientAddress();

    /**
     * @brief Sets the client address.
     * @param value The client address to set.
     */
    void SetClientAddress(unsigned long value);

    /**
     * @brief Gets the server address.
     * @return The server address.
     */
    unsigned long GetServerAddress();

    /**
     * @brief Sets the server address.
     * @param value The server address to set.
     */
    void SetServerAddress(unsigned long value);

    /**
     * @brief Gets the maximum client PDU size.
     * @return The maximum PDU size.
     */
    unsigned short GetMaxPduSize();

    /**
     * @brief Gets whether protected release is used.
     * @return True if protected release is used, false otherwise.
     */
    bool GetUseProtectedRelease();

    /**
     * @brief Sets whether protected release is used.
     * @param value True to use protected release, false otherwise.
     */
    void SetUseProtectedRelease(bool value);

    /**
     * @brief Gets whether to use UTC to normal time conversion.
     * @return True to use UTC to normal time, false otherwise.
     */
    bool GetUseUtc2NormalTime();

    /**
     * @brief Sets whether to use UTC to normal time conversion.
     * @param value True to use UTC to normal time, false otherwise.
     */
    void SetUseUtc2NormalTime(bool value);

    /**
     * @brief Gets the expected invocation counter value.
     * @return The expected invocation counter.
     */
    uint64_t GetExpectedInvocationCounter();

    /**
     * @brief Sets the expected invocation counter value.
     * @param value The expected invocation counter to set.
     */
    void SetExpectedInvocationCounter(uint64_t value);

    /**
     * @brief Gets the skipped date-time fields.
     * @return The skipped fields.
     */
    DATETIME_SKIPS GetDateTimeSkips();

    /**
     * @brief Sets the skipped date-time fields.
     * @param value The fields to skip.
     */
    void SetDateTimeSkips(DATETIME_SKIPS value);

    /**
     * @brief Gets the user ID.
     * @return The user ID.
     */
    unsigned char GetUserID();

    /**
     * @brief Sets the user ID.
     * @param value The user ID to set.
     */
    void SetUserID(unsigned char value);

    /**
     * @brief Gets the quality of service.
     * @return The quality of service.
     */
    unsigned char GetQualityOfService();

    /**
     * @brief Sets the quality of service.
     * @param value The quality of service to set.
     */
    void SetQualityOfService(unsigned char value);

    /**
     * @brief Gets the source system title.
     * @return A reference to the source system title buffer.
     */
    CGXByteBuffer &GetSourceSystemTitle();

    /**
     * @brief Sets the maximum client PDU size.
     * @param value The maximum PDU size to set.
     * @return An error code.
     */
    int SetMaxReceivePDUSize(unsigned short value);

    /**
     * @brief Gets the maximum client PDU size.
     * @return The maximum PDU size.
     */
    unsigned short GetMaxReceivePDUSize();

    /**
     * @brief Sets the GBT window size.
     * @param value The window size to set.
     * @return An error code.
     */
    int SetGbtWindowSize(unsigned char value);

    /**
     * @brief Gets the GBT window size.
     * @return The window size.
     */
    unsigned char GetGbtWindowSize();

    /**
     * @brief Gets the HDLC connection settings.
     * @return A reference to the HDLC settings.
     */
    CGXDLMSLimits &GetLimits();

    /**
     * @brief Gets the HDLC connection settings.
     * @return A reference to the HDLC settings.
     */
    CGXHdlcSettings &GetHdlcSettings();

    /**
     * @brief Gets the PLC connection settings.
     * @return A reference to the PLC settings.
     */
    CGXPlcSettings &GetPlcSettings();

    /**
     * @brief Gets the collection of objects.
     * @return A reference to the object collection.
     */
    CGXDLMSObjectCollection &GetObjects();

    /**
     * @brief Generates an SNRMRequest query.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int SNRMRequest(std::vector<CGXByteBuffer> &packets);

    /**
     * @brief Parses a UAResponse.
     * @param data The data from the meter.
     * @return An error code.
     */
    int ParseUAResponse(CGXByteBuffer &data);

    /**
     * @brief Generates an AARQRequest query.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int AARQRequest(std::vector<CGXByteBuffer> &packets);

    /**
    * @brief Parses the AARE response. Parse method will update the following data:
    * <ul>
    * <li>DLMSVersion</li>
    * <li>MaxReceivePDUSize</li>
    * <li>UseLogicalNameReferencing</li>
    * <li>LNSettings or SNSettings</li>
    * </ul>
    * LNSettings or SNSettings will be updated, depending on the referencing,
    * Logical name or Short name.
    *
    * @param data The received data.
    */
    int ParseAAREResponse(CGXByteBuffer &data);

    /**
     * @brief Gets whether authentication is required.
     * @return True if authentication is required, false otherwise.
     */
    bool IsAuthenticationRequired();

    /**
     * @brief Gets the application association request.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int GetApplicationAssociationRequest(std::vector<CGXByteBuffer> &packets);

    /**
     * @brief Parses the application association response.
     * @param reply The received reply from the server.
     * @return An error code.
     */
    int ParseApplicationAssociationResponse(CGXByteBuffer &reply);

    /**
     * @brief Generates a ReceiverReady query.
     * @param reply The reply data.
     * @param Data The data to send.
     * @return An error code.
     */
    int ReceiverReady(CGXReplyData &reply, CGXByteBuffer &Data);

    /**
     * @brief Generates a ReceiverReady query.
     * @param Type The type of the next requested packet.
     * @param Data The data to send.
     * @return An error code.
     */
    int ReceiverReady(DLMS_DATA_REQUEST_TYPES Type, CGXByteBuffer &Data);

    /**
     * @brief Changes the type of a byte array.
     * @param value The byte array.
     * @param type The target type.
     * @param useUtc Whether to use UTC.
     * @param newValue A reference to store the new value.
     * @return An error code.
     */
    static int ChangeType(CGXByteBuffer &value, DLMS_DATA_TYPE type, bool useUtc, CGXDLMSVariant &newValue);

    /**
     * @brief Changes the type of a byte array.
     * @param value The byte array.
     * @param type The target type.
     * @param newValue A reference to store the new value.
     * @return An error code.
     */
    static int ChangeType(CGXByteBuffer &value, DLMS_DATA_TYPE type, CGXDLMSVariant &newValue);

    /**
     * @brief Changes the type of a variant.
     * @param value The variant.
     * @param type The target type.
     * @param newValue A reference to store the new value.
     * @return An error code.
     */
    static int ChangeType(CGXDLMSVariant &value, DLMS_DATA_TYPE type, CGXDLMSVariant &newValue);

    /**
     * @brief Parses COSEM objects from the received data.
     * @param objects The read objects.
     * @param onlyKnownObjects True to parse only known objects, false otherwise.
     * @return An error code.
     */
    int ParseObjects(std::vector<CGXDLMSVariant> &objects, bool onlyKnownObjects);

    /**
     * @brief Parses COSEM objects from the received data.
     * @param objects The read objects.
     * @param onlyKnownObjects True to parse only known objects, false otherwise.
     * @param ignoreInactiveObjects True to ignore inactive objects, false otherwise.
     * @return An error code.
     */
    int ParseObjects(std::vector<CGXDLMSVariant> &objects, bool onlyKnownObjects, bool ignoreInactiveObjects);

    /**
     * @brief Parses COSEM objects from the received data.
     * @param data The received data.
     * @param onlyKnownObjects True to parse only known objects, false otherwise.
     * @return An error code.
     */
    int ParseObjects(CGXByteBuffer &data, bool onlyKnownObjects);

    /**
     * @brief Parses COSEM objects from the received data.
     * @param data The received data.
     * @param onlyKnownObjects True to parse only known objects, false otherwise.
     * @param ignoreInactiveObjects True to ignore inactive objects, false otherwise.
     * @return An error code.
     */
    int ParseObjects(CGXByteBuffer &data, bool onlyKnownObjects, bool ignoreInactiveObjects);

    /**
     * @brief Updates the value of an attribute.
     * @param target The target object.
     * @param attributeIndex The attribute index.
     * @param value The new value.
     * @return An error code.
     */
    int UpdateValue(CGXDLMSObject &target, int attributeIndex, CGXDLMSVariant &value);

    /**
     * @brief Gets a value from the received data.
     * @param data The received data.
     * @param value A reference to store the value.
     * @return An error code.
     */
    int GetValue(CGXByteBuffer &data, CGXDLMSVariant &value);

    /**
     * @brief Updates a list of values.
     * @param list The list of objects and attributes.
     * @param values The received values.
     * @return An error code.
     */
    int UpdateValues(std::vector<std::pair<CGXDLMSObject *, unsigned char>> &list, std::vector<CGXDLMSVariant> &values);

    /**
     * @brief Generates a release request.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReleaseRequest(std::vector<CGXByteBuffer> &packets);

    /**
     * @brief Generates a disconnect request.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int DisconnectRequest(std::vector<CGXByteBuffer> &packets);

    /**
     * @brief Gets the COSEM data from a packet.
     * @param reply The received data.
     * @param data The exported reply information.
     * @return An error code.
     */
    int GetData(CGXByteBuffer &reply, CGXReplyData &data);

    /**
     * @brief Gets the COSEM data from a packet.
     * @param reply The received data.
     * @param data The exported reply information.
     * @param notify Information from the notify message.
     * @return An error code.
     */
    int GetData(CGXByteBuffer &reply, CGXReplyData &data, CGXReplyData &notify);

    /**
     * @brief Reads the Association view from the device.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int GetObjectsRequest(std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a keep-alive message.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int GetKeepAlive(std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a read message.
     * @param name The short or logical name.
     * @param objectType The COSEM object type.
     * @param attributeOrdinal The attribute index.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int
    Read(CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int attributeOrdinal, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a read message.
     * @param pObject The COSEM object to read.
     * @param attributeOrdinal The attribute index.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Read(CGXDLMSObject *pObject, int attributeOrdinal, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Reads a list of COSEM objects.
     * @param list The list of objects to read.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadList(std::vector<std::pair<CGXDLMSObject *, unsigned char>> &list, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Writes a list of COSEM objects.
     * @param list The list of objects to write.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int WriteList(std::vector<std::pair<CGXDLMSObject *, unsigned char>> &list, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a write message.
     * @param name The short or logical name.
     * @param objectType The object type.
     * @param index The attribute index.
     * @param data The data to write.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int index, CGXDLMSVariant &data,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a write message.
     * @param name The short or logical name.
     * @param objectType The object type.
     * @param index The attribute index.
     * @param data The data to write.
     * @param parameters The selective access parameters.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int index, CGXDLMSVariant &data, CGXByteBuffer *parameters,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a write message.
     * @param name The short or logical name.
     * @param objectType The object type.
     * @param index The attribute index.
     * @param data The data to write.
     * @param parameters The selective access parameters.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int index, CGXDLMSVariant &data, CGXDLMSVariant &parameters,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a write message.
     * @param name The short or logical name.
     * @param objectType The object type.
     * @param index The attribute index.
     * @param data The data to write.
     * @param parameters The selective access parameters.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int index, CGXByteBuffer &data, CGXByteBuffer *parameters,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a write message.
     * @param name The short or logical name.
     * @param objectType The object type.
     * @param index The attribute index.
     * @param value The data to write.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(
        CGXDLMSVariant &name, DLMS_OBJECT_TYPE objectType, int index, CGXByteBuffer &value,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a write message.
     * @param pObject The COSEM object to write.
     * @param index The attribute index.
     * @param data The data to write.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(CGXDLMSObject *pObject, int index, CGXDLMSVariant &data, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a write message.
     * @param pObject The COSEM object to write.
     * @param index The attribute index.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Write(CGXDLMSObject *pObject, int index, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a Method (Action) request.
     * @param item The method object.
     * @param index The method index.
     * @param data The method data.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Method(CGXDLMSObject *item, int index, CGXDLMSVariant &data, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates a Method (Action) request.
     * @param item The method object.
     * @param index The method index.
     * @param data The method data.
     * @param dataType The data type.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Method(
        CGXDLMSObject *item, int index, CGXDLMSVariant &data, DLMS_DATA_TYPE dataType, std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a Method (Action) request.
     * @param name The method object's short or logical name.
     * @param objectType The object type.
     * @param methodIndex The method index.
     * @param data The method data.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Method(
        CGXDLMSVariant name, DLMS_OBJECT_TYPE objectType, int methodIndex, CGXDLMSVariant &data,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a Method (Action) request.
     * @param name The method object's short or logical name.
     * @param objectType The object type.
     * @param methodIndex The method index.
     * @param data The method data.
     * @param dataType The data type.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Method(
        CGXDLMSVariant name, DLMS_OBJECT_TYPE objectType, int methodIndex, CGXDLMSVariant &data,
        DLMS_DATA_TYPE dataType, std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Generates a Method (Action) request.
     * @param name The method object's short or logical name.
     * @param objectType The object type.
     * @param methodIndex The method index.
     * @param data The method data.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int Method(
        CGXDLMSVariant name, DLMS_OBJECT_TYPE objectType, int methodIndex, CGXByteBuffer &data,
        std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Reads rows by entry.
     * @param pg The profile generic object.
     * @param index The zero-based start index.
     * @param count The number of rows to read.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadRowsByEntry(CGXDLMSProfileGeneric *pg, int index, int count, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Reads rows by entry.
     * @param pg The profile generic object.
     * @param index The zero-based start index.
     * @param count The number of rows to read.
     * @param columns The columns to read.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadRowsByEntry(
        CGXDLMSProfileGeneric *pg, int index, int count,
        std::vector<std::pair<CGXDLMSObject *, CGXDLMSCaptureObject *>> &columns, std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Reads rows by range.
     * @param pObject The profile generic object.
     * @param start The start time.
     * @param end The end time.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadRowsByRange(
        CGXDLMSProfileGeneric *pObject, CGXDateTime &start, CGXDateTime &end, std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Reads rows by range.
     * @param pg The profile generic object.
     * @param start The start time.
     * @param end The end time.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadRowsByRange(CGXDLMSProfileGeneric *pg, struct tm *start, struct tm *end, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Reads rows by range.
     * @param pg The profile generic object.
     * @param start The start time.
     * @param end The end time.
     * @param columns The columns to read.
     * @param reply A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int ReadRowsByRange(
        CGXDLMSProfileGeneric *pg, struct tm *start, struct tm *end,
        std::vector<std::pair<CGXDLMSObject *, CGXDLMSCaptureObject *>> &columns, std::vector<CGXByteBuffer> &reply
    );

    /**
     * @brief Gets the negotiated conformance.
     * @return The negotiated conformance.
     */
    DLMS_CONFORMANCE GetNegotiatedConformance();

    /**
     * @brief Sets the negotiated conformance.
     * @param value The conformance to set.
     */
    void SetNegotiatedConformance(DLMS_CONFORMANCE value);

    /**
     * @brief Gets the proposed conformance.
     * @return The proposed conformance.
     */
    DLMS_CONFORMANCE GetProposedConformance();

    /**
     * @brief Sets the proposed conformance.
     * @param value The conformance to set.
     */
    void SetProposedConformance(DLMS_CONFORMANCE value);

    /**
     * @brief Gets the server address from a serial number.
     * @param serialNumber The meter's serial number.
     * @param logicalAddress The meter's logical address.
     * @param formula The formula to use.
     * @return The server address.
     */
    static int GetServerAddressFromSerialNumber(
        unsigned long serialNumber, unsigned short logicalAddress, const char *formula = NULL
    );

    /**
     * @brief Gets the server address.
     * @param logicalAddress The server's logical address.
     * @param physicalAddress The server's physical address.
     * @param addressSize The address size in bytes.
     * @return The server address.
     */
    static int
    GetServerAddress(unsigned long logicalAddress, unsigned long physicalAddress, unsigned char addressSize = 0);

    /**
     * @brief Gets the protocol version.
     * @return The protocol version.
     */
    char *GetProtocolVersion();

    /**
     * @brief Sets the protocol version.
     * @param value The protocol version to set.
     */
    void SetProtocolVersion(char *value);

    /**
     * @brief Converts an object type to a string.
     * @param type The object type.
     * @return The string representation of the object type.
     */
    static const std::string ObjectTypeToString(DLMS_OBJECT_TYPE type) {
        return CGXDLMSConverter::ToString(type);
    }

    /**
     * @brief Parses push objects.
     * @param data The data to parse.
     * @param items A reference to a vector to store the parsed items.
     * @return An error code.
     */
    int
    ParsePushObjects(std::vector<CGXDLMSVariant> &data, std::vector<std::pair<CGXDLMSObject *, unsigned char>> &items);

    /**
     * @brief Sets the custom challenge.
     * @param value The custom challenge to set.
     */
    void SetCtoSChallenge(CGXByteBuffer &value);

    /**
     * @brief Gets the custom challenge.
     * @return A reference to the custom challenge buffer.
     */
    CGXByteBuffer &GetCtoSChallenge();

    /**
     * @brief Generates an access service message.
     * @param time The send time.
     * @param list The list of access items.
     * @param packets A reference to a vector to store the generated packets.
     * @return An error code.
     */
    int AccessRequest(struct tm *time, std::vector<CGXDLMSAccessItem> &list, std::vector<CGXByteBuffer> &packets);

    /**
     * @brief Parses an access response.
     * @param list The collection of access items.
     * @param data The received data from the meter.
     * @return An error code.
     */
    int ParseAccessResponse(std::vector<CGXDLMSAccessItem> &list, CGXByteBuffer &data);

    /**
     * @brief Gets the manufacturer ID.
     * @return The manufacturer ID.
     */
    char *GetManufacturerId();

    /**
     * @brief Sets the manufacturer ID.
     * @param value The manufacturer ID to set.
     */
    void SetManufacturerId(char value[3]);

    /**
     * @brief Encrypts the Landis+Gyr high-level authentication.
     * @param password The user's password.
     * @param seed The seed received from the meter.
     * @param crypted A reference to a buffer to store the encrypted data.
     * @return An error code.
     */
    int EncryptLandisGyrHighLevelAuthentication(CGXByteBuffer &password, CGXByteBuffer &seed, CGXByteBuffer &crypted);
};
#endif  //GXDLMSCLIENT_H
