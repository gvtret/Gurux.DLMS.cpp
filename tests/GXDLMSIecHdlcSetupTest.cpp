#include <gtest/gtest.h>
#include "GXDLMSHdlcSetup.h"

static void AssertEqual(const CGXDLMSIecHdlcSetup& expected, const CGXDLMSIecHdlcSetup& actual)
{
    ASSERT_EQ(expected.GetCommunicationSpeed(), actual.GetCommunicationSpeed());
    ASSERT_EQ(expected.GetWindowSizeTransmit(), actual.GetWindowSizeTransmit());
    ASSERT_EQ(expected.GetWindowSizeReceive(), actual.GetWindowSizeReceive());
    ASSERT_EQ(expected.GetMaximumInfoLengthTransmit(), actual.GetMaximumInfoLengthTransmit());
    ASSERT_EQ(expected.GetMaximumInfoLengthReceive(), actual.GetMaximumInfoLengthReceive());
    ASSERT_EQ(expected.GetInterCharachterTimeout(), actual.GetInterCharachterTimeout());
    ASSERT_EQ(expected.GetInactivityTimeout(), actual.GetInactivityTimeout());
    ASSERT_EQ(expected.GetDeviceAddress(), actual.GetDeviceAddress());
}

TEST(CGXDLMSIecHdlcSetupTest, DefaultConstructor)
{
    CGXDLMSIecHdlcSetup setup;
    ASSERT_EQ(setup.GetCommunicationSpeed(), DLMS_BAUD_RATE_9600);
    ASSERT_EQ(setup.GetWindowSizeTransmit(), 1);
    ASSERT_EQ(setup.GetWindowSizeReceive(), 1);
    ASSERT_EQ(setup.GetMaximumInfoLengthTransmit(), 128);
    ASSERT_EQ(setup.GetMaximumInfoLengthReceive(), 128);
    ASSERT_EQ(setup.GetInterCharachterTimeout(), 30);
    ASSERT_EQ(setup.GetInactivityTimeout(), 120);
    ASSERT_EQ(setup.GetDeviceAddress(), 0);
}

TEST(CGXDLMSIecHdlcSetupTest, PropertyGettersAndSetters)
{
    CGXDLMSIecHdlcSetup setup;
    setup.SetCommunicationSpeed(DLMS_BAUD_RATE_19200);
    ASSERT_EQ(setup.GetCommunicationSpeed(), DLMS_BAUD_RATE_19200);
    setup.SetWindowSizeTransmit(2);
    ASSERT_EQ(setup.GetWindowSizeTransmit(), 2);
    setup.SetWindowSizeReceive(3);
    ASSERT_EQ(setup.GetWindowSizeReceive(), 3);
    setup.SetMaximumInfoLengthTransmit(256);
    ASSERT_EQ(setup.GetMaximumInfoLengthTransmit(), 256);
    setup.SetMaximumInfoLengthReceive(512);
    ASSERT_EQ(setup.GetMaximumInfoLengthReceive(), 512);
    setup.SetInterCharachterTimeout(60);
    ASSERT_EQ(setup.GetInterCharachterTimeout(), 60);
    setup.SetInactivityTimeout(240);
    ASSERT_EQ(setup.GetInactivityTimeout(), 240);
    setup.SetDeviceAddress(1);
    ASSERT_EQ(setup.GetDeviceAddress(), 1);
}

TEST(CGXDLMSIecHdlcSetupTest, CopySemantics)
{
    CGXDLMSIecHdlcSetup setup;
    setup.SetCommunicationSpeed(DLMS_BAUD_RATE_19200);
    setup.SetWindowSizeTransmit(2);
    setup.SetWindowSizeReceive(3);

    CGXDLMSIecHdlcSetup copy_constructed(setup);
    AssertEqual(setup, copy_constructed);

    CGXDLMSIecHdlcSetup copy_assigned;
    copy_assigned = setup;
    AssertEqual(setup, copy_assigned);
}

TEST(CGXDLMSIecHdlcSetupTest, MoveSemantics)
{
    CGXDLMSIecHdlcSetup setup;
    setup.SetCommunicationSpeed(DLMS_BAUD_RATE_19200);
    setup.SetWindowSizeTransmit(2);
    setup.SetWindowSizeReceive(3);

    CGXDLMSIecHdlcSetup setup_copy(setup);

    CGXDLMSIecHdlcSetup move_constructed(std::move(setup));
    AssertEqual(setup_copy, move_constructed);

    CGXDLMSIecHdlcSetup move_assigned;
    move_assigned = std::move(move_constructed);
    AssertEqual(setup_copy, move_assigned);
}
