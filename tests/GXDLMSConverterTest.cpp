#include <gtest/gtest.h>
#include "GXDLMSConverter.h"

TEST(CGXDLMSConverterTest, AuthenticationToString)
{
    ASSERT_STREQ("None", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_NONE));
    ASSERT_STREQ("Low", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_LOW));
    ASSERT_STREQ("High", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH));
    ASSERT_STREQ("HighMd5", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_MD5));
    ASSERT_STREQ("HighSha1", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_SHA1));
    ASSERT_STREQ("HighGMac", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_GMAC));
    ASSERT_STREQ("HighSha256", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_SHA256));
}

TEST(CGXDLMSConverterTest, ValueOfAuthentication)
{
    ASSERT_EQ(DLMS_AUTHENTICATION_NONE, CGXDLMSConverter::ValueOfAuthentication("None"));
    ASSERT_EQ(DLMS_AUTHENTICATION_LOW, CGXDLMSConverter::ValueOfAuthentication("Low"));
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH, CGXDLMSConverter::ValueOfAuthentication("High"));
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH_MD5, CGXDLMSConverter::ValueOfAuthentication("HighMd5"));
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH_SHA1, CGXDLMSConverter::ValueOfAuthentication("HighSha1"));
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH_GMAC, CGXDLMSConverter::ValueOfAuthentication("HighGMac"));
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH_SHA256, CGXDLMSConverter::ValueOfAuthentication("HighSha256"));
}

TEST(CGXDLMSConverterTest, ObjectTypeToString)
{
    ASSERT_STREQ("GXDLMSData", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_DATA));
    ASSERT_STREQ("GXDLMSRegister", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_REGISTER));
    ASSERT_STREQ("GXDLMSClock", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_CLOCK));
}

TEST(CGXDLMSConverterTest, ValueOfObjectType)
{
    ASSERT_EQ(DLMS_OBJECT_TYPE_DATA, CGXDLMSConverter::ValueOfObjectType("GXDLMSData"));
    ASSERT_EQ(DLMS_OBJECT_TYPE_REGISTER, CGXDLMSConverter::ValueOfObjectType("GXDLMSRegister"));
    ASSERT_EQ(DLMS_OBJECT_TYPE_CLOCK, CGXDLMSConverter::ValueOfObjectType("GXDLMSClock"));
}
