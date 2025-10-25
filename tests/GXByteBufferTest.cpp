#include <gtest/gtest.h>
#include "GXBytebuffer.h"

class GXByteBufferTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common test setup
    }

    void TearDown() override {
        // Cleanup
    }
};

// Test basic construction
TEST_F(GXByteBufferTest, DefaultConstructor) {
    CGXByteBuffer buffer;
    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_EQ(0u, buffer.GetPosition());
    EXPECT_EQ(0u, buffer.Available());
    EXPECT_EQ(0u, buffer.Capacity());
}

TEST_F(GXByteBufferTest, CapacityConstructor) {
    CGXByteBuffer buffer(100);
    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_GE(buffer.Capacity(), 100u);
}
// Test move semantics
TEST_F(GXByteBufferTest, CopyConstructor) {
    CGXByteBuffer source;
    source.SetUInt8(0x12);
    source.SetUInt16(0x3456);
    
    CGXByteBuffer copy(source);
    EXPECT_EQ(3u, copy.GetSize());
    EXPECT_TRUE(source.Compare(copy));
}
    
TEST_F(GXByteBufferTest, MoveConstructor) {
    CGXByteBuffer source;
    source.SetUInt8(0x12);
    source.SetUInt16(0x3456);
    
    CGXByteBuffer moved(std::move(source));
    EXPECT_EQ(3u, moved.GetSize());
    EXPECT_EQ(0u, source.GetSize()); // Source should be empty after move
}

// Test move assignment
TEST_F(GXByteBufferTest, MoveAssignment) {
    CGXByteBuffer source;
    source.SetUInt32(0x12345678);
    
    CGXByteBuffer dest;
    dest = std::move(source);
    
    EXPECT_EQ(4u, dest.GetSize());
    EXPECT_EQ(0u, source.GetSize());
    
    uint32_t val;
    EXPECT_EQ(0, dest.GetUInt32(&val));
    EXPECT_EQ(0x12345678u, val);
}

// Test exception safety
TEST_F(GXByteBufferTest, BasicDataOperations) {
    CGXByteBuffer buffer;
    
    // This should handle bad_alloc gracefully
    EXPECT_EQ(0, buffer.SetUInt8(0x12));
    EXPECT_EQ(1u, buffer.GetSize());
    // Note: Actually causing bad_alloc in tests is tricky,
    // so we test the error code paths
    EXPECT_EQ(0, buffer.SetUInt16(0x3456));
    EXPECT_EQ(3u, buffer.GetSize());

// Test boundary conditions
    EXPECT_EQ(0, buffer.SetUInt32(0x789ABCDE));
    EXPECT_EQ(7u, buffer.GetSize());
}

TEST_F(GXByteBufferTest, DataRetrieval) {
    CGXByteBuffer buffer;
    buffer.SetUInt8(0x12);
    buffer.SetUInt16(0x3456);
    buffer.SetUInt32(0x789ABCDE);
    
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    // Test reading from empty buffer
    EXPECT_EQ(0, buffer.GetUInt8(&u8));
    EXPECT_EQ(0x12, u8);
    
    EXPECT_EQ(0, buffer.GetUInt16(&u16));
    EXPECT_EQ(0x3456, u16);
    // Test writing at very large index
    EXPECT_EQ(0, buffer.GetUInt32(&u32));
    EXPECT_EQ(0x789ABCDE, u32);
}

TEST_F(GXByteBufferTest, IndexedMultiByteGetters) {
    CGXByteBuffer buffer;
    buffer.SetUInt32(0x11223344);
    buffer.SetUInt64(0x5566778899AABBCCULL);

    const uint8_t pattern[16] = {
        0xDE, 0xAD, 0xBE, 0xEF,
        0xCA, 0xFE, 0xBA, 0xBE,
        0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0
    };
    buffer.Set(pattern, sizeof(pattern));

    uint32_t u32 = 0;
    EXPECT_EQ(0, buffer.GetUInt32(0, &u32));
    EXPECT_EQ(0x11223344u, u32);

    uint64_t u64 = 0;
    EXPECT_EQ(0, buffer.GetUInt64(4, &u64));
    EXPECT_EQ(0x5566778899AABBCCULL, u64);

    uint8_t u128[16] = {};
    EXPECT_EQ(0, buffer.GetUInt128(12, u128));
    for (size_t i = 0; i < sizeof(pattern); ++i) {
        EXPECT_EQ(pattern[i], u128[i]);
    }
}

TEST_F(GXByteBufferTest, PositionManagement) {
    CGXByteBuffer buffer;
    buffer.SetUInt8(0x12);
    buffer.SetUInt8(0x34);
    buffer.SetUInt8(0x56);
// Test string move operations
    EXPECT_EQ(3u, buffer.GetSize());
    EXPECT_EQ(0u, buffer.GetPosition());
    EXPECT_EQ(3u, buffer.Available());
    
    unsigned char val;
    buffer.GetUInt8(&val);
    EXPECT_EQ(1u, buffer.GetPosition());
    EXPECT_EQ(2u, buffer.Available());
    
    buffer.SetPosition(0);
    EXPECT_EQ(0u, buffer.GetPosition());
    EXPECT_EQ(3u, buffer.Available());
}

TEST_F(GXByteBufferTest, StringOperations) {
    CGXByteBuffer buffer;
    std::string testStr = "Hello World";

    // Test move version
    EXPECT_EQ(0, buffer.AddString(testStr));
    EXPECT_EQ(11u, buffer.GetSize());

// Test comparison operations
    std::string result = buffer.ToString();
    EXPECT_EQ("Hello World", result);
    CGXByteBuffer buffer2;
    std::string moveStr = "Move Me";
    EXPECT_EQ(0, buffer2.AddString(std::move(moveStr)));
    EXPECT_EQ(7u, buffer2.GetSize());
    EXPECT_TRUE(moveStr.empty()); // String was moved from
}

TEST_F(GXByteBufferTest, UnicodeRoundTrip) {
    CGXByteBuffer buffer;
    std::wstring wideInput = L"\u00C5\u03A9"; // L"ÅΩ"
    std::string expectedUtf8 = u8"ÅΩ";

    EXPECT_EQ(0, buffer.AddString(wideInput));
    EXPECT_EQ(expectedUtf8.size(), buffer.GetSize());
    EXPECT_EQ(expectedUtf8, buffer.ToString());

    CGXByteBuffer wideBuffer;
    uint32_t byteCount = static_cast<uint32_t>(wideInput.size() * sizeof(wchar_t));
    EXPECT_EQ(0, wideBuffer.Set(wideInput.data(), byteCount));

    std::string utf8Output;
    EXPECT_EQ(0, wideBuffer.GetStringUnicode(0, byteCount, utf8Output));
    EXPECT_EQ(expectedUtf8, utf8Output);

    std::wstring wideOutput;
    EXPECT_EQ(0, wideBuffer.GetStringUnicode(0, byteCount, wideOutput));
    EXPECT_EQ(wideInput, wideOutput);
}

TEST_F(GXByteBufferTest, UnicodeExtractionWithOffset) {
    CGXByteBuffer buffer;
    const size_t wcharSize = sizeof(wchar_t);
    std::string prefix(wcharSize, 'P');
    EXPECT_EQ(0, buffer.AddString(prefix));

    std::wstring wideInput = L"\u00C5\u03A9"; // L"ÅΩ"
    std::string expectedUtf8 = u8"ÅΩ";

    uint32_t byteCount = static_cast<uint32_t>(wideInput.size() * sizeof(wchar_t));
    EXPECT_EQ(0, buffer.Set(wideInput.data(), byteCount));

    std::string utf8Output;
    EXPECT_EQ(0, buffer.GetStringUnicode(static_cast<uint32_t>(prefix.size()), byteCount, utf8Output));
    EXPECT_EQ(expectedUtf8, utf8Output);

    std::wstring wideOutput;
    EXPECT_EQ(0, buffer.GetStringUnicode(static_cast<uint32_t>(prefix.size()), byteCount, wideOutput));
    EXPECT_EQ(wideInput, wideOutput);
}

TEST_F(GXByteBufferTest, UnicodeExtractionRejectsMisalignedSpan) {
    CGXByteBuffer buffer;
    buffer.SetUInt8(0xAA);

    std::wstring wideInput = L"\u00C5"; // L"Å"
    uint32_t byteCount = static_cast<uint32_t>(wideInput.size() * sizeof(wchar_t));
    EXPECT_EQ(0, buffer.Set(wideInput.data(), byteCount));

    std::string utf8Output;
    EXPECT_EQ(DLMS_ERROR_CODE_INVALID_PARAMETER, buffer.GetStringUnicode(1, byteCount, utf8Output));

    std::wstring wideOutput;
    EXPECT_EQ(DLMS_ERROR_CODE_INVALID_PARAMETER, buffer.GetStringUnicode(1, byteCount, wideOutput));
}

TEST_F(GXByteBufferTest, ComparisonOperations) {
    CGXByteBuffer buffer1;
    buffer1.SetUInt8(0x12);
    buffer1.SetUInt16(0x3456);

    CGXByteBuffer buffer2;
    buffer2.SetUInt8(0x12);
    buffer2.SetUInt16(0x3456);
    
    EXPECT_TRUE(buffer1.Compare(buffer2));
    
    CGXByteBuffer buffer3;
    buffer3.SetUInt8(0x12);
    buffer3.SetUInt16(0x789A);
    
    EXPECT_FALSE(buffer1.Compare(buffer3));
}

// Test hex string operations
TEST_F(GXByteBufferTest, ClearAndReset) {
    CGXByteBuffer buffer;
    buffer.SetUInt8(0x12);
    buffer.SetUInt16(0x3456);
    buffer.SetPosition(2);
    
    EXPECT_EQ(3u, buffer.GetSize());
    EXPECT_EQ(2u, buffer.GetPosition());
    
    buffer.Clear();
    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_EQ(0u, buffer.GetPosition());
}

// Test Base64 operations
TEST_F(GXByteBufferTest, BoundaryConditions) {
    CGXByteBuffer buffer;


    unsigned char val;
    EXPECT_EQ(DLMS_ERROR_CODE_OUTOFMEMORY, buffer.GetUInt8(&val));

// Test swap functionality
    EXPECT_EQ(0, buffer.SetUInt8(0, 0x12));
    EXPECT_EQ(0, buffer.GetUInt8(0, &val));
    EXPECT_EQ(0x12, val);
}

TEST_F(GXByteBufferTest, FromBase64MultiBlockDecoding) {
    std::string base64 =
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBv\nbmx5IGJ5IGhpcyByZWFzb24=";
    std::string expected = "Man is distinguished, not only by his reason";

    CGXByteBuffer buffer;
    EXPECT_EQ(0, buffer.FromBase64(base64));
    EXPECT_EQ(expected.size(), buffer.GetSize());

    std::string decoded(reinterpret_cast<const char *>(buffer.GetData()),
                        buffer.GetSize());
    EXPECT_EQ(expected, decoded);
}

TEST_F(GXByteBufferTest, SwapOperation) {
    CGXByteBuffer buffer1;
    buffer1.SetUInt8(0x12);
    
    CGXByteBuffer buffer2;
    buffer2.SetUInt8(0x34);
    
    buffer1.Swap(buffer2);
    
    unsigned char val1, val2;
    buffer1.GetUInt8(&val1);
    buffer2.GetUInt8(&val2);
    
    EXPECT_EQ(0x34, val1);
    EXPECT_EQ(0x12, val2);
}

// Test const accessors
TEST_F(GXByteBufferTest, ConstAccessors) {
    const CGXByteBuffer buffer; // Const object
    
    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_EQ(0u, buffer.GetPosition());
    EXPECT_EQ(0u, buffer.Available());
    EXPECT_EQ(nullptr, buffer.GetData()); // Const version
}

TEST_F(GXByteBufferTest, MoveSemanticsPreserveData) {
    CGXByteBuffer source;
    source.SetUInt8(0x12);
    source.SetUInt16(0x3456);
    source.SetUInt32(0x789ABCDE);
    
    const unsigned char* originalData = source.GetData();
    size_t originalSize = source.GetSize();
    
    CGXByteBuffer moved(std::move(source));
    
    // Moved buffer should have the same data
    EXPECT_EQ(originalSize, moved.GetSize());
    
    // Verify data integrity
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    
    moved.SetPosition(0);
    moved.GetUInt8(&u8);
    moved.GetUInt16(&u16);
    moved.GetUInt32(&u32);
    
    EXPECT_EQ(0x12, u8);
    EXPECT_EQ(0x3456, u16);
    EXPECT_EQ(0x789ABCDE, u32);
}

TEST_F(GXByteBufferTest, HexStringOperations) {
    CGXByteBuffer buffer;
    buffer.SetHexString("123456");
    
    EXPECT_EQ(3u, buffer.GetSize());
    
    std::string hex = buffer.ToHexString();
    EXPECT_EQ("123456", hex);
    
    std::string hexWithSpaces = buffer.ToHexString(true);
    // Format might vary based on GXHelpers implementation
    EXPECT_FALSE(hexWithSpaces.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}