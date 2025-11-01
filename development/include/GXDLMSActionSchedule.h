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
 * @brief Represents a DLMS/COSEM action schedule, which defines a set of actions to be executed at specific times.
 */
class CGXDLMSActionSchedule: public CGXDLMSObject {
    std::string m_ExecutedScriptLogicalName;
    int m_ExecutedScriptSelector;
    DLMS_SINGLE_ACTION_SCHEDULE_TYPE m_Type;
    std::vector<CGXDateTime> m_ExecutionTime;

public:
    /**
     * @brief Constructor.
     */
    CGXDLMSActionSchedule();

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     */
    CGXDLMSActionSchedule(std::string ln);

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     * @param sn The short name of the object.
     */
    CGXDLMSActionSchedule(std::string ln, unsigned short sn);

    /**
     * @brief Gets the executed script's logical name.
     * @return The executed script's logical name.
     */
    std::string &GetExecutedScriptLogicalName();

    /**
     * @brief Sets the executed script's logical name.
     * @param value The logical name to set.
     */
    void SetExecutedScriptLogicalName(std::string value);

    /**
     * @brief Gets the executed script's selector.
     * @return The executed script's selector.
     */
    int GetExecutedScriptSelector();

    /**
     * @brief Sets the executed script's selector.
     * @param value The selector to set.
     */
    void SetExecutedScriptSelector(int value);

    /**
     * @brief Gets the schedule type.
     * @return The schedule type.
     */
    DLMS_SINGLE_ACTION_SCHEDULE_TYPE GetType();

    /**
     * @brief Sets the schedule type.
     * @param value The schedule type to set.
     */
    void SetType(DLMS_SINGLE_ACTION_SCHEDULE_TYPE value);

    /**
     * @brief Gets the execution times.
     * @return A reference to the vector of execution times.
     */
    std::vector<CGXDateTime> &GetExecutionTime();

    /**
     * @brief Sets the execution times.
     * @param value The vector of execution times to set.
     */
    void SetExecutionTime(std::vector<CGXDateTime> &value);

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
#endif  //DLMS_IGNORE_ACTION_SCHEDULE
#endif  //GXDLMSACTIONSCHEDULE_H
