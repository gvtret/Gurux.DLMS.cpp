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

#ifndef GXDLMSPUSHSETUP_H
#define GXDLMSPUSHSETUP_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_PUSH_SETUP
#include "GXDLMSObject.h"
#include "GXDLMSPushObject.h"
#include "GXDLMSCaptureObject.h"
#include "GXRepetitionDelay.h"
#include "GXPushProtectionParameters.h"
#include "GXPushConfirmationParameter.h"

/**
 * Push operation method defines what service class is used with push messages.
 */
typedef enum {
    /**
     * Unconfirmed, retry on supporting protocol layer failure.
     */
    DLMS_PUSH_OPERATION_METHOD_UNCONFIRMED_FAILURE,
    /**
     * Unconfirmed, retry on missing supporting protocol layer confirmation.
     */
    DLMS_PUSH_OPERATION_METHOD_UNCONFIRMED_MISSING,
    /**
     * Confirmed, retry on missing confirmation.
     */
    DLMS_PUSH_OPERATION_METHOD_CONFIRMED
}DLMS_PUSH_OPERATION_METHOD;

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSPushSetup
*/
class CGXDLMSPushSetup : public CGXDLMSObject
{
private:
    DLMS_SERVICE_TYPE m_Service;
    std::string m_Destination;
    DLMS_MESSAGE_TYPE m_Message;
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> > m_PushObjectList;
    std::vector<std::pair<CGXDateTime, CGXDateTime> > m_CommunicationWindow;

    int m_RandomisationStartInterval, m_NumberOfRetries;
    /**Repetition delay for Version #0 and #1.*/
    int m_RepetitionDelay;

    /*Repetition delay for Version2.*/
    CGXRepetitionDelay m_RepetitionDelay2;

    /*The logical name of a communication port setup object.*/
    CGXDLMSObject* m_PortReference;

    /*Push client SAP.*/
    signed char m_PushClientSAP;

    /*Push protection parameters.*/
    std::vector<CGXPushProtectionParameters> m_PushProtectionParameters;

    /*Push operation method.*/
    DLMS_PUSH_OPERATION_METHOD m_PushOperationMethod;

    /*Push confirmation parameter.*/
    CGXPushConfirmationParameter m_ConfirmationParameters;

    /*Last confirmation date time.*/
    CGXDateTime m_LastConfirmationDateTime;

public:
    //Constructor.
    CGXDLMSPushSetup();

    //SN Constructor.
    CGXDLMSPushSetup(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSPushSetup(std::string ln);

    /**
        Defines the list of attributes or objects to be pushed.
        Upon a call of the push (data) method the selected attributes are sent to the desti-nation
        defined in send_destination_and_method.
    */
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >& GetPushObjectList()
    {
        return m_PushObjectList;
    }

    DLMS_SERVICE_TYPE GetService();
    void SetService(DLMS_SERVICE_TYPE value);

    std::string& GetDestination();
    void SetDestination(std::string& value);

    DLMS_MESSAGE_TYPE GetMessageType();
    void SetMessageType(DLMS_MESSAGE_TYPE value);

    /**
     Contains the start and end date/time
     stamp when the communication window(s) for the push become active
     (for the start instant), or inac-tive (for the end instant).
    */
    std::vector<std::pair<CGXDateTime, CGXDateTime> >& GetCommunicationWindow()
    {
        return m_CommunicationWindow;
    }

    /**
     To avoid simultaneous network connections of a lot of devices at ex-actly
     the same point in time, a randomisation interval in seconds can be defined.
     This means that the push operation is not started imme-diately at the
     beginning of the first communication window but started randomly delayed.
    */
    int GetRandomisationStartInterval()
    {
        return m_RandomisationStartInterval;
    }
    void SetRandomisationStartInterval(int value)
    {
        m_RandomisationStartInterval = value;
    }
    /**
     The maximum number of retrials in case of unsuccessful push at-tempts. After a successful push no further push attempts are made until the push setup is triggered again.
     A value of 0 means no repetitions, i.e. only the initial connection at-tempt is made.
    */

    int GetNumberOfRetries()
    {
        return m_NumberOfRetries;
    }
    void SetNumberOfRetries(int value)
    {
        m_NumberOfRetries = value;
    }

    int GetRepetitionDelay()
    {
        return m_RepetitionDelay;
    }

    void SetRepetitionDelay(int value)
    {
        m_RepetitionDelay = value;
    }
    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    //Get attribute values of object.
    void GetValues(std::vector<std::string>& values);

    /////////////////////////////////////////////////////////////////////////
    // Returns collection of attributes to read.
    //
    // If attribute is static and already read or device is returned
    // HW error it is not returned.
    //
    // all: All items are returned even if they are read already.
    // attributes: Collection of attributes to read.
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    int GetDataType(int index, DLMS_DATA_TYPE& type);

    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    // Set value of given attribute.
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /////////////////////////////////////////////////////////////////////////
    // Get received objects from push message.
    // values : Received values.
    // results: Push values.
    int GetPushValues(CGXDLMSClient* client,
        std::vector<CGXDLMSVariant>& values,
        std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >& results);

    /*Activates the push process.*/
    int Activate(
        CGXDLMSClient* client,
        std::vector<CGXByteBuffer>& reply);

    /*Reset the push process.*/
    int Reset(
        CGXDLMSClient* client,
        std::vector<CGXByteBuffer>& reply);
};
#endif //DLMS_IGNORE_PUSH_SETUP
#endif //GXDLMSPUSHSETUP_H