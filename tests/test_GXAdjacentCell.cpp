#include <gtest/gtest.h>
#include "GXAdjacentCell.h"

TEST(GXAdjacentCellTest, DefaultConstructor) {
    GXAdjacentCell cell;
    EXPECT_EQ(0, cell.GetCellId());
    EXPECT_EQ(0, cell.GetSignalQuality());
}

TEST(GXAdjacentCellTest, ParameterizedConstructor) {
    GXAdjacentCell cell(12345, 99);
    EXPECT_EQ(12345, cell.GetCellId());
    EXPECT_EQ(99, cell.GetSignalQuality());
}

TEST(GXAdjacentCellTest, Setters) {
    GXAdjacentCell cell;
    cell.SetCellId(54321);
    cell.SetSignalQuality(50);
    EXPECT_EQ(54321, cell.GetCellId());
    EXPECT_EQ(50, cell.GetSignalQuality());
}
