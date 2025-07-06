#include "gtest/gtest.h"
#include <cstring>
#include "GXBytebuffer.h" // Assuming this is the correct path relative to include dirs
#include "GXDLMSVariant.h" // For AddString/GetString if they use it, or for general utility

// Test fixture for CGXByteBuffer
class CGXByteBufferTest : public ::testing::Test {
protected:
    CGXByteBuffer bb;
    CGXByteBuffer bb_with_capacity;

    CGXByteBufferTest() : bb_with_capacity(128) {}

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        bb.Clear();
        bb_with_capacity.Clear();
    }

    // void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
    // }
};

TEST_F(CGXByteBufferTest, DefaultConstructor) {
    EXPECT_EQ(bb.GetSize(), 0);
    EXPECT_EQ(bb.GetPosition(), 0);
    // Default capacity might be implementation-defined or small,
    // so not strictly checking it unless it's a guaranteed value.
    // EXPECT_GT(bb.Capacity(), 0);
}

TEST_F(CGXByteBufferTest, ConstructorWithCapacity) {
    // Create a local instance to test the constructor's effect on capacity,
    // as the fixture's bb_with_capacity has Clear() called on it in SetUp(),
    // which resets capacity to 0.
    CGXByteBuffer local_bb_with_capacity(128);
    EXPECT_EQ(local_bb_with_capacity.GetSize(), 0);
    EXPECT_EQ(local_bb_with_capacity.GetPosition(), 0);
    EXPECT_GE(local_bb_with_capacity.Capacity(), 128); // Should be at least what was requested
}

TEST_F(CGXByteBufferTest, SetAndGetUInt8) {
    unsigned char val_in = 0xAB;
    unsigned char val_out = 0;
    bb.SetUInt8(val_in); // This appends to buffer, m_Size becomes 1. m_Position remains 0.
    EXPECT_EQ(bb.GetSize(), 1);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected: SetUInt8(value) should not change position.

    bb.SetPosition(0); // Explicitly set position to 0 for reading.
    bb.GetUInt8(&val_out);
    EXPECT_EQ(val_out, val_in);
    EXPECT_EQ(bb.GetPosition(), 1);
}

TEST_F(CGXByteBufferTest, SetAndGetUInt16) {
    unsigned short val_in = 0xABCD;
    unsigned short val_out = 0;
    bb.SetUInt16(val_in); // This appends to buffer, m_Size becomes 2. m_Position remains 0.
    EXPECT_EQ(bb.GetSize(), 2);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected: SetUInt16(value) should not change position.

    bb.SetPosition(0); // Explicitly set position to 0 for reading.
    bb.GetUInt16(&val_out);
    EXPECT_EQ(val_out, val_in);
    EXPECT_EQ(bb.GetPosition(), 2);
}

TEST_F(CGXByteBufferTest, AddAndGetString) {
    std::string str_in = "Hello, World!";
    std::string str_out;

    bb.AddString(str_in);
    // AddString might add a null terminator or length prefix depending on implementation.
    // Let's assume for now it adds the string and its length is the size.
    // This needs verification against actual CGXByteBuffer::AddString behavior.
    // If it adds a null terminator, size would be str_in.length() + 1
    // If it's length-prefixed, size will be more.
    // For now, let's check if GetString can retrieve it.
    // Actual: AddString(std::string) adds value.length() bytes, no null terminator.
    EXPECT_EQ(bb.GetSize(), str_in.length());
    // Actual: AddString(std::string) does not change m_Position.
    EXPECT_EQ(bb.GetPosition(), 0);

    bb.SetPosition(0); // Set position for subsequent GetString.
    // Assuming GetString reads up to a certain length or null terminator.
    // The GetString signature in GXByteBuffer.h is:
    // int GetString(int count, std::string& value);
    // int GetString(unsigned long index, unsigned long count, std::string& value);
    // We'll use the first one, assuming it reads 'count' characters.
    // The AddString might store length implicitly or explicitly.
    // Let's assume AddString stores the content and GetString needs the length.
    // This part of the test is speculative without knowing AddString's exact behavior.
    // A simple AddString might just append bytes, and GetString might need a count.

    // Re-evaluating: AddString is likely for null-terminated or length-prefixed.
    // Let's test with a known pattern or check source.
    // For now, let's try setting raw bytes and getting them as string.

    bb.Clear();
    const char* c_str_in = "TestStr";
    bb.Set(c_str_in, strlen(c_str_in)); // Set raw bytes without null terminator
    EXPECT_EQ(bb.GetSize(), strlen(c_str_in));
    bb.SetPosition(0);
    int ret = bb.GetString(strlen(c_str_in), str_out);
    EXPECT_EQ(ret, 0); // Assuming 0 is success
    EXPECT_EQ(str_out, c_str_in);
}


TEST_F(CGXByteBufferTest, SizePositionCapacity) {
    EXPECT_EQ(bb.GetSize(), 0);
    EXPECT_EQ(bb.GetPosition(), 0);

    bb.SetUInt8(0x01);
    EXPECT_EQ(bb.GetSize(), 1);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected: SetUInt8 does not change position

    bb.SetUInt16(0x0203);
    EXPECT_EQ(bb.GetSize(), 3); // 1 (from u8) + 2 (from u16)
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected: SetUInt16 does not change position

    unsigned long initial_capacity = bb.Capacity();
    // Grow buffer if needed
    for (int i = 0; i < 200; ++i) {
        bb.SetUInt8( (unsigned char)i); // SetUInt8 does not change position
    }
    EXPECT_EQ(bb.GetSize(), 3 + 200);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected: Position should still be 0
    EXPECT_GE(bb.Capacity(), bb.GetSize());
    EXPECT_GE(bb.Capacity(), initial_capacity); // It should have grown or stayed same
}

TEST_F(CGXByteBufferTest, ToHexString) {
    bb.SetUInt8(0xDE);
    bb.SetUInt8(0xAD);
    bb.SetUInt8(0xBE);
    bb.SetUInt8(0xEF);
    // Default ToHexString might add spaces or not.
    // std::string ToHexString();
    // std::string ToHexString(bool addSpaces);
    // std::string ToHexString(unsigned long position, unsigned long count, bool addSpaces);
    std::string hex_no_space = bb.ToHexString(false);
    EXPECT_EQ(hex_no_space, "DEADBEEF"); // Case might vary, assuming uppercase

    std::string hex_with_space = bb.ToHexString(true);
    EXPECT_EQ(hex_with_space, "DE AD BE EF"); // Case might vary
}

TEST_F(CGXByteBufferTest, Clear) {
    bb.SetUInt32(0x12345678); // SetUInt32 does not change position
    EXPECT_EQ(bb.GetSize(), 4);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected

    bb.Clear();
    EXPECT_EQ(bb.GetSize(), 0);
    EXPECT_EQ(bb.GetPosition(), 0);
    // Capacity should remain or be reset, not strictly testing capacity after clear
    // as it's an optimization detail.
}

TEST_F(CGXByteBufferTest, SetAndGetRawBytes) {
    unsigned char data_in[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    unsigned char data_out[5];

    bb.Set(data_in, 5); // Set(data,count) for appending does not change position
    EXPECT_EQ(bb.GetSize(), 5);
    EXPECT_EQ(bb.GetPosition(), 0); // Corrected

    bb.SetPosition(0); // Explicitly set for read
    int ret = bb.Get(data_out, 5);
    EXPECT_EQ(ret, 0); // Assuming 0 is success
    EXPECT_EQ(bb.GetPosition(), 5); // Get advances position

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(data_out[i], data_in[i]);
    }

    // Test Get with insufficient remaining bytes
    bb.SetPosition(3); // Only 2 bytes remaining (03, 04, 05 -> indices 2,3,4)
                       // Position 3 means data[3] and data[4] are available.
    unsigned char small_out[3];
    ret = bb.Get(small_out, 3); // Try to read 3 bytes
    EXPECT_NE(ret, 0); // Should fail or return error code indicating not enough data
                       // The actual error code depends on implementation (DLMS_ERROR_CODE_OUT_OF_MEMORY, etc.)
                       // For now, just check it's not success.
    // Position might not change or change partially on error, depends on implementation.
}

TEST_F(CGXByteBufferTest, AddStringAndGetCorrectLength) {
    // This test is to clarify AddString behavior based on typical implementations.
    // CGXByteBuffer::AddString(const std::string& value)
    // CGXByteBuffer::AddString(const char* value)
    // These usually add the string including its null terminator.
    std::string test_string = "Gurux";
    bb.AddString(test_string);
    // Library does not append null terminator and position is not moved.
    EXPECT_EQ(bb.GetSize(), test_string.length());
    EXPECT_EQ(bb.GetPosition(), 0u);

    bb.SetPosition(0);
    std::string retrieved_string;
    // GetString(int count, std::string& value)
    // We need to read exactly test_string.length() characters, not including the null.
    int ret = bb.GetString(test_string.length(), retrieved_string);
    EXPECT_EQ(ret, 0); // Success
    EXPECT_EQ(retrieved_string, test_string);
    EXPECT_EQ(bb.GetPosition(), test_string.length());
}

// It would be good to also test error conditions, like reading past the end,
// setting data past capacity if it's not supposed to grow indefinitely (or testing growth).
// The current tests cover basic happy paths.

// Test for SetHexString
TEST_F(CGXByteBufferTest, SetHexString) {
    std::string hex_str = "CAFEBABE";
    bb.SetHexString(hex_str); // Assumes SetHexString2 or similar for std::string
                              // The header has SetHexString(std::string&) and SetHexString2(std::string)
                              // and SetHexString(char*)
    EXPECT_EQ(bb.GetSize(), 4); // 8 hex chars = 4 bytes
    EXPECT_EQ(bb.GetPosition(), 0u);

    bb.SetPosition(0);
    unsigned char val;
    bb.GetUInt8(&val); EXPECT_EQ(val, 0xCA);
    bb.GetUInt8(&val); EXPECT_EQ(val, 0xFE);
    bb.GetUInt8(&val); EXPECT_EQ(val, 0xBA);
    bb.GetUInt8(&val); EXPECT_EQ(val, 0xBE);

    bb.Clear();
    // Test with spaces (if SetHexString handles them, usually it doesn't)
    // The current SetHexString likely expects continuous hex digits.
    // If it should handle spaces, that's another test case.
    // For now, assume it does not.
}

TEST_F(CGXByteBufferTest, AttachString) {
    // char* AttachString(char* value);
    // This is tricky to test safely without knowing memory ownership.
    // It likely takes ownership or copies. Assuming it copies.
    // If it just points, then modifying the original string after attach could be an issue.
    // Let's assume it copies the content up to null terminator.
    char* original_str = strdup("AttachMe");
    bb.AttachString(original_str);
    EXPECT_EQ(bb.GetSize(), strlen("AttachMe"));
    EXPECT_EQ(bb.GetPosition(), 0u);

    bb.SetPosition(0);
    std::string out_str;
    bb.GetString(strlen(original_str), out_str);
    EXPECT_EQ(out_str, original_str);
}

// TODO: Add tests for GetUInt24, GetUInt32, GetInt8, GetInt16, GetInt32, GetInt64, GetUInt64
// TODO: Add tests for float, double
// TODO: Add tests for ToBase64, FromBase64
// TODO: Add tests for SubArray, Move, Reverse

TEST_F(CGXByteBufferTest, GetUInt32) {
    unsigned long val_in = 0xAABBCCDD;
    unsigned long val_out = 0;
    bb.SetUInt32(val_in); // Assumes SetUInt32(unsigned long) exists and works
    EXPECT_EQ(bb.GetSize(), 4);
    EXPECT_EQ(bb.GetPosition(), 0u);

    bb.SetPosition(0);
    bb.GetUInt32(&val_out);
    EXPECT_EQ(val_out, val_in);
    EXPECT_EQ(bb.GetPosition(), 4);
}

TEST_F(CGXByteBufferTest, ZeroFill) {
    bb.SetUInt32(0xFFFFFFFF);
    bb.SetUInt32(0xFFFFFFFF);
    EXPECT_EQ(bb.GetSize(), 8);
    bb.Zero(2, 4); // Zero out 4 bytes starting from index 2
                   // Initial: FF FF FF FF FF FF FF FF
                   // Expected:FF FF 00 00 00 00 FF FF

    bb.SetPosition(0);
    unsigned char byte_val;
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0xFF);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0xFF);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0x00);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0x00);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0x00);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0x00);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0xFF);
    bb.GetUInt8(&byte_val); EXPECT_EQ(byte_val, 0xFF);
}
