#include <gtest/gtest.h>
#include "GXDLMSClient.h"

TEST(CGXDLMSClientTest, DefaultConstructor)
{
    const CGXDLMSClient client;
    ASSERT_EQ(true, client.GetUseLogicalNameReferencing());
    ASSERT_EQ(16, client.GetClientAddress());
    ASSERT_EQ(1, client.GetServerAddress());
    ASSERT_EQ(DLMS_AUTHENTICATION_NONE, client.GetAuthentication());
    ASSERT_EQ(DLMS_INTERFACE_TYPE_HDLC, client.GetInterfaceType());
}

TEST(CGXDLMSClientTest, ParameterizedConstructor)
{
    const CGXDLMSClient client(false, 32, 2, DLMS_AUTHENTICATION_HIGH, "password", DLMS_INTERFACE_TYPE_WRAPPER);
    ASSERT_FALSE(client.GetUseLogicalNameReferencing());
    ASSERT_EQ(32, client.GetClientAddress());
    ASSERT_EQ(2, client.GetServerAddress());
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH, client.GetAuthentication());
    ASSERT_EQ(DLMS_INTERFACE_TYPE_WRAPPER, client.GetInterfaceType());
}

TEST(CGXDLMSClientTest, PropertyGettersAndSetters)
{
    CGXDLMSClient client;

    client.SetPriority(DLMS_PRIORITY_HIGH);
    ASSERT_EQ(DLMS_PRIORITY_HIGH, client.GetPriority());

    client.SetServiceClass(DLMS_SERVICE_CLASS_CONFIRMED);
    ASSERT_EQ(DLMS_SERVICE_CLASS_CONFIRMED, client.GetServiceClass());

    client.SetInvokeID(123);
    ASSERT_EQ(123, client.GetInvokeID());

    client.SetAutoIncreaseInvokeID(false);
    ASSERT_FALSE(client.GetAutoIncreaseInvokeID());

    client.SetUseProtectedRelease(true);
    ASSERT_TRUE(client.GetUseProtectedRelease());

    client.SetUseUtc2NormalTime(true);
    ASSERT_TRUE(client.GetUseUtc2NormalTime());

    client.SetExpectedInvocationCounter(456);
    ASSERT_EQ(456, client.GetExpectedInvocationCounter());

    client.SetDateTimeSkips(static_cast<DATETIME_SKIPS>(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH));
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH, client.GetDateTimeSkips());

    client.SetUserID(78);
    ASSERT_EQ(78, client.GetUserID());

    client.SetQualityOfService(1);
    ASSERT_EQ(1, client.GetQualityOfService());

    client.SetMaxReceivePDUSize(1024);
    ASSERT_EQ(1024, client.GetMaxReceivePDUSize());

    client.SetGbtWindowSize(5);
    ASSERT_EQ(5, client.GetGbtWindowSize());

    client.SetNegotiatedConformance(DLMS_CONFORMANCE_GENERAL_PROTECTION);
    ASSERT_EQ(DLMS_CONFORMANCE_GENERAL_PROTECTION, client.GetNegotiatedConformance());

    client.SetProposedConformance(DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER);
    ASSERT_EQ(DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER, client.GetProposedConformance());
}
