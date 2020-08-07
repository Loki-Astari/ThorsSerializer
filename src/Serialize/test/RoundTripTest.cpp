#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/BinaryParserTest.h"
#include "JsonThor.h"
#include "YamlThor.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;


TEST(RoundTripTest, JsonMap)
{   
    using ThorsAnvil::Serialize::PrinterInterface;
    BinaryParserTest::Base                base    { 10, 1024};
    std::stringstream   stream;

    stream << TA::jsonExporter(base, PrinterInterface::OutputType::Stream);

    std::string expected(R"({"ace":10,"val":1024})");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    BinaryParserTest::Base    base2 {};
    stream >> TA::jsonImporter(base2, false);
    EXPECT_EQ(10,   base2.ace);
    EXPECT_EQ(1024, base2.val);
}

TEST(RoundTripTest, JsonParent)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    BinaryParserTest::Derived             deri;
    deri.ace    = 10;
    deri.val    = 1024;
    deri.der    = 56789;
    deri.flt    = 234.875;
    std::stringstream   stream;

    stream << TA::jsonExporter(deri, PrinterInterface::OutputType::Stream);

    std::string expected(R"({"ace":10,"val":1024,"der":56789,"flt":234.875})");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    BinaryParserTest::Derived             deri2 {};
    stream >> TA::jsonImporter(deri2, false);
    EXPECT_EQ(10,       deri2.ace);     // 56789
    EXPECT_EQ(1024,     deri2.val);     // 1131077632
    EXPECT_EQ(56789,    deri2.der);     // 10
    EXPECT_EQ(234.875,  deri2.flt);     // 1.43493e-42
}
TEST(RoundTripTest, JsonArray)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::jsonExporter(data, PrinterInterface::OutputType::Stream);

    std::string expected(R"([10,1024,9,367,12,34])");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    std::vector<int>    data2 {};
    stream >> TA::jsonImporter(data2, false);
    EXPECT_EQ(10,     data2[0]);
    EXPECT_EQ(1024,   data2[1]);
    EXPECT_EQ(9,      data2[2]);
    EXPECT_EQ(367,    data2[3]);
    EXPECT_EQ(12,     data2[4]);
    EXPECT_EQ(34,     data2[5]);
}
TEST(RoundTripTest, JsonValue)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    int                 data = 68456231;
    std::stringstream   stream;

    stream << TA::jsonExporter(data, PrinterInterface::OutputType::Stream);

    std::string expected("68456231");
    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    int                 data2;
    stream >> TA::jsonImporter(data2, false);
    EXPECT_EQ(68456231, data2);
}
#ifdef HAVE_YAML
TEST(RoundTripTest, YamlMap)
{   
    using ThorsAnvil::Serialize::PrinterInterface;
    BinaryParserTest::Base                base    { 10, 1024};
    std::stringstream   stream;

    stream << TA::yamlExporter(base, PrinterInterface::OutputType::Stream);

    std::string expected("--- {ace: 10, val: 1024}\n...\n");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    BinaryParserTest::Base    base2 {};
    stream >> TA::yamlImporter(base2, false);
    EXPECT_EQ(10,   base2.ace);
    EXPECT_EQ(1024, base2.val);
}

TEST(RoundTripTest, YamlParent)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    BinaryParserTest::Derived             deri;
    deri.ace    = 10;
    deri.val    = 1024;
    deri.der    = 56789;
    deri.flt    = 234.875;
    std::stringstream   stream;

    stream << TA::yamlExporter(deri, PrinterInterface::OutputType::Stream);

    std::string expected("--- {ace: 10, val: 1024, der: 56789, flt: 234.875}\n...\n");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    BinaryParserTest::Derived             deri2 {};
    stream >> TA::yamlImporter(deri2, false);
    EXPECT_EQ(10,       deri2.ace);     // 56789
    EXPECT_EQ(1024,     deri2.val);     // 1131077632
    EXPECT_EQ(56789,    deri2.der);     // 10
    EXPECT_EQ(234.875,  deri2.flt);     // 1.43493e-42
}
TEST(RoundTripTest, YamlArray)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::yamlExporter(data, PrinterInterface::OutputType::Stream);

    std::string expected("--- [10, 1024, 9, 367, 12, 34]\n...\n");

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    std::vector<int>    data2 {};
    stream >> TA::yamlImporter(data2, false);
    EXPECT_EQ(10,     data2[0]);
    EXPECT_EQ(1024,   data2[1]);
    EXPECT_EQ(9,      data2[2]);
    EXPECT_EQ(367,    data2[3]);
    EXPECT_EQ(12,     data2[4]);
    EXPECT_EQ(34,     data2[5]);
}
TEST(RoundTripTest, YamlValue)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    int                 data = 68456231;
    std::stringstream   stream;

    stream << TA::yamlExporter(data, PrinterInterface::OutputType::Stream);

    std::string expected("--- 68456231\n...\n");
    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    int                 data2;
    stream >> TA::yamlImporter(data2, false);
    EXPECT_EQ(68456231, data2);
}

#endif
