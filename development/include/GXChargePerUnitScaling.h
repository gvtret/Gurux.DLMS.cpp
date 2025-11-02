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

#ifndef GXCHARGE_PER_UNIT_SCALING_H
#define GXCHARGE_PER_UNIT_SCALING_H

#include <string>

/**
 * @brief Represents the scaling factors for commodity and price in a charge object.
 *
 * This class holds the scaler and unit information for both the commodity (e.g., energy)
 * and the price, as defined in a DLMS/COSEM charge object.
 */
class CGXChargePerUnitScaling {
    /**
     * @brief The scaling factor (exponent) applied to the commodity value.
     */
    signed char m_CommodityScale;
    /**
     * @brief The scaling factor (exponent) applied to the price value.
     */
    signed char m_PriceScale;

public:
    /**
     * @brief Default constructor.
     */
    CGXChargePerUnitScaling();

    /**
     * @brief Gets the commodity scaling factor.
     * @return The commodity scale exponent.
     */
    signed char GetCommodityScale();

    /**
     * @brief Sets the commodity scaling factor.
     * @param value The commodity scale exponent.
     */
    void SetCommodityScale(signed char value);

    /**
     * @brief Gets the price scaling factor.
     * @return The price scale exponent.
     */
    signed char GetPriceScale();

    /**
     * @brief Sets the price scaling factor.
     * @param value The price scale exponent.
     */
    void SetPriceScale(signed char value);

    /**
     * @brief Converts the scaling information to a string representation.
     * @return A string describing the commodity and price scales.
     */
    std::string ToString();
};
#endif  //GXCHARGE_PER_UNIT_SCALING_H
