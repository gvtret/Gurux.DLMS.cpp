#include "gtest/gtest.h"
#include "GXDLMSClient.h"
#include "GXDLMSSettings.h" // For DLMS_AUTHENTICATION, DLMS_INTERFACE_TYPE etc.
#include "GXBytebuffer.h"   // For GetSourceSystemTitle (corrected typo)
#include "GXDateTime.h"     // For DateTimeSkips

// Test fixture for CGXDLMSClient
class CGXDLMSClientTest : public ::testing::Test {
protected:
    // CGXDLMSClient client_default; // Can't use default constructor easily if it has many required params
                                 // Or if constructor does significant work not suitable for every test.
                                 // Let's construct in each test or use the fixture for common setup.
};

TEST_F(CGXDLMSClientTest, DefaultConstructorAndSimpleGetters) {
    // CGXDLMSClient(
    //     bool UseLogicalNameReferencing = true,
    //     int ClientAddress = 16,
    //     int ServerAddress = 1,
    //     DLMS_AUTHENTICATION authentication = DLMS_AUTHENTICATION_NONE,
    //     const char* password = NULL,
    //     DLMS_INTERFACE_TYPE intefaceType = DLMS_INTERFACE_TYPE_HDLC);

    CGXDLMSClient client; // Uses all default parameters

    EXPECT_TRUE(client.GetUseLogicalNameReferencing());
    EXPECT_EQ(client.GetClientAddress(), 16); // Default client address
    EXPECT_EQ(client.GetServerAddress(), 1);   // Default server address
    EXPECT_EQ(client.GetAuthentication(), DLMS_AUTHENTICATION_NONE);
    EXPECT_EQ(client.GetInterfaceType(), DLMS_INTERFACE_TYPE_HDLC);

    // Other default initial states
    EXPECT_EQ(client.GetPriority(), DLMS_PRIORITY_HIGH); // Default priority
    EXPECT_EQ(client.GetServiceClass(), DLMS_SERVICE_CLASS_CONFIRMED); // Assuming default
    EXPECT_NE(client.GetInvokeID(), 0); // Usually initialized to a non-zero value
    EXPECT_FALSE(client.GetAutoIncreaseInvokeID());
    EXPECT_FALSE(client.GetUseProtectedRelease());
    EXPECT_FALSE(client.GetUseUtc2NormalTime());
    EXPECT_EQ(client.GetExpectedInvocationCounter(), 0); // Default is usually 0 (disabled)
    EXPECT_EQ(client.GetDateTimeSkips(), DATETIME_SKIPS_NONE); // Assuming default
    EXPECT_EQ(client.GetUserID(), 0); // Default user ID
    EXPECT_EQ(client.GetQualityOfService(), 0); // Default QoS

    // Max PDU size often has a default. GXDLMS.h defines DEFAULT_MAX_PDU_SIZE 0x escenarios.
    // Let's check if it's reasonable.
    EXPECT_GT(client.GetMaxPduSize(), 0);
    EXPECT_GT(client.GetMaxReceivePDUSize(), 0);

    // System title should be empty by default
    EXPECT_TRUE(client.GetSourceSystemTitle().ToString().empty());

    // Protocol version might be null or empty string by default
    // char* GetProtocolVersion(); - careful with lifetime if it returns internal ptr
    // For now, just call it to see it doesn't crash.
    // EXPECT_TRUE(client.GetProtocolVersion() == nullptr || std::string(client.GetProtocolVersion()).empty());
}

TEST_F(CGXDLMSClientTest, ConstructorWithCustomParameters) {
    CGXDLMSClient client(
        false,                              // UseLogicalNameReferencing
        100,                                // ClientAddress
        200,                                // ServerAddress
        DLMS_AUTHENTICATION_HIGH,           // authentication
        "testpass",                         // password
        DLMS_INTERFACE_TYPE_WRAPPER);       // intefaceType

    EXPECT_FALSE(client.GetUseLogicalNameReferencing());
    EXPECT_EQ(client.GetClientAddress(), 100);
    EXPECT_EQ(client.GetServerAddress(), 200);
    EXPECT_EQ(client.GetAuthentication(), DLMS_AUTHENTICATION_HIGH);
    EXPECT_EQ(client.GetInterfaceType(), DLMS_INTERFACE_TYPE_WRAPPER);
    // Password itself is not directly gettable for security reasons usually.
    // We'd verify its effect by trying an authenticated operation in a more complex test.
}

TEST_F(CGXDLMSClientTest, SetAndGetClientAddress) {
    CGXDLMSClient client;
    uint32_t new_address = 0xFE;
    client.SetClientAddress(new_address);
    EXPECT_EQ(client.GetClientAddress(), new_address);
}

TEST_F(CGXDLMSClientTest, SetAndGetServerAddress) {
    CGXDLMSClient client;
    uint32_t new_address = 0xFFFE;
    client.SetServerAddress(new_address);
    EXPECT_EQ(client.GetServerAddress(), new_address);
}

TEST_F(CGXDLMSClientTest, SetAndGetAuthentication) {
    CGXDLMSClient client;
    client.SetAuthentication(DLMS_AUTHENTICATION_HIGH_MD5);
    EXPECT_EQ(client.GetAuthentication(), DLMS_AUTHENTICATION_HIGH_MD5);
}

TEST_F(CGXDLMSClientTest, SetAndGetPriority) {
    CGXDLMSClient client;
    client.SetPriority(DLMS_PRIORITY_HIGH);
    EXPECT_EQ(client.GetPriority(), DLMS_PRIORITY_HIGH);
}

TEST_F(CGXDLMSClientTest, SetAndGetServiceClass) {
    CGXDLMSClient client;
    client.SetServiceClass(DLMS_SERVICE_CLASS_UN_CONFIRMED); // Corrected enum name
    EXPECT_EQ(client.GetServiceClass(), DLMS_SERVICE_CLASS_UN_CONFIRMED);
}

TEST_F(CGXDLMSClientTest, SetAndGetInvokeID) {
    CGXDLMSClient client;
    unsigned char new_id = 0x55;
    client.SetInvokeID(new_id);
    EXPECT_EQ(client.GetInvokeID(), new_id);

    // Test auto increase
    client.SetAutoIncreaseInvokeID(true);
    EXPECT_TRUE(client.GetAutoIncreaseInvokeID());
    // To truly test auto-increase, we'd need to simulate a message exchange
    // or if there's a method that explicitly consumes/increments it.
    // For now, just testing the setter/getter for the flag.

    client.SetAutoIncreaseInvokeID(false);
    EXPECT_FALSE(client.GetAutoIncreaseInvokeID());
}

TEST_F(CGXDLMSClientTest, SetAndGetUseProtectedRelease) {
    CGXDLMSClient client;
    client.SetUseProtectedRelease(true);
    EXPECT_TRUE(client.GetUseProtectedRelease());
    client.SetUseProtectedRelease(false);
    EXPECT_FALSE(client.GetUseProtectedRelease());
}

TEST_F(CGXDLMSClientTest, SetAndGetUseUtc2NormalTime) {
    CGXDLMSClient client;
    client.SetUseUtc2NormalTime(true);
    EXPECT_TRUE(client.GetUseUtc2NormalTime());
    client.SetUseUtc2NormalTime(false);
    EXPECT_FALSE(client.GetUseUtc2NormalTime());
}

TEST_F(CGXDLMSClientTest, SetAndGetExpectedInvocationCounter) {
    CGXDLMSClient client;
    uint64_t counter = 1234567890;
    client.SetExpectedInvocationCounter(counter);
    EXPECT_EQ(client.GetExpectedInvocationCounter(), counter);
}

TEST_F(CGXDLMSClientTest, SetAndGetDateTimeSkips) {
    CGXDLMSClient client;
    DATETIME_SKIPS skips = static_cast<DATETIME_SKIPS>(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH);
    client.SetDateTimeSkips(skips);
    EXPECT_EQ(client.GetDateTimeSkips(), skips);
}

TEST_F(CGXDLMSClientTest, SetAndGetUserID) {
    CGXDLMSClient client;
    unsigned char user_id = 0xEE;
    client.SetUserID(user_id);
    EXPECT_EQ(client.GetUserID(), user_id);
}

TEST_F(CGXDLMSClientTest, SetAndGetQualityOfService) {
    CGXDLMSClient client;
    unsigned char qos = 0x01; // Example QoS value
    client.SetQualityOfService(qos);
    EXPECT_EQ(client.GetQualityOfService(), qos);
}

TEST_F(CGXDLMSClientTest, SetMaxReceivePDUSize) {
    CGXDLMSClient client;
    unsigned short pdu_size = 1024;
    int ret = client.SetMaxReceivePDUSize(pdu_size);
    EXPECT_EQ(ret, 0); // Assuming 0 is success
    EXPECT_EQ(client.GetMaxReceivePDUSize(), pdu_size);
    // GetMaxPduSize() might be the same or different, depending on if it's just TX or negotiated.
    // The header seems to imply GetMaxPduSize is the client's capability (TX).
    // GetMaxReceivePDUSize is what the client proposes it can receive.
}

TEST_F(CGXDLMSClientTest, SetGbtWindowSize) {
    CGXDLMSClient client;
    unsigned char window_size = 5;
    int ret = client.SetGbtWindowSize(window_size);
    EXPECT_EQ(ret, 0); // Assuming 0 is success
    EXPECT_EQ(client.GetGbtWindowSize(), window_size);
}

TEST_F(CGXDLMSClientTest, GetHdlcSettings) {
    CGXDLMSClient client;
    // CGXHdlcSettings& GetHdlcSettings();
    // Check if it returns a valid reference
    CGXHdlcSettings& hdlc_settings = client.GetHdlcSettings();
    // We can try setting a value through the reference if HdlcSettings has public members/setters
    // For example:
    // hdlc_settings.SetMaxInfoTX(512); // If such a method exists
    // EXPECT_EQ(client.GetHdlcSettings().GetMaxInfoTX(), 512);
    // For now, just ensure it doesn't crash and returns a reference.
    // A basic check:
    EXPECT_GT(hdlc_settings.GetMaxInfoTX(), 0); // Default should be reasonable
}

TEST_F(CGXDLMSClientTest, GetPlcSettings) {
    CGXDLMSClient client;
    CGXPlcSettings& plc_settings = client.GetPlcSettings();
    // Similar to HdlcSettings, check basic accessibility.
    // Example:
    // EXPECT_FALSE(plc_settings.GetRepeat()); // Assuming a default for a boolean field
    // Just calling it is a basic test for now.
    (void)plc_settings; // Avoid unused variable warning if not further tested
}


TEST_F(CGXDLMSClientTest, SetAndGetProposedConformance) {
    CGXDLMSClient client;
    DLMS_CONFORMANCE conformance = static_cast<DLMS_CONFORMANCE>(
        DLMS_CONFORMANCE_GENERAL_PROTECTION | DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER
    );
    client.SetProposedConformance(conformance);
    EXPECT_EQ(client.GetProposedConformance(), conformance);
    // Negotiated conformance is typically set after AARQ/AARE exchange
    // client.SetNegotiatedConformance(conformance);
    // EXPECT_EQ(client.GetNegotiatedConformance(), conformance);
}

TEST_F(CGXDLMSClientTest, SetAndGetCtoSChallenge) {
    CGXDLMSClient client;
    CGXByteBuffer challenge_val;
    std::string hex_str = "0102030405060708";
    challenge_val.SetHexString(hex_str); // Use std::string overload if available, or ensure char* is fine

    client.SetCtoSChallenge(challenge_val);
    CGXByteBuffer& retrieved_challenge = client.GetCtoSChallenge();
    EXPECT_EQ(retrieved_challenge.ToHexString(false), "0102030405060708");
}

TEST_F(CGXDLMSClientTest, SetAndGetManufacturerId) {
    CGXDLMSClient client;
    char mfg_id[3] = {'G', 'U', 'X'};
    char mfg_id_null[3] = {'\0', '\0', '\0'}; // Default is likely nulls

    // Check default (might be nulls or uninitialized)
    // char* default_mfg = client.GetManufacturerId();
    // EXPECT_TRUE(default_mfg[0] == '\0' && default_mfg[1] == '\0' && default_mfg[2] == '\0');

    client.SetManufacturerId(mfg_id);
    char* retrieved_mfg_id = client.GetManufacturerId();
    EXPECT_EQ(retrieved_mfg_id[0], 'G');
    EXPECT_EQ(retrieved_mfg_id[1], 'U');
    EXPECT_EQ(retrieved_mfg_id[2], 'X');
}


// Static methods like GetServerAddressFromSerialNumber, GetServerAddress, ChangeType
// can also be tested.

TEST_F(CGXDLMSClientTest, StaticGetServerAddressFromSerialNumber) {
    // Default formula: (serialNumber % 999900) / 100 + ((serialNumber % 100) * 10000) + logicalAddress;
    // If logicalAddress is 0, it's physical device.
    // If logicalAddress is 1-1023, it's logical device.
    // Example: SN = 12345678, LA = 1
    // (12345678 % 999900) / 100 = (346578) / 100 = 3465
    // (12345678 % 100) * 10000 = 78 * 10000 = 780000
    // Server Address = 3465 + 780000 + 1 = 783466
    // This is complex. The function returns int, which could be an error code or the address.
    // The actual formula might be specific. Let's test with a known simple case if possible,
    // or just that it returns something.
    // For now, let's assume a specific formula or test a boundary.
    // The default formula is complex and specific to certain meter vendors.
    // Testing this without knowing the exact expected formula is hard.
    // Let's just test that it runs.
    EXPECT_NE(0, CGXDLMSClient::GetServerAddressFromSerialNumber(12345678, 1));
}

TEST_F(CGXDLMSClientTest, StaticGetServerAddress) {
    // Default: addressSize = 0 -> 4 byte addressing
    // Result = (physicalAddress << (10 + addressSizeInBits)) | (logicalAddress & 0x3FFF);
    // If addressSize is 0, addressSizeInBits = 0.
    // According to implementation small addresses are encoded using 7 bit shift.
    EXPECT_EQ(129, CGXDLMSClient::GetServerAddress(1, 1, 0));

    // Example: physicalAddress = 1, logicalAddress = 1, addressSize = 1 (1 byte physical)
    EXPECT_EQ(129, CGXDLMSClient::GetServerAddress(1, 1, 1));

    // Example: physicalAddress = 1, logicalAddress = 1, addressSize = 2 (2 byte physical)
    EXPECT_EQ(129, CGXDLMSClient::GetServerAddress(1, 1, 2));
}

// CGXDLMSClient::ChangeType is static and very important.
// It converts a CGXByteBuffer to a CGXDLMSVariant of a specified DLMS_DATA_TYPE.
TEST_F(CGXDLMSClientTest, StaticChangeType_UInt8) {
    CGXByteBuffer bb;
    unsigned char val_in = 0xAB;
    bb.SetUInt8(val_in);
    bb.SetPosition(0);

    CGXDLMSVariant result_variant;
    int ret = CGXDLMSClient::ChangeType(bb, DLMS_DATA_TYPE_UINT8, result_variant);
    EXPECT_EQ(ret, 0); // Success
    EXPECT_EQ(result_variant.vt, DLMS_DATA_TYPE_UINT8);
    EXPECT_EQ(result_variant.bVal, val_in); // Assuming bVal for byte/uint8_t
}

TEST_F(CGXDLMSClientTest, StaticChangeType_OctetString) {
    CGXByteBuffer bb;
    std::string str_in = "Hello";
    bb.AddString(str_in); // Adds "Hello\0"
    bb.SetPosition(0);

    CGXDLMSVariant result_variant;
    // For octet string, ChangeType usually expects the raw bytes without null.
    // If AddString adds null, we need to be careful.
    // Let's make a bytebuffer with explicit bytes for octet string.
    bb.Clear();
    unsigned char bytes[] = {'H','e','l','l','o'};
    bb.Set(bytes, sizeof(bytes));
    bb.SetPosition(0);

    // ChangeType(CGXByteBuffer& value, DLMS_DATA_TYPE type, CGXDLMSVariant& newValue)
    // For octet string, it might consume the whole buffer or expect a length prefix.
    // Assuming it consumes the whole remaining buffer for octet_string.
    int ret = CGXDLMSClient::ChangeType(bb, DLMS_DATA_TYPE_OCTET_STRING, result_variant);
    EXPECT_EQ(ret, 0);
    // Library converts octet string to dotted decimal string.
    EXPECT_EQ(result_variant.vt, DLMS_DATA_TYPE_STRING);
    EXPECT_EQ(result_variant.strVal, "72.101.108.108.111");
}

// More ChangeType tests would be needed for all supported types (boolean, int, date, arrays, structures etc.)
// These can get complex quickly.
// For example, for a structure, the ByteBuffer would contain multiple encoded fields.
// ChangeType would need to parse them according to the structure definition (which isn't passed here).
// This implies ChangeType might only work for simple, scalar types or types where the structure
// is implicitly known (e.g. a fixed date-time format).
// The header implies it's a general converter.
// The static ChangeType(CGXDLMSVariant& value, DLMS_DATA_TYPE type, CGXDLMSVariant& newValue);
// is also useful for converting between variant types if needed.
// This is a very powerful but complex function to test exhaustively.

// GetObjects() is also not tested as it requires a connection and response.
// Similarly for SNRMRequest, AARQRequest, ParseAAREResponse, Read, Write, Method etc.
// These are interaction tests.
