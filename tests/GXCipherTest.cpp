#include <gtest/gtest.h>

#include "../development/include/GXCipher.h"

namespace {

TEST(CGXCipherTest, DecryptReturnsInvalidTagWhenAuthenticationTagCorrupted) {
	const unsigned char kSystemTitle[8] = {0x4C, 0x47, 0x58, 0x5F, 0x54, 0x49, 0x54, 0x4C};

	CGXByteBuffer systemTitle;
	ASSERT_EQ(0, systemTitle.Set(kSystemTitle, sizeof(kSystemTitle)));

	CGXCipher cipher(systemTitle);
	CGXByteBuffer &blockKey = cipher.GetBlockCipherKey();

	const unsigned char kPlaintext[] = {0x01, 0x02, 0x03, 0x04};
	CGXByteBuffer encrypted;
	ASSERT_EQ(0, encrypted.Set(kPlaintext, sizeof(kPlaintext)));

	const unsigned long frameCounter = 1;
	ASSERT_EQ(
	    0, cipher.Encrypt(DLMS_SECURITY_SUITE_V0, DLMS_SECURITY_AUTHENTICATION, DLMS_COUNT_TYPE_DATA, frameCounter, 0, systemTitle, blockKey, encrypted, true)
	);

	CGXByteBuffer tampered = encrypted;
	ASSERT_GT(tampered.GetSize(), 0u);
	ASSERT_NE(nullptr, tampered.GetData());
	tampered.GetData()[tampered.GetSize() - 1] ^= 0xFF;

	EXPECT_EQ(
	    DLMS_ERROR_CODE_INVALID_TAG,
	    cipher.Encrypt(DLMS_SECURITY_SUITE_V0, DLMS_SECURITY_AUTHENTICATION, DLMS_COUNT_TYPE_DATA, frameCounter, 0, systemTitle, blockKey, tampered, false)
	);
}

}  // namespace
