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

#ifndef GXDLMSSECURECLIENT_H
#define GXDLMSSECURECLIENT_H

#include "GXDLMSClient.h"

/**
 * @brief Represents a DLMS/COSEM client with ciphering capabilities.
 */
class CGXDLMSSecureClient: public CGXDLMSClient {
private:
    CGXCipher m_Cipher;

public:
    /**
     * @brief Constructor.
     * @param UseLogicalNameReferencing True to use logical name referencing, false otherwise.
     * @param ClientAddress The client's address.
     * @param ServerAddress The server's address.
     * @param authentication The authentication type.
     * @param password The password for authentication.
     * @param intefaceType The interface type.
     */
    CGXDLMSSecureClient(
        bool UseLogicalNameReferencing = true, int ClientAddress = 16, int ServerAddress = 1,
        DLMS_AUTHENTICATION authentication = DLMS_AUTHENTICATION_NONE,
        const char *password = NULL, DLMS_INTERFACE_TYPE intefaceType = DLMS_INTERFACE_TYPE_HDLC
    );

    /**
     * @brief Destructor.
     */
    ~CGXDLMSSecureClient();

    /**
     * @brief Gets the ciphering settings.
     * @return A pointer to the ciphering settings.
     */
    CGXCipher *GetCiphering();

    /**
     * @brief Encrypts data using the Key Encrypting Key (KEK).
     * @param kek The Key Encrypting Key (Master Key).
     * @param data The data to encrypt.
     * @param reply A buffer to store the encrypted data.
     * @return An error code.
     */
    static int Encrypt(CGXByteBuffer &kek, CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Decrypts data using the Key Encrypting Key (KEK).
     * @param kek The Key Encrypting Key (Master Key).
     * @param data The data to decrypt.
     * @param reply A buffer to store the decrypted data.
     * @return An error code.
     */
    static int Decrypt(CGXByteBuffer &kek, CGXByteBuffer &data, CGXByteBuffer &reply);

    /**
     * @brief Gets the client's public key certificate.
     * @return A reference to the client's certificate.
     */
    CGXx509Certificate &GetClientPublicKeyCertificate();

    /**
     * @brief Sets the client's public key certificate.
     * @param value The client's certificate to set.
     */
    void SetClientPublicKeyCertificate(CGXx509Certificate &value);

    /**
     * @brief Gets the server's public key certificate.
     * @return A reference to the server's certificate.
     */
    CGXx509Certificate &GetServerPublicKeyCertificate();

    /**
     * @brief Sets the server's public key certificate.
     * @param value The server's certificate to set.
     */
    void SetServerPublicKeyCertificate(CGXx509Certificate &value);
};
#endif  //GXDLMSSECURECLIENT_H
