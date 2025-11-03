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
 * @brief Represents a dynamic, readable, and writable buffer of bytes.
 *
 * This class provides a stream-like interface for a byte buffer, maintaining
 * a position for sequential reading and writing. It is optimized for serialization
 * and deserialization of various data types.
 */
class CGXByteBuffer {
    /** @brief The internal vector that stores the byte data. */
    std::vector<uint8_t> m_Data;
    /** @brief The current read/write position in the buffer. */
    uint32_t m_Position;

public:
    /** @brief Default constructor. */
    CGXByteBuffer();
    /** @brief Constructor with initial capacity. @param capacity The initial capacity. */
    explicit CGXByteBuffer(int capacity);
    /** @brief Copy constructor. @param value The object to copy. */
    CGXByteBuffer(const CGXByteBuffer &value);
    /** @brief Move constructor. @param value The object to move from. */
    CGXByteBuffer(CGXByteBuffer &&value) noexcept;
    /** @brief Default destructor. */
    ~CGXByteBuffer() = default;

    /** @brief Copy assignment operator. @param value The source. @return A reference to this object. */
    CGXByteBuffer &operator=(const CGXByteBuffer &value);
    /** @brief Move assignment operator. @param value The source. @return A reference to this object. */
    CGXByteBuffer &operator=(CGXByteBuffer &&value) noexcept;

    /** @brief Gets the number of bytes available for reading. @return The number of available bytes. */
    uint32_t Available() const;
    /** @brief Gets the total size of the data in the buffer. @return The size in bytes. */
    uint32_t GetSize() const;
    /** @brief Sets the size of the buffer. @param value The new size. */
    void SetSize(uint32_t value);
    /** @brief Increases the size of the buffer by a given amount. @param size The number of bytes to add. @return 0 on success. */
    int IncreaseSize(uint32_t size);
    /** @brief Gets the current read/write position. @return The current position. */
    uint32_t GetPosition() const;
    /** @brief Sets the current read/write position. @param value The new position. */
    void SetPosition(uint32_t value);
    /** @brief Sets the capacity of the internal vector. @param capacity The new capacity. @return 0 on success. */
    int Capacity(uint32_t capacity);
    /** @brief Gets the current capacity of the buffer. @return The capacity in bytes. */
    uint32_t Capacity() const;
    /** @brief Clears the buffer's content and resets its position and size. */
    void Clear();

    /** @brief Fills a portion of the buffer with zeros. @param index The starting index. @param count The number of bytes to zero out. */
    void Zero(uint32_t index, uint32_t count);
    /** @brief Appends an unsigned 8-bit integer. @param item The value to append. @return 0 on success. */
    int SetUInt8(uint8_t item);
    /** @brief Sets an unsigned 8-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
    int SetUInt8(uint32_t index, uint8_t item);
    /** @brief Appends an unsigned 16-bit integer. @param item The value to append. @return 0 on success. */
    int SetUInt16(uint16_t item);
    /** @brief Sets an unsigned 16-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
    int SetUInt16(uint32_t index, uint16_t item);
    /** @brief Appends an unsigned 32-bit integer. @param item The value to append. @return 0 on success. */
    int SetUInt32(uint32_t item);
    /** @brief Sets an unsigned 32-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
    int SetUInt32ByIndex(uint32_t index, uint32_t item);
    /** @brief Appends an unsigned 64-bit integer. @param item The value to append. @return 0 on success. */
    int SetUInt64(uint64_t item);
    /** @brief Appends a signed 8-bit integer. @param item The value to append. @return 0 on success. */
    int SetInt8(char item);
    /** @brief Appends a signed 16-bit integer. @param item The value to append. @return 0 on success. */
    int SetInt16(int16_t item);
    /** @brief Appends a signed 32-bit integer. @param item The value to append. @return 0 on success. */
    int SetInt32(int32_t item);
    /** @brief Appends a signed 64-bit integer. @param item The value to append. @return 0 on success. */
    int SetInt64(int64_t item);
    /** @brief Appends a float. @param value The value to append. @return 0 on success. */
    int SetFloat(float value);
    /** @brief Appends a double. @param value The value to append. @return 0 on success. */
    int SetDouble(double value);
    /** @brief Appends a block of memory. @param pSource Pointer to the source data. @param count Number of bytes to append. @return 0 on success. */
    int Set(const void *pSource, uint32_t count);
    /** @brief Appends data from another CGXByteBuffer. @param data The source buffer. @param index Starting index in source. @param count Number of bytes to append. @return 0 on success. */
    int Set(CGXByteBuffer *data, uint32_t index = 0, uint32_t count = -1);

    /** @brief Appends a standard string. @param value The string to append. @return 0 on success. */
    int AddString(const std::string &value);
    /** @brief Appends a standard string (rvalue). @param value The string to append. @return 0 on success. */
    int AddString(std::string &&value);
    /** @brief Appends a wide string. @param value The string to append. @return 0 on success. */
    int AddString(const std::wstring &value);
    /** @brief Appends a C-style string. @param value The string to append. @return 0 on success. */
    int AddString(const char *value);

    /** @brief Reads an unsigned 8-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt8(uint8_t *value);
    /** @brief Reads an unsigned 8-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt8(uint32_t index, uint8_t *value);
    /** @brief Reads an unsigned 16-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt16(uint16_t *value);
    /** @brief Reads an unsigned 16-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt16(uint32_t index, uint16_t *value);
    /** @brief Reads an unsigned 24-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt24(unsigned int *value);
    /** @brief Reads an unsigned 24-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt24(uint32_t index, unsigned int *value);
    /** @brief Reads an unsigned 32-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt32(uint32_t *value);
    /** @brief Reads an unsigned 32-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt32(uint32_t index, uint32_t *value);
    /** @brief Reads an unsigned 64-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt64(uint64_t *value);
    /** @brief Reads an unsigned 64-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt64(uint32_t index, uint64_t *value);
    /** @brief Reads an unsigned 128-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetUInt128(uint32_t index, uint8_t *value);
    /** @brief Reads a signed 8-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetInt8(char *value);
    /** @brief Reads a signed 16-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetInt16(int16_t *value);
    /** @brief Reads a signed 32-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetInt32(int32_t *value);
    /** @brief Reads a signed 64-bit integer from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetInt64(int64_t *value);
    /** @brief Reads a float from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetFloat(float *value);
    /** @brief Reads a double from the current position. @param[out] value Pointer to store the result. @return 0 on success. */
    int GetDouble(double *value);
    /** @brief Reads a block of bytes from the current position. @param[out] value Destination buffer. @param count Number of bytes to read. @return 0 on success. */
    int Get(uint8_t *value, uint32_t count);

    /** @brief Gets a direct pointer to the underlying data. @return A pointer to the data. */
    uint8_t *GetData();
    /** @brief Gets a const direct pointer to the underlying data. @return A const pointer to the data. */
    const uint8_t *GetData() const;
    /** @brief Copies the data to a new array. @param[out] value Pointer to the new array. @param[out] count The size of the array. */
    void ToArray(uint8_t *&value, uint32_t &count);
    /** @brief Extracts a sub-array into a new byte buffer. @param index Starting index. @param count Number of bytes. @param[out] bb The destination buffer. @return 0 on success. */
    int SubArray(uint32_t index, int count, CGXByteBuffer &bb);
    /** @brief Moves a block of data within the buffer. @param srcPos Source position. @param destPos Destination position. @param count Number of bytes. @return 0 on success. */
    int Move(uint32_t srcPos, uint32_t destPos, uint32_t count);
    /** @brief Removes unused capacity from the buffer. */
    void Trim();
    /** @brief Reverses a portion of the buffer. @param index Starting index. @param count Number of bytes. */
    void Reverse(uint32_t index, uint32_t count);

    /** @brief Compares the buffer's content with a raw byte array. @param buff The array to compare. @param length The number of bytes to compare. @return True if equal. */
    bool Compare(const uint8_t *buff, uint32_t length) const;
    /** @brief Compares this buffer with another. @param other The other buffer. @return True if equal. */
    bool Compare(const CGXByteBuffer &other) const;
    /** @brief Checks if the buffer contains only ASCII characters. @return True if ASCII. */
    bool IsAsciiString();
    /** @brief Checks if a raw byte array contains only ASCII characters. @param value The array. @param length The length. @return True if ASCII. */
    static bool IsAsciiString(uint8_t *value, uint32_t length);

    /** @brief Converts the buffer to a readable string. @return The string representation. */
    std::string ToString() const;
    /** @brief Converts the buffer to a hexadecimal string. @return The hex string. */
    std::string ToHexString() const;
    /** @brief Converts the buffer to a hexadecimal string. @param addSpaces True to add spaces between bytes. @return The hex string. */
    std::string ToHexString(bool addSpaces) const;
    /** @brief Converts a portion of the buffer to a hexadecimal string. @param position Start position. @param count Number of bytes. @param addSpaces True to add spaces. @return The hex string. */
    std::string ToHexString(uint32_t position, uint32_t count, bool addSpaces) const;

    /** @brief Appends an integer as its string representation. @param value The integer. */
    void AddIntAsString(int value);
    /** @brief Appends a double as its string representation. @param value The double. */
    void AddDoubleAsString(double value);

    /** @brief Appends a hexadecimal string. @param value The hex string. */
    void SetHexString(std::string &value);
    /** @brief Appends a hexadecimal string (rvalue). @param value The hex string. */
    void SetHexString(std::string &&value);

    /** @brief Reads a string of a given length from the current position. @param count Number of bytes. @param[out] value The resulting string. @return 0 on success. */
    int GetString(int count, std::string &value);
    /** @brief Reads a string from a specific index. @param index The index. @param count Number of bytes. @param[out] value The resulting string. @return 0 on success. */
    int GetString(uint32_t index, uint32_t count, std::string &value);
    /** @brief Reads a UTF-8 string from a specific index. @param index The index. @param count Number of bytes. @param[out] value The resulting string. @return 0 on success. */
    int GetStringUnicode(uint32_t index, uint32_t count, std::string &value);
    /** @brief Reads a Unicode (wide) string from a specific index. @param index The index. @param count Number of bytes. @param[out] value The resulting wide string. @return 0 on success. */
    int GetStringUnicode(uint32_t index, uint32_t count, std::wstring &value);

    /** @brief Populates the buffer from a Base64 encoded string. @param input The Base64 string. @return 0 on success. */
    int FromBase64(std::string &input);
    /** @brief Converts the buffer to a Base64 encoded string. @param[out] value The resulting Base64 string. @return 0 on success. */
    int ToBase64(std::string &value) const;

    /** @brief Swaps the contents of this buffer with another. @param other The other buffer. */
    void Swap(CGXByteBuffer &other) noexcept;
};

#endif  // GXBYTEBUFFER_H
