#include <gtest/gtest.h>
#include "GXDLMSSettings.h"

TEST(CGXDLMSSettingsTest, Constructor)
{
    CGXDLMSSettings settings(true);
    ASSERT_TRUE(settings.IsServer());

    CGXDLMSSettings clientSettings(false);
    ASSERT_FALSE(clientSettings.IsServer());
}

TEST(CGXDLMSSettingsTest, PropertyGettersAndSetters)
{
    CGXDLMSSettings settings(true);

    settings.SetAuthentication(DLMS_AUTHENTICATION_HIGH);
    ASSERT_EQ(DLMS_AUTHENTICATION_HIGH, settings.GetAuthentication());

    settings.SetDlmsVersionNumber(6);
    ASSERT_EQ(6, settings.GetDlmsVersionNumber());

    settings.SetUseLogicalNameReferencing(false);
    ASSERT_FALSE(settings.GetUseLogicalNameReferencing());

    settings.SetPriority(DLMS_PRIORITY_HIGH);
    ASSERT_EQ(DLMS_PRIORITY_HIGH, settings.GetPriority());

    settings.SetServiceClass(DLMS_SERVICE_CLASS_CONFIRMED);
    ASSERT_EQ(DLMS_SERVICE_CLASS_CONFIRMED, settings.GetServiceClass());

    settings.SetInvokeID(123);
    ASSERT_EQ(123, settings.GetInvokeID());

    settings.SetAutoIncreaseInvokeID(false);
    ASSERT_FALSE(settings.GetAutoIncreaseInvokeID());

    settings.SetUseUtc2NormalTime(true);
    ASSERT_TRUE(settings.GetUseUtc2NormalTime());

    settings.SetExpectedInvocationCounter(456);
    ASSERT_EQ(456, settings.GetExpectedInvocationCounter());

    settings.SetDateTimeSkips(static_cast<DATETIME_SKIPS>(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH));
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH, settings.GetDateTimeSkips());

    settings.SetUserID(78);
    ASSERT_EQ(78, settings.GetUserID());

    settings.SetQualityOfService(1);
    ASSERT_EQ(1, settings.GetQualityOfService());

    settings.SetGbtWindowSize(5);
    ASSERT_EQ(5, settings.GetGbtWindowSize());

    settings.SetNegotiatedConformance(DLMS_CONFORMANCE_GENERAL_PROTECTION);
    ASSERT_EQ(DLMS_CONFORMANCE_GENERAL_PROTECTION, settings.GetNegotiatedConformance());

    settings.SetProposedConformance(DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER);
    ASSERT_EQ(DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER, settings.GetProposedConformance());
}
