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

TEST(CGXDateTest, CopyConstructor)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXDate dt(src);
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}

TEST(CGXDateTest, AssignmentOperator)
{
    CGXDateTime src(2023, 10, 27, 10, 30, 0, 0);
    CGXDate dt;
    dt = src;
    ASSERT_EQ(2023 - 1900, dt.GetValue().tm_year);
    ASSERT_EQ(10 - 1, dt.GetValue().tm_mon);
    ASSERT_EQ(27, dt.GetValue().tm_mday);
    ASSERT_EQ(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS, dt.GetSkip());
}
