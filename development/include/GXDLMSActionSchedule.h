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

#ifndef GXDLMSACTIONSCHEDULE_H
#define GXDLMSACTIONSCHEDULE_H

#include "GXIgnore.h"

#ifndef DLMS_IGNORE_ACTION_SCHEDULE
#include "GXDLMSObject.h"

/**
 * @brief Represents a DLMS/COSEM Action Schedule object (class ID 20).
 *
 * This class defines a set of actions to be executed at specific dates and times.
 * Each action is a script from a Script Table object.
 */
class CGXDLMSActionSchedule: public CGXDLMSObject {
    /** @brief The logical name of the script to be executed. */
    std::string m_ExecutedScriptLogicalName;
    /** @brief The selector for the script to be executed. */
    int m_ExecutedScriptSelector;
    /** @brief The type of schedule (e.g., single action, daily, weekly). */
    DLMS_SINGLE_ACTION_SCHEDULE_TYPE m_Type;
    /** @brief A list of date and time values when the action should be executed. */
    std::vector<CGXDateTime> m_ExecutionTime;

public:
    /** @brief Default constructor. */
    CGXDLMSActionSchedule();
    /** @brief Constructor with logical name. @param ln The logical name of the object. */
    CGXDLMSActionSchedule(std::string ln);
    /** @brief Constructor with logical and short name. @param ln The logical name. @param sn The short name. */
    CGXDLMSActionSchedule(std::string ln, unsigned short sn);

    /** @brief Gets the logical name of the executed script. @return The logical name. */
    std::string &GetExecutedScriptLogicalName();
    /** @brief Sets the logical name of the executed script. @param value The logical name. */
    void SetExecutedScriptLogicalName(std::string value);

    /** @brief Gets the selector of the executed script. @return The script selector. */
    int GetExecutedScriptSelector();
    /** @brief Sets the selector of the executed script. @param value The script selector. */
    void SetExecutedScriptSelector(int value);

    /** @brief Gets the schedule type. @return The schedule type. */
    DLMS_SINGLE_ACTION_SCHEDULE_TYPE GetType();
    /** @brief Sets the schedule type. @param value The schedule type. */
    void SetType(DLMS_SINGLE_ACTION_SCHEDULE_TYPE value);

    /** @brief Gets the list of execution times. @return A reference to the vector of execution times. */
    std::vector<CGXDateTime> &GetExecutionTime();
    /** @brief Sets the list of execution times. @param value The vector of execution times. */
    void SetExecutionTime(std::vector<CGXDateTime> &value);

    // Overridden methods.
    int GetAttributeCount();
    int GetMethodCount();
    void GetValues(std::vector<std::string> &values);
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);
    int GetDataType(int index, DLMS_DATA_TYPE &type);
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
};
#endif  //DLMS_IGNORE_ACTION_SCHEDULE
#endif  //GXDLMSACTIONSCHEDULE_H
