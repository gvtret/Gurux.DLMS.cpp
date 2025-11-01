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
 * @brief Represents a dynamic byte buffer.
 *
 * This class provides methods to manipulate a sequence of bytes,
 * including reading, writing, and modifying data of various types.
 */
class CGXByteBuffer {
    std::vector<uint8_t> m_Data;
    uint32_t m_Position;

public:
    /**
     * @brief Default constructor. Initializes an empty byte buffer.
     */
    CGXByteBuffer();
    /**
     * @brief Constructs a byte buffer with a specified initial capacity.
     * @param capacity The initial capacity of the buffer.
     */
    explicit CGXByteBuffer(int capacity);
    /**
     * @brief Copy constructor.
     * @param value The byte buffer to copy from.
     */
    CGXByteBuffer(const CGXByteBuffer &value);
    /**
     * @brief Move constructor.
     * @param value The byte buffer to move from.
     */
    CGXByteBuffer(CGXByteBuffer &&value) noexcept;
    /**
     * @brief Destructor.
     */
    ~CGXByteBuffer() = default;

    /**
     * @brief Copy assignment operator.
     * @param value The byte buffer to copy from.
     * @return A reference to this byte buffer.
     */
    CGXByteBuffer &operator=(const CGXByteBuffer &value);
    /**
     * @brief Move assignment operator.
     * @param value The byte buffer to move from.
     * @return A reference to this byte buffer.
     */
    CGXByteBuffer &operator=(CGXByteBuffer &&value) noexcept;  // Move assignment

    /**
     * @brief Gets the number of bytes available for reading.
     * @return The number of bytes from the current position to the end of the buffer.
     */
    uint32_t Available() const;
    /**
     * @brief Gets the total size of the buffer.
     * @return The size of the buffer in bytes.
     */
    uint32_t GetSize() const;
    /**
     * @brief Sets the size of the buffer.
     * @param value The new size of the buffer.
     */
    void SetSize(uint32_t value);
    /**
     * @brief Increases the size of the buffer.
     * @param size The number of bytes to add to the buffer's size.
     * @return 0 on success, an error code otherwise.
     */
    int IncreaseSize(uint32_t size);
    /**
     * @brief Gets the current read/write position in the buffer.
     * @return The current position.
     */
    uint32_t GetPosition() const;
    /**
     * @brief Sets the current read/write position in the buffer.
     * @param value The new position.
     */
    void SetPosition(uint32_t value);
    /**
     * @brief Sets the capacity of the buffer.
     * @param capacity The new capacity.
     * @return 0 on success, an error code otherwise.
     */
    int Capacity(uint32_t capacity);
    /**
     * @brief Gets the current capacity of the buffer.
     * @return The capacity of the buffer.
     */
    uint32_t Capacity() const;
    /**
     * @brief Clears the buffer, resetting its size and position.
     */
    void Clear();

    //	int Set(const CGXByteBuffer &value);

    /**
     * @brief Fills a portion of the buffer with zeros.
     * @param index The starting index.
     * @param count The number of bytes to zero out.
     */
    void Zero(uint32_t index, uint32_t count);
    /**
     * @brief Writes a uint8_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt8(uint8_t item);
    /**
     * @brief Writes a uint8_t value at a specific index.
     * @param index The index at which to write.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt8(uint32_t index, uint8_t item);
    /**
     * @brief Writes a uint16_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt16(uint16_t item);
    /**
     * @brief Writes a uint16_t value at a specific index.
     * @param index The index at which to write.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt16(uint32_t index, uint16_t item);
    /**
     * @brief Writes a uint32_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt32(uint32_t item);
    /**
     * @brief Writes a uint32_t value at a specific index.
     * @param index The index at which to write.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt32ByIndex(uint32_t index, uint32_t item);
    /**
     * @brief Writes a uint64_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetUInt64(uint64_t item);
    /**
     * @brief Writes an int8_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetInt8(char item);
    /**
     * @brief Writes an int16_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetInt16(int16_t item);
    /**
     * @brief Writes an int32_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetInt32(int32_t item);
    /**
     * @brief Writes an int64_t value at the current position.
     * @param item The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetInt64(int64_t item);
    /**
     * @brief Writes a float value at the current position.
     * @param value The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetFloat(float value);
    /**
     * @brief Writes a double value at the current position.
     * @param value The value to write.
     * @return 0 on success, an error code otherwise.
     */
    int SetDouble(double value);
    /**
     * @brief Writes a block of memory to the buffer.
     * @param pSource A pointer to the source data.
     * @param count The number of bytes to write.
     * @return 0 on success, an error code otherwise.
     */
    int Set(const void *pSource, uint32_t count);
    /**
     * @brief Writes data from another byte buffer.
     * @param data A pointer to the source byte buffer.
     * @param index The starting index in the source buffer.
     * @param count The number of bytes to write.
     * @return 0 on success, an error code otherwise.
     */
    int Set(CGXByteBuffer *data, uint32_t index = 0, uint32_t count = -1);

    /**
     * @brief Appends a string to the buffer.
     * @param value The string to append.
     * @return 0 on success, an error code otherwise.
     */
    int AddString(const std::string &value);
    /**
     * @brief Appends a string to the buffer using move semantics.
     * @param value The string to append.
     * @return 0 on success, an error code otherwise.
     */
    int AddString(std::string &&value);
    /**
     * @brief Appends a wide string to the buffer.
     * @param value The wide string to append.
     * @return 0 on success, an error code otherwise.
     */
    int AddString(const std::wstring &value);
    /**
     * @brief Appends a C-style string to the buffer.
     * @param value The C-style string to append.
     * @return 0 on success, an error code otherwise.
     */
    int AddString(const char *value);

    // int AttachString(char *value);

    /**
     * @brief Reads a uint8_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt8(uint8_t *value);
    /**
     * @brief Reads a uint8_t value from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt8(uint32_t index, uint8_t *value);
    /**
     * @brief Reads a uint16_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt16(uint16_t *value);
    /**
     * @brief Reads a uint16_t value from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt16(uint32_t index, uint16_t *value);
    /**
     * @brief Reads a 24-bit unsigned integer from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt24(unsigned int *value);
    /**
     * @brief Reads a 24-bit unsigned integer from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt24(uint32_t index, unsigned int *value);
    /**
     * @brief Reads a uint32_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt32(uint32_t *value);
    /**
     * @brief Reads a uint32_t value from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt32(uint32_t index, uint32_t *value);
    /**
     * @brief Reads a uint64_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt64(uint64_t *value);
    /**
     * @brief Reads a uint64_t value from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt64(uint32_t index, uint64_t *value);
    /**
     * @brief Reads a 128-bit unsigned integer from a specific index.
     * @param index The index from which to read.
     * @param value A pointer to an array to store the 16 bytes of the value.
     * @return 0 on success, an error code otherwise.
     */
    int GetUInt128(uint32_t index, uint8_t *value);
    /**
     * @brief Reads an int8_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetInt8(char *value);
    /**
     * @brief Reads an int16_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetInt16(int16_t *value);
    /**
     * @brief Reads an int32_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetInt32(int32_t *value);
    /**
     * @brief Reads an int64_t value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetInt64(int64_t *value);
    /**
     * @brief Reads a float value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetFloat(float *value);
    /**
     * @brief Reads a double value from the current position.
     * @param value A pointer to store the read value.
     * @return 0 on success, an error code otherwise.
     */
    int GetDouble(double *value);
    /**
     * @brief Reads a block of bytes from the buffer.
     * @param value A pointer to the destination buffer.
     * @param count The number of bytes to read.
     * @return 0 on success, an error code otherwise.
     */
    int Get(uint8_t *value, uint32_t count);

    /**
     * @brief Gets a pointer to the internal data buffer.
     * @return A pointer to the data.
     */
    uint8_t *GetData();
    /**
     * @brief Gets a const pointer to the internal data buffer.
     * @return A const pointer to the data.
     */
    const uint8_t *GetData() const;
    /**
     * @brief Copies the buffer's content to a new array.
     * @param value A reference to a pointer that will hold the new array.
     * @param count A reference to a variable that will hold the byte count.
     */
    void ToArray(uint8_t *&value, uint32_t &count);
    /**
     * @brief Extracts a sub-array from the buffer.
     * @param index The starting index.
     * @param count The number of bytes to extract.
     * @param bb The destination byte buffer.
     * @return 0 on success, an error code otherwise.
     */
    int SubArray(uint32_t index, int count, CGXByteBuffer &bb);
    /**
     * @brief Moves a block of bytes within the buffer.
     * @param srcPos The source position.
     * @param destPos The destination position.
     * @param count The number of bytes to move.
     * @return 0 on success, an error code otherwise.
     */
    int Move(uint32_t srcPos, uint32_t destPos, uint32_t count);
    /**
     * @brief Removes unused capacity from the buffer.
     */
    void Trim();
    /**
     * @brief Reverses a portion of the buffer.
     * @param index The starting index.
     * @param count The number of bytes to reverse.
     */
    void Reverse(uint32_t index, uint32_t count);

    /**
     * @brief Compares the buffer with a raw byte array.
     * @param buff The byte array to compare against.
     * @param length The length of the byte array.
     * @return True if the contents are equal, false otherwise.
     */
    bool Compare(const uint8_t *buff, uint32_t length) const;
    /**
     * @brief Compares the buffer with another byte buffer.
     * @param other The byte buffer to compare against.
     * @return True if the contents are equal, false otherwise.
     */
    bool Compare(const CGXByteBuffer &other) const;
    /**
     * @brief Checks if the buffer contains an ASCII string.
     * @return True if the buffer contains an ASCII string, false otherwise.
     */
    bool IsAsciiString();
    /**
     * @brief Checks if a raw byte array contains an ASCII string.
     * @param value A pointer to the byte array.
     * @param length The length of the byte array.
     * @return True if the byte array contains an ASCII string, false otherwise.
     */
    static bool IsAsciiString(uint8_t *value, uint32_t length);


    /**
     * @brief Converts the buffer's content to a string.
     * @return A string representation of the buffer.
     */
    std::string ToString() const;
    /**
     * @brief Converts the buffer's content to a hexadecimal string.
     * @return A hexadecimal string representation of the buffer.
     */
    std::string ToHexString() const;
    /**
     * @brief Converts the buffer's content to a hexadecimal string.
     * @param addSpaces Whether to add spaces between bytes.
     * @return A hexadecimal string representation of the buffer.
     */
    std::string ToHexString(bool addSpaces) const;
    /**
     * @brief Converts a portion of the buffer to a hexadecimal string.
     * @param position The starting position.
     * @param count The number of bytes to convert.
     * @param addSpaces Whether to add spaces between bytes.
     * @return A hexadecimal string representation of the specified portion.
     */
    std::string ToHexString(uint32_t position, uint32_t count, bool addSpaces) const;

    /**
     * @brief Appends an integer to the buffer as a string.
     * @param value The integer value.
     */
    void AddIntAsString(int value);
    /**
     * @brief Appends a double to the buffer as a string.
     * @param value The double value.
     */
    void AddDoubleAsString(double value);

    /**
     * @brief Populates the buffer from a hexadecimal string.
     * @param value The hexadecimal string.
     */
    void SetHexString(std::string &value);
    /**
     * @brief Populates the buffer from a hexadecimal string using move semantics.
     * @param value The hexadecimal string.
     */
    void SetHexString(std::string &&value);

    /**
     * @brief Reads a string from the buffer.
     * @param count The number of characters to read.
     * @param value A reference to store the read string.
     * @return 0 on success, an error code otherwise.
     */
    int GetString(int count, std::string &value);
    /**
     * @brief Reads a string from a specific index in the buffer.
     * @param index The starting index.
     * @param count The number of characters to read.
     * @param value A reference to store the read string.
     * @return 0 on success, an error code otherwise.
     */
    int GetString(uint32_t index, uint32_t count, std::string &value);
    /**
     * @brief Reads a Unicode string from the buffer.
     * @param index The starting index.
     * @param count The number of bytes to read.
     * @param value A reference to store the read string.
     * @return 0 on success, an error code otherwise.
     */
    int GetStringUnicode(uint32_t index, uint32_t count, std::string &value);
    /**
     * @brief Reads a Unicode string into a wide string.
     * @param index The starting index.
     * @param count The number of bytes to read.
     * @param value A reference to store the read wide string.
     * @return 0 on success, an error code otherwise.
     */
    int GetStringUnicode(uint32_t index, uint32_t count, std::wstring &value);

    /**
     * @brief Populates the buffer from a Base64 string.
     * @param input The Base64 string.
     * @return 0 on success, an error code otherwise.
     */
    int FromBase64(std::string &input);
    /**
     * @brief Converts the buffer's content to a Base64 string.
     * @param value A reference to store the Base64 string.
     * @return 0 on success, an error code otherwise.
     */
    int ToBase64(std::string &value) const;

    /**
     * @brief Swaps the content of this buffer with another.
     * @param other The other byte buffer to swap with.
     */
    void Swap(CGXByteBuffer &other) noexcept;
};

#endif  // GXBYTEBUFFER_H
