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
#ifndef GXDLMSPROFILEGENERIC_H
#define GXDLMSPROFILEGENERIC_H

#include "GXIgnore.h"

#ifndef DLMS_IGNORE_PROFILE_GENERIC
#include "GXDLMSCaptureObject.h"
#include "GXDLMSRegister.h"

enum GX_SORT_METHOD {
    /**
     First in first out

     When circle buffer is full first item is removed.
    */
    DLMS_SORT_METHOD_FIFO = 1,
    /**
     Last in first out.

     When circle buffer is full last item is removed.
    */
    DLMS_SORT_METHOD_LIFO = 2,
    /**
     Largest is first.
    */
    DLMS_SORT_METHOD_LARGEST = 3,
    /**
     Smallest is first.
    */
    DLMS_SORT_METHOD_SMALLEST = 4,
    /**
     Nearst to zero is first.
    */
    DLMS_SORT_METHOD_NEAREST_TO_ZERO = 5,
    /**
     Farest from zero is first.
    */
    DLMS_SORT_METHOD_FAREST_FROM_ZERO = 6
};

class CGXDLMSServer;

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSProfileGeneric

 This class is used to model the periodical logging of monitoring results.
 The Profile generic class is configurable by the various attributes and can
 be used flexibly for various purposes, for example:
<ul>
 <li>traditional load profile,</li>
 <li>recording billing period values of various energy types and demand,</li>
 <li>recording events,</li>
 <li>recording alarms.</li>
</ul>
*/
#include <memory>

class CGXDLMSProfileGeneric: public CGXDLMSObject {
public:
    CGXDLMSProfileGeneric();
    CGXDLMSProfileGeneric(std::string ln, unsigned short sn);
    CGXDLMSProfileGeneric(std::string ln);
    virtual ~CGXDLMSProfileGeneric();

    CGXDLMSProfileGeneric(const CGXDLMSProfileGeneric& other);
    CGXDLMSProfileGeneric(CGXDLMSProfileGeneric&& other) noexcept;
    CGXDLMSProfileGeneric& operator=(const CGXDLMSProfileGeneric& other);
    CGXDLMSProfileGeneric& operator=(CGXDLMSProfileGeneric&& other) noexcept;

private:
    std::vector<std::vector<CGXDLMSVariant>> m_Buffer;
    std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> m_CaptureObjects;
    int m_CapturePeriod;
    GX_SORT_METHOD m_SortMethod;
    CGXDLMSObject *m_SortObject;
    unsigned long m_ProfileEntries;
    unsigned long m_EntriesInUse;

    int m_SortObjectAttributeIndex;
    int m_SortObjectDataIndex;

    int GetColumns(CGXByteBuffer &data) const;
    int GetData(
        CGXDLMSSettings &settings, CGXDLMSValueEventArg &e, const std::vector<std::vector<CGXDLMSVariant>> &table,
        std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> &columns, CGXByteBuffer &data
    ) const;

    int GetProfileGenericData(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e, CGXByteBuffer &reply) const;

    /**
     * Get selected columns.
     *
     * @param parameters
     *            Received data.
     * @param cols
     *            Selected columns.
     */
    int GetSelectedColumns(
        std::vector<CGXDLMSVariant> &cols, std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> &columns
    ) const;

public:
    /*
     * Add new capture object (column) to the profile generic.
     */
    int AddCaptureObject(CGXDLMSObject *pObj, int attributeIndex, int dataIndex);

    /**
    * Get selected columns from parameters.
    *
    * @param selector
    *            Is read by entry or range.
    * @param parameters
    *            Received parameters where columns information is found.
    * @param columns
    *            Selected columns.
    * @return Selected columns.
    */
    int GetSelectedColumns(
        int selector, CGXDLMSVariant &parameters,
        std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> &columns
    ) const;

    /**
     * @return Data of profile generic.
    */
    const std::vector<std::vector<CGXDLMSVariant>> &GetBuffer() const;
    std::vector<std::vector<CGXDLMSVariant>> &GetBuffer();

    /**
     * @return Captured Objects.
    */
    const std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> &GetCaptureObjects() const;
    std::vector<std::pair<CGXDLMSObject*, std::unique_ptr<CGXDLMSCaptureObject>>> &GetCaptureObjects();

    /**
     How often values are captured.
    */
    int GetCapturePeriod() const;
    void SetCapturePeriod(int value);

    /**
     How columns are sorted.
    */
    GX_SORT_METHOD GetSortMethod() const;
    void SetSortMethod(GX_SORT_METHOD value);

    /**
     Column that is used for sorting.
    */
    CGXDLMSObject *GetSortObject() const;
    void SetSortObject(CGXDLMSObject *value);

    /**
     Entries (rows) in Use.
    */
    unsigned long GetEntriesInUse() const;
    void SetEntriesInUse(unsigned long value);

    /**
     Maximum Entries (rows) count.
    */
    unsigned long GetProfileEntries() const;
    void SetProfileEntries(unsigned long value);
    /**
    Attribute index of sort object.
    */
    int GetSortObjectAttributeIndex() const;
    void SetSortObjectAttributeIndex(int value);

    /**
     Data index of sort object.
    */
    int GetSortObjectDataIndex() const;
    void SetSortObjectDataIndex(int value);

    /**
     Clears the buffer.
    */
    void Reset();

    /**
    * Copies the values of the objects to capture into the buffer by reading
    * capture objects.
    *
    * @param server
    *            DLMS server.
    * @return Result code.
    */
    int Capture(CGXDLMSServer *server);

    //Get attribute values of object.
    void GetValues(std::vector<std::string> &values) const;

    /////////////////////////////////////////////////////////////////////////
    // Returns collection of attributes to read.
    //
    // If attribute is static and already read or device is returned
    // HW error it is not returned.
    //
    // all: All items are returned even if they are read already.
    // attributes: Collection of attributes to read.
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);

    //Returns amount of attributes.
    int GetAttributeCount();

    //Returns amount of methods.
    int GetMethodCount();

    int GetDataType(int index, DLMS_DATA_TYPE &type);

    int Invoke(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /*
    * Returns value of given attribute.
    */
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /*
     * Set value of given attribute.
     */
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
    * Clears the buffer.
    *
    * @param client
    *            DLMS client.
    * @param reply
    *            Action bytes.
    * @return Result code.
    */
    int Reset(CGXDLMSClient &client, std::vector<CGXByteBuffer> &reply);

    /**
    * Copies the values of the objects to capture into the buffer by reading
    * each capture object.
    *
    * @param client
    *            DLMS client.
    * @param reply
    *            Action bytes.
    * @return Result code.
    */
    int Capture(CGXDLMSClient &client, std::vector<CGXByteBuffer> &reply);
};
#endif  //DLMS_IGNORE_PROFILE_GENERIC
#endif  //GXDLMSPROFILEGENERIC_H