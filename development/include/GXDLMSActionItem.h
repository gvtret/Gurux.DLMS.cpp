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
#ifndef GXDLMSACTIONITEM_H
#define GXDLMSACTIONITEM_H

#include <string>
#include "enums.h"

/**
 * @brief Represents a single action to be performed by a DLMS/COSEM device.
 *
 * This class defines an action by referencing a Script Table object via its
 * logical name and specifying which script to execute via the script selector.
 */
class CGXDLMSActionItem {
    friend class CGXDLMSActionSet;
    /**
     * @brief The logical name (OBIS code) of the Script Table object.
     */
    std::string m_LogicalName;
    /**
     * @brief An integer that selects the specific script to be executed from the Script Table.
     */
    int m_ScriptSelector;

public:
    /** @brief Default constructor. */
    CGXDLMSActionItem();

    /** @brief Destructor. */
    ~CGXDLMSActionItem() {
        m_LogicalName.clear();
    }

    /** @brief Gets the logical name of the Script Table. @return A reference to the logical name string. */
    std::string &GetLogicalName();
    /** @brief Sets the logical name of the Script Table. @param value The new logical name. */
    void SetLogicalName(std::string &value);

    /** @brief Gets the script selector. @return The script selector value. */
    int GetScriptSelector();
    /** @brief Sets the script selector. @param value The new script selector value. */
    void SetScriptSelector(int value);

    /**
     * @brief Converts the action item to a string representation.
     * @return A string describing the logical name and script selector.
     */
    std::string ToString();
};
#endif  //GXDLMSACTIONITEM_H
