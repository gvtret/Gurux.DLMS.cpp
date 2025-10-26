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

#include "../include/GXBytebuffer.h"
#include "../include/GXHelpers.h"
#include "../include/errorcodes.h"
#include "GXBytebuffer.h"
#include <algorithm>
#include <cstring>
#include <codecvt>
#include <locale>
#include <vector>

CGXByteBuffer::CGXByteBuffer(): m_Position(0) {
}

CGXByteBuffer::CGXByteBuffer(int capacity): m_Position(0) {
    if (capacity > 0) {
        m_Data.reserve(capacity);
    }
}

CGXByteBuffer::CGXByteBuffer(const CGXByteBuffer &value): m_Data(value.m_Data), m_Position(value.m_Position) {
}

CGXByteBuffer::CGXByteBuffer(CGXByteBuffer &&value) noexcept: m_Data(std::move(value.m_Data)), m_Position(value.m_Position) {
    value.m_Position = 0;
}

CGXByteBuffer &CGXByteBuffer::operator=(const CGXByteBuffer &value) {
    if (this != &value) {
        m_Data = value.m_Data;
        m_Position = value.m_Position;
    }
    return *this;
}

CGXByteBuffer &CGXByteBuffer::operator=(CGXByteBuffer &&value) noexcept {
    if (this != &value) {
        m_Data = std::move(value.m_Data);
        m_Position = value.m_Position;
        value.m_Position = 0;
    }
    return *this;
}

uint32_t CGXByteBuffer::Available() const {
    return m_Data.size() - m_Position;
}

uint32_t CGXByteBuffer::GetSize() const {
    return m_Data.size();
}

void CGXByteBuffer::SetSize(uint32_t value) {
    try {
        m_Data.resize(value);
        if (m_Position > value) {
            m_Position = value;
        }
    } catch (const std::bad_alloc &e) {
        throw;
    }
}

int CGXByteBuffer::IncreaseSize(uint32_t size) {
    try {
        m_Data.resize(m_Data.size() + size);
        return DLMS_ERROR_CODE_OK;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

uint32_t CGXByteBuffer::GetPosition() const {
    return m_Position;
}

void CGXByteBuffer::SetPosition(uint32_t value) {
    if (value > m_Data.size()) {
        throw std::out_of_range("Position exceeds buffer size");
    }
    m_Position = value;
}

int CGXByteBuffer::Capacity(uint32_t capacity) {
    try {
        m_Data.reserve(capacity);
        // Trim size if new capacity is smaller
        if (capacity < m_Data.size()) {
            m_Data.resize(capacity);
            if (m_Position > capacity) {
                m_Position = capacity;
            }
        }
        return DLMS_ERROR_CODE_OK;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

uint32_t CGXByteBuffer::Capacity() const {
    return m_Data.capacity();
}

void CGXByteBuffer::Clear() {
    m_Data.clear();
    m_Position = 0;
}

void CGXByteBuffer::Zero(uint32_t index, uint32_t count) {
    if (count == 0) {
        return;
    }

    try {
        if (index + count > m_Data.size()) {
            m_Data.resize(index + count);
        }
        std::fill(m_Data.begin() + index, m_Data.begin() + index + count, 0);
    } catch (const std::bad_alloc &) {
        throw;
    }
}

int CGXByteBuffer::SetUInt8(uint8_t item) {
    try {
        m_Data.push_back(item);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetUInt8(uint32_t index, uint8_t item) {
    try {
        if (index >= m_Data.size()) {
            if (index >= m_Data.capacity()) {
                m_Data.reserve(index + VECTOR_CAPACITY);
            }
            m_Data.resize(index + 1);
        }
        m_Data[index] = item;
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    } catch (const std::out_of_range &) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
}

int CGXByteBuffer::SetUInt16(uint16_t item) {
    try {
        m_Data.push_back((item >> 8) & 0xFF);
        m_Data.push_back(item & 0xFF);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetUInt16(uint32_t index, uint16_t item) {
    try {
        if (index + 2 > m_Data.size()) {
            if (index + 2 > m_Data.capacity()) {
                m_Data.reserve(index + 2 + VECTOR_CAPACITY);
            }
            m_Data.resize(index + 2);
        }
        m_Data[index] = (item >> 8) & 0xFF;
        m_Data[index + 1] = item & 0xFF;
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetUInt32(uint32_t item) {
    try {
        m_Data.push_back((item >> 24) & 0xFF);
        m_Data.push_back((item >> 16) & 0xFF);
        m_Data.push_back((item >> 8) & 0xFF);
        m_Data.push_back(item & 0xFF);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetUInt32ByIndex(uint32_t index, uint32_t item) {
    try {
        if (index + 4 > m_Data.size()) {
            if (index + 4 > m_Data.capacity()) {
                m_Data.reserve(index + 4 + VECTOR_CAPACITY);
            }
            m_Data.resize(index + 4);
        }
        m_Data[index] = (item >> 24) & 0xFF;
        m_Data[index + 1] = (item >> 16) & 0xFF;
        m_Data[index + 2] = (item >> 8) & 0xFF;
        m_Data[index + 3] = item & 0xFF;
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetUInt64(uint64_t item) {
    try {
        m_Data.push_back((uint8_t)((item >> 56) & 0xFF));
        m_Data.push_back((item >> 48) & 0xFF);
        m_Data.push_back((item >> 40) & 0xFF);
        m_Data.push_back((item >> 32) & 0xFF);
        m_Data.push_back((item >> 24) & 0xFF);
        m_Data.push_back((item >> 16) & 0xFF);
        m_Data.push_back((item >> 8) & 0xFF);
        m_Data.push_back(item & 0xFF);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetInt8(char item) {
    return SetUInt8(static_cast<uint8_t>(item));
}

int CGXByteBuffer::SetInt16(int16_t item) {
    return SetUInt16(static_cast<uint16_t>(item));
}

int CGXByteBuffer::SetInt32(int32_t item) {
    return SetUInt32(static_cast<uint32_t>(item));
}

int CGXByteBuffer::SetInt64(int64_t item) {
    return SetUInt64(static_cast<uint64_t>(item));
}

int CGXByteBuffer::SetFloat(float value) {
    union {
        float value;
        uint8_t bytes[4];
    } converter;

    converter.value = value;

    try {
        // Store in big-endian order
        m_Data.push_back(converter.bytes[3]);
        m_Data.push_back(converter.bytes[2]);
        m_Data.push_back(converter.bytes[1]);
        m_Data.push_back(converter.bytes[0]);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::SetDouble(double value) {
    union {
        double value;
        uint8_t bytes[8];
    } converter;

    converter.value = value;

    try {
        // Store in big-endian order
        for (int i = 7; i >= 0; --i) {
            m_Data.push_back(converter.bytes[i]);
        }
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::Set(const void *pSource, uint32_t count) {
    if (pSource == nullptr || count == 0) {
        return 0;
    }

    try {
        const uint8_t *src = static_cast<const uint8_t *>(pSource);
        m_Data.insert(m_Data.end(), src, src + count);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::Set(CGXByteBuffer *data, uint32_t index, uint32_t count) {
    if (data == nullptr) {
        return 0;
    }

    if (count == static_cast<uint32_t>(-1)) {
        count = data->m_Data.size() - index;
    }

    if (index + count > data->m_Data.size()) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    try {
        m_Data.insert(m_Data.end(), data->m_Data.begin() + index, data->m_Data.begin() + index + count);
        data->m_Position += count;
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::AddString(const std::string &value) {
    try {
        m_Data.insert(m_Data.end(), value.begin(), value.end());
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::AddString(std::string &&value) {
    try {
        // Reserve space to avoid multiple reallocations
        if (m_Data.capacity() < m_Data.size() + value.size()) {
            m_Data.reserve(m_Data.size() + value.size() + VECTOR_CAPACITY);
        }

        // Move the string data
        m_Data.insert(m_Data.end(), std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
        value.clear();
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::AddString(const std::wstring &value) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8Str = converter.to_bytes(value);
        return AddString(utf8Str);
    } catch (const std::range_error &) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::AddString(const char *value) {
    if (value == nullptr) {
        return 0;
    }

    try {
        size_t len = strlen(static_cast<const char *>(value));
        m_Data.insert(m_Data.end(), value, value + len);
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::GetUInt8(uint8_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position >= m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = m_Data[m_Position++];
    return 0;
}

int CGXByteBuffer::GetUInt8(uint32_t index, uint8_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index >= m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = m_Data[index];
    return 0;
}

int CGXByteBuffer::GetUInt16(uint16_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 2 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint16_t>(m_Data[m_Position]) << 8) | static_cast<uint16_t>(m_Data[m_Position + 1]);
    m_Position += 2;
    return 0;
}

int CGXByteBuffer::GetUInt16(uint32_t index, uint16_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index + 2 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint16_t>(m_Data[index]) << 8) | static_cast<uint32_t>(m_Data[index + 1]);
    return 0;
}

int CGXByteBuffer::GetUInt24(uint32_t index, unsigned int *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index + 3 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value =
        (static_cast<unsigned int>(m_Data[index]) << 16) | (static_cast<unsigned int>(m_Data[index + 1]) << 8) | static_cast<unsigned int>(m_Data[index + 2]);
    return 0;
}

int CGXByteBuffer::GetUInt24(unsigned int *value) {
    int ret = GetUInt24(m_Position, value);
    if (ret == 0) {
        m_Position += 3;
    }
    return ret;
}

int CGXByteBuffer::GetUInt32(uint32_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 4 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint32_t>(m_Data[m_Position]) << 24) | (static_cast<uint32_t>(m_Data[m_Position + 1]) << 16) |
        (static_cast<uint32_t>(m_Data[m_Position + 2]) << 8) | static_cast<uint32_t>(m_Data[m_Position + 3]);
    m_Position += 4;
    return 0;
}

int CGXByteBuffer::GetUInt32(uint32_t index, uint32_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index + 4 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint32_t>(m_Data[index]) << 24) | (static_cast<uint32_t>(m_Data[index + 1]) << 16) | (static_cast<uint32_t>(m_Data[index + 2]) << 8) |
        static_cast<uint32_t>(m_Data[index + 3]);
    return 0;
}

int CGXByteBuffer::GetInt8(char *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position >= m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = static_cast<char>(m_Data[m_Position++]);
    return 0;
}

int CGXByteBuffer::GetInt16(int16_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 2 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<int16_t>(m_Data[m_Position]) << 8) | static_cast<int16_t>(m_Data[m_Position + 1]);
    m_Position += 2;
    return 0;
}

int CGXByteBuffer::GetInt32(int32_t *value) {
    uint32_t temp;
    int ret = GetUInt32(&temp);
    if (ret == 0) {
        *value = static_cast<int32_t>(temp);
    }
    return ret;
}

int CGXByteBuffer::GetInt64(int64_t *value) {
    uint64_t temp;
    int ret = GetUInt64(&temp);
    if (ret == 0) {
        *value = static_cast<int64_t>(temp);
    }
    return ret;
}

int CGXByteBuffer::GetUInt64(uint64_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 8 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint64_t>(m_Data[m_Position]) << 56) | (static_cast<uint64_t>(m_Data[m_Position + 1]) << 48) |
        (static_cast<uint64_t>(m_Data[m_Position + 2]) << 40) | (static_cast<uint64_t>(m_Data[m_Position + 3]) << 32) |
        (static_cast<uint64_t>(m_Data[m_Position + 4]) << 24) | (static_cast<uint64_t>(m_Data[m_Position + 5]) << 16) |
        (static_cast<uint64_t>(m_Data[m_Position + 6]) << 8) | static_cast<uint64_t>(m_Data[m_Position + 7]);
    m_Position += 8;
    return 0;
}

int CGXByteBuffer::GetUInt64(uint32_t index, uint64_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index + 8 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    *value = (static_cast<uint64_t>(m_Data[index]) << 56) | (static_cast<uint64_t>(m_Data[index + 1]) << 48) |
        (static_cast<uint64_t>(m_Data[index + 2]) << 40) | (static_cast<uint64_t>(m_Data[index + 3]) << 32) | (static_cast<uint64_t>(m_Data[index + 4]) << 24) |
        (static_cast<uint64_t>(m_Data[index + 5]) << 16) | (static_cast<uint64_t>(m_Data[index + 6]) << 8) | static_cast<uint64_t>(m_Data[index + 7]);
    return 0;
}

int CGXByteBuffer::GetUInt128(uint32_t index, uint8_t *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (index + 16 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    std::copy(m_Data.begin() + index, m_Data.begin() + index + 16, value);
    return 0;
}

int CGXByteBuffer::GetFloat(float *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 4 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    union {
        float value;
        uint8_t bytes[4];
    } converter;

    // Read in big-endian order
    converter.bytes[3] = m_Data[m_Position];
    converter.bytes[2] = m_Data[m_Position + 1];
    converter.bytes[1] = m_Data[m_Position + 2];
    converter.bytes[0] = m_Data[m_Position + 3];

    *value = converter.value;
    m_Position += 4;
    return 0;
}

int CGXByteBuffer::GetDouble(double *value) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + 8 > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    union {
        double value;
        uint8_t bytes[8];
    } converter;

    // Read in big-endian order
    for (int i = 7; i >= 0; --i) {
        converter.bytes[i] = m_Data[m_Position + (7 - i)];
    }

    *value = converter.value;
    m_Position += 8;
    return 0;
}

int CGXByteBuffer::Get(uint8_t *value, uint32_t count) {
    if (value == nullptr) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (m_Position + count > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    std::copy(m_Data.begin() + m_Position, m_Data.begin() + m_Position + count, value);
    m_Position += count;
    return 0;
}

uint8_t *CGXByteBuffer::GetData() {
    return m_Data.empty() ? nullptr : m_Data.data();
}

const uint8_t *CGXByteBuffer::GetData() const {
    return m_Data.empty() ? nullptr : m_Data.data();
}

void CGXByteBuffer::ToArray(uint8_t *&value, uint32_t &count) {
    if (value != nullptr) {
        free(value);
    }

    count = m_Data.size();
    if (count > 0) {
        value = static_cast<uint8_t *>(malloc(count));
        if (value != nullptr) {
            std::copy(m_Data.begin(), m_Data.end(), value);
        }
    } else {
        value = nullptr;
    }
}

int CGXByteBuffer::SubArray(uint32_t index, int count, CGXByteBuffer &bb) {
    if (count < 0 || index >= m_Data.size()) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    uint32_t actualCount = static_cast<uint32_t>(count);
    if (index + actualCount > m_Data.size()) {
        actualCount = m_Data.size() - index;
    }

    bb.Clear();
    return bb.Set(m_Data.data() + index, actualCount);
}

int CGXByteBuffer::Move(uint32_t srcPos, uint32_t destPos, uint32_t count) {
    if (count == 0) {
        return DLMS_ERROR_CODE_OK;
    }

    if (srcPos + count > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    try {
        if (destPos + count > m_Data.size()) {
            m_Data.resize(destPos + count);
        }

        // Use std::rotate for overlapping ranges
        if (srcPos < destPos && destPos < srcPos + count) {
            std::rotate(m_Data.begin() + srcPos, m_Data.begin() + srcPos + count, m_Data.begin() + destPos + count);
        } else {
            std::copy(m_Data.begin() + srcPos, m_Data.begin() + srcPos + count, m_Data.begin() + destPos);
        }

        return DLMS_ERROR_CODE_OK;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

void CGXByteBuffer::Trim() {
    if (m_Position == 0) {
        return;
    }

    if (m_Position >= m_Data.size()) {
        Clear();
    } else {
        // Move remaining data to the beginning
        std::copy(m_Data.begin() + m_Position, m_Data.end(), m_Data.begin());
        m_Data.resize(m_Data.size() - m_Position);
        m_Position = 0;
    }
}

void CGXByteBuffer::Reverse(uint32_t index, uint32_t count) {
    if (count == 0 || index >= m_Data.size()) {
        return;
    }

    // Adjust count if it exceeds available data
    if (index + count > m_Data.size()) {
        count = m_Data.size() - index;
    }

    std::reverse(m_Data.begin() + index, m_Data.begin() + index + count);
}

bool CGXByteBuffer::Compare(const uint8_t *buff, uint32_t length) const {
    if (buff == nullptr || length == 0) {
        return m_Data.empty();
    }

    if (Available() < length) {
        return false;
    }

    return std::equal(m_Data.begin() + m_Position, m_Data.begin() + m_Position + length, buff);
}

bool CGXByteBuffer::Compare(const CGXByteBuffer &other) const {
    if (Available() != other.Available()) {
        return false;
    }

    return std::equal(m_Data.begin() + m_Position, m_Data.begin() + m_Position + Available(), other.m_Data.begin() + other.m_Position);
}

bool CGXByteBuffer::IsAsciiString(uint8_t *value, uint32_t length) {
    if (value != NULL) {
        for (uint32_t pos = 0; pos != length; ++pos) {
            uint8_t it = value[pos];
            if ((it < 32 || it > 127) && it != '\r' && it != '\n' && it != 0) {
                return false;
            }
        }
    }
    return true;
}

bool CGXByteBuffer::IsAsciiString() {
    return IsAsciiString(m_Data.data(), m_Data.size());
}

std::string CGXByteBuffer::ToString() const {
    if (m_Data.empty()) {
        return "";
    }
    return std::string(reinterpret_cast<const char *>(m_Data.data()), m_Data.size());
}

std::string CGXByteBuffer::ToHexString() const {
    return GXHelpers::BytesToHex(m_Data.data(), m_Data.size());
}

std::string CGXByteBuffer::ToHexString(bool addSpaces) const {
    return GXHelpers::BytesToHex(m_Data.data(), m_Data.size(), addSpaces);
}

std::string CGXByteBuffer::ToHexString(uint32_t position, uint32_t count, bool addSpaces) const {
    if (m_Data.empty() || count == 0 || position >= m_Data.size()) {
        return "";
    }

    // Adjust count if it exceeds available data
    if (position + count > m_Data.size()) {
        count = m_Data.size() - position;
    }

    return GXHelpers::BytesToHex(m_Data.data() + position, count, addSpaces);
}

void CGXByteBuffer::AddIntAsString(int value) {
    std::string str = std::to_string(value);
    AddString(str);
}

void CGXByteBuffer::AddDoubleAsString(double value) {
    std::string str = std::to_string(value);
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (!str.empty() && str.back() == '.') {
        str.push_back('0');
    }
    AddString(str);
}

void CGXByteBuffer::SetHexString(std::string &value) {
    CGXByteBuffer tmp;
    GXHelpers::HexToBytes(value, tmp);
    *this = tmp;
}

void CGXByteBuffer::SetHexString(std::string &&value) {
    CGXByteBuffer tmp;
    GXHelpers::HexToBytes(value, tmp);
    *this = std::move(tmp);
}

int CGXByteBuffer::GetString(int count, std::string &value) {
    if (count < 0) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    unsigned long actualCount = static_cast<unsigned long>(count);
    if (m_Position + actualCount > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    if (actualCount > 0) {
        value.append(reinterpret_cast<const char *>(m_Data.data() + m_Position), actualCount);
        m_Position += actualCount;
    }
    return 0;
}

int CGXByteBuffer::GetString(uint32_t index, uint32_t count, std::string &value) {
    if (index + count > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    if (count > 0) {
        value.append(reinterpret_cast<const char *>(m_Data.data() + index), count);
    }
    return 0;
}

int CGXByteBuffer::GetStringUnicode(uint32_t index, uint32_t count, std::string &value) {
    if (index > m_Data.size() || count > m_Data.size() - index) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    size_t wcharSize = sizeof(wchar_t);

    if ((index % wcharSize) != 0 || (count % wcharSize) != 0) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (count == 0) {
        value.clear();
        return 0;
    }

    size_t wideLen = count / wcharSize;

    try {
        std::vector<wchar_t> buffer(wideLen);
        std::memcpy(buffer.data(), m_Data.data() + index, count);

        std::wstring wstr(buffer.begin(), buffer.end());
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        value = converter.to_bytes(wstr);
        return 0;
    } catch (const std::range_error &) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

int CGXByteBuffer::GetStringUnicode(uint32_t index, uint32_t count, std::wstring &value) {
    if (index + count > m_Data.size()) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }

    size_t wcharSize = sizeof(wchar_t);

    if ((index % wcharSize) != 0 || (count % wcharSize) != 0) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    if (count == 0) {
        value.clear();
        return 0;
    }

    size_t wideLen = count / wcharSize;

    try {
        std::vector<wchar_t> buffer(wideLen);
        std::memcpy(buffer.data(), m_Data.data() + index, count);
        value.assign(buffer.begin(), buffer.end());
        return 0;
    } catch (const std::bad_alloc &) {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
}

static int GetIndex(char ch) {
    if (ch == '+') {
        return 62;
    }
    if (ch == '/') {
        return 63;
    }
    if (ch == '=') {
        return 64;
    }
    if (ch < ':') {
        return (52 + (ch - '0'));
    }
    if (ch < '[') {
        return (ch - 'A');
    }
    if (ch < '{') {
        return (26 + (ch - 'a'));
    }
    return -1;
}

int CGXByteBuffer::FromBase64(std::string &input) {
    GXHelpers::Replace(input, "\r\n", "");
    GXHelpers::Replace(input, "\n", "");
    if (input.length() % 4 != 0) {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    size_t len = (input.length() * 3) / 4;
    size_t pos = input.find('=', 0);
    if (pos != std::string::npos) {
        len -= input.length() - pos;
    }
    if (len > 0) {
        m_Data.reserve(m_Data.size() + len);
    }
    std::string inChars;
    int b[4];
    for (pos = 0; pos != input.length(); pos += 4) {
        inChars = input.substr(pos, 4);
        b[0] = GetIndex(inChars[0]);
        b[1] = GetIndex(inChars[1]);
        b[2] = GetIndex(inChars[2]);
        b[3] = GetIndex(inChars[3]);
        for (int idx = 0; idx < 4; ++idx) {
            if (b[idx] == -1) {
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
        }
        SetUInt8((b[0] << 2) | (b[1] >> 4));
        if (b[2] < 64) {
            SetUInt8((b[1] << 4) | (b[2] >> 2));
            if (b[3] < 64) {
                SetUInt8((b[2] << 6) | b[3]);
            }
        }
    }
    return 0;
}

const char BASE_64_ARRAY[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                              'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '='};

int CGXByteBuffer::ToBase64(std::string &value) const {
    uint32_t b, pos;
    for (pos = 0; pos < m_Data.size(); pos += 3) {
        b = (m_Data[pos] & 0xFC) >> 2;
        value += BASE_64_ARRAY[b];
        b = (m_Data[pos] & 0x03) << 4;
        if (pos + 1 < m_Data.size()) {
            b |= (m_Data[pos + 1] & 0xF0) >> 4;
            value += BASE_64_ARRAY[b];
            b = (m_Data[pos + 1] & 0x0F) << 2;
            if (pos + 2 < m_Data.size()) {
                b |= (m_Data[pos + 2] & 0xC0) >> 6;
                value += BASE_64_ARRAY[b];
                b = m_Data[pos + 2] & 0x3F;
                value += BASE_64_ARRAY[b];
            } else {
                value += BASE_64_ARRAY[b];
                value += '=';
            }
        } else {
            value += BASE_64_ARRAY[b];
            value += "==";
        }
    }
    return 0;
}

void CGXByteBuffer::Swap(CGXByteBuffer &other) noexcept {
    if (this != &other) {
        std::swap(m_Data, other.m_Data);
        std::swap(m_Position, other.m_Position);
    }
}
