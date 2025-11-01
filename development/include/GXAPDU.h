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

#ifndef GXAPDU_H
#define GXAPDU_H

#include <vector>
#include "enums.h"
#include "errorcodes.h"
#include "GXHelpers.h"
#include "GXDLMSSettings.h"
#include "GXDLMSTranslatorStructure.h"

/**
 * @brief Handles the creation and parsing of DLMS/COSEM Application Protocol Data Units (APDUs).
 *
 * This class provides static methods to manage the services of the DLMS/COSEM
 * Application layer. It is responsible for generating and parsing messages like
 * AARQ (Application Association Request), AARE (Application Association Response),
 * and User Information fields, which carry the actual service requests and responses.
 * In DLMS/COSEM, the meter is typically a server, and the controlling system is a client.
 * This class supports both roles.
 */
class CGXAPDU {
    friend class CGXDLMSTranslator;

private:
    /**
     * @brief Default constructor is private because this is a static utility class.
     */
    CGXAPDU() {
    }

    /**
     * @brief Internal helper to parse the core PDU structure.
     * @param settings DLMS settings object containing connection parameters.
     * @param cipher The ciphering object for handling encryption/decryption, if applicable.
     * @param buff The byte buffer containing the received PDU data to be parsed.
     * @param[out] result The result of the association attempt.
     * @param[out] diagnostic Additional diagnostic information from the source.
     * @param xml A translator structure for logging or converting the PDU to XML format.
     * @return 0 on success, or an error code.
     */
    static int ParsePDU2(
        CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &buff, DLMS_ASSOCIATION_RESULT &result,
        DLMS_SOURCE_DIAGNOSTIC &diagnostic
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        ,
        CGXDLMSTranslatorStructure *xml
#endif  //DLMS_IGNORE_XML_TRANSLATOR
    );

    /**
     * @brief Internal helper to parse different components of the APDU.
     * @param initiateRequest A boolean indicating if this is an initiate-request PDU.
     * @param settings DLMS settings object.
     * @param cipher The ciphering object.
     * @param data The byte buffer containing the data to be parsed.
     * @param xml A translator structure for XML logging.
     * @param tag The specific APDU tag to parse.
     * @return 0 on success, or an error code.
     */
    static int Parse(
        bool initiateRequest, CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &data,
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        CGXDLMSTranslatorStructure *xml,
#endif  //DLMS_IGNORE_XML_TRANSLATOR
        unsigned char tag
    );

    /**
    * @brief Generates the ASN.1 encoded application context name.
    * @param settings DLMS settings containing the application context to be encoded.
    * @param[out] data The byte buffer where the encoded data will be saved.
    * @param cipher The ciphering object, used to determine security context.
    * @return 0 on success, or an error code.
    */
    static int GenerateApplicationContextName(CGXDLMSSettings &settings, CGXByteBuffer &data, CGXCipher *cipher);

public:
    /**
     * @brief Parses the User Information field from a received APDU.
     * @param settings DLMS settings object.
     * @param cipher The ciphering object for decryption, if required.
     * @param data The byte buffer containing the User Information field.
     * @param xml A translator structure for XML logging.
     * @return 0 on success, or an error code.
     */
    static int ParseUserInformation(
        CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &data
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        ,
        CGXDLMSTranslatorStructure *xml
#endif  //DLMS_IGNORE_XML_TRANSLATOR
    );

    /**
     * @brief Generates a complete Application Association Request (AARQ) APDU.
     * @param settings DLMS settings to configure the AARQ.
     * @param cipher The ciphering object for encryption, if required.
     * @param encryptedData A buffer to hold any encrypted portions of the request.
     * @param[out] data The byte buffer where the complete generated AARQ is stored.
     * @return 0 on success, or an error code.
     */
    static int
    GenerateAarq(CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer *encryptedData, CGXByteBuffer &data);

    /**
    * @brief Generates the User Information field for an APDU.
    * @param settings DLMS settings.
    * @param cipher The ciphering object for encryption.
    * @param encryptedData A buffer for any encrypted data.
    * @param[out] data The byte buffer where the generated User Information is stored.
    * @return 0 on success, or an error code.
    */
    static int GenerateUserInformation(
        CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer *encryptedData, CGXByteBuffer &data
    );

    /**
     * @brief Parses a complete Application Protocol Data Unit (APDU).
     * @param settings DLMS settings object.
     * @param cipher The ciphering object for decryption.
     * @param buff The byte buffer containing the APDU to be parsed.
     * @param[out] result The result of the association.
     * @param[out] diagnostic Additional diagnostic information.
     * @param xml A translator structure for XML logging.
     * @return 0 on success, or an error code.
     */
    static int ParsePDU(
        CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &buff, DLMS_ASSOCIATION_RESULT &result,
        DLMS_SOURCE_DIAGNOSTIC &diagnostic
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        ,
        CGXDLMSTranslatorStructure *xml
#endif  //DLMS_IGNORE_XML_TRANSLATOR
    );

    /**
     * @brief Generates a complete Application Association Response (AARE) APDU from a server.
     * @param settings DLMS settings to configure the AARE.
     * @param[out] data The byte buffer where the generated AARE is stored.
     * @param result The association result to be included in the response.
     * @param diagnostic The diagnostic code to be included.
     * @param cipher The ciphering object for encryption.
     * @param errorData A buffer containing any specific error data.
     * @param encryptedData A buffer for any encrypted portions of the response.
     * @return 0 on success, or an error code.
     */
    static int GenerateAARE(
        CGXDLMSSettings &settings, CGXByteBuffer &data, DLMS_ASSOCIATION_RESULT result,
        DLMS_SOURCE_DIAGNOSTIC diagnostic, CGXCipher *cipher, CGXByteBuffer *errorData, CGXByteBuffer *encryptedData
    );

    /**
     * @brief Retrieves the User Information field from an APDU.
     * @param settings DLMS settings.
     * @param cipher The ciphering object.
     * @param[out] data The byte buffer where the User Information will be stored.
     * @return 0 on success, or an error code.
     */
    static int GetUserInformation(CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &data);

    /**
     * @brief Parses an initiate-request or initiate-response APDU component.
     * @param initiateRequest True if parsing an initiate-request, false for an initiate-response.
     * @param settings DLMS settings object.
     * @param cipher The ciphering object.
     * @param data The byte buffer containing the data to parse.
     * @param xml A translator structure for XML logging.
     * @return 0 on success, or an error code.
     */
    static int ParseInitiate(
        bool initiateRequest, CGXDLMSSettings &settings, CGXCipher *cipher, CGXByteBuffer &data
#ifndef DLMS_IGNORE_XML_TRANSLATOR
        ,
        CGXDLMSTranslatorStructure *xml
#endif  //DLMS_IGNORE_XML_TRANSLATOR
    );
};

#endif  //GXAPDU_H