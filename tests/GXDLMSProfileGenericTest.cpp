#include <gtest/gtest.h>
#include "GXDLMSProfileGeneric.h"
#include "GXDLMSClock.h"

TEST(CGXDLMSProfileGenericTest, CopyConstructor)
{
    CGXDLMSProfileGeneric pg1;
    CGXDLMSClock clock;
    pg1.AddCaptureObject(&clock, 2, 0);

    CGXDLMSProfileGeneric pg2(pg1);
    ASSERT_EQ(pg1.GetCaptureObjects().size(), pg2.GetCaptureObjects().size());
    ASSERT_NE(pg1.GetCaptureObjects()[0].second.get(), pg2.GetCaptureObjects()[0].second.get());
}

TEST(CGXDLMSProfileGenericTest, MoveConstructor)
{
    CGXDLMSProfileGeneric pg1;
    CGXDLMSClock clock;
    pg1.AddCaptureObject(&clock, 2, 0);
    const auto* originalCaptureObject = pg1.GetCaptureObjects()[0].second.get();

    CGXDLMSProfileGeneric pg2(std::move(pg1));
    ASSERT_EQ(1, pg2.GetCaptureObjects().size());
    ASSERT_EQ(originalCaptureObject, pg2.GetCaptureObjects()[0].second.get());
    ASSERT_TRUE(pg1.GetCaptureObjects().empty());
}

TEST(CGXDLMSProfileGenericTest, CopyAssignment)
{
    CGXDLMSProfileGeneric pg1;
    CGXDLMSClock clock;
    pg1.AddCaptureObject(&clock, 2, 0);

    CGXDLMSProfileGeneric pg2;
    pg2 = pg1;
    ASSERT_EQ(pg1.GetCaptureObjects().size(), pg2.GetCaptureObjects().size());
    ASSERT_NE(pg1.GetCaptureObjects()[0].second.get(), pg2.GetCaptureObjects()[0].second.get());
}

TEST(CGXDLMSProfileGenericTest, MoveAssignment)
{
    CGXDLMSProfileGeneric pg1;
    CGXDLMSClock clock;
    pg1.AddCaptureObject(&clock, 2, 0);
    const auto* originalCaptureObject = pg1.GetCaptureObjects()[0].second.get();

    CGXDLMSProfileGeneric pg2;
    pg2 = std::move(pg1);
    ASSERT_EQ(1, pg2.GetCaptureObjects().size());
    ASSERT_EQ(originalCaptureObject, pg2.GetCaptureObjects()[0].second.get());
    ASSERT_TRUE(pg1.GetCaptureObjects().empty());
}
