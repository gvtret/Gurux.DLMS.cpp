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

#ifndef GXDLMSACTIONSET_H
#define GXDLMSACTIONSET_H

#include "GXDLMSActionItem.h"

/**
 * @brief Represents a set of actions, typically an "up" action and a "down" action.
 *
 * This class is often used in scheduling objects (like Activity Calendar) to define
 * actions to be taken at the start and end of a time period.
 */
class CGXDLMSActionSet {
    /**
     * @brief The action to be executed at the start of a period (e.g., tariff activation).
     */
    CGXDLMSActionItem m_ActionUp;
    /**
     * @brief The action to be executed at the end of a period (e.g., tariff deactivation).
     */
    CGXDLMSActionItem m_ActionDown;

public:
    /**
     * @brief Default constructor.
     */
    CGXDLMSActionSet();

    /**
     * @brief Destructor.
     */
    ~CGXDLMSActionSet() {
    }

    /**
     * @brief Gets the "up" action.
     * @return A reference to the "up" action item.
     */
    CGXDLMSActionItem &GetActionUp();

    /**
     * @brief Gets the "down" action.
     * @return A reference to the "down" action item.
     */
    CGXDLMSActionItem &GetActionDown();

    /**
     * @brief Converts the action set to a string representation.
     * @return A string describing the "up" and "down" actions.
     */
    std::string ToString();
};

#endif  //GXDLMSACTIONSET_H
