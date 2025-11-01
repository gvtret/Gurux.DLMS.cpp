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

#ifndef GXDLMSSETTINGS_H
#define GXDLMSSETTINGS_H

#include "enums.h"
#include "GXBytebuffer.h"
#include "GXDLMSLimits.h"
#include "GXPlcSettings.h"
#include "GXDLMSObjectCollection.h"
#include "GXCipher.h"

// Server sender frame sequence starting number.
const unsigned char SERVER_START_SENDER_FRAME_SEQUENCE = 0x1E;

// Server receiver frame sequence starting number.
const unsigned char SERVER_START_RECEIVER_FRAME_SEQUENCE = 0xFE;

// Client sender frame sequence starting number.
const unsigned char CLIENT_START_SENDER_FRAME_SEQUENCE = 0xFE;

// Client receiver frame sequence starting number.
const unsigned char CLIENT_START_RCEIVER_FRAME_SEQUENCE = 0xE;

// DLMS version number.
const unsigned char DLMS_VERSION = 6;

const unsigned short MAX_RECEIVE_PDU_SIZE = 0xFFFF;

/**
 * @brief Includes DLMS/COSEM communication settings.
 */
class CGXDLMSSettings {
    CGXDLMSObjectCollection m_AllocatedObjects;
    DLMS_CONNECTION_STATE m_Connected;
    bool m_UseCustomChallenge;
    CGXByteBuffer m_CtoSChallenge;
    CGXByteBuffer m_StoCChallenge;
    CGXByteBuffer m_SourceSystemTitle;
    CGXByteBuffer m_PreEstablishedSystemTitle;
    unsigned char m_InvokeID;
    bool m_AutoIncreaseInvokeID;
    int m_LongInvokeID;
    DLMS_PRIORITY m_Priority;
    DLMS_SERVICE_CLASS m_ServiceClass;
    unsigned long m_ClientAddress;
    unsigned long m_PushClientAddress;
    unsigned long m_ServerAddress;
    bool m_UseLogicalNameReferencing;
    DLMS_INTERFACE_TYPE m_InterfaceType;
    DLMS_AUTHENTICATION m_Authentication;
    CGXByteBuffer m_Password;
    CGXByteBuffer m_Kek;
    unsigned short m_Count;
    unsigned short m_Index;
    unsigned char m_DlmsVersionNumber;
    unsigned short m_MaxReceivePDUSize;
    unsigned short m_MaxServerPDUSize;
    unsigned char m_SenderFrame;
    unsigned char m_ReceiverFrame;
    bool m_Server;
    CGXDLMSLimits m_HdlcSettings;
    CGXPlcSettings m_PlcSettings;
    unsigned long m_BlockIndex;
    CGXDLMSObjectCollection m_Objects;
    CGXCipher *m_Cipher;
    int m_BlockNumberAck;
    unsigned char m_GbtWindowSize;
    DLMS_CONFORMANCE m_ProposedConformance;
    DLMS_CONFORMANCE m_NegotiatedConformance;
    char *m_ProtocolVersion;
    unsigned char m_UserId;
    unsigned char m_QualityOfService;
    bool m_UseUtc2NormalTime;
    uint64_t m_ExpectedInvocationCounter;
    unsigned char m_ExpectedSecurityPolicy;
    unsigned char m_ExpectedSecuritySuite;
    DATETIME_SKIPS m_DateTimeSkips;
    unsigned char m_Command;
    unsigned char m_CommandType;
    CGXx509Certificate m_ClientPublicKeyCertificate;
    CGXx509Certificate m_ServerPublicKeyCertificate;

public:
    /**
     * @brief Constructor.
     * @param isServer True if this is a server, false for a client.
     */
    CGXDLMSSettings(bool isServer);

    /**
     * @brief Destructor.
     */
    ~CGXDLMSSettings();

    /**
     * @brief Gets the client-to-server challenge.
     * @return A reference to the challenge buffer.
     */
    CGXByteBuffer &GetCtoSChallenge();

    /**
     * @brief Sets the client-to-server challenge.
     * @param value The challenge to set.
     */
    void SetCtoSChallenge(CGXByteBuffer &value);

    /**
     * @brief Gets the server-to-client challenge.
     * @return A reference to the challenge buffer.
     */
    CGXByteBuffer &GetStoCChallenge();

    /**
     * @brief Sets the server-to-client challenge.
     * @param value The challenge to set.
     */
    void SetStoCChallenge(CGXByteBuffer &value);

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
     * @brief Gets the password.
     * @return A reference to the password buffer.
     */
    CGXByteBuffer &GetPassword();

    /**
     * @brief Sets the password.
     * @param value The password to set.
     */
    void SetPassword(CGXByteBuffer &value);

    /**
     * @brief Gets the DLMS version number.
     * @return The DLMS version number.
     */
    unsigned char GetDlmsVersionNumber();

    /**
     * @brief Sets the DLMS version number.
     * @param value The version number to set.
     */
    void SetDlmsVersionNumber(unsigned char value);

    /**
     * @brief Resets the frame sequence.
     */
    void ResetFrameSequence();

    /**
     * @brief Checks the frame.
     * @param frame The frame to check.
     * @return True if the frame is valid, false otherwise.
     */
    bool CheckFrame(unsigned char frame);

    /**
     * @brief Gets the next send frame.
     * @param first True if this is the first frame, false otherwise.
     * @return The next send frame.
     */
    unsigned char GetNextSend(unsigned char first);

    /**
     * @brief Gets the receiver ready frame.
     * @return The receiver ready frame.
     */
    unsigned char GetReceiverReady();

    /**
     * @brief Gets the keep-alive frame.
     * @return The keep-alive frame.
     */
    unsigned char GetKeepAlive();

    /**
     * @brief Gets the current block index.
     * @return The block index.
     */
    unsigned long GetBlockIndex();

    /**
     * @brief Sets the current block index.
     * @param value The block index to set.
     */
    void SetBlockIndex(unsigned long value);

    /**
     * @brief Resets the block index.
     */
    void ResetBlockIndex();

    /**
     * @brief Increases the block index.
     */
    void IncreaseBlockIndex();

    /**
     * @brief Gets whether this is a server.
     * @return True if this is a server, false for a client.
     */
    bool IsServer();

    /**
     * @brief Gets the HDLC connection settings.
     * @return A reference to the HDLC settings.
     */
    CGXDLMSLimits &GetHdlcSettings();

    /**
     * @brief Gets the PLC connection settings.
     * @return A reference to the PLC settings.
     */
    CGXPlcSettings &GetPlcSettings();

    /**
     * @brief Gets the used interface type.
     * @return The interface type.
     */
    DLMS_INTERFACE_TYPE GetInterfaceType();

    /**
     * @brief Sets the used interface type.
     * @param value The interface type to set.
     */
    void SetInterfaceType(DLMS_INTERFACE_TYPE value);

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
     * @brief Gets the DLMS version number.
     * @return The DLMS version number.
     */
    unsigned char GetDLMSVersion();

    /**
     * @brief Sets the DLMS version number.
     * @param value The version number to set.
     */
    void SetDLMSVersion(unsigned char value);

    /**
     * @brief Gets the maximum PDU size.
     * @return The maximum PDU size.
     */
    unsigned short GetMaxPduSize();

    /**
     * @brief Sets the maximum receive PDU size.
     * @param value The maximum PDU size.
     * @return An error code.
     */
    int SetMaxReceivePDUSize(unsigned short value);

    /**
     * @brief Gets the maximum server PDU size.
     * @return The maximum server PDU size.
     */
    unsigned short GetMaxServerPDUSize();

    /**
     * @brief Sets the maximum server PDU size.
     * @param value The maximum server PDU size.
     * @return An error code.
     */
    int SetMaxServerPDUSize(unsigned short value);

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
     * @brief Updates the Invoke ID.
     * @param value The Invoke ID to update.
     */
    void UpdateInvokeId(unsigned char value);

    /**
     * @brief Gets the long Invoke ID.
     * @return The long Invoke ID.
     */
    unsigned long GetLongInvokeID();

    /**
     * @brief Sets the long Invoke ID.
     * @param value The long Invoke ID to set.
     * @return An error code.
     */
    int SetLongInvokeID(unsigned long value);

    /**
     * @brief Gets the collection of objects.
     * @return A reference to the object collection.
     */
    CGXDLMSObjectCollection &GetObjects();

    /**
     * @brief Gets whether custom challenges are used.
     * @return True if custom challenges are used, false otherwise.
     */
    bool GetUseCustomChallenge();

    /**
     * @brief Sets whether custom challenges are used.
     * @param value True to use custom challenges, false otherwise.
     */
    void SetUseCustomChallenge(bool value);

    /**
     * @brief Gets the connection state.
     * @return The connection state.
     */
    DLMS_CONNECTION_STATE GetConnected();

    /**
     * @brief Sets the connection state.
     * @param value The connection state to set.
     */
    void SetConnected(DLMS_CONNECTION_STATE value);

    /**
     * @brief Gets the ciphering interface.
     * @return A pointer to the ciphering interface.
     */
    CGXCipher *GetCipher();

    /**
     * @brief Sets the ciphering interface.
     * @param value A pointer to the ciphering interface.
     */
    void SetCipher(CGXCipher *value);

    /**
     * @brief Gets the source system title.
     * @return A reference to the source system title buffer.
     */
    CGXByteBuffer &GetSourceSystemTitle();

    /**
     * @brief Sets the source system title.
     * @param value The source system title to set.
     * @return An error code.
     */
    int SetSourceSystemTitle(CGXByteBuffer &value);

    /**
     * @brief Gets the pre-established system title.
     * @return A reference to the pre-established system title buffer.
     */
    CGXByteBuffer &GetPreEstablishedSystemTitle();

    /**
     * @brief Sets the pre-established system title.
     * @param value The pre-established system title to set.
     * @return An error code.
     */
    int SetPreEstablishedSystemTitle(CGXByteBuffer &value);

    /**
     * @brief Gets the Key Encrypting Key (KEK).
     * @return A reference to the KEK buffer.
     */
    CGXByteBuffer &GetKek();

    /**
     * @brief Sets the Key Encrypting Key (KEK).
     * @param value The KEK to set.
     */
    void SetKek(CGXByteBuffer &value);

    /**
     * @brief Gets the long data count.
     * @return The long data count.
     */
    unsigned short GetCount();

    /**
     * @brief Sets the long data count.
     * @param value The long data count to set.
     */
    void SetCount(unsigned short value);

    /**
     * @brief Gets the long data index.
     * @return The long data index.
     */
    unsigned short GetIndex();

    /**
     * @brief Sets the long data index.
     * @param value The long data index to set.
     */
    void SetIndex(unsigned short value);

    /**
     * @brief Gets the negotiated conformance.
     * @return The negotiated conformance.
     */
    DLMS_CONFORMANCE GetNegotiatedConformance();

    /**
     * @brief Sets the negotiated conformance.
     * @param value The negotiated conformance to set.
     */
    void SetNegotiatedConformance(DLMS_CONFORMANCE value);

    /**
     * @brief Gets the proposed conformance.
     * @return The proposed conformance.
     */
    DLMS_CONFORMANCE GetProposedConformance();

    /**
     * @brief Sets the proposed conformance.
     * @param value The proposed conformance to set.
     */
    void SetProposedConformance(DLMS_CONFORMANCE value);

    /**
     * @brief Gets the protocol version.
     * @return The protocol version.
     */
    char *GetProtocolVersion();

    /**
     * @brief Sets the protocol version.
     * @param value The protocol version to set.
     */
    void SetProtocolVersion(const char *value);

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
     * @brief Gets the expected invocation counter.
     * @return The expected invocation counter.
     */
    uint64_t GetExpectedInvocationCounter();

    /**
     * @brief Sets the expected invocation counter.
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
     * @brief Sets the expected security suite.
     * @param value The expected security suite to set.
     */
    void SetExpectedSecuritySuite(unsigned char value);

    /**
     * @brief Gets the expected security suite.
     * @return The expected security suite.
     */
    unsigned char GetExpectedSecuritySuite();

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
     * @brief Gets the block number acknowledged in GBT.
     * @return The block number acknowledged.
     */
    int GetBlockNumberAck();

    /**
     * @brief Sets the block number acknowledged in GBT.
     * @param value The block number acknowledged.
     */
    void SetBlockNumberAck(int value);

    /**
     * @brief Gets the GBT window size.
     * @return The GBT window size.
     */
    unsigned char GetGbtWindowSize();

    /**
     * @brief Sets the GBT window size.
     * @param value The GBT window size.
     */
    void SetGbtWindowSize(unsigned char value);

    /**
     * @brief Gets the last executed command.
     * @return The last executed command.
     */
    unsigned char GetCommand();

    /**
     * @brief Sets the last executed command.
     * @param value The command to set.
     */
    void SetCommand(unsigned char value);

    /**
     * @brief Gets the last executed command type.
     * @return The command type.
     */
    unsigned char GetCommandType();

    /**
     * @brief Sets the last executed command type.
     * @param value The command type to set.
     */
    void SetCommandType(unsigned char value);

    /**
     * @brief Adds a dynamically allocated object.
     * @param pObj A pointer to the object to add.
     */
    void AddAllocateObject(CGXDLMSObject *pObj);

    /**
     * @brief Gets the client's public key certificate.
     * @return A reference to the client's certificate.
     */
    CGXx509Certificate &GetClientPublicKeyCertificate();

    /**
     * @brief Sets the client's public key certificate.
     * @param cert The client's certificate to set.
     */
    void SetClientPublicKeyCertificate(CGXx509Certificate &cert);

    /**
     * @brief Gets the server's public key certificate.
     * @return A reference to the server's certificate.
     */
    CGXx509Certificate &GetServerPublicKeyCertificate();

    /**
     * @brief Sets the server's public key certificate.
     * @param cert The server's certificate to set.
     */
    void SetServerPublicKeyCertificate(CGXx509Certificate &cert);
};

#endif  //GXDLMSSETTINGS_H
