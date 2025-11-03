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
 * @brief Represents a DLMS/COSEM logical name association, managing the
 *        relationship and security context between a client and a server.
 */
class CGXDLMSAssociationLogicalName : public CGXDLMSObject
{
private:
    /**
     * The current status of the association.
     */
    DLMS_ASSOCIATION_STATUS m_AssociationStatus;
    /**
     * A collection of objects accessible through this association.
     */
    CGXDLMSObjectCollection m_ObjectList;
    /**
     * The client's Service Access Point (SAP) address.
     */
    unsigned char m_ClientSAP;
    /**
     * The server's Service Access Point (SAP) address.
     */
    unsigned short m_ServerSAP;
    /**
     * The application context name for this association.
     */
    CGXApplicationContextName m_ApplicationContextName;
    /**
     * Detailed information about the xDLMS context.
     */
    CGXDLMSContextType m_XDLMSContextInfo;
    /**
     * The mechanism used for authentication.
     */
    CGXAuthenticationMechanismName m_AuthenticationMechanismName;
    /**
     * The secret key or password used for authentication.
     */
    CGXByteBuffer m_Secret;
    /**
     * A reference to the security setup object.
     */
    std::string m_SecuritySetupReference;
    /**
     * A list of users and their corresponding roles or IDs.
     */
    std::vector<std::pair<unsigned char, std::string>> m_UserList;
    /**
     * The currently authenticated user for this association.
     */
    std::pair<unsigned char, std::string> m_CurrentUser;

    /**
     * @brief Updates the access rights of a specific DLMS object.
     * @param pObj The object whose access rights are to be updated.
     * @param data The new access rights information.
     */
    void UpdateAccessRights(CGXDLMSObject* pObj, CGXDLMSVariant data);

    /**
     * @brief Retrieves the access rights of a specific DLMS object.
     * @param pItem  The object whose access rights are to be retrieved.
     * @param server The DLMS server instance.
     * @param data   A byte buffer to store the retrieved access rights.
     * @return An error code indicating the success of the operation.
     */
    int GetAccessRights(CGXDLMSObject* pItem, CGXDLMSServer* server, CGXByteBuffer& data);

    /**
     * @brief Retrieves the list of accessible objects for this association.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @param data     A byte buffer to store the retrieved object list.
     * @return An error code indicating the success of the operation.
     */
    int GetObjects(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e, CGXByteBuffer& data);

    /**
     * @brief Retrieves the list of users for this association.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @param data     A byte buffer to store the retrieved user list.
     * @return An error code indicating the success of the operation.
     */
    int GetUsers(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e, CGXByteBuffer& data);

public:
    /**
     * @brief Initializes a new instance of the CGXDLMSAssociationLogicalName
     *        class.
     */
    CGXDLMSAssociationLogicalName();

    /**
     * @brief Initializes a new instance of the CGXDLMSAssociationLogicalName
     *        class.
     * @param ln The logical name of the object.
     */
    CGXDLMSAssociationLogicalName(std::string ln);

    /**
     * @brief Destroys the CGXDLMSAssociationLogicalName object.
     */
    ~CGXDLMSAssociationLogicalName();

    /**
     * @brief Gets the collection of objects accessible through this
     *        association.
     * @return A reference to the object collection.
     */
    CGXDLMSObjectCollection& GetObjectList();

    /**
     * @brief Gets the client's Service Access Point (SAP) address.
     * @return The client SAP.
     */
    unsigned char GetClientSAP();

    /**
     * @brief Sets the client's Service Access Point (SAP) address.
     * @param value The client SAP.
     */
    void SetClientSAP(unsigned char value);

    /**
     * @brief Gets the server's Service Access Point (SAP) address.
     * @return The server SAP.
     */
    unsigned short GetServerSAP();

    /**
     * @brief Sets the server's Service Access Point (SAP) address.
     * @param value The server SAP.
     */
    void SetServerSAP(unsigned short value);

    /**
     * @brief Gets the application context name for this association.
     * @return A reference to the application context name.
     */
    CGXApplicationContextName& GetApplicationContextName();

    /**
     * @brief Gets detailed information about the xDLMS context.
     * @return A reference to the xDLMS context info.
     */
    CGXDLMSContextType& GetXDLMSContextInfo();

    /**
     * @brief Gets the authentication mechanism used for this association.
     * @return A reference to the authentication mechanism name.
     */
    CGXAuthenticationMechanismName& GetAuthenticationMechanismName();

    /**
     * @brief Gets the secret key used for authentication.
     * @return A reference to the secret key.
     */
    CGXByteBuffer& GetSecret();

    /**
     * @brief Sets the secret key used for authentication.
     * @param value The secret key.
     */
    void SetSecret(CGXByteBuffer& value);

    /**
     * @brief Gets the list of users for this association.
     * @return A reference to the user list.
     */
    std::vector<std::pair<unsigned char, std::string>>& GetUserList();

    /**
     * @brief Sets the list of users for this association.
     * @param value The user list.
     */
    void SetUserList(std::vector<std::pair<unsigned char, std::string>>& value);

    /**
     * @brief Gets the currently authenticated user for this association.
     * @return A reference to the current user.
     */
    std::pair<unsigned char, std::string>& GetCurrentUser();

    /**
     * @brief Sets the currently authenticated user for this association.
     * @param value The current user.
     */
    void SetCurrentUser(std::pair<unsigned char, std::string>& value);

    /**
     * @brief Updates the authentication secret on the server.
     * @param client The DLMS client instance.
     * @param reply  A vector to store reply packets from the server.
     * @return An error code indicating the success of the operation.
     */
    int UpdateSecret(CGXDLMSClient* client, std::vector<CGXByteBuffer>& reply);

    /**
     * @brief Adds a new user to the association's user list on the server.
     * @param client The DLMS client instance.
     * @param id     The ID of the user to add.
     * @param name   The name of the user to add.
     * @param reply  A vector to store reply packets from the server.
     * @return An error code indicating the success of the operation.
     */
    int AddUser(CGXDLMSClient* client, unsigned char id, std::string name, std::vector<CGXByteBuffer>& reply);

    /**
     * @brief Removes a user from the association's user list on the server.
     * @param client The DLMS client instance.
     * @param id     The ID of the user to remove.
     * @param name   The name of the user to remove.
     * @param reply  A vector to store reply packets from the server.
     * @return An error code indicating the success of the operation.
     */
    int RemoveUser(CGXDLMSClient* client, unsigned char id, std::string name, std::vector<CGXByteBuffer>& reply);

    /**
     * @brief Gets the current status of the association.
     * @return The association status.
     */
    DLMS_ASSOCIATION_STATUS GetAssociationStatus();

    /**
     * @brief Sets the current status of the association.
     * @param value The association status.
     */
    void SetAssociationStatus(DLMS_ASSOCIATION_STATUS value);

    /**
     * @brief Gets the reference to the security setup object.
     * @return The security setup reference.
     */
    std::string GetSecuritySetupReference();

    /**
     * @brief Sets the reference to the security setup object.
     * @param value The security setup reference.
     */
    void SetSecuritySetupReference(std::string value);

    /**
     * @brief Returns the total number of attributes in the object.
     * @return The attribute count.
     */
    int GetAttributeCount();

    /**
     * @brief Returns the total number of methods in the object.
     * @return The method count.
     */
    int GetMethodCount();

    /**
     * @brief Retrieves all attribute values from the object.
     * @param values A vector to store the attribute values as strings.
     */
    void GetValues(std::vector<std::string>& values);

    /**
     * @brief Fills a list with the attribute indices that should be read from
     *        the device.
     * @param all        If true, all attributes are included; otherwise, only
     *                   unread attributes are included.
     * @param attributes A list to store the indices of attributes to read.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    /**
     * @brief Gets the data type of a specific attribute.
     * @param index The index of the attribute.
     * @param type  An output parameter to store the attribute's data type.
     * @return An error code indicating the success of the operation.
     */
    int GetDataType(int index, DLMS_DATA_TYPE& type);

    /**
     * @brief Invokes a method on the DLMS object.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing method details.
     * @return An error code indicating the success of the operation.
     */
    int Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Gets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Sets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif  //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#endif  //GXDLMSASSOCIATIONLOGICALNAME_H
