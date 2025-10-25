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

class CGXByteBuffer {
	std::vector<uint8_t> m_Data;
	uint32_t m_Position;

public:
	CGXByteBuffer();
	explicit CGXByteBuffer(int capacity);
	CGXByteBuffer(const CGXByteBuffer &value);
	CGXByteBuffer(CGXByteBuffer &&value) noexcept;
	~CGXByteBuffer() = default;

	// Assignment operators
	CGXByteBuffer &operator=(const CGXByteBuffer &value);
	CGXByteBuffer &operator=(CGXByteBuffer &&value) noexcept;  // Move assignment

	uint32_t Available() const;
	uint32_t GetSize() const;
	void SetSize(uint32_t value);
	int IncreaseSize(uint32_t size);
	uint32_t GetPosition() const;
	void SetPosition(uint32_t value);
	int Capacity(uint32_t capacity);
	uint32_t Capacity() const;
	void Clear();

	//	int Set(const CGXByteBuffer &value);

	void Zero(uint32_t index, uint32_t count);
	int SetUInt8(uint8_t item);
	int SetUInt8(uint32_t index, uint8_t item);
	int SetUInt16(uint16_t item);
	int SetUInt16(uint32_t index, uint16_t item);
	int SetUInt32(uint32_t item);
	int SetUInt32ByIndex(uint32_t index, uint32_t item);
	int SetUInt64(uint64_t item);
	int SetInt8(char item);
	int SetInt16(int16_t item);
	int SetInt32(int32_t item);
	int SetInt64(int64_t item);
	int SetFloat(float value);
	int SetDouble(double value);
	int Set(const void *pSource, uint32_t count);
	int Set(CGXByteBuffer *data, uint32_t index = 0, uint32_t count = -1);

	int AddString(const std::string &value);
	int AddString(std::string &&value);
	int AddString(const std::wstring &value);
	int AddString(const char *value);

	// int AttachString(char *value);

	int GetUInt8(uint8_t *value);
	int GetUInt8(uint32_t index, uint8_t *value);
	int GetUInt16(uint16_t *value);
	int GetUInt16(uint32_t index, uint16_t *value);
	int GetUInt24(unsigned int *value);
	int GetUInt24(uint32_t index, unsigned int *value);
	int GetUInt32(uint32_t *value);
	int GetUInt32(uint32_t index, uint32_t *value);
	int GetUInt64(uint64_t *value);
	int GetUInt64(uint32_t index, uint64_t *value);
	int GetUInt128(uint32_t index, uint8_t *value);
	int GetInt8(char *value);
	int GetInt16(int16_t *value);
	int GetInt32(int32_t *value);
	int GetInt64(int64_t *value);
	int GetFloat(float *value);
	int GetDouble(double *value);
	int Get(uint8_t *value, uint32_t count);

	uint8_t *GetData();
	const uint8_t *GetData() const;
	void ToArray(uint8_t *&value, uint32_t &count);
	int SubArray(uint32_t index, int count, CGXByteBuffer &bb);
	int Move(uint32_t srcPos, uint32_t destPos, uint32_t count);
	void Trim();
	void Reverse(uint32_t index, uint32_t count);

	bool Compare(const uint8_t *buff, uint32_t length) const;
	bool Compare(const CGXByteBuffer &other) const;
	bool IsAsciiString();
	static bool IsAsciiString(uint8_t *value, uint32_t length);


	std::string ToString() const;
	std::string ToHexString() const;
	std::string ToHexString(bool addSpaces) const;
	std::string ToHexString(uint32_t position, uint32_t count, bool addSpaces) const;

	void AddIntAsString(int value);
	void AddDoubleAsString(double value);

	void SetHexString(std::string &value);
	void SetHexString(std::string &&value);

	int GetString(int count, std::string &value);
	int GetString(uint32_t index, uint32_t count, std::string &value);
	int GetStringUnicode(uint32_t index, uint32_t count, std::string &value);
	int GetStringUnicode(uint32_t index, uint32_t count, std::wstring &value);

	int FromBase64(std::string &input);
	int ToBase64(std::string &value) const;

	void Swap(CGXByteBuffer &other) noexcept;
};

#endif  // GXBYTEBUFFER_H
