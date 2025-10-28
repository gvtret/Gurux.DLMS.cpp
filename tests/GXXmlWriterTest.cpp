#include <gtest/gtest.h>
#include "GXXmlWriter.h"
#include <fstream>
#include <sstream>

TEST(CGXXmlWriterTest, WriteXml)
{
    const char* fileName = "test.xml";
    FILE* f = fopen(fileName, "w");
    ASSERT_NE(nullptr, f);

    CGXXmlWriter writer(f, false);
    writer.WriteStartDocument();
    writer.WriteStartElement("root");
    writer.WriteElementString("element", "value");
    writer.WriteEndElement();
    writer.WriteEndDocument();
    fclose(f);

    std::ifstream ifs(fileName);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string content = buffer.str();

    const char* expected = "<?xml version=\"1.0\">\n<root>\n  <element>value</element>\n</root>\n";
    ASSERT_STREQ(expected, content.c_str());

    remove(fileName);
}
