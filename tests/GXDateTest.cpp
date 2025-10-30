#include <gtest/gtest.h>
#include "GXDate.h"

TEST(CGXDateTest, DefaultConstructor)
{
    CGXDate dt;
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXDateTest, ConstructorWithValues)
{
    CGXDate dt(2023, 10, 27);
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXDateTest, CopyConstructorFromDateTime)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXDate dt(src);
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXDateTest, AssignmentOperatorFromDateTime)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXDate dt;
    dt = src;
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXDateTest, CopyConstructor)
{
    CGXDate dt1(2023, 10, 27);
    CGXDate dt2(dt1);
    ASSERT_EQ(0, dt1.CompareTo(dt2));
}

TEST(CGXDateTest, MoveConstructor)
{
    CGXDate dt1(2023, 10, 27);
    CGXDate dt2(dt1);
    CGXDate dt3(std::move(dt1));
    ASSERT_EQ(0, dt2.CompareTo(dt3));
}

TEST(CGXDateTest, CopyAssignment)
{
    CGXDate dt1(2023, 10, 27);
    CGXDate dt2;
    dt2 = dt1;
    ASSERT_EQ(0, dt1.CompareTo(dt2));
}

TEST(CGXDateTest, MoveAssignment)
{
    CGXDate dt1(2023, 10, 27);
    CGXDate dt2(dt1);
    CGXDate dt3;
    dt3 = std::move(dt1);
    ASSERT_EQ(0, dt2.CompareTo(dt3));
}
