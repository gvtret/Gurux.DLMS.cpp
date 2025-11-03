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

#ifndef GXASN1BITSTRING_H
#define GXASN1BITSTRING_H

#include "GXHelpers.h"
#include "GXBytebuffer.h"
#include "GXByteArray.h"
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 BIT STRING, a data structure that holds a sequence of bits.
 *
 * This class provides functionality to create, manipulate, and convert ASN.1
 * BIT STRINGs. It handles the padding required to store a bit sequence in
 * a byte-aligned buffer.
 */
class CGXAsn1BitString: public CGXAsn1Base {
private:
    /**
    * @brief The number of unused bits in the last byte of the value.
    */
    unsigned char m_PadBits;

    /**
     * @brief The byte buffer holding the bit string data.
     */
    CGXByteBuffer m_Value;

    /**
     * @brief Appends a specified number of zero characters to a string.
     * @param sb The string builder (string) to append to.
     * @param count The number of zeros to append.
     */
    static void AppendZeros(std::string &sb, int count) {
        for (int pos = 0; pos != count; ++pos) {
            sb += '0';
        }
    }

public:
    /**
     * @brief Default constructor. Initializes an empty bit string.
     */
    CGXAsn1BitString() {
        m_PadBits = 0;
    }

    /**
     * @brief Constructor that initializes from a string of '0's and '1's.
     * @param bitString A string representing the bit sequence.
     */
    CGXAsn1BitString(std::string &bitString) {
        m_PadBits = 8 - (bitString.length() % 8);
        if (m_PadBits == 8) {
            m_PadBits = 0;
        }
        std::string sb = bitString;
        AppendZeros(sb, m_PadBits);
        CGXDLMSVariant value = sb;
        m_Value.Capacity((unsigned long)(sb.length() / 8));
        GXHelpers::SetBitString(m_Value, value, false);
    }

    /**
     * @brief Constructor that initializes from a byte buffer and a pad count.
     * @param str The byte buffer containing the bit string data.
     * @param padCount The number of unused bits in the last byte.
     */
    CGXAsn1BitString(CGXByteBuffer &str, int padCount) {
        m_Value = str;
        m_PadBits = padCount;
    }

    /**
     * @brief Constructor that initializes from a byte array and a pad count.
     * @param str The byte array containing the bit string data.
     * @param padCount The number of unused bits in the last byte.
     */
    CGXAsn1BitString(CGXByteArray &str, int padCount) {
        str.ToByteBuffer(m_Value);
        m_PadBits = padCount;
    }

    /**
     * @brief Constructor that initializes from a byte buffer where the first
     *        byte is the pad count.
     * @param str The byte buffer containing the pad count followed by the bit string data.
     */
    CGXAsn1BitString(CGXByteBuffer &str) {
        str.GetUInt8(&m_PadBits);
        str.SubArray(1, str.Available(), m_Value);
    }

    /**
     * @brief Gets the underlying byte buffer containing the bit string.
     * @return A reference to the internal byte buffer.
     */
    CGXByteBuffer &GetValue() {
        return m_Value;
    }

    /**
     * @brief Gets the number of unused bits in the last byte.
     * @return The number of pad bits.
     */
    int GetPadBits() {
        return m_PadBits;
    }

    /**
     * @brief Calculates the exact length of the bit string in bits.
     * @return The total number of bits.
     */
    int Length() {
        return (8 * m_Value.GetSize()) - m_PadBits;
    }

    /**
     * @brief Converts the bit string to a human-readable string format.
     * @return A string describing the bit string's length and content.
     */
    std::string ToString() {
        if (m_Value.GetSize() == 0) {
            return "";
        }
        std::string str;
        str += std::to_string((8 * m_Value.GetSize()) - m_PadBits);
        str += " bit ";
        str += AsString();
        return str;
    }

    /**
     * @brief Converts the bit string's content to a string of '0's and '1's.
     * @return A string representing the bit sequence.
     */
    std::string AsString() {
        if (m_Value.GetSize() == 0) {
            return "";
        }
        CGXByteBuffer bb;
        for (unsigned long pos = 0; pos != m_Value.GetSize(); ++pos) {
            GXHelpers::ToBitString(bb, m_Value.GetData()[pos], 8);
        }
        bb.SetSize(bb.GetSize() - m_PadBits);
        return bb.ToString();
    }

    /**
     * @brief Converts the bit string value to an integer.
     *
     * This method is suitable for bit strings that represent a numeric value
     * and are short enough to fit into an integer.
     *
     * @return The integer representation of the bit string.
     */
    int ToInteger() {
        int ret = 0;
        int bytePos = 0;
        for (unsigned long pos = 0; pos != m_Value.GetSize(); ++pos) {
            ret |= (int)(GXHelpers::SwapBits(m_Value.GetData()[pos]) << bytePos);
            bytePos += 8;
        }
        return ret;
    }
};

#endif  //GXASN1BITSTRING_H
