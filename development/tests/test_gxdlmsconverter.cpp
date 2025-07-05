#include "gtest/gtest.h"
#include "GXDLMSConverter.h" // Assuming this is correct relative to include dirs
#include "enums.h"           // For DLMS enum types
#include <string>

// Test fixture for CGXDLMSConverter (optional, can use TEST directly if no setup needed)
class CGXDLMSConverterTest : public ::testing::Test {
protected:
    // CGXDLMSConverter converter; // If it had non-static methods we wanted to test
                                 // Or if constructor/destructor did something important.
                                 // For now, all relevant methods seem static.
};

TEST_F(CGXDLMSConverterTest, ObjectTypeToString) {
    EXPECT_STREQ("Data", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_DATA));
    EXPECT_STREQ("Register", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_REGISTER));
    EXPECT_STREQ("ExtendedRegister", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_EXTENDED_REGISTER));
    EXPECT_STREQ("DemandRegister", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_DEMAND_REGISTER));
    EXPECT_STREQ("Clock", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_CLOCK));
    EXPECT_STREQ("ProfileGeneric", CGXDLMSConverter::ToString(DLMS_OBJECT_TYPE_PROFILE_GENERIC));
    // Add more common types if needed
    // What about an invalid type? The function returns const char*. Should return "Unknown" or similar.
    // Let's assume for now it handles known types. The return for unknown is not specified by signature alone.
}

TEST_F(CGXDLMSConverterTest, ValueOfObjectType) {
    EXPECT_EQ(DLMS_OBJECT_TYPE_DATA, CGXDLMSConverter::ValueOfObjectType("Data"));
    EXPECT_EQ(DLMS_OBJECT_TYPE_REGISTER, CGXDLMSConverter::ValueOfObjectType("Register"));
    EXPECT_EQ(DLMS_OBJECT_TYPE_CLOCK, CGXDLMSConverter::ValueOfObjectType("Clock"));
    // Test case-insensitivity or exact match if specified by requirements
    // EXPECT_EQ(DLMS_OBJECT_TYPE_PROFILE_GENERIC, CGXDLMSConverter::ValueOfObjectType("profilegeneric")); // If case-insensitive

    // Test invalid string
    // This depends on how ValueOfObjectType handles unknown strings.
    // It returns DLMS_OBJECT_TYPE, so it might return a specific "unknown" enum or a default.
    // For now, assume it might return 0 or MAX_UINT16 or similar for unknown.
    // Let's test a known failure if the behavior for unknown is defined.
    // Example: EXPECT_EQ(SOME_UNDEFINED_OBJECT_TYPE_ENUM, CGXDLMSConverter::ValueOfObjectType("NonExistentType"));
}


TEST_F(CGXDLMSConverterTest, BaudRateToString) {
    EXPECT_STREQ("BaudRate300", CGXDLMSConverter::ToString(DLMS_BAUD_RATE_300));
    EXPECT_STREQ("BaudRate600", CGXDLMSConverter::ToString(DLMS_BAUD_RATE_600));
    EXPECT_STREQ("BaudRate9600", CGXDLMSConverter::ToString(DLMS_BAUD_RATE_9600));
    EXPECT_STREQ("BaudRate115200", CGXDLMSConverter::ToString(DLMS_BAUD_RATE_115200));
    // Add other baud rates
}

TEST_F(CGXDLMSConverterTest, GetErrorMessage) {
    // These error codes are defined in errorcodes.h (which GXDLMSConverter.h might include or expect)
    // Let's assume DLMS_ERROR_CODE_OK and some other common ones.
    // The actual strings will depend on the implementation in CGXDLMSConverter.cpp
    EXPECT_STREQ("OK", CGXDLMSConverter::GetErrorMessage(DLMS_ERROR_CODE_OK));
    EXPECT_STREQ("Hardware fault", CGXDLMSConverter::GetErrorMessage(DLMS_ERROR_CODE_HARDWARE_FAULT));
    EXPECT_STREQ("Temporary failure", CGXDLMSConverter::GetErrorMessage(DLMS_ERROR_CODE_TEMPORARY_FAILURE));
    EXPECT_STREQ("Read write denied", CGXDLMSConverter::GetErrorMessage(DLMS_ERROR_CODE_READ_WRITE_DENIED));
    // Using another common runtime error code, corrected by compiler suggestion
    EXPECT_STREQ("Type unmatched", CGXDLMSConverter::GetErrorMessage(DLMS_ERROR_CODE_UNMATCH_TYPE));
    // Test an unknown error code - should return "Unknown error" or similar.
    // EXPECT_STREQ("Unknown error", CGXDLMSConverter::GetErrorMessage(9999)); // A non-existent code
}

TEST_F(CGXDLMSConverterTest, AuthenticationToStringAndValue) {
    EXPECT_STREQ("None", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_NONE));
    EXPECT_STREQ("Low", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_LOW));
    EXPECT_STREQ("High", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH));
    EXPECT_STREQ("HighMd5", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_MD5));
    EXPECT_STREQ("HighSha1", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_SHA1));
    EXPECT_STREQ("HighGmac", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_GMAC));
    EXPECT_STREQ("HighEcdsa", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_ECDSA));
    EXPECT_STREQ("HighSha256", CGXDLMSConverter::ToString(DLMS_AUTHENTICATION_HIGH_SHA256));
    // Corrected based on compiler suggestions, assuming these are the available enums
    // It's possible SHA384/512 enums are missing or named differently in this specific enums.h
    // SHA384 and SHA512 lines removed as per compiler feedback implying they aren't defined
    // and suggestions pointed to already existing tested enums.

    EXPECT_EQ(DLMS_AUTHENTICATION_NONE, CGXDLMSConverter::ValueOfAuthentication("None"));
    EXPECT_EQ(DLMS_AUTHENTICATION_LOW, CGXDLMSConverter::ValueOfAuthentication("Low"));
    EXPECT_EQ(DLMS_AUTHENTICATION_HIGH, CGXDLMSConverter::ValueOfAuthentication("High"));
    EXPECT_EQ(DLMS_AUTHENTICATION_HIGH_MD5, CGXDLMSConverter::ValueOfAuthentication("HighMd5"));
    // Test case-insensitivity for ValueOf if applicable
    // EXPECT_EQ(DLMS_AUTHENTICATION_LOW, CGXDLMSConverter::ValueOfAuthentication("low"));

    // Test invalid string for ValueOfAuthentication
    // This depends on how it handles unknown strings. It returns DLMS_AUTHENTICATION.
    // It might return DLMS_AUTHENTICATION_NONE or a specific "unknown" value.
    // EXPECT_EQ(DLMS_AUTHENTICATION_NONE, CGXDLMSConverter::ValueOfAuthentication("InvalidAuth"));
}

TEST_F(CGXDLMSConverterTest, SecurityPolicyToString) {
    EXPECT_STREQ("Nothing", CGXDLMSConverter::ToString(DLMS_SECURITY_POLICY_NOTHING));
    EXPECT_STREQ("Authenticated", CGXDLMSConverter::ToString(DLMS_SECURITY_POLICY_AUTHENTICATED));
    EXPECT_STREQ("Encrypted", CGXDLMSConverter::ToString(DLMS_SECURITY_POLICY_ENCRYPTED));
    EXPECT_STREQ("AuthenticatedEncrypted", CGXDLMSConverter::ToString(DLMS_SECURITY_POLICY_AUTHENTICATED_ENCRYPTED));

    // The version int ToString(DLMS_SECURITY_POLICY value, std::string& str)
    // can also be tested if its behavior is different or needs specific checks.
    std::string out_str;
    int ret = CGXDLMSConverter::ToString(DLMS_SECURITY_POLICY_AUTHENTICATED_ENCRYPTED, out_str);
    EXPECT_EQ(ret, 0); // Assuming 0 for success
    EXPECT_EQ("AuthenticatedEncrypted", out_str);
}

TEST_F(CGXDLMSConverterTest, AssociationStatusToString) {
    EXPECT_STREQ("NonAssociated", CGXDLMSConverter::ToString(DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED));
    EXPECT_STREQ("AssociationPending", CGXDLMSConverter::ToString(DLMS_ASSOCIATION_STATUS_ASSOCIATION_PENDING));
    EXPECT_STREQ("Associated", CGXDLMSConverter::ToString(DLMS_ASSOCIATION_STATUS_ASSOCIATED));
}

// Many other ToString methods exist in CGXDLMSConverter.
// Adding a few more as examples:
TEST_F(CGXDLMSConverterTest, ClockStatusToString) {
    // Assuming DLMS_CLOCK_STATUS is a bitfield
    EXPECT_STREQ("Ok", CGXDLMSConverter::ToString(DLMS_CLOCK_STATUS_OK)); // If 0 means OK
    // For bitfields, you might test individual bits or combinations
    // Example if DLMS_CLOCK_STATUS_INVALID_VALUE is 0x01, DLMS_CLOCK_STATUS_DOUBTFUL_VALUE is 0x02
    // EXPECT_STREQ("InvalidValue", CGXDLMSConverter::ToString(static_cast<DLMS_CLOCK_STATUS>(0x01)));
    // EXPECT_STREQ("DoubtfulValue", CGXDLMSConverter::ToString(static_cast<DLMS_CLOCK_STATUS>(0x02)));
    // EXPECT_STREQ("InvalidValue, DoubtfulValue", CGXDLMSConverter::ToString(static_cast<DLMS_CLOCK_STATUS>(0x03)));
    // The actual string representation for combined flags needs to be known.
    // The header shows `const char* ToString(DLMS_CLOCK_STATUS value);`
    // This suggests it might not return combined strings but rather the primary status.
    // This test needs to be adapted based on actual behavior of bitfield ToString.
    // For now, test a single known value.
}

TEST_F(CGXDLMSConverterTest, GetUnitAsString) {
    // Units are integer codes. Refer to Blue/Green book for common units.
    // Example: Unit for Wh is 30. Unit for V is 35.
    EXPECT_STREQ("Wh", CGXDLMSConverter::GetUnitAsString(30));
    EXPECT_STREQ("V", CGXDLMSConverter::GetUnitAsString(35));
    EXPECT_STREQ("A", CGXDLMSConverter::GetUnitAsString(33));
    EXPECT_STREQ("W", CGXDLMSConverter::GetUnitAsString(27));
    EXPECT_STREQ("", CGXDLMSConverter::GetUnitAsString(0)); // Count/None often 0 or 255
    EXPECT_STREQ("", CGXDLMSConverter::GetUnitAsString(255));
    // Test an unknown unit
    // EXPECT_STREQ("Unknown", CGXDLMSConverter::GetUnitAsString(9999));
}

// The GetDescription and UpdateOBISCodeInformation methods are more complex
// as they interact with CGXStandardObisCodeCollection and CGXDLMSObjectCollection.
// They might be better suited for integration tests or require mocking these collections.
// For now, focusing on simpler, direct conversion static methods.

// Placeholder for X509 Name to String (if needed, many such conversions)
TEST_F(CGXDLMSConverterTest, X509NameToString) {
    // Corrected based on compiler suggestions
    EXPECT_STREQ("givenName", CGXDLMSConverter::ToString(DLMS_X509_NAME_GIVEN_NAME));
    EXPECT_STREQ("surname", CGXDLMSConverter::ToString(DLMS_X509_NAME_SUR_NAME));
    // ... other X509 names like organizationName, etc.
}

TEST_F(CGXDLMSConverterTest, ValueOfX509Name) {
    // Corrected based on compiler suggestions for enum side
    EXPECT_EQ(DLMS_X509_NAME_GIVEN_NAME, CGXDLMSConverter::ValueOfx509Name("givenName"));
    // Assuming "commonName" string might map to a specific enum like GIVEN_NAME or another,
    // or it might be an actual X509 field name that the ValueOfx509Name can parse.
    // For now, testing with strings that match the corrected enums.
    EXPECT_EQ(DLMS_X509_NAME_SUR_NAME, CGXDLMSConverter::ValueOfx509Name("surname"));

    // It's possible that commonName and countryName are valid inputs to ValueOfx509Name
    // and map to some internal enums, but the original test used them as enum names themselves.
    // Example: If "commonName" string is a valid input to ValueOfx509Name:
    // EXPECT_EQ(SOME_ENUM_FOR_COMMON_NAME, CGXDLMSConverter::ValueOfx509Name("commonName"));
}
