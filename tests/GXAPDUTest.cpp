#include <algorithm>
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

// Verify that GenerateAARE encodes lengths larger than 255 bytes correctly.
TEST(CGXAPDUTest, GenerateAareEncodesExtendedLengths) {
    CGXDLMSSettings settings(true);
    settings.SetUserID(-1);

    CGXByteBuffer errorData;
    for (int i = 0; i < 300; ++i) {
        errorData.SetUInt8(static_cast<uint8_t>(i));
    }

    CGXByteBuffer apdu;
    int ret = CGXAPDU::GenerateAARE(settings, apdu, DLMS_ASSOCIATION_RESULT_ACCEPTED, DLMS_SOURCE_DIAGNOSTIC_NONE, nullptr, &errorData, nullptr);

    ASSERT_EQ(0, ret);
    ASSERT_GE(apdu.GetSize(), static_cast<uint32_t>(300));

    const uint8_t *data = apdu.GetData();
    ASSERT_NE(nullptr, data);
    ASSERT_GE(apdu.GetSize(), static_cast<uint32_t>(4));

    EXPECT_EQ(static_cast<uint8_t>(BER_TYPE_APPLICATION | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME), data[0]);

    uint8_t lengthDescriptor = data[1];
    ASSERT_NE(0u, lengthDescriptor & 0x80u);
    size_t lengthBytes = lengthDescriptor & 0x7Fu;
    ASSERT_EQ(2u, lengthBytes);
    ASSERT_GE(apdu.GetSize(), static_cast<uint32_t>(2 + lengthBytes));

    size_t bodyLength = 0;
    for (size_t i = 0; i < lengthBytes; ++i) {
        bodyLength = (bodyLength << 8) | data[2 + i];
    }
    EXPECT_EQ(apdu.GetSize(), static_cast<uint32_t>(1 + 1 + lengthBytes + bodyLength));

    size_t bodyOffset = 2 + lengthBytes;
    size_t userInfoOffset = apdu.GetSize();
    for (size_t i = bodyOffset; i < apdu.GetSize(); ++i) {
        if (data[i] == static_cast<uint8_t>(BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION)) {
            userInfoOffset = i;
            break;
        }
    }
    ASSERT_LT(userInfoOffset, static_cast<size_t>(apdu.GetSize()));

    uint8_t userInfoLengthDescriptor = data[userInfoOffset + 1];
    ASSERT_NE(0u, userInfoLengthDescriptor & 0x80u);
    size_t userInfoLengthBytes = userInfoLengthDescriptor & 0x7Fu;
    ASSERT_EQ(2u, userInfoLengthBytes);

    size_t userInfoLength = 0;
    for (size_t i = 0; i < userInfoLengthBytes; ++i) {
        userInfoLength = (userInfoLength << 8) | data[userInfoOffset + 2 + i];
    }
    EXPECT_EQ(userInfoLength, static_cast<size_t>(2 + errorData.GetSize()));

    size_t octetStringOffset = userInfoOffset + 2 + userInfoLengthBytes;
    ASSERT_LT(octetStringOffset + 1, static_cast<size_t>(apdu.GetSize()));
    EXPECT_EQ(static_cast<uint8_t>(BER_TYPE_OCTET_STRING), data[octetStringOffset]);

    uint8_t errorLengthDescriptor = data[octetStringOffset + 1];
    ASSERT_NE(0u, errorLengthDescriptor & 0x80u);
    size_t errorLengthBytes = errorLengthDescriptor & 0x7Fu;
    ASSERT_EQ(2u, errorLengthBytes);

    size_t errorLength = 0;
    for (size_t i = 0; i < errorLengthBytes; ++i) {
        errorLength = (errorLength << 8) | data[octetStringOffset + 2 + i];
    }
    EXPECT_EQ(errorLength, static_cast<size_t>(errorData.GetSize()));

    const uint8_t *errorPayload = data + octetStringOffset + 2 + errorLengthBytes;
    ASSERT_LE(octetStringOffset + 2 + errorLengthBytes + errorLength, static_cast<size_t>(apdu.GetSize()));
    const uint8_t *expectedPayload = errorData.GetData();
    EXPECT_TRUE(std::equal(expectedPayload, expectedPayload + errorData.GetSize(), errorPayload));
}
