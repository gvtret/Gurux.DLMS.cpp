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

#ifndef GXCERTIFICATEREQUEST_H
#define GXCERTIFICATEREQUEST_H

#include <vector>
#include "GXAsn1Base.h"
#include "GXDLMSVariant.h"

class CGXPkcs10;

/**
 * @brief Represents a request for a digital certificate.
 *
 * This class encapsulates the information needed to request a certificate,
 * including the certificate type, the intended key usage, and the PKCS#10
 * Certificate Signing Request (CSR) itself.
 */
class CGXCertificateRequest {
private:
    friend class CGXPkcs10;
    /**
     * @brief The type of the requested certificate.
     */
    DLMS_CERTIFICATE_TYPE m_CertificateType;
    /**
     * @brief The intended purpose for which the certified public key will be used.
     */
    DLMS_EXTENDED_KEY_USAGE m_ExtendedKeyUsage;
    /**
     * @brief The Certificate Signing Request (CSR) in PKCS#10 format.
     */
    CGXPkcs10 *m_Certificate;

public:
    /**
     * @brief Default constructor.
     */
    CGXCertificateRequest() {
        m_Certificate = NULL;
        m_CertificateType = DLMS_CERTIFICATE_TYPE_DIGITAL_SIGNATURE;
        m_ExtendedKeyUsage = DLMS_EXTENDED_KEY_USAGE_NONE;
    }

    /**
     * @brief Constructor to initialize the certificate request.
     * @param certificateType The type of the certificate.
     * @param certificate A pointer to the PKCS#10 certificate signing request.
     */
    CGXCertificateRequest(DLMS_CERTIFICATE_TYPE certificateType, CGXPkcs10 *certificate) {
        m_Certificate = NULL;
        m_ExtendedKeyUsage = DLMS_EXTENDED_KEY_USAGE_NONE;
        m_Certificate = certificate;
        m_CertificateType = certificateType;
    }

    /**
     * @brief Gets the certificate type.
     * @return The DLMS_CERTIFICATE_TYPE enumeration.
     */
    DLMS_CERTIFICATE_TYPE GetCertificateType() {
        return m_CertificateType;
    }

    /**
     * @brief Sets the certificate type.
     * @param value The DLMS_CERTIFICATE_TYPE enumeration.
     */
    void SetCertificateType(DLMS_CERTIFICATE_TYPE value) {
        m_CertificateType = value;
    }

    /**
     * @brief Gets the extended key usage.
     * @return The DLMS_EXTENDED_KEY_USAGE enumeration, indicating the key's purpose.
     */
    DLMS_EXTENDED_KEY_USAGE GetExtendedKeyUsage() {
        return m_ExtendedKeyUsage;
    }

    /**
     * @brief Sets the extended key usage.
     * @param value The DLMS_EXTENDED_KEY_USAGE enumeration, indicating the key's purpose.
     */
    void SetExtendedKeyUsage(DLMS_EXTENDED_KEY_USAGE value) {
        m_ExtendedKeyUsage = value;
    }

    /**
     * @brief Gets the Certificate Signing Request (CSR).
     * @return A pointer to the CGXPkcs10 object.
     */
    CGXPkcs10 *GetCertificate() {
        return m_Certificate;
    }

    /**
     * @brief Sets the Certificate Signing Request (CSR).
     * @param value A pointer to the CGXPkcs10 object.
     */
    void SetCertificate(CGXPkcs10 *value) {
        m_Certificate = value;
    }
};

#endif  //GXCERTIFICATEREQUEST_H
