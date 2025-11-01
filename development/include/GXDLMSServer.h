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

#ifndef GXDLMSSERVER_H
#define GXDLMSSERVER_H

#include <vector>
#include "GXDLMSLongTransaction.h"
#include "GXReplyData.h"
#include "GXDLMSSettings.h"
#include "GXSNInfo.h"
#include "GXDLMSSNParameters.h"
#include "GXDLMSLNParameters.h"
#include "GXDLMSConnectionEventArgs.h"
#include "GXDLMSHdlcSetup.h"
#include "GXDLMSTcpUdpSetup.h"
#include "GXDLMSAssociationLogicalName.h"
#include "GXDLMSAssociationShortName.h"
#include "GXDLMSPushSetup.h"

class CGXDLMSProfileGeneric;
class CGXServerReply;

/**
 * @brief Represents a DLMS/COSEM server.
 */
class CGXDLMSServer {
    friend class CGXDLMSProfileGeneric;
    friend class CGXDLMSValueEventArg;
    friend class CGXDLMSAssociationLogicalName;
    friend class CGXDLMSAssociationShortName;
    friend class CGXDLMSLNCommandHandler;
    friend class CGXDLMSSNCommandHandler;

private:
    long m_DataReceived;
#ifndef DLMS_IGNORE_IEC_HDLC_SETUP
    CGXDLMSIecHdlcSetup *m_Hdlc;
#endif  //DLMS_IGNORE_IEC_HDLC_SETUP
#ifndef DLMS_IGNORE_TCP_UDP_SETUP
    CGXDLMSTcpUdpSetup *m_Wrapper;
#endif  //DLMS_IGNORE_TCP_UDP_SETUP
    CGXReplyData m_Info;
    /**
     * @brief Received data.
     */
    CGXByteBuffer m_ReceivedData;

    /**
     * @brief Reply data.
     */
    CGXByteBuffer m_ReplyData;

    /**
     * @brief Long get or read transaction information.
     */
    CGXDLMSLongTransaction *m_Transaction;

    /**
     * @brief Is server initialized.
     */
    bool m_Initialized;

    /**
     * @brief Parses an SNRM Request.
     * @param settings The DLMS settings.
     * @param data The request data.
     * @param reply A buffer to store the reply.
     * @return An error code.
     */
    int HandleSnrmRequest(CGXDLMSSettings &settings, CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Resets settings when a connection is made or closed.
     * @param connected True if connected, false otherwise.
     */
    void Reset(bool connected);

    int ReportError(DLMS_COMMAND command, DLMS_ERROR_CODE error, CGXByteBuffer &reply);

    /**
     * @brief Generates a confirmed service error.
     * @param service The confirmed service error.
     * @param type The service error type.
     * @param code The error code.
     * @param data A buffer to store the generated error data.
     */
    static void GenerateConfirmedServiceError(
        DLMS_CONFIRMED_SERVICE_ERROR service, DLMS_SERVICE_ERROR type, unsigned char code, CGXByteBuffer &data
    );

    /**
     * @brief Handles a received command.
     * @param cmd The command to handle.
     * @param data The command data.
     * @param sr The server reply.
     * @param cipheredCommand The ciphered command.
     * @return An error code.
     */
    int HandleCommand(DLMS_COMMAND cmd, CGXByteBuffer &data, CGXServerReply &sr, unsigned char cipheredCommand);

    /**
     * @brief Parses an AARQ request and returns an AARE request.
     * @param data The request data.
     * @param connectionInfo The connection information.
     * @return An error code.
     */
    int HandleAarqRequest(CGXByteBuffer &data, CGXDLMSConnectionEventArgs &connectionInfo);

    /**
     * @brief Counts how many rows can fit into one PDU.
     * @param pg The profile generic object.
     * @return The number of rows that can fit.
     */
    unsigned short GetRowsToPdu(CGXDLMSProfileGeneric *pg);

    /**
     * @brief Updates short names.
     * @param force True to force an update, false otherwise.
     * @return An error code.
     */
    int UpdateShortNames(bool force);

    /**
     * @brief Handles a release request.
     * @param data The request data.
     * @return An error code.
     */
    int HandleReleaseRequest(CGXByteBuffer &data);

    int AddData(CGXDLMSObject *obj, unsigned char index, CGXByteBuffer &buff);

    /**
     * @brief Handles a General Block Transfer (GBT).
     * @param sr The server reply.
     * @param data The request data.
     * @param cipheredCommand The ciphered command.
     * @return An error code.
     */
    int HandleGeneralBlockTransfer(CGXServerReply &sr, CGXByteBuffer &data, unsigned char cipheredCommand);

protected:
    /**
     * @brief Server Settings.
     */
    CGXDLMSSettings m_Settings;

    /**
     * @brief Sets the ciphering interface.
     * @param value The ciphering interface.
     */
    void SetCipher(CGXCipher *value);

    /**
     * @brief Gets the settings.
     * @return A reference to the settings.
     */
    CGXDLMSSettings &GetSettings();

    /**
     * @brief Checks if data is sent to this server.
     * @param serverAddress The server address.
     * @param clientAddress The client address.
     * @return True if data is sent to this server, false otherwise.
     */
    virtual bool IsTarget(unsigned long int serverAddress, unsigned long clientAddress) = 0;

    /**
     * @brief Validates authentication.
     * @param authentication The authentication level.
     * @param password The password.
     * @return The source diagnostic.
     */
    virtual DLMS_SOURCE_DIAGNOSTIC
    ValidateAuthentication(DLMS_AUTHENTICATION authentication, CGXByteBuffer &password) = 0;

    /**
     * @brief Finds an object.
     * @param objectType The object type.
     * @param sn The short name.
     * @param ln The logical name.
     * @return A pointer to the found object, or NULL if not found.
     */
    virtual CGXDLMSObject *FindObject(DLMS_OBJECT_TYPE objectType, int sn, std::string &ln) = 0;

    /**
     * @brief Called before reading selected items.
     * @param args The read requests to handle.
     */
    virtual void PreRead(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called before writing selected items.
     * @param args The write requests to handle.
     */
    virtual void PreWrite(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called when a connection is made.
     * @param connectionInfo The connection information.
     */
    virtual void Connected(CGXDLMSConnectionEventArgs &connectionInfo) = 0;

    /**
     * @brief Called when an invalid connection attempt is made.
     * @param connectionInfo The connection information.
     */
    virtual void InvalidConnection(CGXDLMSConnectionEventArgs &connectionInfo) = 0;

    /**
     * @brief Called when the server disconnects.
     * @param connectionInfo The connection information.
     */
    virtual void Disconnected(CGXDLMSConnectionEventArgs &connectionInfo) = 0;

    /**
     * @brief Gets the attribute access mode.
     * @param arg The value event argument.
     * @return The access mode.
     */
    virtual DLMS_ACCESS_MODE GetAttributeAccess(CGXDLMSValueEventArg *arg) = 0;

    /**
     * @brief Gets the method access mode.
     * @param arg The value event argument.
     * @return The method access mode.
     */
    virtual DLMS_METHOD_ACCESS_MODE GetMethodAccess(CGXDLMSValueEventArg *arg) = 0;

    /**
     * @brief Called before an action is occurred.
     * @param args The action requests to handle.
     */
    virtual void PreAction(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called after reading selected items.
     * @param args The handled read requests.
     */
    virtual void PostRead(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called after writing selected items.
     * @param args The handled write requests.
     */
    virtual void PostWrite(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called after an action is occurred.
     * @param args The handled action requests.
     */
    virtual void PostAction(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called before getting selected values.
     * @param args The value event arguments.
     */
    virtual void PreGet(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Called after getting selected values.
     * @param args The value event arguments.
     */
    virtual void PostGet(std::vector<CGXDLMSValueEventArg *> &args) = 0;

    /**
     * @brief Updates short names.
     * @return An error code.
     */
    int UpdateShortNames();

    int HandleRequest(CGXServerReply &sr);

public:
#ifndef DLMS_IGNORE_IEC_HDLC_SETUP
    /**
     * @brief Gets the HDLC settings.
     * @return A pointer to the HDLC settings.
     */
    CGXDLMSIecHdlcSetup *GetHdlc();

    /**
     * @brief Sets the HDLC settings.
     * @param value A pointer to the HDLC settings.
     */
    void SetHdlc(CGXDLMSIecHdlcSetup *value);
#endif  //DLMS_IGNORE_IEC_HDLC_SETUP
#ifndef DLMS_IGNORE_TCP_UDP_SETUP
    /**
     * @brief Gets the wrapper settings.
     * @return A pointer to the wrapper settings.
     */
    CGXDLMSTcpUdpSetup *GetWrapper();

    /**
     * @brief Sets the wrapper settings.
     * @param value A pointer to the wrapper settings.
     */
    void SetWrapper(CGXDLMSTcpUdpSetup *value);
#endif  //DLMS_IGNORE_TCP_UDP_SETUP

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
     * @brief Gets the expected security policy.
     * @return The expected security policy.
     */
    unsigned char GetExpectedSecurityPolicy();

    /**
     * @brief Sets the expected security policy.
     * @param value The expected security policy to set.
     */
    void SetExpectedSecurityPolicy(unsigned char value);

    /**
     * @brief Gets the expected security suite.
     * @return The expected security suite.
     */
    unsigned char GetExpectedSecuritySuite();

    /**
     * @brief Sets the expected security suite.
     * @param value The expected security suite to set.
     */
    void SetExpectedSecuritySuite(unsigned char value);

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
     * @brief Gets the server-to-client challenge.
     * @return A reference to the challenge buffer.
     */
    CGXByteBuffer &GetStoCChallenge();

    /**
     * @brief Sets the server-to-client custom challenge.
     * @param value The challenge to set.
     */
    void SetStoCChallenge(CGXByteBuffer &value);

    /**
     * @brief Gets the interface type.
     * @return The interface type.
     */
    DLMS_INTERFACE_TYPE GetInterfaceType();

    /**
     * @brief Sets the starting packet index.
     * @param value The starting index.
     */
    void SetStartingPacketIndex(int value);

    /**
     * @brief Gets the Invoke ID.
     * @return The Invoke ID.
     */
    int GetInvokeID();

    /**
     * @brief Constructor.
     * @param logicalNameReferencing True to use logical name referencing, false otherwise.
     * @param type The interface type.
     */
    CGXDLMSServer(bool logicalNameReferencing, DLMS_INTERFACE_TYPE type);

#ifndef DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
    /**
     * @brief Constructor.
     * @param ln The logical name settings.
     * @param hdlc The HDLC settings.
     */
    CGXDLMSServer(CGXDLMSAssociationLogicalName *ln, CGXDLMSIecHdlcSetup *hdlc);

    /**
     * @brief Constructor.
     * @param ln The logical name settings.
     * @param wrapper The WRAPPER settings.
     */
    CGXDLMSServer(CGXDLMSAssociationLogicalName *ln, CGXDLMSTcpUdpSetup *wrapper);

#endif  //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME

#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    /**
     * @brief Constructor.
     * @param sn The short name settings.
     * @param hdlc The HDLC settings.
     */
    CGXDLMSServer(CGXDLMSAssociationShortName *sn, CGXDLMSIecHdlcSetup *hdlc);

    /**
     * @brief Constructor.
     * @param sn The short name settings.
     * @param wrapper The WRAPPER settings.
     */
    CGXDLMSServer(CGXDLMSAssociationShortName *sn, CGXDLMSTcpUdpSetup *wrapper);

#endif  //DLMS_IGNORE_ASSOCIATION_SHORT_NAME

    /**
     * @brief Destructor.
     */
    ~CGXDLMSServer();

    /**
     * @brief Gets the push client address.
     * @return The push client address.
     */
    unsigned long GetPushClientAddress();

    /**
     * @brief Sets the push client address.
     * @param value The push client address to set.
     */
    void SetPushClientAddress(unsigned long value);

    /**
     * @brief Gets the list of items.
     * @return A reference to the list of items.
     */
    CGXDLMSObjectCollection &GetItems();

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
     * @brief Gets the maximum size of a received PDU.
     * @return The maximum PDU size.
     */
    unsigned short GetMaxReceivePDUSize();

    /**
     * @brief Sets the maximum size of a received PDU.
     * @param value The maximum PDU size.
     */
    void SetMaxReceivePDUSize(unsigned short value);

    /**
     * @brief Gets whether logical name referencing is used.
     * @return True if logical name referencing is used, false otherwise.
     */
    bool GetUseLogicalNameReferencing();

    /**
     * @brief Sets whether logical name referencing is used.
     * @param value True to use logical name referencing, false otherwise.
     */
    void SetUseLogicalNameReferencing(bool value);

    /**
     * @brief Initializes the server.
     * @return An error code.
     */
    int Initialize();

    /**
     * @brief Resets the server.
     */
    void Reset();

    /**
     * @brief Handles a client request.
     * @param data The request data.
     * @param reply A buffer to store the reply.
     * @return An error code.
     */
    int HandleRequest(CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Handles a client request.
     * @param connectionInfo The connection information.
     * @param data The request data.
     * @param reply A buffer to store the reply.
     * @return An error code.
     */
    int HandleRequest(CGXDLMSConnectionEventArgs &connectionInfo, CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Handles a client request.
     * @param data The request data.
     * @param size The size of the data.
     * @param reply A buffer to store the reply.
     * @return An error code.
     */
    int HandleRequest(unsigned char *data, unsigned short size, CGXByteBuffer &reply);

    /**
     * @brief Handles a client request.
     * @param connectionInfo The connection information.
     * @param data The request data.
     * @param size The size of the data.
     * @param reply A buffer to store the reply.
     * @return An error code.
     */
    int HandleRequest(
        CGXDLMSConnectionEventArgs &connectionInfo, unsigned char *data, unsigned short size, CGXByteBuffer &reply
    );

    /**
     * @brief Gets the conformance.
     * @return The conformance.
     */
    DLMS_CONFORMANCE GetConformance();

    /**
     * @brief Sets the conformance.
     * @param value The conformance to set.
     */
    void SetConformance(DLMS_CONFORMANCE value);

    /**
     * @brief Generates data notification messages.
     * @param time The time of the notification.
     * @param data The notification data.
     * @param reply A vector to store the generated messages.
     * @return An error code.
     */
    int GenerateDataNotificationMessages(struct tm *time, CGXByteBuffer &data, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates data notification messages.
     * @param date The date of the notification.
     * @param objects The objects to include in the notification.
     * @param reply A vector to store the generated messages.
     * @return An error code.
     */
    int GenerateDataNotificationMessages(
        struct tm *date, std::vector<std::pair<CGXDLMSObject *, unsigned char>> &objects,
        std::vector<CGXByteBuffer> &reply
    );

#ifndef DLMS_IGNORE_PUSH_SETUP
    /**
     * @brief Generates push setup messages.
     * @param date The date of the push.
     * @param push The push setup object.
     * @param reply A vector to store the generated messages.
     * @return An error code.
     */
    int GeneratePushSetupMessages(struct tm *date, CGXDLMSPushSetup *push, std::vector<CGXByteBuffer> &reply);
#endif  //DLMS_IGNORE_PUSH_SETUP
};
#endif  //GXDLMSSERVER_H
