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

#ifndef GXASN1OBJECTIDENTIFIER_H
#define GXASN1OBJECTIDENTIFIER_H

#include <string>
#include "GXHelpers.h"
#include "GXBytebuffer.h"
#include "GXDLMSConverter.h"

/**
 * @brief Represents an ASN.1 Object Identifier (OID).
 *
 * An OID is a globally unique identifier, represented as a sequence of numbers,
 * used to name an object. This class provides methods to handle OIDs, including
 * converting them to and from their byte-encoded and string (dotted) representations.
 */
class CGXAsn1ObjectIdentifier: public CGXAsn1Base {
private:
    /**
     * @brief The string representation of the OID in dotted format (e.g., "1.2.840.113549").
     */
    std::string m_ObjectIdentifier;

public:
    /**
     * @brief Gets the OID as a string in dotted format.
     * @return A reference to the internal OID string.
     */
    std::string &GetObjectIdentifier() {
        return m_ObjectIdentifier;
    }

    /**
     * @brief Sets the OID from a string in dotted format.
     * @param value The new OID string.
     */
    void SetObjectIdentifier(std::string &value) {
        m_ObjectIdentifier = value;
    }

    /**
     * @brief Default constructor. Initializes an empty OID.
     */
    CGXAsn1ObjectIdentifier() {
    }

    /**
     * @brief Constructor that initializes from a string.
     * @param oid The OID in dotted format.
     */
    CGXAsn1ObjectIdentifier(std::string &oid) {
        m_ObjectIdentifier = oid;
    }

    /**
     * @brief Constructor that initializes from a C-style string.
     * @param oid The OID in dotted format.
     */
    CGXAsn1ObjectIdentifier(const char *oid) {
        m_ObjectIdentifier = oid;
    }

    /**
     * @brief Constructor that initializes from a byte buffer.
     * @param bb The byte buffer containing the encoded OID.
     * @param count The number of bytes to read from the buffer.
     */
    CGXAsn1ObjectIdentifier(CGXByteBuffer &bb, int count) {
        m_ObjectIdentifier = OidStringFromBytes(bb, count);
    }

    /**
     * @brief Converts a byte-encoded OID to its string (dotted) representation.
     * @param bb The byte buffer containing the encoded OID.
     * @param len The length of the encoded OID in the buffer.
     * @return The string representation of the OID.
     */
    static std::string OidStringFromBytes(CGXByteBuffer &bb, int len) {
        unsigned char ch;
        int value = 0;
        std::string sb;
        if (len != 0) {
            // Get first byte.
            bb.GetUInt8(&ch);
            sb += '0' + (ch / 40);
            sb += '.';
            sb += '0' + ch % 40;
            for (int pos = 1; pos != len; ++pos) {
                bb.GetUInt8(&ch);
                if ((ch & 0x80) != 0) {
                    value += (ch & 0x7F);
                    value <<= 7;
                } else {
                    value += ch;
                    sb += '.';
                    sb += GXHelpers::IntToString(value);
                    value = 0;
                }
            }
        }
        return sb;
    }

    /**
     * @brief Converts an OID string (dotted format) to its byte-encoded representation.
     * @param oid The OID string to convert.
     * @param[out] value The byte buffer where the encoded OID will be stored.
     * @return 0 on success, or an error code.
     */
    static int OidStringtoBytes(std::string &oid, CGXByteBuffer &value) {
        int ret;
        std::vector<std::string> arr = GXHelpers::Split(oid, ".", true);
        // Make first byte.
        uint64_t v = atol(arr.at(0).c_str()) * 40;
        v += atol(arr.at(1).c_str());
        if ((ret = value.SetUInt8((unsigned char)(v))) == 0) {
            for (size_t pos = 2; pos != arr.size(); ++pos) {
                v = atol(arr.at(pos).c_str());
                if (v < 0x80) {
                    ret = value.SetUInt8((unsigned char)(v));
                } else if (v < 0x4000) {
                    if ((ret = value.SetUInt8((unsigned char)(0x80 | (v >> 7)))) == 0) {
                        ret = value.SetUInt8((unsigned char)(v & 0x7F));
                    }
                } else if (v < 0x200000) {
                    value.SetUInt8((unsigned char)(0x80 | (v >> 14)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 7)));
                    ret = value.SetUInt8((unsigned char)(v & 0x7F));
                } else if (v < 0x10000000) {
                    value.SetUInt8((unsigned char)(0x80 | (v >> 21)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 14)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 7)));
                    ret = value.SetUInt8((unsigned char)(v & 0x7F));
                } else if (v < 0x800000000L) {
                    value.SetUInt8((unsigned char)(0x80 | (v >> 49)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 42)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 35)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 28)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 21)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 14)));
                    value.SetUInt8((unsigned char)(0x80 | (v >> 7)));
                    ret = value.SetUInt8(v & 0x7F);
                } else {
                    ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if (ret != 0) {
                    break;
                }
            }
        }
        return ret;
    }

    /**
     * @brief Converts the OID to its string representation.
     * @return The OID string in dotted format.
     */
    std::string ToString() {
        return m_ObjectIdentifier;
    }

    /**
     * @brief Gets the byte-encoded representation of the OID.
     * @param[out] value The byte buffer where the encoded OID will be stored.
     * @return 0 on success, or an error code.
     */
    int GetEncoded(CGXByteBuffer &value) {
        return OidStringtoBytes(m_ObjectIdentifier, value);
    }

    /**
     * @brief Gets a human-readable description for a known OID.
     * @return A C-style string describing the OID, or NULL if the OID is not recognized.
     */
    const char *GetDescription() {
        const char *id = GetObjectIdentifier().c_str();
        {
            DLMS_X509_NAME tmp = CGXDLMSConverter::ValueOfx509Name(id);
            if (tmp != DLMS_X509_NAME_NONE) {
                return CGXDLMSConverter::ToString(tmp);
            }
        }
        {
            DLMS_HASH_ALGORITHM tmp = CGXDLMSConverter::ValueOfHashAlgorithm(id);
            if (tmp != DLMS_HASH_ALGORITHM_NONE) {
                return CGXDLMSConverter::ToString(tmp);
            }
        }
        {
            DLMS_X9_OBJECT_IDENTIFIER tmp = CGXDLMSConverter::ValueOfX9Identifier(id);
            if (tmp != DLMS_X9_OBJECT_IDENTIFIER_NONE) {
                return CGXDLMSConverter::ToString(tmp);
            }
        }
        {
            DLMS_PKCS_OBJECT_IDENTIFIER tmp = CGXDLMSConverter::ValueOfPKCSObjectIdentifier(id);
            if (tmp != DLMS_PKCS_OBJECT_IDENTIFIER_NONE) {
                return CGXDLMSConverter::ToString(tmp);
            }
        }
        {
            DLMS_X509_CERTIFICATE_TYPE tmp = CGXDLMSConverter::ValueOfSourceDiagnosticX509CertificateType(id);
            if (tmp != DLMS_X509_CERTIFICATE_TYPE_NONE) {
                return CGXDLMSConverter::ToString(tmp);
            }
        }
        return NULL;
    }
};

#endif  //GXASN1OBJECTIDENTIFIER_H
