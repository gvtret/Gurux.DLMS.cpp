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
#include <cstdint>

class CGXCipher
{
private:
    DLMS_SECURITY m_Security;
    /**
    * System title.
    */
    CGXByteBuffer m_SystemTitle;

    /**
    * Is data encrypted.
    */
    bool m_Encrypt;

    /**
    *  Block cipher key.
    */
    CGXByteBuffer m_BlockCipherKey;
    /**
    *  Block Authentication key.
    */
    CGXByteBuffer m_AuthenticationKey;

    // Dedicated key.
    CGXByteBuffer m_DedicatedKey;

    /**
     * Frame counter. AKA Invocation counter.
     */
    uint32_t m_FrameCounter;

    DLMS_SECURITY_SUITE m_SecuritySuite;

    std::pair<CGXPublicKey, CGXPrivateKey> m_KeyAgreementKeyPair;
    std::pair<CGXPublicKey, CGXPrivateKey> m_SigningKeyPair;
    std::vector<CGXx509Certificate> m_Certificates;

    void Init(
        unsigned char* systemTitle,
        unsigned char count);

    static int Int(uint32_t* rk,
        const unsigned char* cipherKey,
        unsigned short keyBits);

    /*
    * Make xor for 128 bits.
    */
    static void Xor(
        unsigned char* dst,
        const unsigned char* src);

    static void shift_right_block(unsigned char* v);

    static void MultiplyH(
        const unsigned char* x,
        const unsigned char* y,
        unsigned char* z);

    /*
    * Count GHash.
    */
    static void GetGHash(
        const unsigned char* h,
        const unsigned char* x,
        int xlen,
        unsigned char* y);

    static void Init_j0(
        const unsigned char* iv,
        unsigned char len,
        const unsigned char* H,
        unsigned char* J0);

    static void Inc32(unsigned char* block);

    static void Gctr(
        unsigned int* aes,
        const unsigned char* icb,
        unsigned char* in,
        int len,
        unsigned char* out);

    static void AesGcmGctr(
        unsigned int* aes,
        const unsigned char* J0,
        unsigned char* in,
        int len,
        unsigned char* out);

    static void AesGcmGhash(
        const unsigned char* H,
        const unsigned char* aad,
        int aad_len,
        const unsigned char* crypt,
        int crypt_len,
        unsigned char* S);

    static void AesEncrypt(
        const unsigned int* rk,
        unsigned int Nr,
        const unsigned char* pt,
        unsigned char* ct);
public:
    /**
    * Constructor.
    */
    CGXCipher(CGXByteBuffer& systemTitle);

    /**
    * Constructor.
    */
    CGXCipher(const char* systemTitle);

    /**
    * Constructor.
    */
    CGXCipher(
        unsigned char* systemTitle,
        unsigned char count);

    /**
    * Destructor.
    */
    ~CGXCipher();


    /**
      * Encrypt PDU.
      *
      * suite
      *            Security suite.
      * security
      *            Security.
      * tag
      *            Tag.
      * systemTitle
      *            System Title.
      * plainText
      *            Data to encrypt.
      * encrypted
      *            Encrypted data.
      */
    int Encrypt(
        DLMS_SECURITY_SUITE suite,
        DLMS_SECURITY security,
        DLMS_COUNT_TYPE type,
        uint32_t frameCounter,
        unsigned char tag,
        CGXByteBuffer& systemTitle,
        CGXByteBuffer& key,
        CGXByteBuffer& input,
        bool encrypt);

    /**
      * Decrypt data.
      *
      * systemTitle: System Title.
      * data: Decrypted data.
      * security: Used security level.
      * suite: Used security suite.
      * InvocationCounter: Invocation counter value.
      */
    int Decrypt(
        CGXByteBuffer& title,
        CGXByteBuffer& key,
        CGXByteBuffer& data,
        DLMS_SECURITY& security,
        DLMS_SECURITY_SUITE& suite,
        uint64_t& InvocationCounter);

    /*
     * Encrypt data using AES.
     *
     * data: Encrypted data.
     * offset: Data offset.
     * secret: Secret.
     */
    static int Aes1Encrypt(
        CGXByteBuffer& data,
        unsigned short offset,
        CGXByteBuffer& secret);

    /*
     * Decrypt data using AES.
     *
     * data: Encrypted data.
     * secret:  Secret.
     */
    static int Aes1Decrypt(
        CGXByteBuffer& data,
        CGXByteBuffer& secret);

    /**
     * Returns is ciphering used.
     */
    bool IsCiphered();

    /**
     * Returns used security.
     */
    DLMS_SECURITY GetSecurity();

    /**
    * value: Used security.
    */
    void SetSecurity(DLMS_SECURITY value);

    /*
    * Returns Used security suite.
    */
    DLMS_SECURITY_SUITE GetSecuritySuite();

    /*
     * value: Used security suite.
     */
    void SetSecuritySuite(DLMS_SECURITY_SUITE value);

    /**
     * Returns System title.
     */
    CGXByteBuffer& GetSystemTitle();

    /**
    *  value: System title.
    */
    int SetSystemTitle(CGXByteBuffer& value);

    /**
     * Returns Block cipher key.
     */
    CGXByteBuffer& GetBlockCipherKey();

    /**
    *  value: Block cipher key.
    */
    int SetBlockCipherKey(CGXByteBuffer& value);

    /**
     * Returns Authentication key.
     */
    CGXByteBuffer& GetAuthenticationKey();

    /**
     * value
     *            Authentication key.
     */
    int SetAuthenticationKey(CGXByteBuffer& value);

    /**
     * Returns Frame counter. AKA. Invocation counter.
     */
    uint32_t GetFrameCounter();

    void SetFrameCounter(uint32_t value);

    /**
     * Returns Invocation counter. AKA Frame counter.
     */
    uint32_t GetInvocationCounter();

    void SetInvocationCounter(uint32_t value);

    void Reset();

    /**
    * Returns Dedicated key.
    */
    CGXByteBuffer& GetDedicatedKey();

    /**
     * value
     *            Dedicated key.
     */
    void SetDedicatedKey(CGXByteBuffer& value);

    /*Get key agreement key pair.*/
    std::pair<CGXPublicKey, CGXPrivateKey>& GetKeyAgreementKeyPair();
    /*Set key agreement key pair.*/
    void SetKeyAgreementKeyPair(std::pair<CGXPublicKey, CGXPrivateKey>& value);

    /*Get signing key pair.*/
    std::pair<CGXPublicKey, CGXPrivateKey>& GetSigningKeyPair();
    /*Set signing key pair.*/
    void SetSigningKeyPair(std::pair<CGXPublicKey, CGXPrivateKey>& value);

    /*Get available certificates.*/
    std::vector<CGXx509Certificate>& GetCertificates();
    /*Set available certificates.*/
    void SetCertificates(std::vector<CGXx509Certificate>& value);
};
#endif //GXCIPHER_H
