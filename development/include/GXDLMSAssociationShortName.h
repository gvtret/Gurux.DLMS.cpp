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

#ifndef GXDLMSASSOCIATIONSHORTNAME_H
#define GXDLMSASSOCIATIONSHORTNAME_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#include "GXDLMSObject.h"

/**
 * @brief Represents a DLMS/COSEM short name association object.
 */
class CGXDLMSAssociationShortName: public CGXDLMSObject {
    /**
     * Object list.
     */
    CGXDLMSObjectCollection m_ObjectList;
    /**
     * Security setup reference.
     */
    std::string m_SecuritySetupReference;
    /**
     * Secret.
     */
    CGXByteBuffer m_Secret;

    /**
     * @brief Gets the access rights for an object.
     * @param pObj The object.
     * @param server The DLMS server.
     * @param data The buffer to store the access rights.
     * @return An error code.
     */
    int GetAccessRights(CGXDLMSObject *pObj, CGXDLMSServer *server, CGXByteBuffer &data);

    /**
     * @brief Updates the access rights for an object.
     * @param buff The buffer containing the new access rights.
     */
    void UpdateAccessRights(CGXDLMSVariant &buff);

public:
    /**
     * @brief Constructor.
     */
    CGXDLMSAssociationShortName();

    /**
     * @brief Gets the object list.
     * @return A reference to the object list.
     */
    CGXDLMSObjectCollection &GetObjectList();

    /**
     * @brief Gets the secret.
     * @return A reference to the secret buffer.
     */
    CGXByteBuffer &GetSecret();

    /**
     * @brief Sets the secret.
     * @param value The secret to set.
     */
    void SetSecret(CGXByteBuffer &value);

    /**
     * @brief Gets the security setup reference.
     * @return A reference to the security setup reference string.
     */
    std::string &GetSecuritySetupReference();

    /**
     * @brief Sets the security setup reference.
     * @param value The security setup reference to set.
     */
    void SetSecuritySetupReference(std::string &value);

    /**
     * @brief Gets the attribute values as strings.
     * @param values A reference to a vector to store the values.
     */
    void GetValues(std::vector<std::string> &values);

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);

    /**
     * @brief Gets the number of attributes.
     * @return The number of attributes.
     */
    int GetAttributeCount();

    /**
     * @brief Gets the number of methods.
     * @return The number of methods.
     */
    int GetMethodCount();

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Gets the SN Association View.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @param data A buffer to store the data.
     * @return An error code.
     */
    int GetObjects(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e, CGXByteBuffer &data);

    /**
     * @brief Invokes a method.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * M@return An error code.
     */
    int Invoke(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
     * @brief Gets the value of an attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
     * @brief Sets the value of an attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
};
#endif  //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#endif  //GXDLMSASSOCIATIONSHORTNAME_H
