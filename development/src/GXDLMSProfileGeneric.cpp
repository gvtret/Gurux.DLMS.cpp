#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <map>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <cmath>

#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSDemandRegister.h"
#include "../include/GXDLMSServer.h"

#ifndef DLMS_IGNORE_PROFILE_GENERIC

CGXDLMSProfileGeneric::CGXDLMSProfileGeneric() :
    CGXDLMSProfileGeneric("", 0)
{
}

CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_PROFILE_GENERIC, ln, sn),
    m_CapturePeriod(3600),
    m_SortMethod(DLMS_SORT_METHOD_FIFO),
    m_SortObject(nullptr),
    m_ProfileEntries(0),
    m_EntriesInUse(0),
    m_SortObjectAttributeIndex(0),
    m_SortObjectDataIndex(0)
{
}

CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(std::string ln) :
    CGXDLMSProfileGeneric(ln, 0)
{
}

CGXDLMSProfileGeneric::~CGXDLMSProfileGeneric()
{
}

CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(const CGXDLMSProfileGeneric& other) :
    CGXDLMSObject(other),
    m_Buffer(other.m_Buffer),
    m_CapturePeriod(other.m_CapturePeriod),
    m_SortMethod(other.m_SortMethod),
    m_SortObject(other.m_SortObject),
    m_ProfileEntries(other.m_ProfileEntries),
    m_EntriesInUse(other.m_EntriesInUse),
    m_SortObjectAttributeIndex(other.m_SortObjectAttributeIndex),
    m_SortObjectDataIndex(other.m_SortObjectDataIndex)
{
    m_CaptureObjects.reserve(other.m_CaptureObjects.size());
    for (const auto& pair : other.m_CaptureObjects)
    {
        m_CaptureObjects.emplace_back(pair.first, new CGXDLMSCaptureObject(*pair.second));
    }
}

CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(CGXDLMSProfileGeneric&& other) noexcept :
    CGXDLMSObject(std::move(other)),
    m_Buffer(std::move(other.m_Buffer)),
    m_CaptureObjects(std::move(other.m_CaptureObjects)),
    m_CapturePeriod(other.m_CapturePeriod),
    m_SortMethod(other.m_SortMethod),
    m_SortObject(other.m_SortObject),
    m_ProfileEntries(other.m_ProfileEntries),
    m_EntriesInUse(other.m_EntriesInUse),
    m_SortObjectAttributeIndex(other.m_SortObjectAttributeIndex),
    m_SortObjectDataIndex(other.m_SortObjectDataIndex)
{
}

CGXDLMSProfileGeneric& CGXDLMSProfileGeneric::operator=(const CGXDLMSProfileGeneric& other)
{
    if (this == &other)
    {
        return *this;
    }

    CGXDLMSObject::operator=(other);
    m_Buffer = other.m_Buffer;
    m_CaptureObjects.clear();
    m_CaptureObjects.reserve(other.m_CaptureObjects.size());
    for (const auto& pair : other.m_CaptureObjects)
    {
        m_CaptureObjects.emplace_back(pair.first, new CGXDLMSCaptureObject(*pair.second));
    }
    m_CapturePeriod = other.m_CapturePeriod;
    m_SortMethod = other.m_SortMethod;
    m_SortObject = other.m_SortObject;
    m_ProfileEntries = other.m_ProfileEntries;
    m_EntriesInUse = other.m_EntriesInUse;
    m_SortObjectAttributeIndex = other.m_SortObjectAttributeIndex;
    m_SortObjectDataIndex = other.m_SortObjectDataIndex;

    return *this;
}

CGXDLMSProfileGeneric& CGXDLMSProfileGeneric::operator=(CGXDLMSProfileGeneric&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    CGXDLMSObject::operator=(std::move(other));
    m_Buffer = std::move(other.m_Buffer);
    m_CaptureObjects = std::move(other.m_CaptureObjects);
    m_CapturePeriod = other.m_CapturePeriod;
    m_SortMethod = other.m_SortMethod;
    m_SortObject = other.m_SortObject;
    m_ProfileEntries = other.m_ProfileEntries;
    m_EntriesInUse = other.m_EntriesInUse;
    m_SortObjectAttributeIndex = other.m_SortObjectAttributeIndex;
    m_SortObjectDataIndex = other.m_SortObjectDataIndex;

    return *this;
}

int CGXDLMSProfileGeneric::GetSelectedColumns(
    int selector, CGXDLMSVariant& parameters,
    std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>>& columns) const
{
    columns.clear();

    if (selector == 0)
    {
        columns.reserve(m_CaptureObjects.size());
        for (const auto& pair : m_CaptureObjects)
        {
            columns.emplace_back(pair.first, new CGXDLMSCaptureObject(*pair.second));
        }
        return 0;
    }
    else if (selector == 1)
    {
        return GetSelectedColumns(parameters.Arr.at(3).Arr, columns);
    }
    else if (selector == 2)
    {
        size_t colStart = 1;
        size_t colCount = 0;

        if (parameters.Arr.size() > 2)
        {
            colStart = parameters.Arr[2].ToInteger();
        }
        if (parameters.Arr.size() > 3)
        {
            colCount = parameters.Arr[3].ToInteger();
        }
        else if (colStart != 1)
        {
            colCount = m_CaptureObjects.size();
        }

        if (colStart != 1 || colCount != 0)
        {
            size_t startIndex = colStart - 1;
            size_t endIndex = startIndex + colCount;

            if (startIndex < m_CaptureObjects.size() && endIndex <= m_CaptureObjects.size())
            {
                columns.reserve(colCount);
                for (size_t i = startIndex; i < endIndex; ++i)
                {
                    const auto& pair = m_CaptureObjects[i];
                    columns.emplace_back(pair.first, new CGXDLMSCaptureObject(*pair.second));
                }
            }
        }
        else
        {
            columns.reserve(m_CaptureObjects.size());
            for (const auto& pair : m_CaptureObjects)
            {
                columns.emplace_back(pair.first, new CGXDLMSCaptureObject(*pair.second));
            }
        }
        return 0;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
}

int CGXDLMSProfileGeneric::GetColumns(CGXByteBuffer& data) const
{
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount(static_cast<unsigned long>(m_CaptureObjects.size()), data);

    for (const auto& pair : m_CaptureObjects)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(4); // Count

        CGXDLMSVariant tmp;
        int ret;

        tmp = pair.first->GetObjectType();
        if ((ret = GXHelpers::SetData(nullptr, data, DLMS_DATA_TYPE_UINT16, tmp)) != 0) // ClassID
        {
            return ret;
        }

        tmp.Clear();
        if ((ret = GetLogicalName(pair.first, tmp)) != 0)
        {
            return ret;
        }

        CGXDLMSVariant ai = pair.second->GetAttributeIndex();
        CGXDLMSVariant di = pair.second->GetDataIndex();

        if ((ret = GXHelpers::SetData(nullptr, data, DLMS_DATA_TYPE_OCTET_STRING, tmp)) != 0 || // LN
            (ret = GXHelpers::SetData(nullptr, data, DLMS_DATA_TYPE_INT8, ai)) != 0 ||           // Attribute Index
            (ret = GXHelpers::SetData(nullptr, data, DLMS_DATA_TYPE_UINT16, di)) != 0)          // Data Index
        {
            return ret;
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::GetData(
    CGXDLMSSettings& settings, CGXDLMSValueEventArg& e, const std::vector<std::vector<CGXDLMSVariant>>& table,
    std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>>& columns, CGXByteBuffer& data) const
{
    if (settings.GetIndex() == 0)
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        if (e.GetRowEndIndex() != 0)
        {
            GXHelpers::SetObjectCount(e.GetRowEndIndex() - e.GetRowBeginIndex(), data);
        }
        else
        {
            GXHelpers::SetObjectCount(static_cast<unsigned long>(table.size()), data);
        }
    }

    std::vector<DLMS_DATA_TYPE> types;
    types.reserve(m_CaptureObjects.size());
    for (const auto& pair : m_CaptureObjects)
    {
        DLMS_DATA_TYPE type;
        int ret;
        if ((ret = pair.first->GetDataType(pair.second->GetAttributeIndex(), type)) != 0)
        {
            return ret;
        }
        types.push_back(type);
    }

    for (const auto& row : table)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        GXHelpers::SetObjectCount(columns.empty() ? static_cast<unsigned long>(row.size()) : static_cast<unsigned long>(columns.size()), data);

        for (size_t i = 0; i < row.size(); ++i)
        {
            DLMS_DATA_TYPE tp = types[i];
            if (tp == DLMS_DATA_TYPE_NONE)
            {
                tp = row[i].vt;
                types[i] = tp;
            }

            bool columnMatch = false;
            if (columns.empty())
            {
                columnMatch = true;
            }
            else
            {
                for (const auto& col : columns)
                {
                    if (col.first == m_CaptureObjects[i].first &&
                        col.second->GetAttributeIndex() == m_CaptureObjects[i].second->GetAttributeIndex() &&
                        col.second->GetDataIndex() == m_CaptureObjects[i].second->GetDataIndex())
                    {
                        columnMatch = true;
                        break;
                    }
                }
            }

            if (columnMatch)
            {
                int ret;
                CGXDLMSVariant val = row[i];
                if ((ret = GXHelpers::SetData(&settings, data, tp, val)) != 0)
                {
                    return ret;
                }
            }
        }
        settings.SetIndex(settings.GetIndex() + 1);
    }

    if (e.GetRowEndIndex() != 0)
    {
        e.SetRowBeginIndex(e.GetRowBeginIndex() + static_cast<unsigned short>(table.size()));
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::AddCaptureObject(CGXDLMSObject* pObj, int attributeIndex, int dataIndex)
{
    if (pObj == nullptr)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (attributeIndex < 1)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (dataIndex < 0)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    m_CaptureObjects.emplace_back(pObj, new CGXDLMSCaptureObject(attributeIndex, dataIndex));
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::GetSelectedColumns(
    std::vector<CGXDLMSVariant>& cols, std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>>& columns) const
{
    for (const auto& it : cols)
    {
        CGXDLMSVariant val = it;
        DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE)val.Arr[0].ToInteger();
        std::string ln;
        GXHelpers::GetLogicalName(val.Arr[1].byteArr, ln);
        unsigned char attributeIndex = val.Arr[2].ToInteger();
        int dataIndex = val.Arr[3].ToInteger();

        for (const auto& c : m_CaptureObjects)
        {
            std::string ln2;
            c.first->GetLogicalName(ln2);
            if (c.first->GetObjectType() == ot &&
                c.second->GetAttributeIndex() == attributeIndex &&
                c.second->GetDataIndex() == dataIndex &&
                ln2.compare(ln) == 0)
            {
                columns.emplace_back(c.first, new CGXDLMSCaptureObject(*c.second));
                break;
            }
        }
    }
    return 0;
}

int CGXDLMSProfileGeneric::GetProfileGenericData(
    CGXDLMSSettings& settings, CGXDLMSValueEventArg& e, CGXByteBuffer& reply) const
{
    std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> columns;
    if (e.GetSelector() == 0 || e.GetParameters().vt == DLMS_DATA_TYPE_NONE || e.GetRowEndIndex() != 0)
    {
        return GetData(settings, e, GetBuffer(), columns, reply);
    }
    const auto& table = GetBuffer();
    std::vector<std::vector<CGXDLMSVariant>> items;

    if (e.GetSelector() == 1) // Read by range
    {
        int ret;
        CGXDLMSVariant value;
        if ((ret = CGXDLMSClient::ChangeType(e.GetParameters().Arr[1], DLMS_DATA_TYPE_DATETIME, value)) != 0)
        {
            return ret;
        }
        CGXDateTime val = value.dateTime;
        struct tm tmp = val.GetValue();
        time_t start = mktime(&tmp);
        value.Clear();
        if ((ret = CGXDLMSClient::ChangeType(e.GetParameters().Arr[2], DLMS_DATA_TYPE_DATETIME, value)) != 0)
        {
            return ret;
        }
        val = value.dateTime;
        tmp = val.GetValue();
        time_t end = mktime(&tmp);
        value.Clear();

        if (e.GetParameters().Arr.size() > 3)
        {
            ret = GetSelectedColumns(e.GetParameters().Arr[3].Arr, columns);
        }
        for (const auto& row : table)
        {
            CGXDLMSVariant val2 = row[0];
            CGXDateTime dt = val2.dateTime;
            tmp = dt.GetValue();
            time_t tm = mktime(&tmp);
            if (tm >= start && tm <= end)
            {
                items.push_back(row);
            }
        }
    }
    else if (e.GetSelector() == 2) // Read by entry
    {
        size_t start = e.GetParameters().Arr[0].ToInteger();
        size_t count = e.GetParameters().Arr[1].ToInteger();
        if (start == 0)
        {
            start = 1;
        }
        if (count == 0)
        {
            count = table.size();
        }
        if (start + count - 1 > table.size())
        {
            count = table.size() - start + 1;
        }

        GetSelectedColumns(2, e.GetParameters(), columns);

        for (size_t pos = 0; pos < count; ++pos)
        {
            if (pos + start - 1 >= table.size())
            {
                break;
            }
            items.push_back(table[start + pos - 1]);
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return GetData(settings, e, items, columns, reply);
}

const std::vector<std::vector<CGXDLMSVariant>>& CGXDLMSProfileGeneric::GetBuffer() const
{
    return m_Buffer;
}

std::vector<std::vector<CGXDLMSVariant>>& CGXDLMSProfileGeneric::GetBuffer()
{
    return m_Buffer;
}

const std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>>& CGXDLMSProfileGeneric::GetCaptureObjects() const
{
    return m_CaptureObjects;
}

std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>>& CGXDLMSProfileGeneric::GetCaptureObjects()
{
    return m_CaptureObjects;
}

int CGXDLMSProfileGeneric::GetCapturePeriod() const
{
    return m_CapturePeriod;
}

void CGXDLMSProfileGeneric::SetCapturePeriod(int value)
{
    m_CapturePeriod = value;
}

GX_SORT_METHOD CGXDLMSProfileGeneric::GetSortMethod() const
{
    return m_SortMethod;
}

void CGXDLMSProfileGeneric::SetSortMethod(GX_SORT_METHOD value)
{
    m_SortMethod = value;
}

CGXDLMSObject* CGXDLMSProfileGeneric::GetSortObject() const
{
    return m_SortObject;
}

void CGXDLMSProfileGeneric::SetSortObject(CGXDLMSObject* value)
{
    m_SortObject = value;
}

unsigned long CGXDLMSProfileGeneric::GetEntriesInUse() const
{
    return m_EntriesInUse;
}

void CGXDLMSProfileGeneric::SetEntriesInUse(unsigned long value)
{
    m_EntriesInUse = value;
}

unsigned long CGXDLMSProfileGeneric::GetProfileEntries() const
{
    return m_ProfileEntries;
}

void CGXDLMSProfileGeneric::SetProfileEntries(unsigned long value)
{
    m_ProfileEntries = value;
}

int CGXDLMSProfileGeneric::GetSortObjectAttributeIndex() const
{
    return m_SortObjectAttributeIndex;
}

void CGXDLMSProfileGeneric::SetSortObjectAttributeIndex(int value)
{
    m_SortObjectAttributeIndex = value;
}

int CGXDLMSProfileGeneric::GetSortObjectDataIndex() const
{
    return m_SortObjectDataIndex;
}

void CGXDLMSProfileGeneric::SetSortObjectDataIndex(int value)
{
    m_SortObjectDataIndex = value;
}

void CGXDLMSProfileGeneric::Reset()
{
    m_Buffer.clear();
    m_EntriesInUse = 0;
}

int CGXDLMSProfileGeneric::Capture(CGXDLMSServer* server)
{
    std::vector<CGXDLMSVariant> values;
    int ret;
    CGXDLMSValueEventArg e(server, this, 2);
    CGXDLMSValueEventCollection args;
    args.push_back(&e);
    server->PreGet(args);
    if (!e.GetHandled())
    {
        for (const auto& it : m_CaptureObjects)
        {
            CGXDLMSValueEventArg tmp(server, it.first, it.second->GetAttributeIndex());
            if ((ret = it.first->GetValue(server->GetSettings(), tmp)) != 0)
            {
                return ret;
            }
            values.push_back(tmp.GetValue());
        }

        if (!m_Buffer.empty() && GetProfileEntries() == m_Buffer.size())
        {
            m_Buffer.erase(m_Buffer.begin());
        }
        m_Buffer.push_back(values);
        m_EntriesInUse = static_cast<unsigned long>(m_Buffer.size());
    }
    server->PostGet(args);
    return 0;
}

int CGXDLMSProfileGeneric::Reset(CGXDLMSClient& client, std::vector<CGXByteBuffer>& reply)
{
    CGXDLMSVariant value = (unsigned char)0;
    return client.Method(this, 1, value, reply);
}

int CGXDLMSProfileGeneric::Capture(CGXDLMSClient& client, std::vector<CGXByteBuffer>& reply)
{
    CGXDLMSVariant value = (unsigned char)0;
    return client.Method(this, 2, value, reply);
}

void CGXDLMSProfileGeneric::GetValues(std::vector<std::string>& values) const
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    std::stringstream sb;
    for (const auto& row : m_Buffer)
    {
        bool first = true;
        for (const auto& cell : row)
        {
            if (!first)
            {
                sb << " | ";
            }
            first = false;
            sb << cell.ToString();
        }
        sb << "\r\n";
    }
    values.push_back(sb.str());
    sb.str(std::string());
    sb << '[';
    bool first = true;
    for (const auto& it : m_CaptureObjects)
    {
        if (!first)
        {
            sb << ", ";
        }
        first = false;
        std::string str = it.first->GetName().ToString();
        sb.write(str.c_str(), str.size());
    }
    sb << ']';
    values.push_back(sb.str());

    values.push_back(CGXDLMSVariant(m_CapturePeriod).ToString());
    values.push_back(CGXDLMSVariant(m_SortMethod).ToString());
    if (m_SortObject == nullptr)
    {
        values.push_back("");
    }
    else
    {
        values.push_back(m_SortObject->GetName().ToString());
    }
    values.push_back(CGXDLMSVariant(m_EntriesInUse).ToString());
    values.push_back(CGXDLMSVariant(m_ProfileEntries).ToString());
}

void CGXDLMSProfileGeneric::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    if (all || IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    if (all || !IsRead(2))
    {
        attributes.push_back(2);
    }
    if (all || !IsRead(3))
    {
        attributes.push_back(3);
    }
    if (all || !IsRead(4))
    {
        attributes.push_back(4);
    }
    if (all || !IsRead(5))
    {
        attributes.push_back(5);
    }
    if (all || !IsRead(6))
    {
        attributes.push_back(6);
    }
    if (all || !IsRead(7))
    {
        attributes.push_back(7);
    }
    if (all || !IsRead(8))
    {
        attributes.push_back(8);
    }
}

int CGXDLMSProfileGeneric::GetAttributeCount()
{
    return 8;
}

int CGXDLMSProfileGeneric::GetMethodCount()
{
    return 2;
}

int CGXDLMSProfileGeneric::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index)
    {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
    case 3:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    case 4:
    case 7:
    case 8:
        type = DLMS_DATA_TYPE_UINT32;
        break;
    case 5:
        type = DLMS_DATA_TYPE_ENUM;
        break;
    case 6:
        type = DLMS_DATA_TYPE_STRUCTURE;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::Invoke(CGXDLMSSettings&, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        Reset();
    }
    else if (e.GetIndex() == 2)
    {
        Capture(e.GetServer());
    }
    else
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    }
    return 0;
}

int CGXDLMSProfileGeneric::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    switch (e.GetIndex())
    {
    case 1:
    {
        CGXDLMSVariant tmp;
        int ret;
        if ((ret = GetLogicalName(this, tmp)) != 0)
        {
            return ret;
        }
        e.SetValue(tmp);
        break;
    }
    case 2:
    {
        CGXByteBuffer tmp;
        int ret = GetProfileGenericData(settings, e, tmp);
        e.SetByteArray(true);
        e.SetValue(tmp);
        return ret;
    }
    case 3:
    {
        CGXByteBuffer data;
        int ret = GetColumns(data);
        e.SetByteArray(true);
        e.SetValue(data);
        return ret;
    }
    case 4:
        e.SetValue(GetCapturePeriod());
        break;
    case 5:
        e.SetValue(GetSortMethod());
        break;
    case 6:
    {
        e.SetByteArray(true);
        CGXByteBuffer data;
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(4);
        if (m_SortObject == nullptr)
        {
            data.SetUInt8(DLMS_DATA_TYPE_UINT16);
            data.SetUInt16(0);
            data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
            data.SetUInt8(6);
            data.Set(std::vector<unsigned char>(6, 0).data(), 6);
            data.SetUInt8(DLMS_DATA_TYPE_INT8);
            data.SetUInt8(0);
            data.SetUInt8(DLMS_DATA_TYPE_UINT16);
            data.SetUInt16(0);
        }
        else
        {
            int ret;
            CGXDLMSVariant ln;
            data.SetUInt8(DLMS_DATA_TYPE_UINT16);
            data.SetUInt16(m_SortObject->GetObjectType());
            data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
            data.SetUInt8(6);
            if ((ret = GetLogicalName(m_SortObject, ln)) != 0)
            {
                return ret;
            }
            data.Set(ln.byteArr, 6);
            data.SetUInt8(DLMS_DATA_TYPE_INT8);
            data.SetUInt8(m_SortObjectAttributeIndex);
            data.SetUInt8(DLMS_DATA_TYPE_UINT16);
            data.SetUInt16(m_SortObjectDataIndex);
        }
        e.SetValue(data);
        break;
    }
    case 7:
        e.SetValue(GetEntriesInUse());
        break;
    case 8:
        e.SetValue(GetProfileEntries());
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret;
    static unsigned char UNIX_TIME[6] = { 0, 0, 1, 1, 0, 255 };
    switch (e.GetIndex())
    {
    case 1:
        return SetLogicalName(this, e.GetValue());
    case 2:
        if (m_CaptureObjects.empty())
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        if (e.GetValue().vt != DLMS_DATA_TYPE_NONE)
        {
            std::vector<DLMS_DATA_TYPE> types;
            types.reserve(m_CaptureObjects.size());
            for (const auto& it : m_CaptureObjects)
            {
                DLMS_DATA_TYPE dataType;
                if ((ret = it.first->GetUIDataType(it.second->GetAttributeIndex(), dataType)) != 0)
                {
                    return ret;
                }
                types.push_back(dataType);
            }

            CGXDateTime lastDate;
            for (auto& row : e.GetValue().Arr)
            {
                if (row.Arr.size() != m_CaptureObjects.size())
                {
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                for (unsigned int pos = 0; pos < row.Arr.size(); ++pos)
                {
                    const auto& item = m_CaptureObjects[pos];
                    if (row.Arr[pos].vt == DLMS_DATA_TYPE_OCTET_STRING)
                    {
                        DLMS_DATA_TYPE currentType = types.at(pos);
                        if (currentType != DLMS_DATA_TYPE_NONE)
                        {
                            CGXDLMSVariant data;
                            if ((ret = CGXDLMSClient::ChangeType(row.Arr[pos], currentType, data)) != 0)
                            {
                                return ret;
                            }
                            row.Arr[pos] = data;
                            if (currentType == DLMS_DATA_TYPE_DATETIME)
                            {
                                lastDate = data.dateTime;
                            }
                        }
                    }
                    else if (row.Arr[pos].vt == DLMS_DATA_TYPE_NONE ||
                        row.Arr[pos].vt == DLMS_DATA_TYPE_UINT32)
                    {
                        if (item.first->GetObjectType() == DLMS_OBJECT_TYPE_CLOCK &&
                            item.second->GetAttributeIndex() == 2)
                        {
                            if (row.Arr[pos].vt == DLMS_DATA_TYPE_NONE)
                            {
                                if ((ret = lastDate.AddSeconds(
                                    m_SortMethod == DLMS_SORT_METHOD_FIFO ||
                                    m_SortMethod == DLMS_SORT_METHOD_SMALLEST
                                    ? m_CapturePeriod
                                    : -m_CapturePeriod
                                )) != 0)
                                {
                                    return ret;
                                }
                                row.Arr[pos] = lastDate;
                            }
                        }
                        else if (row.Arr[pos].vt == DLMS_DATA_TYPE_UINT32 &&
                            item.first->GetObjectType() == DLMS_OBJECT_TYPE_DATA &&
                            memcmp(item.first->m_LN, UNIX_TIME, 6) == 0)
                        {
                            lastDate = CGXDateTime(row.Arr[pos].ulVal);
                            row.Arr[pos] = lastDate;
                        }
                    }

                    if ((item.first->GetObjectType() == DLMS_OBJECT_TYPE_REGISTER ||
                        item.first->GetObjectType() == DLMS_OBJECT_TYPE_EXTENDED_REGISTER) &&
                        item.second->GetAttributeIndex() == 2)
                    {
                        double scaler = ((CGXDLMSRegister*)item.first)->GetScaler();
                        if (scaler != 1)
                        {
                            row.Arr[pos] = row.Arr[pos].ToDouble() * scaler;
                        }
                    }
#ifndef DLMS_IGNORE_DEMAND_REGISTER
                    else if (item.first->GetObjectType() == DLMS_OBJECT_TYPE_DEMAND_REGISTER &&
                        (item.second->GetAttributeIndex() == 2 || item.second->GetAttributeIndex() == 3))
                    {
                        double scaler = ((CGXDLMSDemandRegister*)item.first)->GetScaler();
                        if (scaler != 1)
                        {
                            row.Arr[pos] = row.Arr[pos].ToDouble() * scaler;
                        }
                    }
#endif //DLMS_IGNORE_DEMAND_REGISTER
                }
                m_Buffer.push_back(row.Arr);
            }
        }
        m_EntriesInUse = static_cast<unsigned long>(m_Buffer.size());
        break;
    case 3:
        m_CaptureObjects.clear();
        m_Buffer.clear();
        m_EntriesInUse = 0;
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (auto& it : e.GetValue().Arr)
            {
                if (it.Arr.size() != 4)
                {
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)it.Arr[0].ToInteger();
                std::string ln;
                GXHelpers::GetLogicalName(it.Arr[1].byteArr, ln);
                CGXDLMSObject* pObj = settings.GetObjects().FindByLN(type, ln);
                if (pObj == nullptr)
                {
                    pObj = CGXDLMSObjectFactory::CreateObject(type, ln);
                    settings.AddAllocateObject(pObj);
                }
                AddCaptureObject(pObj, it.Arr[2].ToInteger(), it.Arr[3].ToInteger());
            }
        }
        break;
    case 4:
        m_CapturePeriod = e.GetValue().ToInteger();
        break;
    case 5:
        m_SortMethod = (GX_SORT_METHOD)e.GetValue().ToInteger();
        break;
    case 6:
        if (e.GetValue().vt == DLMS_DATA_TYPE_NONE)
        {
            m_SortObject = nullptr;
        }
        else
        {
            if (e.GetValue().Arr.size() != 4)
            {
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)e.GetValue().Arr[0].ToInteger();
            std::string ln;
            GXHelpers::GetLogicalName(e.GetValue().Arr[1].byteArr, ln);
            m_SortObjectAttributeIndex = e.GetValue().Arr[2].ToInteger();
            m_SortObjectDataIndex = e.GetValue().Arr[3].ToInteger();
            m_SortObject = settings.GetObjects().FindByLN(type, ln);
            if (m_SortObject == nullptr)
            {
                m_SortObject = CGXDLMSObjectFactory::CreateObject(type, ln);
                settings.AddAllocateObject(m_SortObject);
            }
        }
        break;
    case 7:
        m_EntriesInUse = e.GetValue().ToInteger();
        break;
    case 8:
        m_ProfileEntries = e.GetValue().ToInteger();
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

#endif //DLMS_IGNORE_PROFILE_GENERIC
