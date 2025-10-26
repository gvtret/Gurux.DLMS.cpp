#include <climits>
#include <cstdint>
#include <gtest/gtest.h>

#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"

TEST(CGXDLMSVariantTest, WideStringToUtf8Conversion) {
	std::wstring input = L"Gr";
	input.push_back(static_cast<wchar_t>(0x00FC));  // ü
	input.push_back(static_cast<wchar_t>(0x00DF));  // ß
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
	std::string bytes(reinterpret_cast<const char *>(buffer.GetData()), buffer.GetSize());
	EXPECT_EQ(expected, bytes);
}

TEST(CGXDLMSVariantTest, Int8SerializationPreservesBitPattern) {
	const char original = static_cast<char>(-1);
	CGXDLMSVariant variant(original);

	CGXByteBuffer buffer;
	ASSERT_EQ(0, variant.GetBytes(buffer));
	ASSERT_EQ(1u, buffer.GetSize());

	const uint8_t expected = static_cast<uint8_t>(original);
	ASSERT_NE(nullptr, buffer.GetData());
	EXPECT_EQ(expected, buffer.GetData()[0]);
}

TEST(CGXDLMSVariantTest, UInt8SerializationPreservesBitPattern) {
	const unsigned char original = static_cast<unsigned char>(0xFE);
	CGXDLMSVariant variant(original);

	CGXByteBuffer buffer;
	ASSERT_EQ(0, variant.GetBytes(buffer));
	ASSERT_EQ(1u, buffer.GetSize());

	ASSERT_NE(nullptr, buffer.GetData());
	EXPECT_EQ(original, buffer.GetData()[0]);
}
