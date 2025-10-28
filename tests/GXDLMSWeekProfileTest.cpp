#include <gtest/gtest.h>
#include "GXDLMSWeekProfile.h"

TEST(CGXDLMSWeekProfileTest, Constructor)
{
    CGXDLMSWeekProfile profile;
    ASSERT_EQ("", profile.GetName());
    ASSERT_EQ(0, profile.GetMonday());
    ASSERT_EQ(0, profile.GetTuesday());
    ASSERT_EQ(0, profile.GetWednesday());
    ASSERT_EQ(0, profile.GetThursday());
    ASSERT_EQ(0, profile.GetFriday());
    ASSERT_EQ(0, profile.GetSaturday());
    ASSERT_EQ(0, profile.GetSunday());
}

TEST(CGXDLMSWeekProfileTest, PropertyGettersAndSetters)
{
    CGXDLMSWeekProfile profile;

    profile.SetName("test_profile");
    ASSERT_EQ("test_profile", profile.GetName());

    profile.SetMonday(1);
    ASSERT_EQ(1, profile.GetMonday());

    profile.SetTuesday(2);
    ASSERT_EQ(2, profile.GetTuesday());

    profile.SetWednesday(3);
    ASSERT_EQ(3, profile.GetWednesday());

    profile.SetThursday(4);
    ASSERT_EQ(4, profile.GetThursday());

    profile.SetFriday(5);
    ASSERT_EQ(5, profile.GetFriday());

    profile.SetSaturday(6);
    ASSERT_EQ(6, profile.GetSaturday());

    profile.SetSunday(7);
    ASSERT_EQ(7, profile.GetSunday());
}
