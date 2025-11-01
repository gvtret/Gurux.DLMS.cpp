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

#ifndef GXBYTEBUFFER_H
#define GXBYTEBUFFER_H

#include "enums.h"
#include "errorcodes.h"
#include <string>
#include <vector>
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include <cstdint>
#endif  // defined(_WIN32) || defined(_WIN64) || defined(__linux__)

const uint8_t VECTOR_CAPACITY = 50;

/**
 * @brief Represents a buffer of bytes that can be manipulated.
 */
class CGXByteBuffer {
    std::vector<uint8_t> m_Data;
    uint32_t m_Position;

public:
    /**
     * @brief Default constructor.
     */
    CGXByteBuffer();

    /**
     * @brief Constructor with initial capacity.
     * @param capacity The initial capacity of the buffer.
     */
    explicit CGXByteBuffer(int capacity);

    /**
     * @brief Copy constructor.
     * @param value The object to copy.
     */
    CGXByteBuffer(const CGXByteBuffer &value);

    /**
     * @brief Move constructor.
     * @param value The object to move.
     */
    CGXByteBuffer(CGXByteBuffer &&value) noexcept;

    /**
     * @brief Destructor.
     */
    ~CGXByteBuffer() = default;

    /**
     * @brief Copy assignment operator.
     * @param value The object to copy.
     * @return A reference to this object.
     */
    CGXByteBuffer &operator=(const CGXByteBuffer &value);

    /**
     * @brief Move assignment operator.
     * @param value The object to move.
     * @return A reference to this object.
     */
    CGXByteBuffer &operator=(CGXByteBuffer &&value) noexcept;  // Move assignment

    /**
     * @brief Gets the number of bytes available to be read.
     * @return The number of available bytes.
     */
    uint32_t Available() const;

    /**
     * @brief Gets the size of the buffer.
     * @return The size of the buffer.
     */
    uint32_t GetSize() const;

    /**
     * @brief Sets the size of the buffer.
     * @param value The new size.
     */
    void SetSize(uint32_t value);

    /**
     * @brief Increases the size of the buffer.
     * @param size The amount to increase the size by.
     * @return An error code.
     */
    int IncreaseSize(uint32_t size);

    /**
     * @brief Gets the current position in the buffer.
     * @return The current position.
     */
    uint32_t GetPosition() const;

    /**
     * @brief Sets the current position in the buffer.
     * @param value The new position.
     */
    void SetPosition(uint32_t value);

    /**
     * @brief Sets the capacity of the buffer.
     * @param capacity The new capacity.
     * @return An error code.
     */
    int Capacity(uint32_t capacity);

    /**
     * @brief Gets the capacity of the buffer.
     * @return The capacity.
     */
    uint32_t Capacity() const;

    /**
     * @brief Clears the buffer.
     */
    void Clear();

    /**
     * @brief Sets the buffer to zeros.
     * @param index The starting index.
     * @param count The number of bytes to zero.
     */
    void Zero(uint32_t index, uint32_t count);

    /**
     * @brief Sets a UInt8 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt8(uint8_t item);

    /**
     * @brief Sets a UInt8 value at a specific index.
     * @param index The index.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt8(uint32_t index, uint8_t item);

    /**
     * @brief Sets a UInt16 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt16(uint16_t item);

    /**
     * @brief Sets a UInt16 value at a specific index.
     * @param index The index.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt16(uint32_t index, uint16_t item);

    /**
     * @brief Sets a UInt32 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt32(uint32_t item);

    /**
     * @brief Sets a UInt32 value at a specific index.
     * @param index The index.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt32ByIndex(uint32_t index, uint32_t item);

    /**
     * @brief Sets a UInt64 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetUInt64(uint64_t item);

    /**
     * @brief Sets an Int8 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetInt8(char item);

    /**
     * @brief Sets an Int16 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetInt16(int16_t item);

    /**
     * @brief Sets an Int32 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetInt32(int32_t item);

    /**
     * @brief Sets an Int64 value at the current position.
     * @param item The value to set.
     * @return An error code.
     */
    int SetInt64(int64_t item);

    /**
     * @brief Sets a float value at the current position.
     * @param value The value to set.
     * @return An error code.
     */
    int SetFloat(float value);

    /**
     * @brief Sets a double value at the current position.
     * @param value The value to set.
     * @return An error code.
     */
    int SetDouble(double value);

    /**
     * @brief Sets a block of data at the current position.
     * @param pSource A pointer to the source data.
     * @param count The number of bytes to set.
     * @return An error code.
     */
    int Set(const void *pSource, uint32_t count);

    /**
     * @brief Sets data from another byte buffer.
     * @param data The source buffer.
     * @param index The starting index in the source buffer.
     * @param count The number of bytes to set.
     * @return An error code.
     */
    int Set(CGXByteBuffer *data, uint32_t index = 0, uint32_t count = -1);

    /**
     * @brief Adds a string to the buffer.
     * @param value The string to add.
     * @return An error code.
     */
    int AddString(const std::string &value);

    /**
     * @brief Adds a string to the buffer.
     * @param value The string to add.
     * @return An error code.
     */
    int AddString(std::string &&value);

    /**
     * @brief Adds a wide string to the buffer.
     * @param value The wide string to add.
     * @return An error code.
     */
    int AddString(const std::wstring &value);

    /**
     * @brief Adds a C-style string to the buffer.
     * @param value The C-style string to add.
     * @return An error code.
     */
    int AddString(const char *value);

    /**
     * @brief Gets a UInt8 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt8(uint8_t *value);

    /**
     * @brief Gets a UInt8 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt8(uint32_t index, uint8_t *value);

    /**
     * @brief Gets a UInt16 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt16(uint16_t *value);

    /**
     * @brief Gets a UInt16 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt16(uint32_t index, uint16_t *value);

    /**
     * @brief Gets a UInt24 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt24(unsigned int *value);

    /**
     * @brief Gets a UInt24 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt24(uint32_t index, unsigned int *value);

    /**
     * @brief Gets a UInt32 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt32(uint32_t *value);

    /**
     * @brief Gets a UInt32 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt32(uint32_t index, uint32_t *value);

    /**
     * @brief Gets a UInt64 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt64(uint64_t *value);

    /**
     * @brief Gets a UInt64 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt64(uint32_t index, uint64_t *value);

    /**
     * @brief Gets a UInt128 value from a specific index.
     * @param index The index.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetUInt128(uint32_t index, uint8_t *value);

    /**
     * @brief Gets an Int8 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetInt8(char *value);

    /**
     * @brief Gets an Int16 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetInt16(int16_t *value);

    /**
     * @brief Gets an Int32 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetInt32(int32_t *value);

    /**
     * @brief Gets an Int64 value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetInt64(int64_t *value);

    /**
     * @brief Gets a float value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetFloat(float *value);

    /**
     * @brief Gets a double value from the current position.
     * @param value A pointer to store the result.
     * @return An error code.
     */
    int GetDouble(double *value);

    /**
     * @brief Gets a block of data from the current position.
     * @param value A pointer to store the result.
     * @param count The number of bytes to get.
     * @return An error code.
     */
    int Get(uint8_t *value, uint32_t count);

    /**
     * @brief Gets a pointer to the raw data.
     * @return A pointer to the data.
     */
    uint8_t *GetData();

    /**
     * @brief Gets a const pointer to the raw data.
     * @return A const pointer to the data.
     */
    const uint8_t *GetData() const;

    /**
     * @brief Converts the buffer to an array.
     * @param value A reference to a pointer to store the array.
     * @param count A reference to store the size of the array.
     */
    void ToArray(uint8_t *&value, uint32_t &count);

    /**
     * @brief Creates a sub-array from the buffer.
     * @param index The starting index.
     * @param count The number of bytes in the sub-array.
     * @param bb The byte buffer to store the sub-array in.
     * @return An error code.
     */
    int SubArray(uint32_t index, int count, CGXByteBuffer &bb);

    /**
     * @brief Moves a block of data within the buffer.
     * @param srcPos The source position.
     * @param destPos The destination position.
     * @param count The number of bytes to move.
     * @return An error code.
     */
    int Move(uint32_t srcPos, uint32_t destPos, uint32_t count);

    /**
     * @brief Trims the buffer to the current position.
     */
    void Trim();

    /**
     * @brief Reverses a block of data in the buffer.
     * @param index The starting index.
     * @param count The number of bytes to reverse.
     */
    void Reverse(uint32_t index, uint32_t count);

    /**
     * @brief Compares the buffer with another buffer.
     * @param buff The buffer to compare with.
     * @param length The length of the buffer to compare.
     * @return True if the buffers are equal, false otherwise.
     */
    bool Compare(const uint8_t *buff, uint32_t length) const;

    /**
     * @brief Compares the buffer with another CGXByteBuffer.
     * @param other The other buffer.
     * @return True if the buffers are equal, false otherwise.
     */
    bool Compare(const CGXByteBuffer &other) const;

    /**
     * @brief Checks if the buffer contains an ASCII string.
     * @return True if the buffer is an ASCII string, false otherwise.
     */
    bool IsAsciiString();

    /**
     * @brief Checks if a buffer contains an ASCII string.
     * @param value The buffer.
     * @param length The length of the buffer.
     * @return True if the buffer is an ASCII string, false otherwise.
     */
    static bool IsAsciiString(uint8_t *value, uint32_t length);

    /**
     * @brief Converts the buffer to a string.
     * @return The string representation of the buffer.
     */
    std::string ToString() const;

    /**
     * @brief Converts the buffer to a hex string.
     * @return The hex string representation of the buffer.
     */
    std::string ToHexString() const;

    /**
     * @brief Converts the buffer to a hex string.
     * @param addSpaces Whether to add spaces between bytes.
     * @return The hex string representation of the buffer.
     */
    std::string ToHexString(bool addSpaces) const;

    /**
     * @brief Converts a portion of the buffer to a hex string.
     * @param position The starting position.
     * @param count The number of bytes to convert.
     * @param addSpaces Whether to add spaces between bytes.
     * @return The hex string representation of the buffer portion.
     */
    std::string ToHexString(uint32_t position, uint32_t count, bool addSpaces) const;

    /**
     * @brief Adds an integer to the buffer as a string.
     * @param value The integer to add.
     */
    void AddIntAsString(int value);

    /**
     * @brief Adds a double to the buffer as a string.
     * @param value The double to add.
     */
    void AddDoubleAsString(double value);

    /**
     * @brief Sets the buffer from a hex string.
     * @param value The hex string.
     */
    void SetHexString(std::string &value);

    /**
     * @brief Sets the buffer from a hex string.
     * @param value The hex string.
     */
    void SetHexString(std::string &&value);

    /**
     * @brief Gets a string from the buffer.
     * @param count The number of bytes in the string.
     * @param value A reference to store the result.
     * @return An error code.
     */
    int GetString(int count, std::string &value);

    /**
     * @brief Gets a string from the buffer.
     * @param index The starting index.
     * @param count The number of bytes in the string.
     * @param value A reference to store the result.
     * @return An error code.
     */
    int GetString(uint32_t index, uint32_t count, std::string &value);

    /**
     * @brief Gets a Unicode string from the buffer.
     * @param index The starting index.
     * @param count The number of bytes in the string.
     * @param value A reference to store the result.
     * @return An error code.
     */
    int GetStringUnicode(uint32_t index, uint32_t count, std::string &value);

    /**
     * @brief Gets a Unicode string from the buffer.
     * @param index The starting index.
     * @param count The number of bytes in the string.
     * @param value A reference to store the result.
     * @return An error code.
     */
    int GetStringUnicode(uint32_t index, uint32_t count, std::wstring &value);

    /**
     * @brief Sets the buffer from a Base64 string.
     * @param input The Base64 string.
     * @return An error code.
     */
    int FromBase64(std::string &input);

    /**
     * @brief Converts the buffer to a Base64 string.
     * @param value A reference to store the result.
     * @return An error code.
     */
    int ToBase64(std::string &value) const;

    /**
     * @brief Swaps the contents of this buffer with another.
     * @param other The other buffer.
     */
    void Swap(CGXByteBuffer &other) noexcept;
};

#endif  // GXBYTEBUFFER_H
