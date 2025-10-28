#include <gtest/gtest.h>
#include "GXDLMSValueEventArg.h"
#include "GXDLMSObject.h"

TEST(CGXDLMSValueEventArgTest, Constructor)
{
    CGXDLMSObject obj;
    CGXDLMSValueEventArg arg(&obj, 1);
    ASSERT_EQ(&obj, arg.GetTarget());
    ASSERT_EQ(1, arg.GetIndex());
    ASSERT_FALSE(arg.GetHandled());
    ASSERT_EQ(0, arg.GetSelector());
    ASSERT_EQ(DLMS_ERROR_CODE_OK, arg.GetError());
    ASSERT_FALSE(arg.IsAction());
    ASSERT_FALSE(arg.IsByteArray());
    ASSERT_FALSE(arg.GetSkipMaxPduSize());
    ASSERT_EQ(0, arg.GetRowToPdu());
    ASSERT_EQ(0, arg.GetRowBeginIndex());
    ASSERT_EQ(0, arg.GetRowEndIndex());
    ASSERT_EQ(0, arg.GetInvokeId());
}

TEST(CGXDLMSValueEventArgTest, PropertyGettersAndSetters)
{
    CGXDLMSObject obj;
    CGXDLMSValueEventArg arg(&obj, 1);

    CGXDLMSObject newObj;
    arg.SetTarget(&newObj);
    ASSERT_EQ(&newObj, arg.GetTarget());

    arg.SetIndex(2);
    ASSERT_EQ(2, arg.GetIndex());

    CGXDLMSVariant value("test");
    arg.SetValue(value);
    ASSERT_EQ("test", arg.GetValue().strVal);

    arg.SetHandled(true);
    ASSERT_TRUE(arg.GetHandled());

    arg.SetSelector(3);
    ASSERT_EQ(3, arg.GetSelector());

    CGXDLMSVariant params(true);
    arg.SetParameters(params);
    ASSERT_TRUE(arg.GetParameters().boolVal);

    arg.SetError(DLMS_ERROR_CODE_INVALID_PARAMETER);
    ASSERT_EQ(DLMS_ERROR_CODE_INVALID_PARAMETER, arg.GetError());

    arg.SetAction(true);
    ASSERT_TRUE(arg.IsAction());

    arg.SetByteArray(true);
    ASSERT_TRUE(arg.IsByteArray());

    arg.SetSkipMaxPduSize(true);
    ASSERT_TRUE(arg.GetSkipMaxPduSize());

    arg.SetRowToPdu(10);
    ASSERT_EQ(10, arg.GetRowToPdu());

    arg.SetRowBeginIndex(20);
    ASSERT_EQ(20, arg.GetRowBeginIndex());

    arg.SetRowEndIndex(30);
    ASSERT_EQ(30, arg.GetRowEndIndex());

    arg.SetInvokeId(40);
    ASSERT_EQ(40, arg.GetInvokeId());
}
