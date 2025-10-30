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
 * Represents a dynamic array of bytes.
*/
class CGXByteArray {
	friend class CGXCipher;
	friend class CGXByteBuffer;
	friend class CGXPrivateKey;
	friend class CGXEcdsa;
	friend class CGXPkcs10;
	friend class CGXPkcs8;
	std::vector<unsigned char> m_Data;

public:
	//Constructor.
	CGXByteArray();

	//Constructor.
	CGXByteArray(int capacity);

	//Copy constructor.
	CGXByteArray(const CGXByteArray& value);

	//Move constructor.
	CGXByteArray(CGXByteArray&& value) noexcept;

	//Destructor.
	~CGXByteArray() = default;

	//Returns buffer size.
	unsigned long GetSize() const;

	//Set buffer size.
	void SetSize(unsigned long value);

	//Allocate new size for the array in bytes.
	void Capacity(unsigned long capacity);

	//Get buffer capacity.
	unsigned long Capacity() const;

	//Fill buffer it with zeros.
	void Zero(unsigned long index, unsigned long count);

	//Push new data to the byteArray.
	int SetUInt8(unsigned char item);

	int SetUInt8(unsigned long index, unsigned char item);

	int SetUInt16(unsigned short item);
	int SetUInt16(unsigned long index, unsigned short item);

	int SetUInt32(unsigned long item);

	int SetUInt32ByIndex(unsigned long index, unsigned long item);

	int SetUInt64(unsigned long long item);

	int SetInt8(char item);

	int SetInt16(short item);

	int SetInt32(long item);

	int SetInt64(long long item);

	int SetFloat(float value);

	int SetDouble(double value);

	int Set(const void* pSource, unsigned long count);

	int Set(CGXByteBuffer* data, unsigned long index = 0, unsigned long count = -1);

	//Add string to byte buffer.
	int AddString(const std::string& value);

	//Add string to byte buffer.
	int AddString(const std::wstring& value);

	int AddString(const char* value);

	int AttachString(char* value);

	void Clear();

	int GetUInt8(unsigned long index, unsigned char* value) const;

	int GetUInt24(unsigned long index, unsigned int* value) const;

	const unsigned char* GetData() const;
	unsigned char* GetData();

	void ToArray(unsigned char*& value, unsigned long& count) const;

	int ToByteBuffer(CGXByteBuffer& value) const;

	/**
	 * Compares, whether two given arrays are similar starting from current
	 * position.
	 *
	 * @param buff
	 *            Array to compare.
	 * @param length
	 *            Length of the array to compare.
	 * @return True, if arrays are similar. False, if the arrays differ.
	 */
	bool Compare(const unsigned char* buff, unsigned long length) const;

	int GetUInt16(unsigned long index, unsigned short* value) const;
	int GetUInt32(unsigned long index, unsigned long* value) const;
	int GetUInt64(unsigned long index, unsigned long long* value) const;
	int GetUInt128(unsigned long index, unsigned char* value) const;

	//Get byte array as a std::string.
	std::string ToString() const;

	//Get byte array as hex std::string.
	std::string ToHexString() const;

	//Get byte array as hex std::string.
	std::string ToHexString(bool addSpaces) const;

	//Get byte array as hex std::string.
	std::string ToHexString(unsigned long position, unsigned long count, bool addSpaces) const;

	//Add integer value to byte array as a std::string.
	void AddIntAsString(int value);

	//Add double value to byte array as a std::string.
	void AddDoubleAsString(double value);

	/**
		* Returns data as byte array.
		*
		* @param index Starting index.
		* @param count Number of bytes.
		* @param bb Byte buffer as a byte array.
		*/
	int SubArray(unsigned long index, int count, CGXByteArray& bb) const;

	/**
	* Returns data as byte array.
	*
	* @param index Starting index.
	* @param count Number of bytes.
	* @param bb Byte buffer as a byte array.
	*/
	int SubArray(unsigned long index, int count, CGXByteBuffer& bb) const;

	CGXByteArray& operator=(CGXByteArray& value);

	CGXByteArray& operator=(CGXByteBuffer& value);

	//Push the given hex string as byte array into this buffer at the current position, and then increments the position.
	void SetHexString(const std::string& value);

	//Push the given hex string as byte array into this buffer at the current position, and then increments the position.
	void SetHexString2(const std::string& value);

	//Push the given hex string as byte array into this buffer at the current position, and then increments the position.
	void SetHexString(const char* value);

	//Check is byte buffer ASCII string.
	static bool IsAsciiString(const unsigned char* value, unsigned long length);

	//Check is byte buffer ASCII string.
	bool IsAsciiString() const;

	// Get String value from byte array.
	int GetString(unsigned long index, unsigned long count, std::string& value) const;

	// Get UTF-8 value from byte array.
	int GetStringUnicode(unsigned long index, unsigned long count, std::string& value) const;

	// Get unicode string value from byte array.
	int GetStringUnicode(unsigned long index, unsigned long count, std::wstring& value) const;

	/**
	* Convert Base64 string to byte array.
	*
	* input: Base64 string.
	*/
	int FromBase64(const std::string& input);

	/**
   * Convert byte array to Base64 string.
   *
   * @param value
   *            Byte array to convert.
   * @return Base64 string.
   */
	int ToBase64(std::string& value) const;

	CGXByteArray& operator=(const CGXByteArray& value);

	// Move assignment operator.
	CGXByteArray& operator=(CGXByteArray&& value) noexcept;

	CGXByteArray& operator=(const CGXByteBuffer& value);

	/*Reverse byte array.*/
	void Reverse(unsigned long index, unsigned long count);
};

#endif  //GXBYTEARRAY_H
