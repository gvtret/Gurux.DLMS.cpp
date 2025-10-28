#include <gtest/gtest.h>
#include "GXBigInteger.h"

TEST(CGXBigIntegerTest, DefaultConstructor)
{
    CGXBigInteger i;
    ASSERT_TRUE(i.IsZero());
    ASSERT_FALSE(i.IsNegative());
}

TEST(CGXBigIntegerTest, ConstructorWithValue)
{
    CGXBigInteger i(12345);
    ASSERT_FALSE(i.IsZero());
    ASSERT_FALSE(i.IsNegative());
    ASSERT_EQ("0x3039", i.ToString());
}

TEST(CGXBigIntegerTest, Add)
{
    CGXBigInteger i1(12345);
    CGXBigInteger i2(54321);
    i1.Add(i2);
    ASSERT_EQ("0x01046A", i1.ToString());
}

TEST(CGXBigIntegerTest, Subtract)
{
    CGXBigInteger i1(54321);
    CGXBigInteger i2(12345);
    i1.Sub(i2);
    ASSERT_EQ("0xA3F8", i1.ToString());
}

TEST(CGXBigIntegerTest, Multiply)
{
    CGXBigInteger i1(123);
    CGXBigInteger i2(456);
    i1.Multiply(i2);
    ASSERT_EQ("0xDB18", i1.ToString());
}

TEST(CGXBigIntegerTest, Compare)
{
    CGXBigInteger i1(123);
    CGXBigInteger i2(456);
    CGXBigInteger i3(123);
    ASSERT_EQ(-1, i1.Compare(i2));
    ASSERT_EQ(1, i2.Compare(i1));
    ASSERT_EQ(0, i1.Compare(i3));
}
