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

#ifndef GXBIT_STRING_H
#define GXBIT_STRING_H

#include <string>

/**
 * @brief Represents a string of bits.
 *
 * This class provides functionality to handle sequences of bits represented as a
 * string of '0's and '1's. It supports conversion to and from integer types.
 */
class CGXBitString {
private:
    /**
     * @brief The internal string holding the bit sequence.
     */
    std::string m_Value;

    /**
     * @brief Internal helper to convert the bit string to an integer.
     * @param[out] value The integer result.
     * @param maxSize The maximum number of bits to convert.
     * @return 0 on success, or an error code.
     */
    int ToInteger(int &value, unsigned char maxSize);

public:
    /**
     * @brief Default constructor. Initializes an empty bit string.
     */
    CGXBitString();

    /**
     * @brief Constructor that initializes from a string.
     * @param value A string of '0's and '1's.
     */
    CGXBitString(std::string value);

    /**
     * @brief Gets the bit string as a standard string.
     * @return A reference to the internal string.
     */
    std::string &ToString();

    /**
     * @brief Converts the bit string to an integer.
     * @param[out] value The integer result.
     * @return 0 on success, or an error code.
     */
    int ToInteger(int &value);

    /**
     * @brief Converts the bit string to a byte.
     * @param[out] value The byte result.
     * @return 0 on success, or an error code.
     */
    int ToByte(unsigned char &value);

    /**
     * @brief Converts an integer value to a bit string of a specified length.
     * @param value The integer value to convert.
     * @param count The desired number of bits in the output string.
     * @return A string of '0's and '1's representing the integer.
     */
    static std::string ToBitString(unsigned int value, unsigned int count);
};
#endif  //GXBIT_STRING_H
