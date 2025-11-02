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

#ifndef GXAUTHENTICATIONMECHANISMNAME_H
#define GXAUTHENTICATIONMECHANISMNAME_H

#include "enums.h"
#include <string>

/**
 * @brief Represents a DLMS/COSEM Authentication Mechanism Name.
 *
 * This class encapsulates the Object Identifier (OID) that uniquely identifies
 * a DLMS/COSEM authentication mechanism, such as Low-Level or High-Level Security.
 */
class CGXAuthenticationMechanismName {
private:
    /**
     * @brief The 'joint-iso-ctt' component of the OID.
     */
    int m_JointIsoCtt;
    /**
     * @brief The 'country' component of the OID.
     */
    int m_Country;
    /**
     * @brief The 'country-name' component of the OID.
     */
    int m_CountryName;
    /**
     * @brief The 'identified-organization' component of the OID.
     */
    int m_IdentifiedOrganization;
    /**
     * @brief The 'dlms-ua' component of the OID.
     */
    int m_DlmsUA;
    /**
     * @brief The 'authentication-mechanism-name' component of the OID.
     */
    int m_AuthenticationMechanismName;
    /**
     * @brief An enumeration representing the complete mechanism ID.
     */
    DLMS_AUTHENTICATION m_MechanismId;

public:
    /**
     * @brief Constructor.
     */
    CGXAuthenticationMechanismName();

    /**
     * @brief Gets the 'joint-iso-ctt' component.
     * @return The value.
     */
    int GetJointIsoCtt();

    /**
     * @brief Sets the 'joint-iso-ctt' component.
     * @param value The new value.
     */
    void SetJointIsoCtt(int value);

    /**
     * @brief Gets the 'country' component.
     * @return The value.
     */
    int GetCountry();

    /**
     * @brief Sets the 'country' component.
     * @param value The new value.
     */
    void SetCountry(int value);

    /**
     * @brief Gets the 'country-name' component.
     * @return The value.
     */
    int GetCountryName();

    /**
     * @brief Sets the 'country-name' component.
     * @param value The new value.
     */
    void SetCountryName(int value);

    /**
     * @brief Gets the 'identified-organization' component.
     * @return The value.
     */
    int GetIdentifiedOrganization();

    /**
     * @brief Sets the 'identified-organization' component.
     * @param value The new value.
     */
    void SetIdentifiedOrganization(int value);

    /**
     * @brief Gets the 'dlms-ua' component.
     * @return The value.
     */
    int GetDlmsUA();

    /**
     * @brief Sets the 'dlms-ua' component.
     * @param value The new value.
     */
    void SetDlmsUA(int value);

    /**
     * @brief Gets the 'authentication-mechanism-name' component.
     * @return The value.
     */
    int GetAuthenticationMechanismName();

    /**
     * @brief Sets the 'authentication-mechanism-name' component.
     * @param value The new value.
     */
    void SetAuthenticationMechanismName(int value);

    /**
     * @brief Gets the complete mechanism ID enumeration.
     * @return The DLMS_AUTHENTICATION value.
     */
    DLMS_AUTHENTICATION GetMechanismId();

    /**
     * @brief Sets the complete mechanism ID from an enumeration.
     * @param value The new DLMS_AUTHENTICATION value.
     */
    void SetMechanismId(DLMS_AUTHENTICATION value);

    /**
     * @brief Returns a string representation of the Authentication Mechanism Name.
     * @return A string containing the formatted OID.
     */
    std::string ToString();
};
#endif  //GXAUTHENTICATIONMECHANISMNAME_H
