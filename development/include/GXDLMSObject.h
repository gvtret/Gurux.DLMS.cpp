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

#ifndef GXDLMSOBJECT_H
#define GXDLMSOBJECT_H

#include <string.h>
#include <vector>
#include <map>
#include <assert.h>
#include "GXAttributeCollection.h"
#include "GXDLMSVariant.h"
#include "IGXDLMSBase.h"
#include "GXHelpers.h"
#include "GXDateTime.h"

class CGXDLMSObjectCollection;

/**
 * @brief Represents a generic DLMS/COSEM object.
 */
class CGXDLMSObject: public IGXDLMSBase {
    friend class CGXDLMSClient;
    friend class CGXDLMSObjectCollection;
    friend class CGXDLMSObjectFactory;
    friend class CGXDLMSAssociationLogicalName;
    friend class CGXDLMSAssociationShortName;
    friend class CGXDLMSProfileGeneric;

    CGXAttributeCollection m_Attributes;
    CGXAttributeCollection m_MethodAttributes;
    void Initialize(short sn, unsigned short class_id, unsigned char version, CGXByteBuffer *pLogicalName);
    std::string m_Description;
    DLMS_OBJECT_TYPE m_ObjectType;

protected:
    unsigned short m_Version;
    std::map<int, time_t> m_ReadTimes;
    unsigned short m_SN;
    unsigned char m_LN[6];

    /**
     * @brief Checks if an attribute has been read.
     * @param index The attribute index.
     * @return True if the attribute has been read, false otherwise.
     */
    bool IsRead(int index);

    /**
     * @brief Checks if an attribute can be read.
     * @param index The attribute index.
     * @return True if the attribute can be read, false otherwise.
     */
    bool CanRead(int index);

    static int GetLogicalName(CGXDLMSObject *target, CGXDLMSVariant &value);
    static int SetLogicalName(CGXDLMSObject *target, CGXDLMSVariant &value);
    static int SetLogicalName(CGXDLMSObject *target, std::string &value);

public:
    /**
     * @brief Checks if a logical name is empty.
     * @param pLN A pointer to the logical name.
     * @return True if the logical name is empty, false otherwise.
     */
    static bool IsLogicalNameEmpty(unsigned char *pLN) {
        const unsigned char EmptyLN[] = {0, 0, 0, 0, 0, 0};
        return memcmp(pLN, EmptyLN, 6) == 0;
    }

    /**
     * @brief Default constructor.
     */
    CGXDLMSObject(void);

    /**
     * @brief Constructor.
     * @param type The object type.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type);

    /**
     * @brief Constructor for SN referencing.
     * @param type The object type.
     * @param ln The logical name.
     * @param sn The short name.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string &ln, unsigned short sn);

    /**
     * @brief Constructor for LN referencing.
     * @param type The object type.
     * @param ln The logical name.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string &ln);

    /**
     * @brief Constructor.
     * @param sn The short name.
     * @param class_id The class ID.
     * @param version The version.
     * @param ln The logical name.
     */
    CGXDLMSObject(short sn, unsigned short class_id, unsigned char version, CGXByteBuffer &ln);

    /**
     * @brief Destructor.
     */
    virtual ~CGXDLMSObject(void);

    /**
     * @brief Gets the object's name (logical or short).
     * @return The name as a variant.
     */
    CGXDLMSVariant GetName();

    /**
     * @brief Sets the object's name.
     * @param value The name to set.
     * @return An error code.
     */
    int SetName(CGXDLMSVariant &value);

    /**
     * @brief Gets the object's interface class type.
     * @return The object type.
     */
    DLMS_OBJECT_TYPE GetObjectType();

    /**
     * @brief Gets the object's short name.
     * @return The short name.
     */
    unsigned short GetShortName();

    /**
     * @brief Sets the object's short name.
     * @param value The short name to set.
     */
    void SetShortName(unsigned short value);

    /**
     * @brief Gets the object's logical name.
     * @param ln A reference to a string to store the logical name.
     */
    void GetLogicalName(std::string &ln) const;

    /**
     * @brief Sets the object's version.
     * @param value The version to set.
     */
    void SetVersion(unsigned short value);

    /**
     * @brief Gets the object's version.
     * @return The version.
     */
    unsigned short GetVersion();

    /**
     * @brief Gets the object's attributes.
     * @return A reference to the attribute collection.
     */
    CGXAttributeCollection &GetAttributes();

    /**
     * @brief Gets the object's method attributes.
     * @return A reference to the method attribute collection.
     */
    CGXAttributeCollection &GetMethodAttributes();

    /**
     * @brief Sets the data type of an attribute.
     * @param index The attribute index.
     * @param type The data type to set.
     * @return An error code.
     */
    virtual int SetDataType(int index, DLMS_DATA_TYPE type);

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    virtual int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Gets the UI data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    virtual int GetUIDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Sets the UI data type of an attribute.
     * @param index The attribute index.
     * @param type The data type to set.
     */
    void SetUIDataType(int index, DLMS_DATA_TYPE type);

    /**
     * @brief Gets the access mode of an attribute.
     * @param index The attribute index.
     * @return The access mode.
     */
    DLMS_ACCESS_MODE GetAccess(int index);

    /**
     * @brief Sets the access mode of an attribute.
     * @param index The attribute index.
     * @param access The access mode to set.
     */
    void SetAccess(int index, DLMS_ACCESS_MODE access);

    /**
     * @brief Gets the access mode of a method.
     * @param index The method index.
     * @return The method access mode.
     */
    DLMS_METHOD_ACCESS_MODE GetMethodAccess(int index);

    /**
     * @brief Sets the access mode of a method.
     * @param index The method index.
     * @param access The method access mode to set.
     */
    void SetMethodAccess(int index, DLMS_METHOD_ACCESS_MODE access);

    /**
     * @brief Gets the description of the object.
     * @return A reference to the description string.
     */
    std::string &GetDescription();

    /**
     * @brief Sets the description of the object.
     * @param value The description to set.
     */
    void SetDescription(std::string &value);

    /**
     * @brief Gets the attribute values as strings.
     * @param values A reference to a vector to store the values.
     */
    virtual void GetValues(std::vector<std::string> &values) {
        assert(0);
    }

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    virtual void GetAttributeIndexToRead(bool all, std::vector<int>& attributes) {
        assert(0);
    }

    /**
     * @brief Gets the attribute indices to read.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    virtual void GetAttributeIndexToRead(std::vector<int> &attributes) {
        GetAttributeIndexToRead(false, attributes);
    }

    /**
     * @brief Gets the number of attributes.
     * @return The number of attributes.
     */
    virtual int GetAttributeCount() {
        assert(0);
        return 1;
    }

    /**
     * @brief Gets the number of methods.
     * @return The number of methods.
     */
    virtual int GetMethodCount() {
        assert(0);
        return 0;
    }

    /**
     * @brief Gets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    virtual int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    /**
     * @brief Sets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    virtual int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    /**
     * @brief Invokes a method.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    virtual int Invoke(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }
};

/**
 * @brief Represents a custom DLMS/COSEM object.
 */
class CGXDLMSCustomObject: public CGXDLMSObject {
public:
    CGXDLMSCustomObject(DLMS_OBJECT_TYPE type): CGXDLMSObject(type) {
    }
};

#endif  //GXDLMSOBJECT_H
