#include <gtest/gtest.h>
#include "GXDLMSSecuritySetup.h"

static void AssertEqual(const CGXDLMSSecuritySetup& expected, const CGXDLMSSecuritySetup& actual)
{
    ASSERT_EQ(expected.GetSecurityPolicy(), actual.GetSecurityPolicy());
    ASSERT_EQ(expected.GetSecuritySuite(), actual.GetSecuritySuite());
    ASSERT_EQ(expected.GetClientSystemTitle(), actual.GetClientSystemTitle());
    ASSERT_EQ(expected.GetServerSystemTitle(), actual.GetServerSystemTitle());
    ASSERT_EQ(expected.GetCertificates().size(), actual.GetCertificates().size());
}

TEST(CGXDLMSSecuritySetupTest, DefaultConstructor)
{
    CGXDLMSSecuritySetup setup;
    ASSERT_EQ(DLMS_SECURITY_POLICY_NOTHING, setup.GetSecurityPolicy());
    ASSERT_EQ(DLMS_SECURITY_SUITE_V0, setup.GetSecuritySuite());
}

TEST(CGXDLMSSecuritySetupTest, PropertyGettersAndSetters)
{
    CGXDLMSSecuritySetup setup;

    setup.SetSecurityPolicy(DLMS_SECURITY_POLICY_AUTHENTICATED_ENCRYPTED);
    ASSERT_EQ(DLMS_SECURITY_POLICY_AUTHENTICATED_ENCRYPTED, setup.GetSecurityPolicy());

    setup.SetSecuritySuite(DLMS_SECURITY_SUITE_V1);
    ASSERT_EQ(DLMS_SECURITY_SUITE_V1, setup.GetSecuritySuite());

    CGXByteBuffer clientTitle;
    clientTitle.AddString("client");
    setup.SetClientSystemTitle(clientTitle);
    ASSERT_EQ(clientTitle.ToString(), setup.GetClientSystemTitle().ToString());

    CGXByteBuffer serverTitle;
    serverTitle.AddString("server");
    setup.SetServerSystemTitle(serverTitle);
    ASSERT_EQ(serverTitle.ToString(), setup.GetServerSystemTitle().ToString());
}
