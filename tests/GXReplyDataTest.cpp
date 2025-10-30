#include <gtest/gtest.h>
#include "GXReplyData.h"

TEST(CGXReplyDataTest, DefaultConstructor)
{
    const CGXReplyData obj;
    ASSERT_EQ(DLMS_DATA_REQUEST_TYPES_NONE, obj.GetMoreData());
    ASSERT_EQ(DLMS_COMMAND_NONE, obj.GetCommand());
    ASSERT_FALSE(obj.IsComplete());
    ASSERT_EQ(0, obj.GetTotalCount());
    ASSERT_EQ(0, obj.GetCount());
    ASSERT_FALSE(obj.GetPeek());
    ASSERT_EQ(0, obj.GetCipherIndex());
    ASSERT_EQ(nullptr, obj.GetTime());
    ASSERT_EQ(0, obj.GetInvokeId());
    ASSERT_EQ(0, obj.GetBlockNumber());
    ASSERT_EQ(0, obj.GetBlockNumberAck());
    ASSERT_FALSE(obj.GetStreaming());
    ASSERT_EQ(0, obj.GetGbtWindowSize());
    ASSERT_EQ(0, obj.GetClientAddress());
    ASSERT_EQ(0, obj.GetServerAddress());
    ASSERT_EQ(0, obj.GetCipheredCommand());
}

TEST(CGXReplyDataTest, CopyConstructor)
{
    CGXReplyData obj1;
    obj1.SetCommand(DLMS_COMMAND_GET_REQUEST);
    const CGXReplyData obj2(obj1);
    ASSERT_EQ(obj1.GetCommand(), obj2.GetCommand());
}

TEST(CGXReplyDataTest, MoveConstructor)
{
    CGXReplyData obj1;
	obj1.SetCommand(DLMS_COMMAND_GET_REQUEST);
    const CGXReplyData obj2(std::move(obj1));
    ASSERT_EQ(DLMS_COMMAND_GET_REQUEST, obj2.GetCommand());
}

TEST(CGXReplyDataTest, CopyAssignment)
{
    CGXReplyData obj1;
	obj1.SetCommand(DLMS_COMMAND_GET_REQUEST);
    CGXReplyData obj2;
    obj2 = obj1;
    ASSERT_EQ(obj1.GetCommand(), obj2.GetCommand());
}

TEST(CGXReplyDataTest, MoveAssignment)
{
    CGXReplyData obj1;
	obj1.SetCommand(DLMS_COMMAND_GET_REQUEST);
    CGXReplyData obj2;
    obj2 = std::move(obj1);
    ASSERT_EQ(DLMS_COMMAND_GET_REQUEST, obj2.GetCommand());
}
