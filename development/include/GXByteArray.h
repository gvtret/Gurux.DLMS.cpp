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

#ifndef GXBYTEARRAY_H
#define GXBYTEARRAY_H

#include <vector>
#include <string>
#include "errorcodes.h"
#include "enums.h"
#include "GXBytebuffer.h"

/**
 * @brief Represents a dynamic, modifiable array of bytes.
 *
 * This class provides a flexible container for byte sequences, similar to
 * `std::vector<unsigned char>`, but with additional helper methods for serialization
 * of primitive data types, string conversions, and other common operations.
 */
class CGXByteArray {
	friend class CGXCipher;
	friend class CGXByteBuffer;
	friend class CGXPrivateKey;
	friend class CGXEcdsa;
	friend class CGXPkcs10;
	friend class CGXPkcs8;
	/**
	 * @brief The internal vector that stores the byte data.
	 */
	std::vector<unsigned char> m_Data;

public:
	/** @brief Default constructor. */
	CGXByteArray();
	/** @brief Constructor with initial capacity. @param capacity The initial capacity. */
	CGXByteArray(int capacity);
	/** @brief Copy constructor. @param value The object to copy. */
	CGXByteArray(const CGXByteArray& value);
	/** @brief Move constructor. @param value The object to move from. */
	CGXByteArray(CGXByteArray&& value) noexcept;
	/** @brief Default destructor. */
	~CGXByteArray() = default;

	/** @brief Gets the current size of the byte array. @return The size in bytes. */
	unsigned long GetSize() const;
	/** @brief Sets the size of the byte array. @param value The new size. */
	void SetSize(unsigned long value);

	/** @brief Sets the capacity of the internal vector. @param capacity The new capacity. */
	void Capacity(unsigned long capacity);
	/** @brief Gets the current capacity of the byte array. @return The capacity in bytes. */
	unsigned long Capacity() const;

	/** @brief Fills a portion of the array with zeros. @param index The starting index. @param count The number of bytes to zero out. */
	void Zero(unsigned long index, unsigned long count);

	/** @brief Appends an unsigned 8-bit integer. @param item The value to append. @return 0 on success. */
	int SetUInt8(unsigned char item);
	/** @brief Sets an unsigned 8-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
	int SetUInt8(unsigned long index, unsigned char item);
	/** @brief Appends an unsigned 16-bit integer. @param item The value to append. @return 0 on success. */
	int SetUInt16(unsigned short item);
	/** @brief Sets an unsigned 16-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
	int SetUInt16(unsigned long index, unsigned short item);
	/** @brief Appends an unsigned 32-bit integer. @param item The value to append. @return 0 on success. */
	int SetUInt32(unsigned long item);
	/** @brief Sets an unsigned 32-bit integer at a specific index. @param index The index. @param item The value. @return 0 on success. */
	int SetUInt32ByIndex(unsigned long index, unsigned long item);
	/** @brief Appends an unsigned 64-bit integer. @param item The value to append. @return 0 on success. */
	int SetUInt64(unsigned long long item);
	/** @brief Appends a signed 8-bit integer. @param item The value to append. @return 0 on success. */
	int SetInt8(char item);
	/** @brief Appends a signed 16-bit integer. @param item The value to append. @return 0 on success. */
	int SetInt16(short item);
	/** @brief Appends a signed 32-bit integer. @param item The value to append. @return 0 on success. */
	int SetInt32(long item);
	/** @brief Appends a signed 64-bit integer. @param item The value to append. @return 0 on success. */
	int SetInt64(long long item);
	/** @brief Appends a float. @param value The value to append. @return 0 on success. */
	int SetFloat(float value);
	/** @brief Appends a double. @param value The value to append. @return 0 on success. */
	int SetDouble(double value);
	/** @brief Appends a block of memory. @param pSource Pointer to the source data. @param count Number of bytes to append. @return 0 on success. */
	int Set(const void* pSource, unsigned long count);
	/** @brief Appends data from a CGXByteBuffer. @param data The source buffer. @param index Starting index in the source buffer. @param count Number of bytes to append. @return 0 on success. */
	int Set(CGXByteBuffer* data, unsigned long index = 0, unsigned long count = -1);
	/** @brief Appends a standard string. @param value The string to append. @return 0 on success. */
	int AddString(const std::string& value);
	/** @brief Appends a wide string. @param value The string to append. @return 0 on success. */
	int AddString(const std::wstring& value);
	/** @brief Appends a C-style string. @param value The string to append. @return 0 on success. */
	int AddString(const char* value);
	/** @brief Attaches a C-style string. @param value The string to attach. @return 0 on success. */
	int AttachString(char* value);

	/** @brief Clears the contents of the byte array. */
	void Clear();

	/** @brief Gets an unsigned 8-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt8(unsigned long index, unsigned char* value) const;
	/** @brief Gets an unsigned 24-bit integer from a specific index. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt24(unsigned long index, unsigned int* value) const;
	/** @brief Gets a direct pointer to the underlying data. @return A pointer to the data. */
	unsigned char* GetData();
	/** @brief Copies the data to a new array. @param[out] value Pointer to the new array. @param[out] count The size of the array. */
	void ToArray(unsigned char*& value, unsigned long& count) const;
	/** @brief Converts the byte array to a CGXByteBuffer. @param[out] value The destination buffer. @return 0 on success. */
	int ToByteBuffer(CGXByteBuffer& value) const;
	/**
	 * @brief Compares this array with another byte buffer.
	 * @param buff The buffer to compare with.
	 * @param length The number of bytes to compare.
	 * @return True if the contents are identical.
	 */
	bool Compare(const unsigned char* buff, unsigned long length) const;
	/** @brief Gets an unsigned 16-bit integer. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt16(unsigned long index, unsigned short* value) const;
	/** @brief Gets an unsigned 32-bit integer. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt32(unsigned long index, unsigned long* value) const;
	/** @brief Gets an unsigned 64-bit integer. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt64(unsigned long index, unsigned long long* value) const;
	/** @brief Gets an unsigned 128-bit integer. @param index The index. @param[out] value Pointer to store the result. @return 0 on success. */
	int GetUInt128(unsigned long index, unsigned char* value) const;

	/** @brief Converts the byte array to a readable string (non-printable characters are replaced). @return The string representation. */
	std::string ToString() const;
	/** @brief Converts the byte array to a hexadecimal string. @return The hex string. */
	std::string ToHexString() const;
	/** @brief Converts the byte array to a hexadecimal string. @param addSpaces If true, spaces are added between bytes. @return The hex string. */
	std::string ToHexString(bool addSpaces) const;
	/** @brief Converts a portion of the byte array to a hexadecimal string. @param position The starting position. @param count The number of bytes. @param addSpaces If true, add spaces. @return The hex string. */
	std::string ToHexString(unsigned long position, unsigned long count, bool addSpaces) const;
	/** @brief Appends an integer to the array as its string representation. @param value The integer to add. */
	void AddIntAsString(int value);
	/** @brief Appends a double to the array as its string representation. @param value The double to add. */
	void AddDoubleAsString(double value);
	/**
	 * @brief Extracts a sub-array.
	 * @param index Starting index.
	 * @param count Number of bytes.
	 * @param[out] bb The destination byte array.
	 * @return 0 on success.
	 */
	int SubArray(unsigned long index, int count, CGXByteArray& bb) const;
	/**
	 * @brief Extracts a sub-array into a byte buffer.
	 * @param index Starting index.
	 * @param count Number of bytes.
	 * @param[out] bb The destination byte buffer.
	 * @return 0 on success.
	 */
	int SubArray(unsigned long index, int count, CGXByteBuffer& bb) const;

	/** @brief Assignment operator from another CGXByteArray. @param value The source. @return A reference to this object. */
	CGXByteArray& operator=(CGXByteArray& value);
	/** @brief Assignment operator from a CGXByteBuffer. @param value The source. @return A reference to this object. */
	CGXByteArray& operator=(CGXByteBuffer& value);

	/** @brief Appends a hexadecimal string to the array. @param value The hex string. */
	void SetHexString(const std::string& value);
	/** @brief Appends a hexadecimal string (alternative format). @param value The hex string. */
	void SetHexString2(const std::string& value);
	/** @brief Appends a hexadecimal C-style string. @param value The hex string. */
	void SetHexString(const char* value);

	/** @brief Checks if a buffer contains only ASCII characters. @param value The buffer. @param length The length to check. @return True if ASCII. */
	static bool IsAsciiString(const unsigned char* value, unsigned long length);
	/** @brief Checks if this byte array contains only ASCII characters. @return True if ASCII. */
	bool IsAsciiString() const;
	/** @brief Gets a string value from a portion of the array. @param index The starting index. @param count The number of bytes. @param[out] value The resulting string. @return 0 on success. */
	int GetString(unsigned long index, unsigned long count, std::string& value) const;
	/** @brief Gets a UTF-8 string from a portion of the array. @param index The starting index. @param count The number of bytes. @param[out] value The resulting string. @return 0 on success. */
	int GetStringUnicode(unsigned long index, unsigned long count, std::string& value) const;
	/** @brief Gets a Unicode (wide) string from a portion of the array. @param index The starting index. @param count The number of bytes. @param[out] value The resulting wide string. @return 0 on success. */
	int GetStringUnicode(unsigned long index, unsigned long count, std::wstring& value) const;
	/**
	 * @brief Populates the array from a Base64 encoded string.
	 * @param input The Base64 string.
	 * @return 0 on success.
	 */
	int FromBase64(const std::string& input);
	/**
	 * @brief Converts the byte array to a Base64 encoded string.
	 * @param[out] value The resulting Base64 string.
	 * @return 0 on success.
	 */
	int ToBase64(std::string& value) const;

	/** @brief Copy assignment operator. @param value The source. @return A reference to this object. */
	CGXByteArray& operator=(const CGXByteArray& value);
	/** @brief Move assignment operator. @param value The source. @return A reference to this object. */
	CGXByteArray& operator=(CGXByteArray&& value) noexcept;
	/** @brief Assignment operator from CGXByteBuffer. @param value The source. @return A reference to this object. */
	CGXByteArray& operator=(const CGXByteBuffer& value);

	/**
	 * @brief Reverses a portion of the byte array.
	 * @param index The starting index.
	 * @param count The number of bytes to reverse.
	 */
	void Reverse(unsigned long index, unsigned long count);
};

#endif  //GXBYTEARRAY_H
