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

#ifndef GXCHARGE_TABLE_H
#define GXCHARGE_TABLE_H

#include <string>

/**
 * @brief Represents a single entry in a charge table.
 *
 * This class defines a single tier or step in a charging schedule, associating
 * an index (often related to a time period or consumption level) with a specific
 * charge per unit.
 */
class CGXChargeTable {
    /**
     * @brief The index or identifier for this charge table entry.
     */
    std::string m_Index;
    /**
     * @brief The charge to be applied per unit for this entry.
     */
    short m_ChargePerUnit;

public:
    /**
     * @brief Default constructor.
     */
    CGXChargeTable();

    /**
     * @brief Gets the index of the charge table entry.
     * @return A reference to the index string.
     */
    std::string &GetIndex();

    /**
     * @brief Sets the index of the charge table entry.
     * @param value The new index string.
     */
    void SetIndex(std::string &value);

    /**
     * @brief Gets the charge per unit.
     * @return The charge per unit value.
     */
    short GetChargePerUnit();

    /**
     * @brief Sets the charge per unit.
     * @param value The new charge per unit value.
     */
    void SetChargePerUnit(short value);

    /**
     * @brief Converts the charge table entry to a string representation.
     * @return A string describing the index and charge per unit.
     */
    std::string ToString();
};
#endif  //GXCHARGE_TABLE_H
