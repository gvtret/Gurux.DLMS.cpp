#include <gtest/gtest.h>
#include "GXDLMSTokenGateway.h"
#include "enums.h"
#include "GXDateTime.h"

TEST(CGXDLMSTokenGatewayTest, Constructor)
{
    CGXDLMSTokenGateway gateway;
    ASSERT_EQ(0, gateway.GetToken().GetSize());
    ASSERT_EQ(DLMS_TOKEN_DELIVERY_REMOTE, gateway.GetDeliveryMethod());
    ASSERT_EQ(DLMS_TOKEN_STATUS_CODE_TOKEN_FORMAT_FAILURE, gateway.GetStatusCode());
    ASSERT_EQ("", gateway.GetDataValue());
}

TEST(CGXDLMSTokenGatewayTest, PropertyGettersAndSetters)
{
    CGXDLMSTokenGateway gateway;

    CGXByteBuffer token;
    token.AddString("test_token");
    gateway.SetToken(token);
    ASSERT_EQ("test_token", gateway.GetToken().ToString());

    CGXDateTime time;
    gateway.SetTime(time);
    ASSERT_EQ(time.ToUnixTime(), gateway.GetTime().ToUnixTime());

    std::vector<std::string> descriptions;
    descriptions.push_back("desc1");
    gateway.setDescriptions(descriptions);
    ASSERT_EQ(1, gateway.GetDescriptions().size());
    ASSERT_EQ("desc1", gateway.GetDescriptions()[0]);

    gateway.SetDeliveryMethod(DLMS_TOKEN_DELIVERY_LOCAL);
    ASSERT_EQ(DLMS_TOKEN_DELIVERY_LOCAL, gateway.GetDeliveryMethod());

    gateway.SetStatusCode(DLMS_TOKEN_STATUS_CODE_TOKEN_RECEIVED);
    ASSERT_EQ(DLMS_TOKEN_STATUS_CODE_TOKEN_RECEIVED, gateway.GetStatusCode());

    std::string dataValue = "test_value";
    gateway.SetDataValue(dataValue);
    ASSERT_EQ("test_value", gateway.GetDataValue());
}
