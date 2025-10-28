#include <gtest/gtest.h>
#include "GXDLMSSha1.h"

TEST(CGXDLMSSha1Test, Encrypt)
{
    CGXByteBuffer data;
    data.AddString("test");
    CGXByteBuffer crypted;
    CGXDLMSSha1::Encrypt(data, crypted);
    ASSERT_STREQ("A94A8FE5CCB19BA61C4C0873D391E987982FBBD3", crypted.ToHexString(false).c_str());
}
