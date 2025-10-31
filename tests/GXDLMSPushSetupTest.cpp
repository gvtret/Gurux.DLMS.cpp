#include <gtest/gtest.h>
#include "../development/include/GXDLMSPushSetup.h"

class CGXDLMSPushSetupTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // Suppress cout.
        original_buf = std::cout.rdbuf();
        std::cout.rdbuf(nullptr);
    }

    virtual void TearDown() {
        // Restore cout.
        std::cout.rdbuf(original_buf);
    }

private:
    std::streambuf* original_buf;
};

TEST_F(CGXDLMSPushSetupTest, Constructor)
{
    CGXDLMSPushSetup obj1;
    ASSERT_EQ(obj1.GetService(), DLMS_SERVICE_TYPE_TCP);
    ASSERT_EQ(obj1.GetMessageType(), DLMS_MESSAGE_TYPE_COSEM_APDU);

    CGXDLMSPushSetup obj2("0.1.25.9.0.255", 1);
    ASSERT_EQ(obj2.GetService(), DLMS_SERVICE_TYPE_TCP);
    ASSERT_EQ(obj2.GetMessageType(), DLMS_MESSAGE_TYPE_COSEM_APDU);
}

TEST_F(CGXDLMSPushSetupTest, CopyConstructor)
{
    CGXDLMSPushSetup obj1;
    obj1.SetService(DLMS_SERVICE_TYPE_TCP);
    std::string dest = "destination";
    obj1.SetDestination(dest);

    CGXDLMSPushSetup obj2(obj1);
    ASSERT_EQ(obj1.GetService(), obj2.GetService());
    ASSERT_EQ(obj1.GetDestination(), obj2.GetDestination());
}

TEST_F(CGXDLMSPushSetupTest, MoveConstructor)
{
    CGXDLMSPushSetup obj1;
    obj1.SetService(DLMS_SERVICE_TYPE_TCP);
    std::string dest = "destination";
    obj1.SetDestination(dest);

    CGXDLMSPushSetup obj2(std::move(obj1));
    ASSERT_EQ(obj2.GetService(), DLMS_SERVICE_TYPE_TCP);
    ASSERT_EQ(obj2.GetDestination(), "destination");
}

TEST_F(CGXDLMSPushSetupTest, CopyAssignment)
{
    CGXDLMSPushSetup obj1;
    obj1.SetService(DLMS_SERVICE_TYPE_TCP);
    std::string dest = "destination";
    obj1.SetDestination(dest);

    CGXDLMSPushSetup obj2;
    obj2 = obj1;
    ASSERT_EQ(obj1.GetService(), obj2.GetService());
    ASSERT_EQ(obj1.GetDestination(), obj2.GetDestination());
}

TEST_F(CGXDLMSPushSetupTest, MoveAssignment)
{
    CGXDLMSPushSetup obj1;
    obj1.SetService(DLMS_SERVICE_TYPE_TCP);
    std::string dest = "destination";
    obj1.SetDestination(dest);

    CGXDLMSPushSetup obj2;
    obj2 = std::move(obj1);
    ASSERT_EQ(obj2.GetService(), DLMS_SERVICE_TYPE_TCP);
    ASSERT_EQ(obj2.GetDestination(), "destination");
}
