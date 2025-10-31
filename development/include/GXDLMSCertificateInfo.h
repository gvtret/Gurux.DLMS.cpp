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

#ifndef GXDLMSCERTIFICATEINFO_H
#define GXDLMSCERTIFICATEINFO_H

#include <string>
#include "enums.h"
#include "GXBigInteger.h"

/**
 * Represents information about a DLMS/COSEM certificate.
*/
class CGXDLMSCertificateInfo {
private:
    friend class CGXDLMSSecuritySetup;
    /**
 * Used certificate entity.
 */
    DLMS_CERTIFICATE_ENTITY m_Entity;

    /**
     * Used certificate type.
     */
    DLMS_CERTIFICATE_TYPE m_Type;

    /**
     * Certificate serial number.
     */
    CGXBigInteger m_SerialNumber;

    /**
     * Certificate issuer.
     */
    std::string m_Issuer;

    /**
    * Certificate issuer in ASN1 format.
    */
    CGXByteBuffer m_IssuerRaw;

    /**
     * Certificate subject.
     */
    std::string m_Subject;

    /**
     * Certificate subject alt name.
     */
    std::string m_SubjectAltName;

public:
    //Constructor.
    CGXDLMSCertificateInfo();

    /**
     * Used certificate entity.
     */
    DLMS_CERTIFICATE_ENTITY GetEntity();
    /**
     * Used certificate entity.
     */
    void SetEntity(DLMS_CERTIFICATE_ENTITY value);

    /**
     * Used certificate type.
     */
    DLMS_CERTIFICATE_TYPE GetType();

    /**
     * Used certificate type.
     */
    void SetType(DLMS_CERTIFICATE_TYPE value);

    /**
     * @return Certificate serial number.
     */
    const CGXBigInteger& GetSerialNumber() const;

    /**
     *  Certificate serial number.
     */
    void SetSerialNumber(const CGXBigInteger& value);

    /**
     * Certificate issuer.
     */
    const std::string& GetIssuer() const;

    /**
     * Certificate issuer.
     */
    void SetIssuer(const std::string& value);

    /**
    * Certificate issuer in ASN1 format.
    */
    const CGXByteBuffer& GetIssuerRaw() const;

    /**
     * Certificate subject.
     */
    const std::string& GetSubject() const;

    /**
     * Certificate subject.
     */
    void SetSubject(const std::string& value);

    /**
     * Certificate subject alt name.
     */
    const std::string& GetSubjectAltName() const;

    /**
     * Certificate subject alt name.
     */
    void SetSubjectAltName(const std::string& value);
};
#endif  //GXDLMSCERTIFICATEINFO_H