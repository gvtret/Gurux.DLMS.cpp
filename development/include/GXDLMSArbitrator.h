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

#ifndef GXDLMSArbitrator_H
#define GXDLMSArbitrator_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_ARBITRATOR
#include "GXDLMSObject.h"
#include "GXDLMSActionItem.h"

/**
 * @brief Represents a DLMS/COSEM arbitrator, which manages access to shared
 *        resources by different actors based on defined permissions and
*        priorities.
 */
class CGXDLMSArbitrator : public CGXDLMSObject
{
    /**
     * A list of actions that can be requested by actors.
     */
    std::vector<CGXDLMSActionItem> m_Actions;

    /**
     * A table defining the permissions for each actor to request actions.
     */
    std::vector<std::string> m_PermissionsTable;
    /**
     * A table defining the weight allocated to each actor for each possible
     * action, used for prioritization.
     */
    std::vector<std::vector<uint16_t>> m_WeightingsTable;
    /**
     * A table storing the most recent requests made by each actor.
     */
    std::vector<std::string> m_MostRecentRequestsTable;
    /**
     * The outcome of the last arbitration process, identifying a bit in the
     * Actions list.
     */
    unsigned char m_LastOutcome;

public:
    /**
     * @brief Initializes a new instance of the CGXDLMSArbitrator class.
     */
    CGXDLMSArbitrator();

    /**
     * @brief Initializes a new instance of the CGXDLMSArbitrator class.
     * @param ln The logical name of the object.
     * @param sn The short name of the object.
     */
    CGXDLMSArbitrator(std::string ln, unsigned short sn);

    /**
     * @brief Initializes a new instance of the CGXDLMSArbitrator class.
     * @param ln The logical name of the object.
     */
    CGXDLMSArbitrator(std::string ln);

    /**
     * @brief Gets the list of actions that can be requested.
     * @return A reference to the vector of action items.
     */
    std::vector<CGXDLMSActionItem>& GetActions()
    {
        return m_Actions;
    }

    /**
     * @brief Gets the permissions table for each actor.
     * @return A reference to the vector of permission strings.
     */
    std::vector<std::string>& GetPermissionsTable()
    {
        return m_PermissionsTable;
    }

    /**
     * @brief Gets the weightings table for each actor and action.
     * @return A reference to the vector of weighting values.
     */
    std::vector<std::vector<uint16_t>>& GetWeightingsTable()
    {
        return m_WeightingsTable;
    }

    /**
     * @brief Gets the table of the most recent requests from each actor.
     * @return A reference to the vector of recent request strings.
     */
    std::vector<std::string>& GetMostRecentRequestsTable()
    {
        return m_MostRecentRequestsTable;
    }

    /**
     * @brief Gets the outcome of the last arbitration.
     * @return The last outcome value.
     */
    unsigned char GetLastOutcome()
    {
        return m_LastOutcome;
    }

    /**
     * @brief Sets the outcome of the last arbitration.
     * @param value The last outcome value.
     */
    void SetLastOutcome(unsigned char value)
    {
        m_LastOutcome = value;
    }

    /**
     * @brief Returns the total number of attributes in the object.
     * @return The attribute count.
     */
    int GetAttributeCount();

    /**
     * @brief Returns the total number of methods in the object.
     * @return The method count.
     */
    int GetMethodCount();

    /**
     * @brief Retrieves all attribute values from the object.
     * @param values A vector to store the attribute values as strings.
     */
    void GetValues(std::vector<std::string>& values);

    /**
     * @brief Fills a list with the attribute indices that should be read from
     *        the device.
     * @param all        If true, all attributes are included; otherwise, only
     *                   unread attributes are included.
     * @param attributes A list to store the indices of attributes to read.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    /**
     * @brief Gets the data type of a specific attribute.
     * @param index The index of the attribute.
     * @param type  An output parameter to store the attribute's data type.
     * @return An error code indicating the success of the operation.
     */
    int GetDataType(int index, DLMS_DATA_TYPE& type);

    /**
     * @brief Gets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Sets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif  //DLMS_IGNORE_ARBITRATOR
#endif  //GXDLMSArbitrator_H