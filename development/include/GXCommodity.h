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

#ifndef CGXCOMMODITY_H
#define CGXCOMMODITY_H

#include <string>
#include "enums.h"

/**
 * @brief Represents a commodity in a charge object.
 *
 * This class identifies the type of energy or service being charged by referencing
 * a specific DLMS/COSEM object (e.g., a Register object) via its logical name and
 * attribute index.
 */
class CGXCommodity {
    /**
     * @brief The object type of the referenced commodity (e.g., Register, Extended Register).
     */
    DLMS_OBJECT_TYPE m_Type;
    /**
     * @brief The 6-byte logical name (OBIS code) of the referenced object.
     */
    unsigned char m_LogicalName[6];
    /**
     * @brief The index of the attribute within the referenced object that holds the commodity value.
     */
    unsigned char m_Index;

public:
    /**
     * @brief Default constructor.
     */
    CGXCommodity();

    /**
     * @brief Gets the object type of the commodity.
     * @return The DLMS_OBJECT_TYPE enumeration.
     */
    DLMS_OBJECT_TYPE GetType();

    /**
     * @brief Sets the object type of the commodity.
     * @param value The DLMS_OBJECT_TYPE enumeration.
     */
    void SetType(DLMS_OBJECT_TYPE value);

    /**
     * @brief Gets the logical name of the commodity object.
     * @return A pointer to the 6-byte logical name array.
     */
    unsigned char *GetLogicalName();

    /**
     * @brief Sets the logical name of the commodity object.
     * @param value A pointer to the 6-byte logical name array.
     */
    void SetLogicalName(unsigned char *value);

    /**
     * @brief Gets the attribute index of the commodity.
     * @return The attribute index.
     */
    unsigned char GetIndex();

    /**
     * @brief Sets the attribute index of the commodity.
     * @param value The attribute index.
     */
    void SetIndex(unsigned char value);

    /**
     * @brief Converts the commodity information to a string representation.
     * @return A string describing the commodity's logical name and attribute index.
     */
    std::string ToString();
};
#endif  //CGXCOMMODITY_H
