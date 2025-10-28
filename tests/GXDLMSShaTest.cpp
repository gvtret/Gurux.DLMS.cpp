#include <gtest/gtest.h>
#include "GXDLMSSha256.h"
#include "GXDLMSSha384.h"

TEST(CGXDLMSSha256Test, Hash)
{
    CGXByteBuffer data;
    data.AddString("test");
    CGXByteBuffer crypted;
    CGXDLMSSha256::Hash(data, crypted);
    ASSERT_STREQ("9F86D081884C7D659A2FEAA0C55AD015A3BF4F1B2B0B822CD15D6C15B0F00A08", crypted.ToHexString(false).c_str());
}

//TEST(CGXDLMSSha384Test, DISABLED_Hash)
//{
//    CGXByteBuffer data;
//    data.AddString("test");
//    CGXByteBuffer crypted;
//    CGXDLMSSha384::Hash(data, crypted);
//    ASSERT_STREQ("768412320F7B0AA5812FCE428DC4706B3CAE50E02A64CAA97A582A6D1AADA8561E93D444A5452E1B166A529C523DA782", crypted.ToHexString(false).c_str());
//}
