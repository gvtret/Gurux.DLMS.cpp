#include <gtest/gtest.h>
#include "GXDLMSSpecialDaysTable.h"

TEST(CGXDLMSSpecialDaysTableTest, Constructor)
{
    CGXDLMSSpecialDaysTable table;
    ASSERT_EQ(0, table.GetEntries().size());
}
