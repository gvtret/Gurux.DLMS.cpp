#include <gtest/gtest.h>

#include "../development/include/GXAPDU.h"

// Regression test for handling missing cipher configurations when user ID is set.
TEST(CGXAPDUTest, GenerateAarqWithoutCipherDoesNotCrash) {
	CGXDLMSSettings settings(false);
	settings.SetUserID(1);
	settings.SetCipher(nullptr);

	CGXByteBuffer data;
	int ret = CGXAPDU::GenerateAarq(settings, nullptr, nullptr, data);

	EXPECT_TRUE(ret == 0 || ret == DLMS_ERROR_CODE_INVALID_PARAMETER);
}
