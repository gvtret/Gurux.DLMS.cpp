#include <gtest/gtest.h>
#include "GXDateTime.h"

TEST(CGXDateTimeTest, DefaultConstructor)
{
    CGXDateTime dt;
    ASSERT_EQ(0, dt.GetValue().tm_year);
    ASSERT_EQ(0, dt.GetValue().tm_mon);
    ASSERT_EQ(1, dt.GetValue().tm_mday);
    ASSERT_EQ(0, dt.GetValue().tm_hour);
    ASSERT_EQ(0, dt.GetValue().tm_min);
    ASSERT_EQ(0, dt.GetValue().tm_sec);
}

TEST(CGXDateTimeTest, ConstructorWithValues)
{
    CGXDateTime dt(2023, 10, 27, 10, 30, 0, 0);
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_TRUE(dt.GetValue().tm_hour == 10 || dt.GetValue().tm_hour == 9);
    ASSERT_EQ(30, dt.GetValue().tm_min);
    ASSERT_EQ(0, dt.GetValue().tm_sec);
}

#include <time.h>

TEST(CGXDateTimeTest, UnixTimeConstructor)
{
    // Corresponds to 2023-10-27 10:30:00 UTC
    CGXDateTime dt(1698399000UL);
    struct tm expected;
    time_t t = 1698399000UL;
    gmtime_r(&t, &expected);
    ASSERT_EQ(expected.tm_year, dt.GetValue().tm_year);
    ASSERT_EQ(expected.tm_mon, dt.GetValue().tm_mon);
    ASSERT_EQ(expected.tm_mday, dt.GetValue().tm_mday);
    ASSERT_EQ(expected.tm_hour, dt.GetValue().tm_hour);
    ASSERT_EQ(expected.tm_min, dt.GetValue().tm_min);
    ASSERT_EQ(expected.tm_sec, dt.GetValue().tm_sec);
}

TEST(CGXDateTimeTest, AddDays)
{
    CGXDateTime dt(2023, 10, 27, 10, 30, 0, 0);
    dt.AddDays(1);
    ASSERT_EQ(28, dt.GetValue().tm_mday);
    dt.AddDays(4); // Test month change
    ASSERT_EQ(11 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(1, dt.GetValue().tm_mday);
}

TEST(CGXDateTimeTest, AddHours)
{
    CGXDateTime dt(2023, 10, 27, 10, 30, 0, 0);
    dt.AddHours(1);
    ASSERT_EQ(11, dt.GetValue().tm_hour);
    dt.AddHours(14); // Test day change
    ASSERT_EQ(28, dt.GetValue().tm_mday);
    ASSERT_EQ(1, dt.GetValue().tm_hour);
}

TEST(CGXDateTimeTest, AddMinutes)
{
    CGXDateTime dt(2023, 10, 27, 10, 30, 0, 0);
    dt.AddMinutes(1);
    ASSERT_EQ(31, dt.GetValue().tm_min);
    dt.AddMinutes(30); // Test hour change
    ASSERT_EQ(11, dt.GetValue().tm_hour);
    ASSERT_EQ(1, dt.GetValue().tm_min);
}

TEST(CGXDateTimeTest, AddSeconds)
{
    CGXDateTime dt(2023, 10, 27, 10, 30, 0, 0);
    dt.AddSeconds(1);
    ASSERT_EQ(1, dt.GetValue().tm_sec);
    dt.AddSeconds(60); // Test minute change
    ASSERT_EQ(31, dt.GetValue().tm_min);
    ASSERT_EQ(1, dt.GetValue().tm_sec);
}

TEST(CGXDateTimeTest, CompareTo)
{
    CGXDateTime dt1(2023, 10, 27, 10, 30, 0, 0);
    CGXDateTime dt2(2023, 10, 27, 10, 30, 0, 0);
    CGXDateTime dt3(2023, 10, 27, 10, 30, 1, 0);
    CGXDateTime dt4(2023, 10, 26, 10, 30, 0, 0);
    ASSERT_EQ(0, dt1.CompareTo(dt2));
    ASSERT_EQ(-1, dt1.CompareTo(dt3));
    ASSERT_EQ(1, dt1.CompareTo(dt4));
}
