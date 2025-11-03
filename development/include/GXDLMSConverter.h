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

#ifndef GXDLMSCONVERTER_H
#define GXDLMSCONVERTER_H

#include "enums.h"
#include "GXStandardObisCodeCollection.h"
#include "GXDLMSObjectCollection.h"

/**
 * @brief This class is used to convert enum and error values to std::string.
 */
class CGXDLMSConverter {
    /**
     * @brief Collection of standard OBIS codes.
     */
    CGXStandardObisCodeCollection m_Codes;
    /**
     * @brief Updates the OBIS codes.
     */
    void UpdateObisCodes();

public:
    /**
     * @brief Destructor.
     */
    ~CGXDLMSConverter();
    /**
     * @brief Get Unit as String.
     * @param unit The unit to convert.
     * @return The unit as a string.
     */
    static const char *GetUnitAsString(int unit);
    /**
     * @brief Get baudrate enum value as std::string.
     * @param value The baudrate value.
     * @return The baudrate as a string.
     */
    static const char *ToString(DLMS_BAUD_RATE value);
    /**
     * @brief Get clock base enum value as std::string.
     * @param value The clock base value.
     * @return The clock base as a string.
     */
    static const char *ToString(DLMS_CLOCK_BASE value);
    /**
     * @brief Get clock status enum value as std::string.
     * @param value The clock status value.
     * @return The clock status as a string.
     */
    static const char *ToString(DLMS_CLOCK_STATUS value);

    /**
     * @brief Get error message as std::string.
     * @param error The error code.
     * @return The error message as a string.
     */
    static const char *GetErrorMessage(int error);

    /**
     * @brief Get address state enum value as std::string.
     * @param value The address state value.
     * @return The address state as a string.
     */
    static const char *ToString(DLMS_ADDRESS_STATE value);

    /**
     * @brief Get Disconnect control control state as a std::string.
     * @param value The control state value.
     * @return The control state as a string.
     */
    static const char *ToString(DLMS_CONTROL_STATE value);

    /**
     * @brief Get Disconnect control control mode as a std::string.
     * @param value The control mode value.
     * @return The control mode as a string.
     */
    static const char *ToString(DLMS_CONTROL_MODE value);

    /**
     * @brief Get Security Setup security policy as a std::string.
     * @param value The security policy value.
     * @return The security policy as a string.
     */
    static const char *ToString(DLMS_SECURITY_POLICY value);

    /**
     * @brief Get Security Setup security policy as a std::string.
     * @param value The security policy value.
     * @param str The output string.
     * @return 0 on success.
     */
    static int ToString(DLMS_SECURITY_POLICY value, std::string &str);

    /**
     * @brief Get Security Setup security suite as a std::string.
     * @param value The security suite value.
     * @return The security suite as a string.
     */
    static const char *ToString(DLMS_SECURITY_SUITE value);

    /**
     * @brief Get Logical Name association status as a std::string.
     * @param value The association status value.
     * @return The association status as a string.
     */
    static const char *ToString(DLMS_ASSOCIATION_STATUS value);

    /**
     * @brief Get optical port protocol mode as a std::string.
     * @param value The protocol mode value.
     * @return The protocol mode as a string.
     */
    static const char *ToString(DLMS_OPTICAL_PROTOCOL_MODE value);

    /**
     * @brief Get optical port response time as a std::string.
     * @param value The response time value.
     * @return The response time as a string.
     */
    static const char *ToString(DLMS_LOCAL_PORT_RESPONSE_TIME value);

    /**
     * @brief GSM status to string.
     * @param value The GSM status value.
     * @return The GSM status as a string.
     */
    static const char *ToString(DLMS_GSM_STATUS value);

    /**
     * @brief GSM circuit switced status to string.
     * @param value The circuit switched status value.
     * @return The circuit switched status as a string.
     */
    static const char *ToString(DLMS_GSM_CIRCUIT_SWITCH_STATUS value);

    /**
     * @brief Packet switched status to the string.
     * @param value The packet switched status value.
     * @return The packet switched status as a string.
     */
    static const char *ToString(DLMS_GSM_PACKET_SWITCH_STATUS value);

    /**
     * @brief Convert authentication enum value to string.
     * @param value The authentication value.
     * @return The authentication as a string.
     */
    static const char *ToString(DLMS_AUTHENTICATION value);

    /**
     * @brief Convert authentication string to enum value.
     * @param value The authentication string.
     * @return The authentication enum value.
     */
    static DLMS_AUTHENTICATION ValueOfAuthentication(const char *value);

    /**
     * @brief Convert association enum value to string.
     * @param value The association result value.
     * @return The association result as a string.
     */
    static const char *ToString(DLMS_ASSOCIATION_RESULT value);

    /**
     * @brief Convert association string to enum value.
     * @param value The association result string.
     * @return The association result enum value.
     */
    static DLMS_ASSOCIATION_RESULT ValueOfAssociation(const char *value);

    /**
     * @brief Convert source diagnostic enum value to string.
     * @param value The source diagnostic value.
     * @return The source diagnostic as a string.
     */
    static const char *ToString(DLMS_SOURCE_DIAGNOSTIC value);

    /**
     * @brief Convert source diagnostic string to enum value.
     * @param value The source diagnostic string.
     * @return The source diagnostic enum value.
     */
    static DLMS_SOURCE_DIAGNOSTIC ValueOfSourceDiagnostic(const char *value);

    /**
     * @brief Convert security enum value to string.
     * @param value The security value.
     * @return The security as a string.
     */
    static const char *ToString(DLMS_SECURITY value);

    /**
     * @brief Convert object type enum value to string.
     * @param type The object type.
     * @return The object type as a string.
     */
    static const char *ToString(DLMS_OBJECT_TYPE type);

    /**
     * @brief Convert object type string to enum value.
     * @param value The object type string.
     * @return The object type enum value.
     */
    static DLMS_OBJECT_TYPE ValueOfObjectType(const char *value);

    /**
     * @brief Get OBIS code description.
     * @param logicalName The logical name.
     * @param type The object type.
     * @param descriptions The output descriptions.
     */
    void GetDescription(std::string &logicalName, DLMS_OBJECT_TYPE type, std::vector<std::string> &descriptions);

    /**
     * @brief Update standard OBIS codes descriptions and type if defined.
     * @param objects The object collection.
     */
    void UpdateOBISCodeInformation(CGXDLMSObjectCollection &objects);

    /**
     * @brief Get X509 name.
     * @param value The X509 name value.
     * @return The X509 name as a string.
     */
    static const char *GetName(DLMS_X509_NAME value);

    /**
     * @brief Get X509 value.
     * @param value The X509 name string.
     * @return The X509 name enum value.
     */
    static DLMS_X509_NAME GetNameValue(const char *value);

    /**
     * @brief Converts X509 name enum value to string.
     * @param value The X509 name value.
     * @return The X509 name as a string.
     */
    static const char *ToString(DLMS_X509_NAME value);

    /**
     * @brief Converts X509 certificate type enum value to string.
     * @param value The certificate type value.
     * @return The certificate type as a string.
     */
    static const char *ToString(DLMS_X509_CERTIFICATE_TYPE value);

    /**
     * @brief Converts X509 certificate type string to enum value.
     * @param value The certificate type string.
     * @return The certificate type enum value.
     */
    static DLMS_X509_CERTIFICATE_TYPE ValueOfSourceDiagnosticX509CertificateType(const char *value);

    /**
     * @brief Converts X509 name string to enum value.
     * @param value The X509 name string.
     * @return The X509 name enum value.
     */
    static DLMS_X509_NAME ValueOfx509Name(const char *value);

    /**
     * @brief Converts X9 object identifier enum value to string.
     * @param value The X9 object identifier value.
     * @return The X9 object identifier as a string.
     */
    static const char *ToString(DLMS_X9_OBJECT_IDENTIFIER value);

    /**
     * @brief Converts X9 object identifier string to enum value.
     * @param value The X9 object identifier string.
     * @return The X9 object identifier enum value.
     */
    static DLMS_X9_OBJECT_IDENTIFIER ValueOfX9Identifier(const char *value);

    /**
     * @brief Converts PKCS object identifier enum value to string.
     * @param value The PKCS object identifier value.
     * @return The PKCS object identifier as a string.
     */
    static const char *ToString(DLMS_PKCS_OBJECT_IDENTIFIER value);

    /**
     * @brief Converts PKCS object identifier string to enum value.
     * @param value The PKCS object identifier string.
     * @return The PKCS object identifier enum value.
     */
    static DLMS_PKCS_OBJECT_IDENTIFIER ValueOfPKCSObjectIdentifier(const char *value);

    /**
     * @brief Converts hash algorithm enum value to string.
     * @param value The hash algorithm value.
     * @return The hash algorithm as a string.
     */
    static const char *ToString(DLMS_HASH_ALGORITHM value);

    /**
     * @brief Converts hash algorithm string to enum value.
     * @param value The hash algorithm string.
     * @return The hash algorithm enum value.
     */
    static DLMS_HASH_ALGORITHM ValueOfHashAlgorithm(const char *value);

    /*
    * @brief Convert key usage to certificate type.
    *
    * @param value Key usage.
    * @param type Certificate type.
    * @return 0 on success.
    */
    static int KeyUsageToCertificateType(DLMS_KEY_USAGE value, DLMS_CERTIFICATE_TYPE &type);
};
#endif  //GXDLMSCONVERTER_H