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

#ifndef GXDLMS_H
#define GXDLMS_H

#include "GXDLMSLimits.h"
#include "GXDLMSObject.h"
#include "GXDLMSObjectCollection.h"
#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"
#include "GXDLMSVariant.h"
#include "GXCipher.h"
#include "GXReplyData.h"
#include "GXDLMSLNParameters.h"
#include "GXDLMSSNParameters.h"

/**
 * @brief Provides the core functionality for the DLMS/COSEM communication protocol.
 *
 * This class contains static methods for handling the various layers of the
 * DLMS/COSEM protocol, including framing (HDLC, WRAPPER), PDU parsing, and
 * handling of different service requests and responses. It is a central utility
 * class used by both client and server implementations.
 */
class CGXDLMS {
private:
    friend class CGXDLMSClient;
    friend class CGXDLMSServer;

    static int AppendMultipleSNBlocks(CGXDLMSSNParameters &p, CGXByteBuffer &reply);

    static unsigned short CountFCS16(CGXByteBuffer &buff, int index, int count);
    static uint32_t CountFCS24(unsigned char *buff, int index, int count);

    static int GetAddress(long value, unsigned long &address, int &size);
    static int GetAddressBytes(unsigned long value, CGXByteBuffer &bytes);

    static bool UseHdlc(DLMS_INTERFACE_TYPE type);
    static bool IsReplyMessage(DLMS_COMMAND cmd);
    static void GetLLCBytes(bool server, CGXByteBuffer &data);
    static int CheckWrapperAddress(CGXDLMSSettings &settings, CGXByteBuffer &buff, CGXReplyData *notify);
    static int GetValueFromData(CGXDLMSSettings &settings, CGXReplyData &reply);
    static void GetDataFromFrame(CGXByteBuffer &reply, CGXReplyData &info, bool hdlc);
    static int GetMBusData(CGXDLMSSettings &settings, CGXByteBuffer &buff, CGXReplyData &data);
    static int GetPlcData(CGXDLMSSettings &settings, CGXByteBuffer &buff, CGXReplyData &data);
    static int GetPlcHdlcData(CGXDLMSSettings &settings, CGXByteBuffer &buff, CGXReplyData &data, unsigned char *frame);
    static int ReadResponseDataBlockResult(CGXDLMSSettings &settings, CGXReplyData &reply, int index);
    static int HandleGloDedRequest(CGXDLMSSettings &settings, CGXReplyData &data);
    static int HandleGloDedResponse(CGXDLMSSettings &settings, CGXReplyData &data, int index);
    static int HandleGeneralCiphering(CGXDLMSSettings &settings, CGXReplyData &data);
    static int HandleGetResponseWithList(CGXDLMSSettings &settings, CGXReplyData &reply);

public:
    /**
     * @brief Checks the initialization parameters of the DLMS settings.
     * @param settings The DLMS settings object to check.
     * @return 0 on success, or an error code.
     */
    static int CheckInit(CGXDLMSSettings &settings);

    /**
     * @brief Generates all required messages for a Logical Name (LN) referencing request.
     * @param p The LN parameters describing the request.
     * @param[out] reply A vector where the generated message frames will be stored.
     * @return 0 on success, or an error code.
     */
    static int GetLnMessages(CGXDLMSLNParameters &p, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Generates all required messages for a Short Name (SN) referencing request.
     * @param p The SN parameters describing the request.
     * @param[out] reply A vector where the generated message frames will be stored.
     * @return 0 on success, or an error code.
     */
    static int GetSnMessages(CGXDLMSSNParameters &p, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Handles a General Block Transfer (GBT) message.
     * @param settings The DLMS settings.
     * @param data The received reply data containing the GBT block.
     * @return 0 on success, or an error code.
     */
    static int HandleGbt(CGXDLMSSettings &settings, CGXReplyData &data);

    /**
     * @brief Creates a WRAPPER frame for a given PDU.
     * @param settings The DLMS settings.
     * @param command The DLMS command of the PDU.
     * @param data The PDU data to be wrapped.
     * @param[out] reply The resulting WRAPPER frame.
     * @return 0 on success, or an error code.
     */
    static int GetWrapperFrame(CGXDLMSSettings &settings, DLMS_COMMAND command, CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Generates the next PDU for a multi-part Logical Name (LN) request.
     * @param p The LN parameters.
     * @param[out] reply The generated PDU.
     * @return 0 on success, or an error code.
     */
    static int GetLNPdu(CGXDLMSLNParameters &p, CGXByteBuffer &reply);

    /**
     * @brief Generates the next PDU for a multi-part Short Name (SN) request.
     * @param p The SN parameters.
     * @param[out] reply The generated PDU.
     * @return 0 on success, or an error code.
     */
    static int GetSNPdu(CGXDLMSSNParameters &p, CGXByteBuffer &reply);

    /**
     * @brief Generates a Receiver Ready (RR) acknowledgment frame.
     * @param settings The DLMS settings.
     * @param type The type of acknowledgment requested.
     * @param cipher The ciphering object, if security is active.
     * @param[out] reply The generated RR frame.
     * @return 0 on success, or an error code.
     */
    static int ReceiverReady(CGXDLMSSettings &settings, DLMS_DATA_REQUEST_TYPES type, CGXCipher *cipher, CGXByteBuffer &reply);

    /**
     * @brief Generates a Receiver Ready (RR) acknowledgment based on received data.
     * @param settings The DLMS settings.
     * @param data The received data that prompts the acknowledgment.
     * @param cipher The ciphering object.
     * @param[out] reply The generated RR frame.
     * @return 0 on success, or an error code.
     */
    static int ReceiverReady(CGXDLMSSettings &settings, CGXReplyData &data, CGXCipher *cipher, CGXByteBuffer &reply);

    /**
     * @brief Creates an HDLC frame.
     * @param settings The DLMS settings.
     * @param frame The frame ID. A new one is generated if this is zero.
     * @param data The data payload for the frame.
     * @param[out] reply The resulting HDLC frame.
     * @return 0 on success, or an error code.
     */
    static int GetHdlcFrame(CGXDLMSSettings &settings, unsigned char frame, CGXByteBuffer *data, CGXByteBuffer &reply);

    /**
     * @brief Extracts data from an HDLC frame.
     * @param server A flag indicating if this is running on a server.
     * @param settings The DLMS settings.
     * @param reply The received HDLC frame.
     * @param[out] data The extracted data and reply information.
     * @param[out] frame The frame ID.
     * @param notify Optional object for notifications.
     * @return 0 on success, or an error code.
     */
    static int GetHdlcData(
        bool server, CGXDLMSSettings &settings, CGXByteBuffer &reply, CGXReplyData &data, unsigned char &frame,
        CGXReplyData *notify
    );

    /**
     * @brief Creates a MAC layer frame with LLC.
     * @param settings The DLMS settings.
     * @param frame The HDLC frame sequence number.
     * @param creditFields Credit fields for flow control.
     * @param data The data payload.
     * @param[out] reply The resulting MAC frame.
     * @return 0 on success, or an error code.
     */
    static int GetMacFrame(
        CGXDLMSSettings &settings, unsigned char frame, unsigned char creditFields, CGXByteBuffer *data,
        CGXByteBuffer &reply
    );

    /**
     * @brief Creates a PLC frame.
     * @param settings DLMS settings.
     * @param creditFields Credit fields.
     * @param data Data to add.
     * @param[out] reply The PLC frame.
     * @return 0 on success, or an error code.
     */
    static int GetPlcFrame(CGXDLMSSettings &settings, unsigned char creditFields, CGXByteBuffer *data, CGXByteBuffer &reply);

    /**
     * @brief Creates a MAC layer frame with embedded HDLC.
     * @param settings DLMS settings.
     * @param frame HDLC frame.
     * @param creditFields Credit fields.
     * @param data Data to add.
     * @param[out] reply MAC frame.
     * @return 0 on success, or an error code.
     */
    static int GetMacHdlcFrame(
        CGXDLMSSettings &settings, unsigned char frame, unsigned char creditFields, CGXByteBuffer *data,
        CGXByteBuffer &reply
    );

    /**
     * @brief Extracts the HDLC address from a byte buffer.
     * @param buff The byte buffer.
     * @param[out] address The extracted HDLC address.
     * @return 0 on success, or an error code.
     */
    static int GetHDLCAddress(CGXByteBuffer &buff, unsigned long &address);

    /**
     * @brief Checks if the client and server addresses in an HDLC frame are correct.
     * @param server True if running on a server.
     * @param settings The DLMS settings.
     * @param reply The received data.
     * @param index The current position in the buffer.
     * @param[out] source The source address from the frame.
     * @param[out] target The target address from the frame.
     * @return 0 if addresses match, or an error code.
     */
    static int CheckHdlcAddress(
        bool server, CGXDLMSSettings &settings, CGXByteBuffer &reply, int index, unsigned long &source,
        unsigned long &target
    );

    /**
     * @brief Extracts PDU data from a TCP/IP (WRAPPER) frame.
     * @param settings The DLMS settings.
     * @param buff The received data buffer.
     * @param[out] data The extracted data and reply information.
     * @param notify Optional object for notifications.
     * @return 0 on success, or an error code.
     */
    static int GetTcpData(CGXDLMSSettings &settings, CGXByteBuffer &buff, CGXReplyData &data, CGXReplyData *notify);

    /** @brief Handles a read response, processing data blocks and errors. @param settings DLMS settings. @param data Received data. @param index Current position. @return 0 on success. */
    static int HandleReadResponse(CGXDLMSSettings &settings, CGXReplyData &data, int index);
    /** @brief Adds an invoke ID to the XML translator log. @return 0 on success. */
    static int AddInvokeId(CGXDLMSTranslatorStructure *xml, DLMS_COMMAND command, uint8_t type, uint32_t invokeId);
    /** @brief Handles a method response. @param settings DLMS settings. @param data Received data. @param index Current position. @return 0 on success. */
    static int HandleMethodResponse(CGXDLMSSettings &settings, CGXReplyData &data, unsigned long index);
    /** @brief Handles a push (event notification) request. @param reply Received data. @return 0 on success. */
    static int HandlePush(CGXReplyData &reply);
    /** @brief Handles a set response. @param settings DLMS settings. @param data Received data. @return 0 on success. */
    static int HandleSetResponse(CGXDLMSSettings &settings, CGXReplyData &data);
    /** @brief Handles an access response. @param settings DLMS settings. @param reply Received data. @return 0 on success. */
    static int HandleAccessResponse(CGXDLMSSettings &settings, CGXReplyData &reply);
    /** @brief Handles a data notification. @param settings DLMS settings. @param reply Received data. @return 0 on success. */
    static int HandleDataNotification(CGXDLMSSettings &settings, CGXReplyData &reply);
    /** @brief Handles a write response. @param data Received data. @return 0 on success. */
    static int HandleWriteResponse(CGXReplyData &data);
    /** @brief Handles a normal Get-Response. @param settings DLMS settings. @param reply Received data. @param[out] empty True if response is empty. @return 0 on success. */
    static int HandleGetResponseNormal(CGXDLMSSettings &settings, CGXReplyData &reply, bool &empty);
    /** @brief Handles a Get-Response for the next data block. @param settings DLMS settings. @param reply Received data. @param index Block index. @return 0 on success. */
    static int HandleGetResponseNextDataBlock(CGXDLMSSettings &settings, CGXReplyData &reply, int index);
    /** @brief Handles a Get-Response, including data blocks. @param settings DLMS settings. @param reply Received data. @param index Block index. @return 0 on success. */
    static int HandleGetResponse(CGXDLMSSettings &settings, CGXReplyData &reply, int index);

    /**
     * @brief Extracts the PDU from a received frame, handling decryption if necessary.
     * @param settings The DLMS settings.
     * @param data The received reply data.
     * @return 0 on success, or an error code.
     */
    static int GetPdu(CGXDLMSSettings &settings, CGXReplyData &data);

    /**
     * @brief Extracts data from a received frame, handling different interface types.
     * @param settings The DLMS settings.
     * @param reply The received data buffer.
     * @param[out] data The extracted data and reply information.
     * @param notify Optional object for notifications.
     * @return 0 on success, or an error code.
     */
    static int GetData(CGXDLMSSettings &settings, CGXByteBuffer &reply, CGXReplyData &data, CGXReplyData *notify);

    /**
     * @brief Gets information about the number of attributes for a given object type.
     * @param objectType The DLMS object type.
     * @param[out] value The starting address (typically 1).
     * @param[out] count The number of attributes.
     * @return 0 on success, or an error code.
     */
    static int GetActionInfo(DLMS_OBJECT_TYPE objectType, unsigned char &value, unsigned char &count);

    /**
     * @brief Appends a value to a byte buffer, formatted according to the object and attribute.
     * @param settings DLMS settings.
     * @param obj The DLMS object.
     * @param index The attribute index.
     * @param[out] bb The byte buffer to append to.
     * @param value The value to append.
     * @return 0 on success, or an error code.
     */
    static int AppendData(
        CGXDLMSSettings *settings, CGXDLMSObject *obj, unsigned char index, CGXByteBuffer &bb, CGXDLMSVariant &value
    );

    /** @brief Parses an SNRM or UA response frame. @param data The response data. @param[out] limits The parsed HDLC limits. @return 0 on success. */
    static int ParseSnrmUaResponse(CGXByteBuffer &data, CGXHdlcSettings *limits);
    /** @brief Appends an HDLC parameter to a byte buffer. @param data The buffer. @param value The parameter value. */
    static void AppendHdlcParameter(CGXByteBuffer &data, unsigned short value);

    /** @brief Handles a Confirmed-Service-Error response. @param data The reply data. @return The error code. */
    static int HandleConfirmedServiceError(CGXReplyData &data);
    /** @brief Handles an Exception-Response. @param data The reply data. @return The error code. */
    static int HandleExceptionResponse(CGXReplyData &data);
};
#endif  //GXDLMS_H
