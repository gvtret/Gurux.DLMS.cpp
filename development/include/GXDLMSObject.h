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
 * @brief Base class for all DLMS/COSEM objects.
 *
 * This class provides the fundamental properties and methods for DLMS/COSEM objects,
 * including logical name (LN), short name (SN), version, and attribute management.
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

    /*
     * Is attribute read. This can be used with static attributes to make
     * meter reading faster.
     */
    bool IsRead(int index);
    bool CanRead(int index);
    static int GetLogicalName(CGXDLMSObject *target, CGXDLMSVariant &value);
    static int SetLogicalName(CGXDLMSObject *target, CGXDLMSVariant &value);
    static int SetLogicalName(CGXDLMSObject *target, std::string &value);

public:
    /**
     * @brief Checks if a logical name is empty (all zeros).
     * @param pLN Pointer to the 6-byte logical name array.
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
     * @brief Constructor with object type.
     * @param type The DLMS object type.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type);

    /**
     * @brief Short Name (SN) constructor.
     * @param type The DLMS object type.
     * @param ln The logical name as a string.
     * @param sn The short name.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string &ln, unsigned short sn);

    /**
     * @brief Logical Name (LN) constructor.
     * @param type The DLMS object type.
     * @param ln The logical name as a string.
     */
    CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string &ln);
    /**
     * @brief Constructor with detailed parameters.
     * @param sn The short name.
     * @param class_id The class ID.
     * @param version The version number.
     * @param ln The logical name as a byte buffer.
     */
    CGXDLMSObject(short sn, unsigned short class_id, unsigned char version, CGXByteBuffer &ln);

    /**
     * @brief Virtual destructor.
     */
    virtual ~CGXDLMSObject(void);

    /**
     * @brief Gets the object's name (Logical or Short Name).
     * @return A variant containing the name.
     */
    CGXDLMSVariant GetName();

    /**
     * @brief Sets the object's name.
     * @param value A variant containing the name.
     * @return 0 on success, an error code otherwise.
     */
    int SetName(CGXDLMSVariant &value);

    /**
     * @brief Gets the object's interface class type.
     * @return The DLMS object type.
     */
    DLMS_OBJECT_TYPE GetObjectType();

    /**
     * @brief Gets the object's Short Name (SN).
     * @return The short name.
     */
    unsigned short GetShortName();

    /**
     * @brief Sets the object's Short Name (SN).
     * @param value The new short name.
     */
    void SetShortName(unsigned short value);

    /**
     * @brief Gets the object's Logical Name (LN).
     * @param ln A string to store the logical name.
     */
    void GetLogicalName(std::string &ln) const;

    /**
     * @brief Sets the object's version.
     * @param value The new version.
     */
    void SetVersion(unsigned short value);
    /**
     * @brief Gets the object's version.
     * @return The version.
     */
    unsigned short GetVersion();

    /**
     * @brief Gets the collection of attributes.
     * @return A reference to the attribute collection.
     */
    CGXAttributeCollection &GetAttributes();
    /**
     * @brief Gets the collection of method attributes.
     * @return A reference to the method attribute collection.
     */
    CGXAttributeCollection &GetMethodAttributes();
    /**
     * @brief Sets the data type for a specific attribute.
     * @param index The attribute index.
     * @param type The data type.
     * @return 0 on success, an error code otherwise.
     */
    virtual int SetDataType(int index, DLMS_DATA_TYPE type);
    /**
     * @brief Gets the data type of a specific attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return 0 on success, an error code otherwise.
     */
    virtual int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Gets the UI-specific data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return 0 on success, an error code otherwise.
     */
    virtual int GetUIDataType(int index, DLMS_DATA_TYPE &type);
    /**
     * @brief Sets the UI-specific data type for an attribute.
     * @param index The attribute index.
     * @param type The UI data type.
     */
    void SetUIDataType(int index, DLMS_DATA_TYPE type);

    /**
     * @brief Gets the access mode for an attribute.
     * @param index The attribute index.
     * @return The access mode.
     */
    DLMS_ACCESS_MODE GetAccess(int index);
    /**
     * @brief Sets the access mode for an attribute.
     * @param index The attribute index.
     * @param access The new access mode.
     */
    void SetAccess(int index, DLMS_ACCESS_MODE access);
    /**
     * @brief Gets the access mode for a method.
     * @param index The method index.
     * @return The method access mode.
     */
    DLMS_METHOD_ACCESS_MODE GetMethodAccess(int index);
    /**
     * @brief Sets the access mode for a method.
     * @param index The method index.
     * @param access The new method access mode.
     */
    void SetMethodAccess(int index, DLMS_METHOD_ACCESS_MODE access);


    /**
     * @brief Gets the description of the object.
     * @return A reference to the description string.
     */
    std::string &GetDescription();

    /**
     * @brief Sets the description of the object.
     * @param value The new description string.
     */
    void SetDescription(std::string &value);

    /**
     * @brief Gets the string representations of the object's attribute values.
     * @param values A vector to store the string values.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual void GetValues(std::vector<std::string> &/*values*/) {
        assert(0);
    }

    /**
     * @brief Gets the indices of attributes that need to be read.
     *
     * This method determines which attributes to read, potentially skipping
     * static attributes that have already been read.
     *
     * @param all If true, all attribute indices are returned, regardless of read status.
     * @param attributes A vector to store the indices of attributes to read.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual void GetAttributeIndexToRead(bool /*all*/, std::vector<int>& /*attributes*/) {
        assert(0);
    }

    /**
     * @brief Gets the indices of attributes that need to be read.
     *
     * This is an overloaded version that defaults to not reading all attributes.
     *
     * @param attributes A vector to store the indices of attributes to read.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual void GetAttributeIndexToRead(std::vector<int> &attributes) {
        GetAttributeIndexToRead(false, attributes);
    }

    /**
     * @brief Gets the total number of attributes in the object.
     * @return The attribute count.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual int GetAttributeCount() {
        assert(0);
        return 1;
    }

    /**
     * @brief Gets the total number of methods in the object.
     * @return The method count.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual int GetMethodCount() {
        assert(0);
        return 0;
    }

    /**
     * @brief Gets the value of a specific attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument, containing attribute index and returning the value.
     * @return 0 on success, an error code otherwise.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual int GetValue(CGXDLMSSettings &/*settings*/, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    /**
     * @brief Sets the value of a specific attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument, containing attribute index and the value to set.
     * @return 0 on success, an error code otherwise.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual int SetValue(CGXDLMSSettings &/*settings*/, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    /**
     * @brief Invokes a method on the object.
     * @param settings The DLMS settings.
     * @param e The value event argument, containing method index and parameters.
     * @return 0 on success, an error code otherwise.
     * @note This is a virtual method and must be implemented by derived classes.
     */
    virtual int Invoke(CGXDLMSSettings &/*settings*/, CGXDLMSValueEventArg &e) {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }
};

/**
 * @brief Represents a custom DLMS object.
 *
 * This class is a placeholder for custom or manufacturer-specific DLMS objects.
 */
class CGXDLMSCustomObject: public CGXDLMSObject {
public:
    /**
     * @brief Constructor for a custom object.
     * @param type The DLMS object type.
     */
    CGXDLMSCustomObject(DLMS_OBJECT_TYPE type): CGXDLMSObject(type) {
    }
};

#endif  //GXDLMSOBJECT_H