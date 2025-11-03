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

#ifndef GXASN1INTEGER_H
#define GXASN1INTEGER_H

#include "GXBytebuffer.h"
#include "GXBigInteger.h"
#include "GXHelpers.h"
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 INTEGER, a signed whole number of arbitrary size.
 *
 * This class stores the integer value in a byte buffer, allowing it to represent
 * numbers larger than standard primitive types. It provides methods to construct
 * the integer from various types and to convert it to standard integer types.
 */
class CGXAsn1Integer: public CGXAsn1Base {
private:
    /**
     * @brief The byte buffer that holds the raw byte representation of the integer.
     */
    CGXByteBuffer m_Value;

public:
    /**
     * @brief Gets the underlying byte buffer containing the integer value.
     * @return A reference to the internal byte buffer.
     */
    CGXByteBuffer &GetValue() {
        return m_Value;
    }

    /**
     * @brief Sets the integer value from a byte buffer.
     * @param value The byte buffer containing the new value.
     */
    void SetValue(CGXByteBuffer &value) {
        m_Value = value;
    }

    /**
     * @brief Default constructor. Initializes an empty integer object.
     */
    CGXAsn1Integer() {
    }

    /**
     * @brief Constructor that initializes the integer from a byte buffer.
     * @param value The byte buffer containing the integer data.
     */
    CGXAsn1Integer(CGXByteBuffer &value) {
        m_Value = value;
    }

    /**
     * @brief Constructor that initializes the integer from a part of a byte buffer.
     * @param data The source byte buffer.
     * @param index The starting index in the source buffer.
     * @param count The number of bytes to copy.
     */
    CGXAsn1Integer(CGXByteBuffer &data, int index, int count) {
        data.SubArray(index, count, m_Value);
    }

    /**
     * @brief Constructor that initializes the integer from a string.
     * @param data A string containing the numeric value.
     */
    CGXAsn1Integer(std::string &data) {
        m_Value.SetUInt64(atoll(data.c_str()));
    }

    /**
     * @brief Constructor that initializes the integer from a 64-bit unsigned integer.
     * @param data The 64-bit integer value.
     */
    CGXAsn1Integer(uint64_t data) {
        m_Value.SetUInt64(data);
    }

    /**
     * @brief Converts the ASN.1 integer to a big integer object.
     * @return A CGXBigInteger object representing the value.
     */
    CGXBigInteger ToBigInteger() {
        return CGXBigInteger(m_Value);
    }

    /**
     * @brief Converts the integer value to an unsigned char (byte).
     * @note This may result in data loss if the value is outside the range of a byte.
     * @return The value as an unsigned char.
     */
    unsigned char ToByte() {
        unsigned char value;
        m_Value.GetUInt8(&value);
        return value;
    }

    /**
     * @brief Converts the integer value to a short.
     * @note This may result in data loss if the value is outside the range of a short.
     * @return The value as a short.
     */
    short ToShort() {
        short value;
        m_Value.GetInt16(&value);
        return value;
    }

    /**
     * @brief Converts the integer value to a long.
     * @note This may result in data loss if the value is outside the range of a long.
     * @return The value as a long.
     */
    long ToInt() {
        int32_t value;
        m_Value.GetInt32(&value);
        return value;
    }

    /**
     * @brief Converts the integer value to a long long.
     * @note This may result in data loss if the value is outside the range of a long long.
     * @return The value as a long long.
     */
    long long ToLong() {
        int64_t value;
        m_Value.GetInt64(&value);
        return value;
    }

    /**
     * @brief Converts the integer to its string representation.
     *
     * The conversion is based on the size of the underlying byte buffer.
     *
     * @return A string representation of the integer value.
     */
    std::string ToString() {
        std::string str;
        switch (m_Value.GetSize()) {
            case 1:
                str = GXHelpers::IntToString(ToByte());
                break;
            case 2:
                str = GXHelpers::IntToString(ToShort());
                break;
            case 4:
                str = GXHelpers::IntToString(ToInt());
                break;
            case 8:
                str = std::to_string(ToLong());
                break;
            default:
                str = "Invalid value.";
                break;
        }
        return str;
    }
};

#endif  //GXASN1INTEGER_H
