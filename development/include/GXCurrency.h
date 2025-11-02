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

#ifndef GXCURRENCY_H
#define GXCURRENCY_H

#include "enums.h"
#include <string>

/**
 * @brief Represents a currency, including its name, scale, and unit.
 *
 * This class is used in DLMS/COSEM to define the monetary unit for charges and credits.
 */
class CGXCurrency {
    /**
     * @brief The name or symbol of the currency (e.g., "USD", "EUR").
     */
    std::string m_Name;
    /**
     * @brief The scaling factor (exponent) applied to the currency value.
     */
    char m_Scale;
    /**
     * @brief The standardized unit of the currency.
     */
    DLMS_CURRENCY m_Unit;

public:
    /**
     * @brief Default constructor.
     */
    CGXCurrency();

    /**
     * @brief Gets the currency name.
     * @return A reference to the currency name string.
     */
    std::string &GetName();

    /**
     * @brief Sets the currency name.
     * @param value The new currency name string.
     */
    void SetName(std::string &value);

    /**
     * @brief Gets the currency scaling factor.
     * @return The currency scale exponent.
     */
    char GetScale();

    /**
     * @brief Sets the currency scaling factor.
     * @param value The new currency scale exponent.
     */
    void SetScale(char value);

    /**
     * @brief Gets the currency unit.
     * @return The DLMS_CURRENCY enumeration.
     */
    DLMS_CURRENCY GetUnit();

    /**
     * @brief Sets the currency unit.
     * @param value The DLMS_CURRENCY enumeration.
     */
    void SetUnit(DLMS_CURRENCY value);

    /**
     * @brief Converts the currency information to a string representation.
     * @return A string describing the currency's name, scale, and unit.
     */
    std::string ToString();
};
#endif  //GXCURRENCY_H
