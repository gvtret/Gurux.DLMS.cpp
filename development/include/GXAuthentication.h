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

#ifndef GXAUTHENTICATION_H
#define GXAUTHENTICATION_H

#include "GXDLMSVariant.h"

/**
 * @brief Represents a DLMS/COSEM authentication context.
 *
 * This class holds the necessary information for a DLMS/COSEM authentication
 * procedure, including the authentication mechanism type, the client's identifier
 * (or address), and the password or secret.
 */
class GXAuthentication {
    /**
     * @brief The identifier of the client initiating the authentication.
     */
    CGXDLMSVariant m_ClientID;
    /**
     * @brief The type of authentication mechanism to be used (e.g., Low, High-level).
     */
    DLMS_AUTHENTICATION m_Type;
    /**
     * @brief The password or secret used for the authentication.
     */
    std::string m_Password;

public:
    /**
     * @brief Default constructor.
     */
    GXAuthentication(void) {
    }

    /**
     * @brief Constructor to initialize the authentication context.
     * @param type The authentication mechanism type.
     * @param password The password or secret.
     * @param clientID The client's identifier.
     */
    GXAuthentication(DLMS_AUTHENTICATION type, std::string password, CGXDLMSVariant clientID) {
        m_Type = type;
        m_ClientID = clientID;
    }

    /**
     * @brief Gets the authentication type.
     * @return The DLMS_AUTHENTICATION enumeration value.
     */
    DLMS_AUTHENTICATION GetType() {
        return m_Type;
    }

    /**
     * @brief Sets the authentication type.
     * @param value The DLMS_AUTHENTICATION enumeration value.
     */
    void SetType(DLMS_AUTHENTICATION value) {
        m_Type = value;
    }

    /**
     * @brief Gets the client's identifier.
     * @return The client ID as a CGXDLMSVariant.
     */
    CGXDLMSVariant GetClientID() {
        return m_ClientID;
    }

    /**
     * @brief Sets the client's identifier.
     * @param value The client ID as a CGXDLMSVariant.
     */
    void SetClientID(CGXDLMSVariant value) {
        m_ClientID = value;
    }

    /**
     * @brief Gets the password or secret.
     * @return The password string.
     */
    std::string GetPassword() {
        return m_Password;
    }

    /**
     * @brief Sets the password or secret.
     * @param value The password string.
     */
    void SetPassword(std::string value) {
        m_Password = value;
    }
};
#endif  //GXAUTHENTICATION_H
