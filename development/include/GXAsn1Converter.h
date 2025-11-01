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
// See the GNU General Public License for more details->
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXASN1CONVERTER_H
#define GXASN1CONVERTER_H

#include <vector>
#include <map>
#include "GXDLMSVariant.h"
#include "GXHelpers.h"
#include "GXAsn1Base.h"
#include "GXAsn1BitString.h"
#include "GXDLMSConverter.h"
#include "GXAsn1Context.h"
#include "GXAsn1Integer.h"
#include "GXAsn1Ia5String.h"
#include "GXAsn1Utf8String.h"
#include "GXAsn1Sequence.h"
#include "GXAsn1ObjectIdentifier.h"
#include "GXAsn1Variant.h"
#include "GXAsn1Set.h"
#include "GXAsn1Helpers.h"
#include "GXAsn1Time.h"

/**
 * @brief Provides static methods to convert between ASN.1 encoded byte arrays and a hierarchy of ASN.1 objects.
 *
 * This class is a utility for handling Abstract Syntax Notation One (ASN.1) data,
 * which is commonly used in telecommunication and computer networking, and is a
 * key part of the DLMS/COSEM standard, particularly for security features involving
 * certificates (x.509) and public key infrastructure (PKCS).
 */
class CGXAsn1Converter {
private:
    friend class CGXPkcs8;

    /**
     * @brief Recursively parses a byte buffer to extract ASN.1 objects.
     * @param bb The byte buffer containing the ASN.1 data.
     * @param objects A list to which the parsed ASN.1 objects are added.
     * @param getNext A flag to control recursive parsing.
     * @return 0 on success, or an error code.
     */
    static int GetValue(CGXByteBuffer &bb, std::vector<CGXAsn1Base *> *objects, bool getNext);

    /**
     * @brief Parses a UTCTime string from ASN.1 data.
     * @param dateString The string representation of the UTCTime.
     * @return A CGXDateTime object.
     */
    static CGXDateTime GetUtcTime(std::string &dateString);

    /**
     * @brief Parses a GeneralizedTime string from ASN.1 data.
     * @param dateString The string representation of the GeneralizedTime.
     * @return A CGXDateTime object.
     */
    static CGXDateTime GetGeneralizedTime(std::string &dateString);

    /**
     * @brief Converts an integer to a string with a minimum number of digits (zero-padded).
     * @param value The integer value.
     * @param numbers The minimum number of digits.
     * @return The formatted string.
     */
    static std::string ToString(int value, int numbers);

    /**
     * @brief Converts a CGXDateTime object to an ASN.1 date string representation.
     * @param date The date object.
     * @return The formatted date string.
     */
    static std::string DateToString(CGXDateTime &date);

    /**
     * @brief Serializes an ASN.1 object into a byte buffer.
     * @param bb The byte buffer where the serialized data is appended.
     * @param target The ASN.1 object to serialize.
     * @param[out] count The size of the serialized object.
     * @return 0 on success, or an error code.
     */
    static int GetBytes(CGXByteBuffer &bb, CGXAsn1Base *target, int &count);

    /**
     * @brief Determines the PKCS (Public-Key Cryptography Standards) type from a byte array.
     * @param data The byte buffer containing the certificate or key data.
     * @param seq The parsed ASN.1 sequence from the data.
     * @return The identified DLMS_PKCS_TYPE.
     */
    static DLMS_PKCS_TYPE GetCertificateType(CGXByteBuffer &data, CGXAsn1Sequence *seq);

public:
    /**
     * @brief Default constructor is private because this is a static utility class.
     */
    CGXAsn1Converter();

    /**
     * @brief Encodes a subject string (e.g., from a certificate) into an ASN.1 sequence.
     * @param value The subject string to encode.
     * @param[out] list The ASN.1 sequence that will contain the encoded subject.
     * @return 0 on success, or an error code.
     */
    static int EncodeSubject(std::string &value, CGXAsn1Sequence *list);

    /**
     * @brief Extracts a subject string from an ASN.1 sequence.
     * @param values The ASN.1 sequence containing the subject.
     * @param[out] value The extracted subject string.
     * @return 0 on success, or an error code.
     */
    static int GetSubject(CGXAsn1Sequence *values, std::string &value);

    /**
     * @brief Deserializes a byte array into an ASN.1 object hierarchy.
     * @param data The byte buffer containing the ASN.1 data.
     * @param[out] value A pointer to the resulting base ASN.1 object.
     * @return 0 on success, or an error code.
     */
    static int FromByteArray(CGXByteBuffer &data, CGXAsn1Base *&value);

    /**
     * @brief Parses the next ASN.1 value from a byte buffer.
     * @param data The byte buffer to parse from.
     * @param[out] value The parsed value as a CGXDLMSVariant.
     * @return 0 on success, or an error code.
     */
    static int GetNext(CGXByteBuffer &data, CGXDLMSVariant &value);

    /**
     * @brief Serializes an ASN.1 object hierarchy into a byte array.
     * @param objects The base ASN.1 object to serialize.
     * @param[out] value The byte buffer where the serialized data will be stored.
     * @return 0 on success, or an error code.
     */
    static int ToByteArray(CGXAsn1Base *objects, CGXByteBuffer &value);

    /**
     * @brief Converts a DLMS/COSEM system title into a certificate subject string.
     * @param systemTitle The system title as a byte buffer.
     * @return The formatted subject string.
     */
    static std::string SystemTitleToSubject(CGXByteBuffer &systemTitle);

    /**
     * @brief Extracts a system title from a certificate subject string.
     * @param subject The subject string.
     * @param[out] value The extracted system title as a byte buffer.
     * @return 0 on success, or an error code.
     */
    static int SystemTitleFromSubject(std::string &subject, CGXByteBuffer &value);

    /**
     * @brief Extracts a system title from a subject string as a hex string.
     * @param subject The subject string.
     * @param[out] value The extracted system title as a hexadecimal string.
     * @return 0 on success, or an error code.
     */
    static int HexSystemTitleFromSubject(std::string &subject, std::string &value);

    /**
     * @brief Converts an ASN.1 certificate type to a DLMS key usage enumeration.
     * @param type The DLMS_CERTIFICATE_TYPE.
     * @return The corresponding DLMS_KEY_USAGE.
     */
    static DLMS_KEY_USAGE CertificateTypeToKeyUsage(DLMS_CERTIFICATE_TYPE type);

    /**
     * @brief Determines the PKCS type of a certificate from its byte array representation.
     * @param data The byte buffer containing the certificate data.
     * @return The DLMS_PKCS_TYPE enumeration.
     */
    static DLMS_PKCS_TYPE GetCertificateType(CGXByteBuffer &data);

    /**
     * @brief Determines the PKCS type of a certificate from its DER-encoded string.
     * @param der The DER-encoded string.
     * @return The DLMS_PKCS_TYPE enumeration.
     */
    static DLMS_PKCS_TYPE GetCertificateType(std::string &der);
};

#endif  //GXASN1CONVERTER_H
