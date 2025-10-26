#include <climits>
#include <gtest/gtest.h>

#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"

TEST(CGXDLMSVariantTest, WideStringToUtf8Conversion) {
    std::wstring input = L"Gr";
    input.push_back(static_cast<wchar_t>(0x00FC)); // ü
    input.push_back(static_cast<wchar_t>(0x00DF)); // ß
#if WCHAR_MAX == 0xFFFF
    input.push_back(static_cast<wchar_t>(0xD83D));
    input.push_back(static_cast<wchar_t>(0xDE0A));
#else
    input.push_back(static_cast<wchar_t>(0x1F60A));
#endif

    CGXDLMSVariant variant(input);
    const std::string expected = u8"Grüß😊";

    EXPECT_EQ(expected, variant.ToString());

    CGXByteBuffer buffer;
    ASSERT_EQ(0, variant.GetBytes(buffer));
    ASSERT_EQ(expected.size(), buffer.GetSize());
    std::string bytes(reinterpret_cast<const char*>(buffer.GetData()), buffer.GetSize());
    EXPECT_EQ(expected, bytes);
}
