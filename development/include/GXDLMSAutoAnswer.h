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
class CGXDLMSAutoAnswer: public CGXDLMSObject
{
    /**
     * Number of rings in listening window.
     */
    int m_NumberOfRingsInListeningWindow;
    /**
     * Number of rings out of listening window.
     */
    int m_NumberOfRingsOutListeningWindow;
    /**
     * Auto answer mode.
     */
    DLMS_AUTO_ANSWER_MODE m_Mode;
    /**
     * Listening window.
     */
    std::vector<std::pair<CGXDateTime, CGXDateTime> > m_ListeningWindow;
    /**
     * Auto answer status.
     */
    AUTO_ANSWER_STATUS m_Status;
    /**
     * Number of calls.
     */
    int m_NumberOfCalls;
public:
    /**
     * Constructor.
     */
    CGXDLMSAutoAnswer();

    /**
     * Constructor.
     *
     * @param ln
     *            Logical Name of the object.
     */
    CGXDLMSAutoAnswer(std::string ln);

    /**
     * Constructor.
     *
     * @param ln
     *            Logical Name of the object.
     * @param sn
     *            Short Name of the object.
     */
    CGXDLMSAutoAnswer(std::string ln, unsigned short sn);

    /**
     * @return The auto-answer mode.
     */
    DLMS_AUTO_ANSWER_MODE GetMode();

    /**
     * @param value
     *            The auto-answer mode.
     */
    void SetMode(DLMS_AUTO_ANSWER_MODE value);

    /**
     * @return The listening window.
     */
    std::vector<std::pair<CGXDateTime, CGXDateTime> >& GetListeningWindow();

    /**
     * @param value
     *            The listening window.
     */
    void SetListeningWindow(
        std::vector<std::pair<CGXDateTime, CGXDateTime> >& value);

    /**
     * @return Auto-answer status.
     */
    AUTO_ANSWER_STATUS GetStatus();

    /**
     * @param value
     *            Auto-answer status.
     */
    void SetStatus(AUTO_ANSWER_STATUS value);

    /**
     * @return The number of calls.
     */
    int GetNumberOfCalls();

    /**
     * @param value
     *            The number of calls.
     */
    void SetNumberOfCalls(int value);

    /**
     * @return The number of rings within the listening window.
     */
    int GetNumberOfRingsInListeningWindow();

    /**
     * @param value
     *            The number of rings within the listening window.
     */
    void SetNumberOfRingsInListeningWindow(int value);

    /**
     * @return The number of rings outside the listening window.
     */
    int GetNumberOfRingsOutListeningWindow();

    /**
     * @param value
     *            The number of rings outside the listening window.
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
    void GetValues(std::vector<std::string>& values);

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE& type);

    /**
     * @brief Gets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Sets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif  //DLMS_IGNORE_AUTO_ANSWER
#endif  //GXDLMSAUTOANSWER_H
