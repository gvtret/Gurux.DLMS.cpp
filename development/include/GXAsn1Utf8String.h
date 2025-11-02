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

#ifndef GXASN1UTF8STRING_H
#define GXASN1UTF8STRING_H

#include <string>
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 UTF8String, a string of characters encoded in UTF-8.
 *
 * This class provides a container for UTF-8 encoded strings within the ASN.1
 * object hierarchy.
 */
class CGXAsn1Utf8String: public CGXAsn1Base {
private:
    /**
     * @brief The internal string value, encoded in UTF-8.
     */
    std::string m_Value;

public:
    /**
     * @brief Default constructor. Initializes an empty UTF8String.
     */
    CGXAsn1Utf8String() {
    }

    /**
     * @brief Constructor that initializes the string with a given value.
     * @param value The initial string value.
     */
    CGXAsn1Utf8String(std::string &value) {
        m_Value = value;
    }

    /**
     * @brief Gets the value of the UTF8String.
     * @return A reference to the internal string.
     */
    std::string &GetValue() {
        return m_Value;
    }

    /**
     * @brief Sets the value of the UTF8String.
     * @param value The new string value.
     */
    void SetValue(std::string &value) {
        m_Value = value;
    }

    /**
     * @brief Converts the UTF8String to its string representation.
     * @return The string value.
     */
    std::string ToString() {
        return m_Value;
    }
};

#endif  //GXASN1UTF8STRING_H
