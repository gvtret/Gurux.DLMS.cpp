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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include "../include/errorcodes.h"
#include "../include/GXByteArray.h"
#include "../include/GXHelpers.h"

//Constructor.
CGXByteArray::CGXByteArray()
{
}

//Constructor.
CGXByteArray::CGXByteArray(int capacity)
{
	m_Data.reserve(capacity);
}

//Copy constructor.
CGXByteArray::CGXByteArray(const CGXByteArray& value)
{
	if (value.m_Data.size() != 0)
	{
		m_Data.assign(value.m_Data.begin(), value.m_Data.end());
	}
}

//Move constructor.
CGXByteArray::CGXByteArray(CGXByteArray&& value) noexcept
{
	m_Data = std::move(value.m_Data);
}

unsigned long CGXByteArray::GetSize() const
{
	return m_Data.size();
}

void CGXByteArray::SetSize(unsigned long value)
{
	m_Data.resize(value);
}

// Allocate new size for the array in bytes.
void CGXByteArray::Capacity(unsigned long capacity)
{
	m_Data.reserve(capacity);
}

unsigned long CGXByteArray::Capacity() const
{
	return m_Data.capacity();
}

// Fill buffer it with zeros.
void CGXByteArray::Zero(unsigned long index, unsigned long count)
{
	if (index + count > m_Data.capacity())
	{
		m_Data.reserve(index + count);
	}
	if (m_Data.size() < index + count)
	{
		m_Data.resize(index + count);
	}
	memset(&m_Data[index], 0, count);
}

// Push new data to the byteArray.
int CGXByteArray::SetUInt8(unsigned char item)
{
	m_Data.push_back(item);
	return 0;
}

int CGXByteArray::SetUInt8(unsigned long index, unsigned char item)
{
	if (index >= m_Data.size())
	{
		m_Data.resize(index + 1);
	}
	m_Data[index] = item;
	return 0;
}

int CGXByteArray::SetUInt16(unsigned short item)
{
	m_Data.push_back((item >> 8) & 0xFF);
	m_Data.push_back(item & 0xFF);
	return 0;
}

int CGXByteArray::SetUInt16(unsigned long index, unsigned short item)
{
	if (index + 2 > m_Data.size())
	{
		m_Data.resize(index + 2);
	}
	m_Data[index] = (item >> 8) & 0xFF;
	m_Data[index + 1] = item & 0xFF;
	return 0;
}

int CGXByteArray::SetUInt32(unsigned long item)
{
	return CGXByteArray::SetUInt32ByIndex(m_Data.size(), item);
}

int CGXByteArray::SetUInt32ByIndex(unsigned long index, unsigned long item)
{
	if (index + 4 > m_Data.size())
	{
		m_Data.resize(index + 4);
	}
	m_Data[index] = (item >> 24) & 0xFF;
	m_Data[index + 1] = (item >> 16) & 0xFF;
	m_Data[index + 2] = (item >> 8) & 0xFF;
	m_Data[index + 3] = item & 0xFF;
	return 0;
}

int CGXByteArray::SetUInt64(unsigned long long item)
{
	m_Data.resize(m_Data.size() + 8);
	m_Data[m_Data.size() - 8] = (unsigned char)((item >> 56) & 0xFF);
	m_Data[m_Data.size() - 7] = (item >> 48) & 0xFF;
	m_Data[m_Data.size() - 6] = (item >> 40) & 0xFF;
	m_Data[m_Data.size() - 5] = (item >> 32) & 0xFF;
	m_Data[m_Data.size() - 4] = (item >> 24) & 0xFF;
	m_Data[m_Data.size() - 3] = (item >> 16) & 0xFF;
	m_Data[m_Data.size() - 2] = (item >> 8) & 0xFF;
	m_Data[m_Data.size() - 1] = item & 0xFF;
	return 0;
}

int CGXByteArray::SetFloat(float value)
{
	union {
		float value;
		char b[sizeof(float)];
	} HELPER;

	HELPER.value = value;
	m_Data.resize(m_Data.size() + 4);
	m_Data[m_Data.size() - 4] = HELPER.b[3];
	m_Data[m_Data.size() - 3] = HELPER.b[2];
	m_Data[m_Data.size() - 2] = HELPER.b[1];
	m_Data[m_Data.size() - 1] = HELPER.b[0];
	return 0;
}

int CGXByteArray::SetDouble(double value)
{
	union {
		double value;
		char b[sizeof(double)];
	} HELPER;

	HELPER.value = value;
	m_Data.resize(m_Data.size() + 8);
	m_Data[m_Data.size() - 8] = HELPER.b[7];
	m_Data[m_Data.size() - 7] = HELPER.b[6];
	m_Data[m_Data.size() - 6] = HELPER.b[5];
	m_Data[m_Data.size() - 5] = HELPER.b[4];
	m_Data[m_Data.size() - 4] = HELPER.b[3];
	m_Data[m_Data.size() - 3] = HELPER.b[2];
	m_Data[m_Data.size() - 2] = HELPER.b[1];
	m_Data[m_Data.size() - 1] = HELPER.b[0];
	return 0;
}

int CGXByteArray::SetInt8(char item)
{
	return CGXByteArray::SetUInt8(static_cast<unsigned char>(item));
}

int CGXByteArray::SetInt16(short item)
{
	return CGXByteArray::SetUInt16(static_cast<unsigned short>(item));
}

int CGXByteArray::SetInt32(long item)
{
	return CGXByteArray::SetUInt32(static_cast<unsigned long>(item));
}

int CGXByteArray::SetInt64(long long item)
{
	return CGXByteArray::SetUInt64(static_cast<unsigned long long>(item));
}

int CGXByteArray::Set(const void* pSource, unsigned long count)
{
	if (pSource != NULL && count != 0)
	{
		m_Data.insert(m_Data.end(), static_cast<const unsigned char*>(pSource), static_cast<const unsigned char*>(pSource) + count);
	}
	return 0;
}

int CGXByteArray::Set(CGXByteBuffer* data, unsigned long index, unsigned long count)
{
	if (data != NULL)
	{
		if (count == (unsigned long)-1)
		{
			count = data->GetSize() - index;
		}
		int ret = CGXByteArray::Set(data->GetData() + index, count);
		if (ret == 0)
		{
			data->SetPosition(count);
		}
	}
	return 0;
}

int CGXByteArray::AddString(const char* value)
{
	if (value != NULL)
	{
		unsigned long len = (unsigned long)strlen(value);
		return CGXByteArray::Set(value, len);
	}
	return 0;
}

int CGXByteArray::AddString(const std::string& value)
{
	return CGXByteArray::Set(value.c_str(), (unsigned long)value.length());
}

int CGXByteArray::AddString(const std::wstring& value)
{
	return CGXByteArray::Set(value.c_str(), (unsigned long)value.length() * sizeof(wchar_t));
}

int CGXByteArray::AttachString(char* value)
{
	unsigned long len = (unsigned long)strlen(value);
	int ret = CGXByteArray::Set(value, len);
	if (ret == 0)
	{
		free(value);
	}
	return ret;
}

void CGXByteArray::Clear()
{
	m_Data.clear();
}

int CGXByteArray::GetUInt8(unsigned long index, unsigned char* value) const
{
	if (index >= m_Data.size())
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = m_Data[index];
	return 0;
}

int CGXByteArray::GetUInt24(unsigned long index, unsigned int* value) const
{
	if (index + 3 > m_Data.size())
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = m_Data[index] << 16 | m_Data[index + 1] << 8 | m_Data[index + 2];
	return 0;
}

int CGXByteArray::GetUInt32(unsigned long index, unsigned long* value) const
{
	if (index + 4 > m_Data.size())
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = m_Data[index] << 24 | m_Data[index + 1] << 16 | m_Data[index + 2] << 8 | m_Data[index + 3];
	return 0;
}

int CGXByteArray::GetUInt64(unsigned long index, unsigned long long* value) const
{
	if (index + 8 > m_Data.size())
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = (unsigned long long)m_Data[index] << 56 | (unsigned long long)m_Data[index + 1] << 48 |
		(unsigned long long)m_Data[index + 2] << 40 | (unsigned long long)m_Data[index + 3] << 32 |
		(unsigned long long)m_Data[index + 4] << 24 | (unsigned long long)m_Data[index + 5] << 16 |
		(unsigned long long)m_Data[index + 6] << 8 | (unsigned long long)m_Data[index + 7];
	return 0;
}

int CGXByteArray::GetUInt128(unsigned long index, unsigned char* value) const
{
	int ret = CGXByteArray::GetUInt32(index, (unsigned long*)value);
	if (ret == 0)
	{
		ret = CGXByteArray::GetUInt32(index + 4, (unsigned long*)value + 1);
		if (ret == 0)
		{
			ret = CGXByteArray::GetUInt32(index + 8, (unsigned long*)value + 2);
			if (ret == 0)
			{
				ret = CGXByteArray::GetUInt32(index + 12, (unsigned long*)value + 3);
			}
		}
	}
	return ret;
}

const unsigned char* CGXByteArray::GetData() const
{
	return m_Data.data();
}

unsigned char* CGXByteArray::GetData()
{
	return m_Data.data();
}

int CGXByteArray::GetUInt16(unsigned long index, unsigned short* value) const
{
	if (index + 2 > m_Data.size())
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = m_Data[index] << 8 | m_Data[index + 1];
	return 0;
}

std::string CGXByteArray::ToString() const
{
	std::string str;
	if (m_Data.size() != 0)
	{
		str.append(reinterpret_cast<char const*>(m_Data.data()), m_Data.size());
	}
	return str;
}

std::string CGXByteArray::ToHexString() const
{
	return GXHelpers::BytesToHex(m_Data.data(), m_Data.size());
}

std::string CGXByteArray::ToHexString(bool addSpaces) const
{
	return GXHelpers::BytesToHex(m_Data.data(), m_Data.size(), addSpaces);
}

std::string CGXByteArray::ToHexString(unsigned long position, unsigned long count, bool addSpaces) const
{
	if (m_Data.empty() || count == 0)
	{
		return "";
	}
	return GXHelpers::BytesToHex(m_Data.data() + position, count, addSpaces);
}

void CGXByteArray::AddIntAsString(int value)
{
	std::string str = GXHelpers::IntToString(value);
	CGXByteArray::AddString(str.c_str());
}

void CGXByteArray::AddDoubleAsString(double value)
{
	char buff[20];
	//Show as integer value if there is no fractal part.
	if (value - (long)value == 0)
	{
		CGXByteArray::AddIntAsString((int)value);
	}
	else
	{
#if _MSC_VER > 1000
		sprintf_s(buff, 20, "%lf", value);
#else
		sprintf(buff, "%lf", value);
#endif
		CGXByteArray::AddString(buff);
	}
}

int CGXByteArray::SubArray(unsigned long index, int count, CGXByteArray& bb) const
{
	bb.Clear();
	bb.Set(m_Data.data() + index, count);
	return 0;
}

int CGXByteArray::SubArray(unsigned long index, int count, CGXByteBuffer& bb) const
{
	bb.Clear();
	bb.Set(m_Data.data() + index, count);
	return 0;
}

bool CGXByteArray::Compare(const unsigned char* buff, unsigned long length) const
{
	if (buff == NULL || length == 0)
	{
		return m_Data.empty();
	}
	if (m_Data.size() < length)
	{
		return false;
	}
	return memcmp(m_Data.data(), buff, length) == 0;
}

void CGXByteArray::ToArray(unsigned char*& value, unsigned long& count) const
{
	if (value != NULL)
	{
		free(value);
	}
	count = m_Data.size();
	value = (unsigned char*)malloc(count);
	memcpy(value, m_Data.data(), count);
}

int CGXByteArray::ToByteBuffer(CGXByteBuffer& value) const
{
	value.Capacity(GetSize());
	value.SetSize(0);
	if (GetSize() != 0)
	{
		return value.Set(m_Data.data(), m_Data.size());
	}
	return 0;
}

CGXByteArray& CGXByteArray::operator=(CGXByteArray& value)
{
	m_Data.assign(value.m_Data.begin(), value.m_Data.end());
	return *this;
}

CGXByteArray& CGXByteArray::operator=(CGXByteBuffer& value)
{
	m_Data.assign(value.GetData(), value.GetData() + value.GetSize());
	return *this;
}

void CGXByteArray::SetHexString(const std::string& value)
{
	CGXByteBuffer tmp;
	std::string val = value;
	GXHelpers::HexToBytes(val, tmp);
	Set(&tmp);
}

void CGXByteArray::SetHexString2(const std::string& value)
{
	CGXByteBuffer tmp;
	std::string val = value;
	GXHelpers::HexToBytes(val, tmp);
	Set(&tmp);
}

void CGXByteArray::SetHexString(const char* value)
{
	CGXByteBuffer tmp;
	std::string str = value;
	GXHelpers::HexToBytes(str, tmp);
	Set(&tmp);
}

bool CGXByteArray::IsAsciiString(const unsigned char* value, unsigned long length)
{
	if (value != NULL)
	{
		for (unsigned long pos = 0; pos != length; ++pos)
		{
			unsigned char it = value[pos];
			if ((it < 32 || it > 127) && it != '\r' && it != '\n' && it != 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool CGXByteArray::IsAsciiString() const
{
	return IsAsciiString(m_Data.data(), m_Data.size());
}

int CGXByteArray::GetString(unsigned long index, unsigned long count, std::string& value) const
{
	if (index + count > m_Data.size())
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (count != 0)
	{
		value.append(reinterpret_cast<char const*>(m_Data.data() + index), count);
	}
	return 0;
}

int CGXByteArray::GetStringUnicode(unsigned long index, unsigned long count, std::string& value) const
{
	if (index + count > m_Data.size())
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (m_Data.size() != 0)
	{
		value.append(reinterpret_cast<char const*>(m_Data.data() + index), m_Data.size());
	}
	return 0;
}

int CGXByteArray::GetStringUnicode(unsigned long index, unsigned long count, std::wstring& value) const
{
	if (index + count > m_Data.size())
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (m_Data.size() != 0)
	{
		value.append(reinterpret_cast<wchar_t const*>(m_Data.data() + index), m_Data.size());
	}
	return 0;
}

/**
* Get index of given char.
*
* @param ch
* @return
*/
static int GetIndex(char ch)
{
	if (ch == '+')
	{
		return 62;
	}
	if (ch == '/')
	{
		return 63;
	}
	if (ch == '=')
	{
		return 64;
	}
	if (ch < ':')
	{
		return (52 + (ch - '0'));
	}
	if (ch < '[')
	{
		return (ch - 'A');
	}
	if (ch < '{')
	{
		return (26 + (ch - 'a'));
	}
	return -1;
}

/**
   * Convert Base64 string to byte array.
   *
   * @param input
   *            Base64 string.
   * @return Converted byte array.
   */
int CGXByteArray::FromBase64(const std::string& input)
{
	std::string Tmp = input;
	GXHelpers::Replace(Tmp, "\r\n", "");
	GXHelpers::Replace(Tmp, "\n", "");
	if (Tmp.length() % 4 != 0)
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	size_t len = (Tmp.length() * 3) / 4;
	size_t pos = Tmp.find('=', 0);
	if (pos > 0)
	{
		len -= Tmp.length() - pos;
	}
	std::string inChars;
	int b[4];
	for (pos = 0; pos != Tmp.length(); pos += 4)
	{
		inChars = Tmp.substr(pos, 4);
		b[0] = GetIndex(inChars[0]);
		b[1] = GetIndex(inChars[1]);
		b[2] = GetIndex(inChars[2]);
		b[3] = GetIndex(inChars[3]);
		SetUInt8((b[0] << 2) | (b[1] >> 4));
		if (b[2] < 64)
		{
			SetUInt8((b[1] << 4) | (b[2] >> 2));
			if (b[3] < 64)
			{
				SetUInt8((b[2] << 6) | b[3]);
			}
		}
	}
	return 0;
}

const char BASE_64_ARRAY[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
							  'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
							  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
							  'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '=' };

int CGXByteArray::ToBase64(std::string& value) const
{
	unsigned long b, pos;
	for (pos = 0; pos < m_Data.size(); pos += 3)
	{
		b = (m_Data[pos] & 0xFC) >> 2;
		value += BASE_64_ARRAY[b];
		b = (m_Data[pos] & 0x03) << 4;
		if (pos + 1 < m_Data.size())
		{
			b |= (m_Data[pos + 1] & 0xF0) >> 4;
			value += BASE_64_ARRAY[b];
			b = (m_Data[pos + 1] & 0x0F) << 2;
			if (pos + 2 < m_Data.size())
			{
				b |= (m_Data[pos + 2] & 0xC0) >> 6;
				value += BASE_64_ARRAY[b];
				b = m_Data[pos + 2] & 0x3F;
				value += BASE_64_ARRAY[b];
			}
			else
			{
				value += BASE_64_ARRAY[b];
				value += '=';
			}
		}
		else
		{
			value += BASE_64_ARRAY[b];
			value += "==";
		}
	}
	return 0;
}

CGXByteArray& CGXByteArray::operator=(const CGXByteArray& value)
{
	m_Data = value.m_Data;
	return *this;
}

CGXByteArray& CGXByteArray::operator=(CGXByteArray&& value) noexcept
{
	m_Data = std::move(value.m_Data);
	return *this;
}

CGXByteArray& CGXByteArray::operator=(const CGXByteBuffer& value)
{
	m_Data.assign(value.GetData(), value.GetData() + value.GetSize());
	return *this;
}

void CGXByteArray::Reverse(unsigned long index, unsigned long count)
{
	std::reverse(m_Data.begin() + index, m_Data.begin() + index + count);
}
