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

#ifndef GXCIPHER_H
#define GXCIPHER_H

#include "GXBytebuffer.h"
#include "GXPrivateKey.h"
#include "GXPublicKey.h"
#include "GXx509Certificate.h"

/**
 * @brief Handles cryptographic operations for DLMS/COSEM communication.
 *
 * This class provides methods for encryption, decryption, and authentication of
 * APDUs (Application Protocol Data Units) according to the DLMS/COSEM security
 * suites. It manages security contexts, keys, and frame counters.
 */
class CGXCipher {
private:
    /** @brief The active security policy. */
    DLMS_SECURITY m_Security;
    /** @brief The system title of the local device. */
    CGXByteBuffer m_SystemTitle;
    /** @brief A flag indicating whether data should be encrypted. */
    bool m_Encrypt;
    /** @brief The block cipher key (KEK). */
    CGXByteBuffer m_BlockCipherKey;
    /** @brief The authentication key (AK). */
    CGXByteBuffer m_AuthenticationKey;
    /** @brief The dedicated key used for a specific client. */
    CGXByteBuffer m_DedicatedKey;
    /** @brief The frame counter (invocation counter). */
    unsigned long m_FrameCounter;
    /** @brief The active security suite (e.g., AES-GCM-128). */
    DLMS_SECURITY_SUITE m_SecuritySuite;
    /** @brief The key pair for key agreement protocols. */
    std::pair<CGXPublicKey, CGXPrivateKey> m_KeyAgreementKeyPair;
    /** @brief The key pair for digital signatures. */
    std::pair<CGXPublicKey, CGXPrivateKey> m_SigningKeyPair;
    /** @brief A collection of available X.509 certificates. */
    std::vector<CGXx509Certificate> m_Certificates;

    void Init(unsigned char *systemTitle, unsigned char count);
    static int Int(uint32_t *rk, const unsigned char *cipherKey, unsigned short keyBits);
    static void Xor(unsigned char *dst, const unsigned char *src);
    static void shift_right_block(unsigned char *v);
    static void MultiplyH(const unsigned char *x, const unsigned char *y, unsigned char *z);
    static void GetGHash(const unsigned char *h, const unsigned char *x, int xlen, unsigned char *y);
    static void Init_j0(const unsigned char *iv, unsigned char len, const unsigned char *H, unsigned char *J0);
    static void Inc32(unsigned char *block);
    static void Gctr(unsigned int *aes, const unsigned char *icb, unsigned char *in, int len, unsigned char *out);
    static void AesGcmGctr(unsigned int *aes, const unsigned char *J0, unsigned char *in, int len, unsigned char *out);
    static void AesGcmGhash(
        const unsigned char *H, const unsigned char *aad, int aad_len, const unsigned char *crypt, int crypt_len,
        unsigned char *S
    );
    static void AesEncrypt(const unsigned int *rk, unsigned int Nr, const unsigned char *pt, unsigned char *ct);

public:
    /**
     * @brief Constructor.
     * @param systemTitle The system title of the device.
     */
    CGXCipher(CGXByteBuffer &systemTitle);
    /**
     * @brief Constructor.
     * @param systemTitle The system title of the device as a C-string.
     */
    CGXCipher(const char *systemTitle);
    /**
     * @brief Constructor.
     * @param systemTitle A pointer to the system title byte array.
     * @param count The length of the system title.
     */
    CGXCipher(unsigned char *systemTitle, unsigned char count);
    /**
     * @brief Destructor.
     */
    ~CGXCipher();

    /**
     * @brief Encrypts or authenticates an APDU.
     * @param suite The security suite to use.
     * @param security The security policy (encryption, authentication, or both).
     * @param type The type of frame counter.
     * @param frameCounter The current frame counter value.
     * @param tag The APDU tag.
     * @param systemTitle The source system title.
     * @param key The encryption/authentication key.
     * @param input The plaintext data to process.
     * @param encrypt A flag to perform encryption (true) or just authentication (false).
     * @return 0 on success, or an error code.
     */
    int Encrypt(
        DLMS_SECURITY_SUITE suite, DLMS_SECURITY security, DLMS_COUNT_TYPE type, unsigned long frameCounter,
        unsigned char tag, CGXByteBuffer &systemTitle, CGXByteBuffer &key, CGXByteBuffer &input, bool encrypt
    );

    /**
     * @brief Decrypts or verifies an APDU.
     * @param title The source system title.
     * @param key The decryption/authentication key.
     * @param data The ciphertext data to process.
     * @param[out] security The security policy that was applied.
     * @param[out] suite The security suite that was used.
     * @param[out] InvocationCounter The frame counter from the message.
     * @return 0 on success, or an error code.
     */
    int Decrypt(
        CGXByteBuffer &title, CGXByteBuffer &key, CGXByteBuffer &data, DLMS_SECURITY &security,
        DLMS_SECURITY_SUITE &suite, uint64_t &InvocationCounter
    );

    /**
     * @brief Encrypts data using AES-128 ECB.
     * @param data The data to encrypt (in-place).
     * @param offset The offset within the data to start encryption.
     * @param secret The 128-bit secret key.
     * @return 0 on success, or an error code.
     */
    static int Aes1Encrypt(CGXByteBuffer &data, unsigned short offset, CGXByteBuffer &secret);

    /**
     * @brief Decrypts data using AES-128 ECB.
     * @param data The data to decrypt (in-place).
     * @param secret The 128-bit secret key.
     * @return 0 on success, or an error code.
     */
    static int Aes1Decrypt(CGXByteBuffer &data, CGXByteBuffer &secret);

    /** @brief Checks if ciphering (encryption) is active. @return True if active. */
    bool IsCiphered();
    /** @brief Gets the current security policy. @return The DLMS_SECURITY value. */
    DLMS_SECURITY GetSecurity();
    /** @brief Sets the security policy. @param value The new security policy. */
    void SetSecurity(DLMS_SECURITY value);

    /** @brief Gets the current security suite. @return The DLMS_SECURITY_SUITE value. */
    DLMS_SECURITY_SUITE GetSecuritySuite();
    /** @brief Sets the security suite. @param value The new security suite. */
    void SetSecuritySuite(DLMS_SECURITY_SUITE value);

    /** @brief Gets the system title. @return A reference to the system title buffer. */
    CGXByteBuffer &GetSystemTitle();
    /** @brief Sets the system title. @param value The new system title. @return 0 on success. */
    int SetSystemTitle(CGXByteBuffer &value);

    /** @brief Gets the block cipher key. @return A reference to the key buffer. */
    CGXByteBuffer &GetBlockCipherKey();
    /** @brief Sets the block cipher key. @param value The new key. @return 0 on success. */
    int SetBlockCipherKey(CGXByteBuffer &value);

    /** @brief Gets the authentication key. @return A reference to the key buffer. */
    CGXByteBuffer &GetAuthenticationKey();
    /** @brief Sets the authentication key. @param value The new key. @return 0 on success. */
    int SetAuthenticationKey(CGXByteBuffer &value);

    /** @brief Gets the frame counter. @return The frame counter value. */
    unsigned long GetFrameCounter();
    /** @brief Sets the frame counter. @param value The new value. */
    void SetFrameCounter(unsigned long value);

    /** @brief Gets the invocation counter (alias for frame counter). @return The invocation counter value. */
    unsigned long GetInvocationCounter();
    /** @brief Sets the invocation counter (alias for frame counter). @param value The new value. */
    void SetInvocationCounter(unsigned long value);

    /** @brief Resets the ciphering state, including the frame counter. */
    void Reset();

    /** @brief Gets the dedicated key. @return A reference to the key buffer. */
    CGXByteBuffer &GetDedicatedKey();
    /** @brief Sets the dedicated key. @param value The new key. */
    void SetDedicatedKey(CGXByteBuffer &value);

    /** @brief Gets the key agreement key pair. @return A reference to the key pair. */
    std::pair<CGXPublicKey, CGXPrivateKey> &GetKeyAgreementKeyPair();
    /** @brief Sets the key agreement key pair. @param value The new key pair. */
    void SetKeyAgreementKeyPair(std::pair<CGXPublicKey, CGXPrivateKey> &value);

    /** @brief Gets the signing key pair. @return A reference to the key pair. */
    std::pair<CGXPublicKey, CGXPrivateKey> &GetSigningKeyPair();
    /** @brief Sets the signing key pair. @param value The new key pair. */
    void SetSigningKeyPair(std::pair<CGXPublicKey, CGXPrivateKey> &value);

    /** @brief Gets the list of available certificates. @return A reference to the certificate vector. */
    std::vector<CGXx509Certificate> &GetCertificates();
    /** @brief Sets the list of available certificates. @param value The new certificate vector. */
    void SetCertificates(std::vector<CGXx509Certificate> &value);
};
#endif  //GXCIPHER_H
