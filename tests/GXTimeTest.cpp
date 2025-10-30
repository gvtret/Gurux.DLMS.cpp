#include <gtest/gtest.h>
#include "GXTime.h"

TEST(CGXTimeTest, DefaultConstructor)
{
    CGXTime dt;
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK, dt.GetSkip());
}

TEST(CGXTimeTest, ConstructorWithValues)
{
    CGXTime dt(10, 30, 0, 0);
    ASSERT_EQ(10, dt.GetValue().tm_hour);
    ASSERT_EQ(30, dt.GetValue().tm_min);
    ASSERT_EQ(0, dt.GetValue().tm_sec);
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXTimeTest, CopyConstructorFromDateTime)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXTime dt(src);
    ASSERT_EQ(10, dt.GetValue().tm_hour);
    ASSERT_EQ(30, dt.GetValue().tm_min);
    ASSERT_EQ(0, dt.GetValue().tm_sec);
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK | src.GetSkip(), dt.GetSkip());
}

TEST(CGXTimeTest, AssignmentOperatorFromDateTime)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXTime dt;
    dt = src;
    ASSERT_EQ(10, dt.GetValue().tm_hour);
    ASSERT_EQ(30, dt.GetValue().tm_min);
    ASSERT_EQ(0, dt.GetValue().tm_sec);
    ASSERT_EQ(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK | src.GetSkip(), dt.GetSkip());
}

TEST(CGXTimeTest, CopyConstructor)
{
    CGXTime dt1(10, 30, 0, 0);
    CGXTime dt2(dt1);
    ASSERT_EQ(0, dt1.CompareTo(dt2));
}

TEST(CGXTimeTest, MoveConstructor)
{
    CGXTime dt1(10, 30, 0, 0);
    CGXTime dt2(dt1);
    CGXTime dt3(std::move(dt1));
    ASSERT_EQ(0, dt2.CompareTo(dt3));
}

TEST(CGXTimeTest, CopyAssignment)
{
    CGXTime dt1(10, 30, 0, 0);
    CGXTime dt2;
    dt2 = dt1;
    ASSERT_EQ(0, dt1.CompareTo(dt2));
}

TEST(CGXTimeTest, MoveAssignment)
{
    CGXTime dt1(10, 30, 0, 0);
    CGXTime dt2(dt1);
    CGXTime dt3;
    dt3 = std::move(dt1);
    ASSERT_EQ(0, dt2.CompareTo(dt3));
}
