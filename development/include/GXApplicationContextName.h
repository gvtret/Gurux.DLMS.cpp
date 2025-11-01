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

#ifndef GXAPPLICATIONCONTEXTNAME_H
#define GXAPPLICATIONCONTEXTNAME_H

#include <string>
#include "enums.h"

/**
 * @brief Represents a DLMS/COSEM Application Context Name (ACN).
 *
 * The ACN is an Object Identifier (OID) that specifies the application-layer
 * protocol being used for a DLMS/COSEM association. It determines the set of
 * available services, such as Logical Name (LN) referencing or Short Name (SN)
 * referencing, and the security level of the connection.
 */
class CGXApplicationContextName {
private:
    /**
     * @brief The logical name derived from the ACN components.
     */
    std::string m_LogicalName;
    /**
     * @brief The 'joint-iso-ctt' component of the OID.
     */
    unsigned char m_JointIsoCtt;
    /**
     * @brief The 'country' component of the OID.
     */
    unsigned char m_Country;
    /**
     * @brief The 'country-name' component of the OID.
     */
    unsigned short m_CountryName;
    /**
     * @brief The 'identified-organization' component of the OID.
     */
    unsigned char m_IdentifiedOrganization;
    /**
     * @brief The 'dlms-ua' component of the OID.
     */
    unsigned char m_DlmsUA;
    /**
     * @brief The 'application-context' component of the OID.
     */
    unsigned char m_ApplicationContext;
    /**
     * @brief An enumeration representing the complete application context ID.
     */
    DLMS_APPLICATION_CONTEXT_NAME m_ContextId;

public:
    /**
     * @brief Default constructor. Initializes a new instance of the CGXApplicationContextName class.
     */
    CGXApplicationContextName();

    /**
     * @brief Gets the 'joint-iso-ctt' component.
     * @return The value of the 'joint-iso-ctt' component.
     */
    unsigned char GetJointIsoCtt();
    /**
     * @brief Sets the 'joint-iso-ctt' component.
     * @param value The new value for the 'joint-iso-ctt' component.
     */
    void SetJointIsoCtt(unsigned char value);

    /**
     * @brief Gets the 'country' component.
     * @return The value of the 'country' component.
     */
    unsigned char GetCountry();
    /**
     * @brief Sets the 'country' component.
     * @param value The new value for the 'country' component.
     */
    void SetCountry(unsigned char value);

    /**
     * @brief Gets the 'country-name' component.
     * @return The value of the 'country-name' component.
     */
    unsigned short GetCountryName();
    /**
     * @brief Sets the 'country-name' component.
     * @param value The new value for the 'country-name' component.
     */
    void SetCountryName(unsigned short value);

    /**
     * @brief Gets the 'identified-organization' component.
     * @return The value of the 'identified-organization' component.
     */
    unsigned char GetIdentifiedOrganization();
    /**
     * @brief Sets the 'identified-organization' component.
     * @param value The new value for the 'identified-organization' component.
     */
    void SetIdentifiedOrganization(unsigned char value);

    /**
     * @brief Gets the 'dlms-ua' component.
     * @return The value of the 'dlms-ua' component.
     */
    unsigned char GetDlmsUA();
    /**
     * @brief Sets the 'dlms-ua' component.
     * @param value The new value for the 'dlms-ua' component.
     */
    void SetDlmsUA(unsigned char value);

    /**
     * @brief Gets the 'application-context' component.
     * @return The value of the 'application-context' component.
     */
    unsigned char GetApplicationContext();
    /**
     * @brief Sets the 'application-context' component.
     * @param value The new value for the 'application-context' component.
     */
    void SetApplicationContext(unsigned char value);

    /**
     * @brief Gets the complete context ID enumeration.
     * @return The DLMS_APPLICATION_CONTEXT_NAME enumeration value.
     */
    DLMS_APPLICATION_CONTEXT_NAME GetContextId();
    /**
     * @brief Sets the complete context ID from an enumeration.
     * @param value The new DLMS_APPLICATION_CONTEXT_NAME value.
     */
    void SetContextId(DLMS_APPLICATION_CONTEXT_NAME value);

    /**
     * @brief Returns a string representation of the Application Context Name.
     * @return A string containing the formatted ACN.
     */
    std::string ToString();
};
#endif  //GXAPPLICATIONCONTEXTNAME_H