#include <gtest/gtest.h>
#include "GXDLMSTcpUdpSetup.h"

TEST(CGXDLMSTcpUdpSetupTest, Constructor)
{
    CGXDLMSTcpUdpSetup setup;
    ASSERT_EQ(4059, setup.GetPort());
    ASSERT_EQ("127.0.0.1", setup.GetIPReference());
    ASSERT_EQ(1, setup.GetMaximumSimultaneousConnections());
    ASSERT_EQ(180, setup.GetInactivityTimeout());
    ASSERT_EQ(576, setup.GetMaximumSegmentSize());
}

TEST(CGXDLMSTcpUdpSetupTest, PropertyGettersAndSetters)
{
    CGXDLMSTcpUdpSetup setup;

    setup.SetPort(8080);
    ASSERT_EQ(8080, setup.GetPort());

    setup.SetIPReference("127.0.0.1");
    ASSERT_EQ("127.0.0.1", setup.GetIPReference());

    setup.SetMaximumSimultaneousConnections(10);
    ASSERT_EQ(10, setup.GetMaximumSimultaneousConnections());

    setup.SetInactivityTimeout(60);
    ASSERT_EQ(60, setup.GetInactivityTimeout());

    setup.SetMaximumSegmentSize(1024);
    ASSERT_EQ(1024, setup.GetMaximumSegmentSize());
}
