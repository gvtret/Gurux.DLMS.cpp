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
#ifndef GXDLMSAUTOANSWER_H
#define GXDLMSAUTOANSWER_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_AUTO_ANSWER
#include "GXDLMSObject.h"

/**
 * @brief Enumerates the auto-answer modes.
 */
typedef enum {
    /**
     * @brief Line dedicated to the device.
     */
    DLMS_AUTO_ANSWER_MODE_DEVICE = 0,
    /**
     * @brief Shared line management with a limited number of calls allowed.
     */
    DLMS_AUTO_ANSWER_MODE_CALL = 1,
    /**
     * @brief Shared line management with a limited number of successful calls allowed.
     */
    DLMS_AUTO_ANSWER_MODE_CONNECTED = 2,
    /**
     * @brief Currently no modem connected.
     */
    DLMS_AUTO_ANSWER_MODE_NONE = 3
} DLMS_AUTO_ANSWER_MODE;

/**
 * @brief Enumerates the auto-answer statuses.
 */
enum AUTO_ANSWER_STATUS {
    /**
     * @brief Inactive.
     */
    AUTO_ANSWER_STATUS_INACTIVE = 0,
    /**
     * @brief Active.
     */
    AUTO_ANSWER_STATUS_ACTIVE = 1,
    /**
     * @brief Locked.
     */
    AUTO_ANSWER_STATUS_LOCKED = 2
};

/**
 * @brief Represents a DLMS/COSEM auto-answer object, which controls how a device responds to incoming calls.
 */
class CGXDLMSAutoAnswer: public CGXDLMSObject {
    int m_NumberOfRingsInListeningWindow, m_NumberOfRingsOutListeningWindow;
    DLMS_AUTO_ANSWER_MODE m_Mode;
    std::vector<std::pair<CGXDateTime, CGXDateTime>> m_ListeningWindow;
    AUTO_ANSWER_STATUS m_Status;
    int m_NumberOfCalls;

public:
    /**
     * @brief Constructor.
     */
    CGXDLMSAutoAnswer();

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     */
    CGXDLMSAutoAnswer(std::string ln);

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     * @param sn The short name of the object.
     */
    CGXDLMSAutoAnswer(std::string ln, unsigned short sn);

    /**
     * @brief Gets the auto-answer mode.
     * @return The auto-answer mode.
     */
    DLMS_AUTO_ANSWER_MODE GetMode();

    /**
     * @brief Sets the auto-answer mode.
     * @param value The mode to set.
     */
    void SetMode(DLMS_AUTO_ANSWER_MODE value);

    /**
     * @brief Gets the listening window.
     * @return A reference to the vector of listening windows.
     */
    std::vector<std::pair<CGXDateTime, CGXDateTime>> &GetListeningWindow();

    /**
     * @brief Sets the listening window.
     * @param value The vector of listening windows to set.
     */
    void SetListeningWindow(std::vector<std::pair<CGXDateTime, CGXDateTime>> &value);

    /**
     * @brief Gets the auto-answer status.
     * @return The status.
     */
    AUTO_ANSWER_STATUS GetStatus();

    /**
     * @brief Sets the auto-answer status.
     * @param value The status to set.
     */
    void SetStatus(AUTO_ANSWER_STATUS value);

    /**
     * @brief Gets the number of calls.
     * @return The number of calls.
     */
    int GetNumberOfCalls();

    /**
     * @brief Sets the number of calls.
     * @param value The number of calls to set.
     */
    void SetNumberOfCalls(int value);

    /**
     * @brief Gets the number of rings within the listening window.
     * @return The number of rings.
     */
    int GetNumberOfRingsInListeningWindow();

    /**
     * @brief Sets the number of rings within the listening window.
     * @param value The number of rings to set.
     */
    void SetNumberOfRingsInListeningWindow(int value);

    /**
     * @brief Gets the number of rings outside the listening window.
     * @return The number of rings.
     */
    int GetNumberOfRingsOutListeningWindow();

    /**
     * @brief Sets the number of rings outside the listening window.
     * @param value The number of rings to set.
     */
    void SetNumberOfRingsOutListeningWindow(int value);

    /**
     * @brief Gets the number of attributes.
     * @return The number of attributes.
     */
    int GetAttributeCount();

    /**
     * @brief Gets the number of methods.
     * @return The number of methods.
     */
    int GetMethodCount();

    /**
     * @brief Gets the attribute values as strings.
     * @param values A reference to a vector to store the values.
     */
    void GetValues(std::vector<std::string> &values);

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Gets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
     * @brief Sets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
};
#endif  //DLMS_IGNORE_AUTO_ANSWER
#endif  //GXDLMSAUTOANSWER_H
