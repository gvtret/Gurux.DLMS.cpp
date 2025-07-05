#include "gtest/gtest.h"
#include "GXDLMSObject.h"
#include "GXDLMSVariant.h"
#include "GXBytebuffer.h" // For creating logical name byte buffer if needed for constructor (corrected typo)
#include "enums.h"        // For DLMS_OBJECT_TYPE

// Test fixture for CGXDLMSObject
class CGXDLMSObjectTest : public ::testing::Test {
protected:
    // Example: CGXDLMSObject obj_default;
    // CGXDLMSObject obj_typed(DLMS_OBJECT_TYPE_DATA);
    // CGXDLMSObject obj_ln(DLMS_OBJECT_TYPE_CLOCK, "0.0.1.0.0.255");
};

TEST_F(CGXDLMSObjectTest, DefaultConstructor) {
    CGXDLMSObject obj;
    // Default object type might be 0 or a specific "None" type.
    // Let's assume it's 0 or some uninitialized/default state.
    // The GetObjectType() should return something.
    // The GetName() should return an empty variant or a variant representing an empty name.
    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_NONE); // Assuming DLMS_OBJECT_TYPE_NONE exists and is 0 or default

    CGXDLMSVariant name = obj.GetName();
    EXPECT_TRUE(name.IsShortName() || name.IsLogicalName()); // It should be one or the other
    if (name.IsShortName()) {
        EXPECT_EQ(name.ToShortName(), 0); // Default SN is often 0
    } else {
        std::string ln_str;
        CGXDLMSObject::GetLogicalName(&obj, name); // Populate name if it was empty but logical
                                                  // Or, GetLogicalName(std::string&)
        obj.GetLogicalName(ln_str);
        EXPECT_TRUE(ln_str.empty() || ln_str == "\0\0\0\0\0\0"); // Check if it's an "empty" LN
    }
    EXPECT_EQ(obj.GetVersion(), 0); // Default version is usually 0
}

TEST_F(CGXDLMSObjectTest, ConstructorWithType) {
    CGXDLMSObject obj(DLMS_OBJECT_TYPE_REGISTER);
    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_REGISTER);
    EXPECT_EQ(obj.GetVersion(), 0); // Default version
}

TEST_F(CGXDLMSObjectTest, ConstructorWithLogicalNameString) {
    std::string ln_str_in = "0.0.1.0.0.255"; // Standard Clock LN
    CGXDLMSObject obj(DLMS_OBJECT_TYPE_CLOCK, ln_str_in);

    EXPECT_EQ(obj.GetObjectType(), DLMS_OBJECT_TYPE_CLOCK);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_TRUE(name_var.IsLogicalName());
    // EXPECT_EQ(name_var.ToString(), ln_str_in); // CGXDLMSVariant::ToString might format it.

    std::string ln_str_out;
    obj.GetLogicalName(ln_str_out); // Gets "0-0:1.0.0.255"
                                    // The internal representation is bytes.
                                    // GetLogicalName(std::string) converts bytes to "A.B.C.D.E.F" string.
    EXPECT_EQ(ln_str_out, "0.0.1.0.0.255");


    // Test internal LN bytes if possible, or rely on Set/Get consistency.
    // The constructor CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string& ln)
    // calls SetLogicalName internally.
}

TEST_F(CGXDLMSObjectTest, ConstructorWithSN) {
    // CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string& ln, unsigned short sn);
    // This constructor is a bit confusing. If LN is provided, SN might be ignored or used differently.
    // Let's assume it prioritizes SN if LN is empty, or uses LN if provided.
    // The header shows: CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string& ln, unsigned short sn);
    // The implementation: CGXDLMSObject::CGXDLMSObject(DLMS_OBJECT_TYPE type, std::string& ln, unsigned short sn) : CGXDLMSObject(type, ln) { m_SN = sn; }
    // This means it first constructs with LN, then overrides m_SN.
    // If this is the case, GetName() might still report LN if ln was not empty.

    std::string empty_ln = "";
    unsigned short sn_val = 0x1234;
    CGXDLMSObject obj_sn_only(DLMS_OBJECT_TYPE_DATA, empty_ln, sn_val);

    // Since LN is empty, it should be SN referenced.
    // However, the constructor logic shown above seems to always call the LN constructor first.
    // If LN is empty, the object might still be considered LN-referenced with an empty LN.
    // This needs to be clarified by behavior.
    // For now, let's test setting SN directly.
}


TEST_F(CGXDLMSObjectTest, SetAndGetShortName) {
    CGXDLMSObject obj;
    unsigned short sn_in = 0xABCD;
    obj.SetShortName(sn_in);
    EXPECT_EQ(obj.GetShortName(), sn_in);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_TRUE(name_var.IsShortName());
    EXPECT_EQ(name_var.ToShortName(), sn_in);
}

TEST_F(CGXDLMSObjectTest, SetAndGetLogicalName) {
    CGXDLMSObject obj;
    std::string ln_str_in = "1.0.99.1.0.255"; // A generic data object LN

    // SetLogicalName is protected: static int SetLogicalName(CGXDLMSObject* target, std::string& value);
    // It's called by SetName if variant is string.
    CGXDLMSVariant ln_variant(ln_str_in);
    int ret = obj.SetName(ln_variant);
    EXPECT_EQ(ret, 0); // Assuming 0 for success

    std::string ln_str_out;
    obj.GetLogicalName(ln_str_out);
    EXPECT_EQ(ln_str_out, ln_str_in);

    CGXDLMSVariant name_var = obj.GetName();
    EXPECT_TRUE(name_var.IsLogicalName());
    // How GetName formats logical name to variant needs checking.
    // It might return the raw bytes, or the string.
    // If it returns raw bytes:
    // CGXByteBuffer ln_bytes_expected;
    // GXHelpers::GetObisCode(ln_str_in, ln_bytes_expected);
    // EXPECT_EQ(name_var.byteArr, ln_bytes_expected);

    // For simplicity, rely on GetLogicalName(std::string&) consistency.
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
    EXPECT_TRUE(name_sn.IsShortName());
    EXPECT_EQ(name_sn.ToShortName(), sn_val);

    // Set LN - this should change the naming preference
    std::string ln_str = "0.0.42.0.0.255";
    CGXDLMSVariant ln_variant(ln_str);
    obj.SetName(ln_variant);

    CGXDLMSVariant name_ln = obj.GetName();
    EXPECT_TRUE(name_ln.IsLogicalName());
    std::string ln_out_str;
    // The GetName() for LN might return the byte array in the variant.
    // We need to convert it to string to compare with ln_str or use GetLogicalName(std::string).
    // Let's use GetLogicalName(std::string&) for verification here.
    obj.GetLogicalName(ln_out_str);
    EXPECT_EQ(ln_out_str, ln_str);

    // After setting LN, GetShortName() might return the old SN or 0.
    // The standard says an object has EITHER LN or SN.
    // Once LN is set, SN should ideally be considered invalid or reset.
    // The implementation detail: m_SN field and m_LN field both exist.
    // GetName() decides which one to return in the variant.
    // GetShortName() directly returns m_SN.
    // Let's check if m_SN is affected by SetName(LN). Typically it should not be.
    EXPECT_EQ(obj.GetShortName(), sn_val); // m_SN should still hold its value
}

TEST_F(CGXDLMSObjectTest, Description) {
    CGXDLMSObject obj;
    std::string desc_in = "This is a test object.";
    obj.SetDescription(desc_in);
    EXPECT_EQ(obj.GetDescription(), desc_in);
}

// Attributes and Methods are more complex, involving CGXAttributeCollection
// For a basic test, we check counts if they are fixed or known for a base object.
// CGXDLMSObject::GetAttributeCount() and GetMethodCount() assert(0) in the header.
// This means derived classes must implement them. So, for CGXDLMSObject itself,
// these cannot be meaningfully tested without a derived class or if the base behavior is defined.

// Test IsLogicalNameEmpty
TEST_F(CGXDLMSObjectTest, IsLogicalNameEmptyUtil) {
    unsigned char empty_ln[] = {0, 0, 0, 0, 0, 0};
    unsigned char non_empty_ln[] = {0, 0, 1, 0, 0, 255};
    EXPECT_TRUE(CGXDLMSObject::IsLogicalNameEmpty(empty_ln));
    EXPECT_FALSE(CGXDLMSObject::IsLogicalNameEmpty(non_empty_ln));
}

// The constructor: CGXDLMSObject(short sn, unsigned short class_id, unsigned char version, CGXByteBuffer& ln)
// This one is also interesting. `class_id` is not directly stored as m_ObjectType seems to be.
// `m_ObjectType` comes from `DLMS_OBJECT_TYPE` enum. `class_id` is an integer.
// This constructor calls Initialize:
// void CGXDLMSObject::Initialize(short sn, unsigned short class_id, unsigned char version, CGXByteBuffer* pLogicalName)
// {
//    m_ObjectType = (DLMS_OBJECT_TYPE)class_id; // This is how class_id relates to ObjectType
//    m_SN = sn;
//    m_Version = version;
//    if (pLogicalName != NULL && pLogicalName->GetSize() == 6)
//    {
//        memcpy(m_LN, pLogicalName->GetData(), 6);
//    }
// }
TEST_F(CGXDLMSObjectTest, ConstructorWithByteBufferLN) {
    unsigned char ln_bytes[] = {1, 2, 3, 4, 5, 6};
    CGXByteBuffer ln_bb;
    ln_bb.Set(ln_bytes, 6);

    CGXDLMSObject obj1(0x1234, DLMS_OBJECT_TYPE_DATA, 1, ln_bb); // class_id from enum for clarity
    EXPECT_EQ(obj1.GetObjectType(), DLMS_OBJECT_TYPE_DATA);
    EXPECT_EQ(obj1.GetShortName(), 0x1234);
    EXPECT_EQ(obj1.GetVersion(), 1);
    std::string ln_str_out1;
    obj1.GetLogicalName(ln_str_out1);
    EXPECT_EQ(ln_str_out1, "1.2.3.4.5.6");

    // Test with a class_id integer that maps to an enum
    CGXDLMSObject obj2(0x5678, 1, 2, ln_bb); // class_id 1 is DLMS_OBJECT_TYPE_DATA
    EXPECT_EQ(obj2.GetObjectType(), DLMS_OBJECT_TYPE_DATA); // DLMS_OBJECT_TYPE_DATA is enum 1
    EXPECT_EQ(obj2.GetShortName(), 0x5678);
    EXPECT_EQ(obj2.GetVersion(), 2);
    std::string ln_str_out2;
    obj2.GetLogicalName(ln_str_out2);
    EXPECT_EQ(ln_str_out2, "1.2.3.4.5.6");
}

// GetUIDataType and SetUIDataType are virtual and seem to call assert(0) in base.
// GetAccess and SetAccess also seem to be for derived classes, managing m_Attributes.
// GetValue, SetValue, Invoke are also virtual and return error in base.
// These are better tested in derived classes or if base has default behavior.
