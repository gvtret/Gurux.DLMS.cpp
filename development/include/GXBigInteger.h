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

#ifndef GXBIGINTEGER_H
#define GXBIGINTEGER_H

#include "GXBytebuffer.h"
#include "GXByteArray.h"

/**
 * @brief Provides functionality for handling arbitrarily large integers.
 *
 * This class is essential for cryptographic operations that require numbers
 * much larger than standard 64-bit integers. It supports arithmetic operations
 * like addition, subtraction, multiplication, division, and modular exponentiation.
 */
class CGXBigInteger {
private:
    friend class CGXPrivateKey;
    /**
     * @brief An array of 32-bit unsigned integers storing the value. The least significant part is at index 0.
     */
    uint32_t *m_Data;

    /**
     * @brief The number of 32-bit integers currently used in the data buffer.
     */
    uint16_t m_Count;

    /**
     * @brief The allocated capacity of the data buffer, in number of 32-bit integers.
     */
    uint16_t m_Capacity;

    /**
     * @brief A flag indicating whether the value is negative.
     */
    bool m_IsNegative;

    /**
     * @brief Initializes the big integer from a byte buffer.
     * @param value The byte buffer, with data in Most Significant Bit (MSB) format.
     * @return 0 on success, or an error code.
     */
    int FromByteBuffer(CGXByteBuffer &value);

    /**
     * @brief Initializes the big integer from a byte array.
     * @param value The byte array, with data in MSB format.
     * @return 0 on success, or an error code.
     */
    int FromByteBuffer(CGXByteArray &value);

    /**
     * @brief Sets the sign of the number.
     * @param value True for negative, false for positive.
     */
    void SetIsNegative(bool value);

    /**
     * @brief Internal helper to add a 32-bit integer value.
     * @param value The value to add.
     * @return 0 on success.
     */
    int Add(const uint32_t value);

    /**
     * @brief Internal helper for addition.
     */
    int AddValue(uint32_t *list, uint16_t length, uint32_t value, uint16_t index);

    /**
     * @brief Ensures the internal buffer has enough capacity.
     * @param value The required capacity.
     * @return 0 on success.
     */
    int Capacity(uint16_t value);

public:
    /**
     * @brief Default constructor. Initializes to zero.
     */
    CGXBigInteger();

    /**
     * @brief Constructor that initializes from a hexadecimal string.
     * @param value A string containing the big integer value in hexadecimal format (MSB first).
     */
    CGXBigInteger(std::string &value);

    /**
     * @brief Constructor for 64-bit unsigned integer.
     * @param value The initial value.
     */
    CGXBigInteger(uint64_t value);

    /**
     * @brief Constructor for 32-bit unsigned integer.
     * @param value The initial value.
     */
    CGXBigInteger(uint32_t value);

    /**
     * @brief Constructor for signed integer.
     * @param value The initial value.
     */
    CGXBigInteger(int value);

    /**
     * @brief Constructor that initializes from an array of 32-bit integers.
     * @param values A pointer to the array of uint32_t values.
     * @param count The number of values in the array.
     */
    CGXBigInteger(const uint32_t *values, uint16_t count);

    /**
     * @brief Constructor that initializes from a byte array.
     * @param values A pointer to the byte array (MSB format).
     * @param count The number of bytes in the array.
     */
    CGXBigInteger(const unsigned char *values, uint16_t count);

    /**
     * @brief Constructor that initializes from a byte buffer.
     * @param value The byte buffer (MSB format).
     */
    CGXBigInteger(CGXByteBuffer &value);

    /**
     * @brief Constructor that initializes from a byte array object.
     * @param value The byte array object (MSB format).
     */
    CGXBigInteger(CGXByteArray &value);

    /**
     * @brief Copy constructor from a pointer.
     * @param value The object to copy.
     */
    CGXBigInteger(CGXBigInteger *value);

    /**
     * @brief Copy constructor.
     * @param value The object to copy.
     */
    CGXBigInteger(const CGXBigInteger &value);

    /**
     * @brief Destructor.
     */
    ~CGXBigInteger();

    /**
     * @brief Gets the number of 32-bit integers used.
     * @return The count.
     */
    uint16_t GetCount();

    /**
     * @brief Sets the number of 32-bit integers used.
     * @param value The new count.
     */
    void SetCount(uint16_t value);

    /**
     * @brief Checks if the value is negative.
     * @return True if negative.
     */
    bool IsNegative();

    /**
     * @brief Checks if the value is zero.
     * @return True if zero.
     */
    bool IsZero();

    /**
     * @brief Checks if the value is even.
     * @return True if even.
     */
    bool IsEven();

    /**
     * @brief Checks if the value is one.
     * @return True if one.
     */
    bool IsOne();

    /**
     * @brief Converts the value to a byte array.
     * @param[out] data The byte buffer to store the result in.
     * @param removeLeadingZeroes If true, any leading zero bytes are omitted.
     * @return 0 on success, or an error code.
     */
    int ToArray(CGXByteBuffer &data, bool removeLeadingZeroes);

    /**
     * @brief Converts the value to a byte array, preserving leading zeros.
     * @param[out] data The byte buffer to store the result in.
     * @return 0 on success, or an error code.
     */
    int ToArray(CGXByteBuffer &data);

    /**
     * @brief Converts a specific part of the value to a byte array.
     * @param start The starting 32-bit chunk index.
     * @param size The number of 32-bit chunks to convert.
     * @param[out] data The byte buffer to store the result in.
     * @return 0 on success, or an error code.
     */
    int ToArray(uint32_t start, uint32_t size, CGXByteBuffer &data);

    /**
     * @brief Adds a range of 32-bit integers.
     * @param values Pointer to the array.
     * @param count Number of items.
     * @return 0 on success.
     */
    int AddRange(const uint32_t *values, uint16_t count);

    /**
     * @brief Performs a bitwise OR operation.
     * @param value The other operand.
     */
    void Or(CGXBigInteger &value);

    /**
     * @brief Adds another big integer.
     * @param value The value to add.
     * @return 0 on success.
     */
    int Add(CGXBigInteger &value);

    /**
     * @brief Subtracts another big integer.
     * @param value The value to subtract.
     */
    void Sub(CGXBigInteger &value);

    /**
     * @brief Multiplies by a standard integer.
     * @param value The multiplier.
     */
    void Multiply(int value);

    /**
     * @brief Multiplies by another big integer.
     * @param value The multiplier.
     */
    void Multiply(CGXBigInteger &value);

    /**
     * @brief Compares this big integer with another.
     * @param value The big integer to compare against.
     * @return 1 if this is greater, -1 if smaller, 0 if equal.
     */
    int Compare(CGXBigInteger &value);

    /**
     * @brief Compares this big integer with a 32-bit unsigned integer.
     * @param value The integer to compare against.
     * @return 1 if this is greater, -1 if smaller, 0 if equal.
     */
    int Compare(uint32_t value);

    /**
     * @brief Performs a left bit shift.
     * @param amount The number of bits to shift.
     */
    void Lshift(uint32_t amount);

    /**
     * @brief Performs a right bit shift.
     * @param amount The number of bits to shift.
     */
    void Rshift(uint32_t amount);

    /**
     * @brief Resets the value to zero.
     */
    void Clear();

    /**
     * @brief Calculates the power of the number (exponentiation).
     * @param exponent The exponent.
     */
    void Pow(uint32_t exponent);

    /**
     * @brief Divides by another big integer.
     * @param value The divisor.
     */
    void Div(CGXBigInteger *value);

    /**
     * @brief Performs a modulus operation.
     * @param mod The modulus.
     */
    void Mod(CGXBigInteger &mod);

    /**
     * @brief Calculates the modular multiplicative inverse.
     * @param value The modulus.
     */
    void Inv(CGXBigInteger &value);

    /**
     * @brief Converts the big integer to a string representation.
     * @return The string value.
     */
    std::string ToString();

    /**
     * @brief Assignment operator.
     * @param value The object to assign from.
     * @return A reference to this object.
     */
    CGXBigInteger &operator=(const CGXBigInteger &value);

    /**
     * @brief Gets the number of bits used to represent the value.
     * @return The number of used bits.
     */
    uint16_t GetUsedBits();

    /**
     * @brief Checks if a specific bit is set.
     * @param index The index of the bit to check.
     * @return True if the bit is set, false otherwise.
     */
    bool IsBitSet(uint16_t index);
};
#endif  //GXBIGINTEGER_H
