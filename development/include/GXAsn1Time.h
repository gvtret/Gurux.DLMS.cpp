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

#ifndef GXAsn1Time_H
#define GXAsn1Time_H

#include "GXAsn1Base.h"
#include "GXDateTime.h"

/**
 * @brief Represents an ASN.1 Time value.
 *
 * This class is a container for a CGXDateTime object, providing a way to handle
 * ASN.1 time types like UTCTime and GeneralizedTime within the ASN.1 object hierarchy.
 */
class CGXAsn1Time: public CGXAsn1Base {
private:
    /**
     * @brief The internal CGXDateTime object holding the time value.
     */
    CGXDateTime m_Time;

public:
    /**
     * @brief Default constructor. Initializes a new instance with a default date-time value.
     */
    CGXAsn1Time() {
    }

    /**
     * @brief Constructor that initializes the time with a given CGXDateTime object.
     * @param value The initial date-time value.
     */
    CGXAsn1Time(CGXDateTime &value) {
        m_Time = value;
    }

    /**
     * @brief Gets the value of the ASN.1 Time object.
     * @return A reference to the internal CGXDateTime object.
     */
    CGXDateTime &GetValue() {
        return m_Time;
    }

    /**
     * @brief Sets the value of the ASN.1 Time object.
     * @param value The new date-time value.
     */
    void SetValue(CGXDateTime &value) {
        m_Time = value;
    }

    /**
     * @brief Converts the ASN.1 Time to its string representation.
     * @return A string representation of the date-time value.
     */
    std::string ToString() {
        return m_Time.ToString();
    }
};

#endif  //GXAsn1Time_H
