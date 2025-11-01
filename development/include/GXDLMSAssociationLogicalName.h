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
#ifndef GXDLMSASSOCIATIONLOGICALNAME_H
#define GXDLMSASSOCIATIONLOGICALNAME_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#include "GXDLMSObject.h"
#include "GXApplicationContextName.h"
#include "GXDLMSContextType.h"
#include "GXAuthenticationMechanismName.h"
#include "GXDLMSObjectCollection.h"

/**
 * @brief Represents a DLMS/COSEM logical name association object.
 */
class CGXDLMSAssociationLogicalName: public CGXDLMSObject {
private:
    /**
     * Association status.
     */
    DLMS_ASSOCIATION_STATUS m_AssociationStatus;
    /**
     * Object list.
     */
    CGXDLMSObjectCollection m_ObjectList;
    /**
     * Client SAP.
     */
    unsigned char m_ClientSAP;
    /**
     * Server SAP.
     */
    unsigned short m_ServerSAP;
    /**
     * Application context name.
     */
    CGXApplicationContextName m_ApplicationContextName;
    /**
     * xDLMS context info.
     */
    CGXDLMSContextType m_XDLMSContextInfo;
    /**
     * Authentication mechanism name.
     */
    CGXAuthenticationMechanismName m_AuthenticationMechanismName;

    /**
     * @brief Secret for authentication.
     */
    CGXByteBuffer m_Secret;

    /**
     * Security setup reference.
     */
    std::string m_SecuritySetupReference;

    /**
     * User list.
     */
    std::vector<std::pair<unsigned char, std::string>> m_UserList;

    /**
     * Current user.
     */
    std::pair<unsigned char, std::string> m_CurrentUser;

    /**
     * @brief Updates the access rights of an object.
     * @param pObj A pointer to the object.
     * @param data The access rights data.
     */
    void UpdateAccessRights(CGXDLMSObject *pObj, CGXDLMSVariant data);

    /**
     * @brief Gets the access rights of an object.
     * @param pItem A pointer to the object.
     * @param server A pointer to the DLMS server.
     * @param data A reference to a buffer to store the access rights.
     * @return An error code.
     */
    int GetAccessRights(CGXDLMSObject *pItem, CGXDLMSServer *server, CGXByteBuffer &data);

    /**
     * @brief Gets the list of objects.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @param data A reference to a buffer to store the object list.
     * @return An error code.
     */
    int GetObjects(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e, CGXByteBuffer &data);

    /**
     * @brief Gets the list of users.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @param data A reference to a buffer to store the user list.
     * @return An error code.
     */
    int GetUsers(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e, CGXByteBuffer &data);

public:
    /**
     * @brief Constructor.
     */
    CGXDLMSAssociationLogicalName();

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     */
    CGXDLMSAssociationLogicalName(std::string ln);

    /**
     * @brief Destructor.
     */
    ~CGXDLMSAssociationLogicalName();

    /**
     * @brief Gets the object list.
     * @return A reference to the object list.
     */
    CGXDLMSObjectCollection &GetObjectList();

    /**
     * @brief Gets the client SAP.
     * @return The client SAP.
     */
    unsigned char GetClientSAP();

    /**
     * @brief Sets the client SAP.
     * @param value The client SAP to set.
     */
    void SetClientSAP(unsigned char value);

    /**
     * @brief Gets the server SAP.
     * @return The server SAP.
     */
    unsigned short GetServerSAP();

    /**
     * @brief Sets the server SAP.
     * @param value The server SAP to set.
     */
    void SetServerSAP(unsigned short value);

    /**
     * @brief Gets the application context name.
     * @return A reference to the application context name.
     */
    CGXApplicationContextName &GetApplicationContextName();

    /**
     * @brief Gets the xDLMS context info.
     * @return A reference to the xDLMS context info.
     */
    CGXDLMSContextType &GetXDLMSContextInfo();

    /**
     * @brief Gets the authentication mechanism name.
     * @return A reference to the authentication mechanism name.
     */
    CGXAuthenticationMechanismName &GetAuthenticationMechanismName();

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
     * @brief Gets the user list.
     * @return A reference to the user list.
     */
    std::vector<std::pair<unsigned char, std::string>> &GetUserList();

    /**
     * @brief Sets the user list.
     * @param value The user list to set.
     */
    void SetUserList(std::vector<std::pair<unsigned char, std::string>> &value);

    /**
     * @brief Gets the current user.
     * @return A reference to the current user.
     */
    std::pair<unsigned char, std::string> &GetCurrentUser();

    /**
     * @brief Sets the current user.
     * @param value The current user to set.
     */
    void SetCurrentUser(std::pair<unsigned char, std::string> &value);

    /**
     * @brief Updates the secret.
     * @param client The DLMS client.
     * @param reply A vector to store the reply packets.
     * @return An error code.
     */
    int UpdateSecret(CGXDLMSClient *client, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Adds a user to the user list.
     * @param client The DLMS client.
     * @param id The user ID.
     * @param name The user name.
     * @param reply A vector to store the reply packets.
     * @return An error code.
     */
    int AddUser(CGXDLMSClient *client, unsigned char id, std::string name, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Removes a user from the user list.
     * @param client The DLMS client.
     * @param id The user ID.
     * @param name The user name.
     * @param reply A vector to store the reply packets.
     * @return An error code.
     */
    int RemoveUser(CGXDLMSClient *client, unsigned char id, std::string name, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Gets the association status.
     * @return The association status.
     */
    DLMS_ASSOCIATION_STATUS GetAssociationStatus();

    /**
     * @brief Sets the association status.
     * @param value The association status to set.
     */
    void SetAssociationStatus(DLMS_ASSOCIATION_STATUS value);

    /**
     * @brief Gets the security setup reference.
     * @return The security setup reference.
     */
    std::string GetSecuritySetupReference();

    /**
     * @brief Sets the security setup reference.
     * @param value The security setup reference to set.
     */
    void SetSecuritySetupReference(std::string value);

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
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Invokes a method.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
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
#endif  //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#endif  //GXDLMSASSOCIATIONLOGICALNAME_H
