#include <iostream>
#include "../include/GXDLMSMd5.h"
#include "../include/GXDLMSSha1.h"
#include "../include/GXDLMSSha256.h"
#include "../include/GXDLMSSha384.h"

int main()
{
    CGXByteBuffer data;
    data.AddString("test");
    CGXByteBuffer hash;

    CGXDLMSMD5::Encrypt(data, hash);
    if (hash.ToHexString(false) != "098f6bcd4621d373cade4e832627b4f6")
    {
        std::cout << "MD5 test failed!" << std::endl;
        return 1;
    }
    std::cout << "MD5 test passed!" << std::endl;

    hash.Clear();
    CGXDLMSSha1::Encrypt(data, hash);
    if (hash.ToHexString(false) != "a94a8fe5ccb19ba61c4c0873d391e987982fbbd3")
    {
        std::cout << "SHA1 test failed!" << std::endl;
        return 1;
    }
    std::cout << "SHA1 test passed!" << std::endl;

    hash.Clear();
    CGXDLMSSha256::Hash(data, hash);
    if (hash.ToHexString(false) != "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08")
    {
        std::cout << "SHA256 test failed!" << std::endl;
        return 1;
    }
    std::cout << "SHA256 test passed!" << std::endl;

    hash.Clear();
    CGXDLMSSha384::Hash(data, hash);
    if (hash.ToHexString(false) != "768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9")
    {
        std::cout << "SHA384 test failed!" << std::endl;
        return 1;
    }
    std::cout << "SHA384 test passed!" << std::endl;

    return 0;
}
