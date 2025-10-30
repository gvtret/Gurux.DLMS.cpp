#include <gtest/gtest.h>
#include "GXDLMSObject.h"

TEST(CGXDLMSObjectTest, DefaultConstructor)
{
    const CGXDLMSObject obj;
    ASSERT_EQ(DLMS_OBJECT_TYPE_NONE, obj.GetObjectType());
    ASSERT_EQ(0, obj.GetShortName());
    std::string ln;
    obj.GetLogicalName(ln);
    ASSERT_EQ("0.0.0.0.0.0", ln);
    ASSERT_EQ(0, obj.GetVersion());
}

TEST(CGXDLMSObjectTest, CopyConstructor)
{
    CGXDLMSObject obj1(DLMS_OBJECT_TYPE_DATA, "1.2.3.4.5.6");
    const CGXDLMSObject obj2(obj1);
    ASSERT_EQ(obj1.GetObjectType(), obj2.GetObjectType());
    std::string ln1, ln2;
    obj1.GetLogicalName(ln1);
    obj2.GetLogicalName(ln2);
    ASSERT_EQ(ln1, ln2);
}

TEST(CGXDLMSObjectTest, MoveConstructor)
{
    CGXDLMSObject obj1(DLMS_OBJECT_TYPE_DATA, "1.2.3.4.5.6");
    const CGXDLMSObject obj2(std::move(obj1));
    ASSERT_EQ(DLMS_OBJECT_TYPE_DATA, obj2.GetObjectType());
    std::string ln;
    obj2.GetLogicalName(ln);
    ASSERT_EQ("1.2.3.4.5.6", ln);
}

TEST(CGXDLMSObjectTest, CopyAssignment)
{
    CGXDLMSObject obj1(DLMS_OBJECT_TYPE_DATA, "1.2.3.4.5.6");
    CGXDLMSObject obj2;
    obj2 = obj1;
    ASSERT_EQ(obj1.GetObjectType(), obj2.GetObjectType());
    std::string ln1, ln2;
    obj1.GetLogicalName(ln1);
    obj2.GetLogicalName(ln2);
    ASSERT_EQ(ln1, ln2);
}

TEST(CGXDLMSObjectTest, MoveAssignment)
{
    CGXDLMSObject obj1(DLMS_OBJECT_TYPE_DATA, "1.2.3.4.5.6");
    CGXDLMSObject obj2;
    obj2 = std::move(obj1);
    ASSERT_EQ(DLMS_OBJECT_TYPE_DATA, obj2.GetObjectType());
    std::string ln;
    obj2.GetLogicalName(ln);
    ASSERT_EQ("1.2.3.4.5.6", ln);
}
