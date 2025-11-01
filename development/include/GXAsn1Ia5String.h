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

#ifndef GXASN1IA5STRING_H
#define GXASN1IA5STRING_H

#include <string>
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 IA5String.
 *
 * The IA5String type in ASN.1 corresponds to the International Alphabet No. 5,
 * which is essentially the 7-bit ASCII character set. This class provides a
 * container for such strings.
 */
class CGXAsn1Ia5String: public CGXAsn1Base {
private:
    /**
     * @brief The internal string value.
     */
    std::string m_Ia5String;

public:
    /**
     * @brief Default constructor. Initializes an empty IA5String.
     */
    CGXAsn1Ia5String() {
    }

    /**
     * @brief Constructor that initializes the string with a given value.
     * @param value The initial string value.
     */
    CGXAsn1Ia5String(std::string &value) {
        m_Ia5String = value;
    }

    /**
     * @brief Gets the value of the IA5String.
     * @return A reference to the internal string.
     */
    std::string &GetValue() {
        return m_Ia5String;
    }

    /**
     * @brief Sets the value of the IA5String.
     * @param value The new string value.
     */
    void SetValue(std::string &value) {
        m_Ia5String = value;
    }

    /**
     * @brief Converts the IA5String to its string representation.
     * @return The string value.
     */
    std::string ToString() {
        return m_Ia5String;
    }
};

#endif  //GXASN1IA5STRING_H
