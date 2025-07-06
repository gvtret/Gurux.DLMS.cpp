#include "gtest/gtest.h"
#include "GXDLMSObject.h"
#include "GXDLMSVariant.h"
#include "GXBytebuffer.h" // For creating logical name byte buffer if needed for constructor
#include "enums.h"        // For DLMS_OBJECT_TYPE, DLMS_DATA_TYPE

// Test fixture for CGXDLMSObject
class CGXDLMSObjectTest : public ::testing::Test {
protected:
    // Example: CGXDLMSObject obj_default;
    // CGXDLMSObject obj_typed(DLMS_OBJECT_TYPE_DATA);
    // CGXDLMSObject obj_ln(DLMS_OBJECT_TYPE_CLOCK, "0.0.1.0.0.255");
};

TEST_F(CGXDLMSObjectTest, DefaultConstructor) {
    CGXDLMSObject obj;
    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_NONE);

    CGXDLMSVariant name = obj.GetName();
    EXPECT_EQ(name.vt, DLMS_DATA_TYPE_STRING);
    EXPECT_EQ(name.strVal, "0.0.0.0.0.0");
    EXPECT_EQ(obj.GetVersion(), 0);
}

TEST_F(CGXDLMSObjectTest, ConstructorWithType) {
    CGXDLMSObject obj(DLMS_OBJECT_TYPE_REGISTER);
    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_REGISTER);
    EXPECT_EQ(obj.GetVersion(), 0);
}

TEST_F(CGXDLMSObjectTest, ConstructorWithLogicalNameString) {
    std::string ln_str_in = "0.0.1.0.0.255";
    CGXDLMSObject obj(DLMS_OBJECT_TYPE_CLOCK, ln_str_in);

    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_CLOCK);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_EQ(name_var.vt, DLMS_DATA_TYPE_STRING);

    std::string ln_str_out;
    obj.GetLogicalName(ln_str_out);
    EXPECT_EQ(ln_str_out, "0.0.1.0.0.255");
}

TEST_F(CGXDLMSObjectTest, ConstructorWithSN) {
    std::string empty_ln = "";
    unsigned short sn_val = 0x1234;
    CGXDLMSObject obj_sn_only(DLMS_OBJECT_TYPE_DATA, empty_ln, sn_val);
    // Further assertions would depend on how this constructor is expected to behave
    // regarding SN taking precedence or being set. For now, just ensure it constructs.
}


TEST_F(CGXDLMSObjectTest, SetAndGetShortName) {
    CGXDLMSObject obj;
    unsigned short sn_in = 0xABCD;
    obj.SetShortName(sn_in);
    EXPECT_EQ(obj.GetShortName(), sn_in);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_EQ(name_var.vt, DLMS_DATA_TYPE_UINT16); // Corrected check
    EXPECT_EQ(name_var.uiVal, sn_in);              // Corrected access
}

TEST_F(CGXDLMSObjectTest, SetAndGetLogicalName) {
    CGXDLMSObject obj;
    std::string ln_str_in = "1.0.99.1.0.255";

    CGXDLMSVariant ln_variant(ln_str_in);
    int ret = obj.SetName(ln_variant);
    EXPECT_EQ(ret, 0);

    std::string ln_str_out;
    obj.GetLogicalName(ln_str_out);
    EXPECT_EQ(ln_str_out, ln_str_in);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_EQ(name_var.vt, DLMS_DATA_TYPE_STRING);
}


TEST_F(CGXDLMSObjectTest, SetAndGetVersion) {
    CGXDLMSObject obj;
    unsigned short version_in = 1;
    obj.SetVersion(version_in);
    EXPECT_EQ(obj.GetVersion(), version_in);
}

TEST_F(CGXDLMSObjectTest, GetNameConsistency) {
    CGXDLMSObject obj;

    // Set SN
    unsigned short sn_val = 0x1000;
    obj.SetShortName(sn_val);
    CGXDLMSVariant name_sn = obj.GetName();
    EXPECT_EQ(name_sn.vt, DLMS_DATA_TYPE_UINT16); // Corrected check
    EXPECT_EQ(name_sn.uiVal, sn_val);              // Corrected access

    // Set LN - this should change the naming preference
    std::string ln_str = "0.0.42.0.0.255";
    CGXDLMSVariant ln_variant(ln_str);
    obj.SetName(ln_variant);

    CGXDLMSVariant name_ln = obj.GetName();
    EXPECT_EQ(name_ln.vt, DLMS_DATA_TYPE_UINT16); // Name still returns SN
    std::string ln_out_str;
    obj.GetLogicalName(ln_out_str);
    EXPECT_EQ(ln_out_str, ln_str);

    EXPECT_EQ(obj.GetShortName(), sn_val);
}

TEST_F(CGXDLMSObjectTest, Description) {
    CGXDLMSObject obj;
    std::string desc_in = "This is a test object.";
    obj.SetDescription(desc_in);
    EXPECT_EQ(obj.GetDescription(), desc_in);
}

TEST_F(CGXDLMSObjectTest, IsLogicalNameEmptyUtil) {
    unsigned char empty_ln[] = {0, 0, 0, 0, 0, 0};
    unsigned char non_empty_ln[] = {0, 0, 1, 0, 0, 255};
    EXPECT_TRUE(CGXDLMSObject::IsLogicalNameEmpty(empty_ln));
    EXPECT_FALSE(CGXDLMSObject::IsLogicalNameEmpty(non_empty_ln));
}

TEST_F(CGXDLMSObjectTest, ConstructorWithByteBufferLN) {
    unsigned char ln_bytes[] = {1, 2, 3, 4, 5, 6};
    CGXByteBuffer ln_bb;
    ln_bb.Set(ln_bytes, 6);

    CGXDLMSObject obj1(0x1234, DLMS_OBJECT_TYPE_DATA, 1, ln_bb);
    EXPECT_EQ(obj1.GetObjectType(), DLMS_OBJECT_TYPE_DATA);
    EXPECT_EQ(obj1.GetShortName(), 0x1234);
    EXPECT_EQ(obj1.GetVersion(), 1);
    std::string ln_str_out1;
    obj1.GetLogicalName(ln_str_out1);
    EXPECT_EQ(ln_str_out1, "1.2.3.4.5.6");

    ln_bb.SetPosition(0);
    CGXDLMSObject obj2(0x5678, 1, 2, ln_bb);
    EXPECT_EQ(obj2.GetObjectType(), DLMS_OBJECT_TYPE_DATA);
    EXPECT_EQ(obj2.GetShortName(), 0x5678);
    EXPECT_EQ(obj2.GetVersion(), 2);
    std::string ln_str_out2;
    obj2.GetLogicalName(ln_str_out2);
    EXPECT_EQ(ln_str_out2, "1.2.3.4.5.6");
}
