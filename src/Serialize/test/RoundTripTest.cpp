#include "../../config.h"

#include "gtest/gtest.h"
#include "test/BinaryParserTest.h"
#include "BinaryThor.h"
#include "JsonThor.h"
#include "YamlThor.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;


#ifdef NETWORK_BYTE_ORDER
TEST(RoundTripTest, BinaryMap)
{   
    Base                base    { 10, 1024};
    std::stringstream   stream;

    stream << TA::binExport(base);

    std::string expected("\x1c\xa2\x7d\xce"     // THash of Base    \x00\x00
                         "\x00\x00\x00\x0a"     // 10
                         "\x00\x00\x04\x00",    // 1024
                         12);

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Base    base2 {};
    stream >> TA::binImport(base2);
    EXPECT_EQ(10,   base2.ace);
    EXPECT_EQ(1024, base2.val);
}

TEST(RoundTripTest, BinaryParent)
{
    Derived             deri;
    deri.ace    = 10;
    deri.val    = 1024;
    deri.der    = 56789;
    deri.flt    = 234.875;
    std::stringstream   stream;

    stream << TA::binExport(deri);

    std::string expected("\xf1\x21\x74\x88"     // THash of Derived
                         "\x00\x00\x00\x0a"     // 10
                         "\x00\x00\x04\x00"     // 1024
                         "\x00\x00\xdd\xd5"     // 56789
                         "\x43\x6a\xe0\x00",    // 234.875
                         /*
                            Bit Patter of 234.875
                         Sign: 1 bit Exponent: 8 bits Significant: 24  bits (23 explicitly stored)
                         s => 0
                         e => 7 + 127 => 134
                         i => (1) 1101 0101 11
                                s e e e e e e e e i i i i i i i i i i i i i i i i
                         flt => 0|1 0 0 0|0 1 1 0|1 1 0 1|0 1 0 1|1 1 0 0|0......
                                0 1 0 0 - 0 0 1 1 - 0 1 1 0 - 1 0 1 0 - 1 1 1 0 - 0.....
                                43 6a e0 00
                          */
                         20);

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Derived             deri2 {};
    stream >> TA::binImport(deri2);
    EXPECT_EQ(10,       deri2.ace);     // 56789
    EXPECT_EQ(1024,     deri2.val);     // 1131077632
    EXPECT_EQ(56789,    deri2.der);     // 10
    EXPECT_EQ(234.875,  deri2.flt);     // 1.43493e-42
}
TEST(RoundTripTest, BinaryArray)
{
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::binExport(data);

    std::string expected("\xea\xb0\x50\x2f"     // THash of vector<int>
                         "\x00\x00\x00\x06"     // data.size()
                         "\x00\x00\x00\x0a"     // 10
                         "\x00\x00\x04\x00"     // 1024
                         "\x00\x00\x00\x09"     // 9
                         "\x00\x00\x01\x6f"     // 367
                         "\x00\x00\x00\x0c"     // 12
                         "\x00\x00\x00\x22",    // 34
                         32);

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    std::vector<int>    data2 {};
    stream >> TA::binImport(data2);
    EXPECT_EQ(10,     data2[0]);
    EXPECT_EQ(1024,   data2[1]);
    EXPECT_EQ(9,      data2[2]);
    EXPECT_EQ(367,    data2[3]);
    EXPECT_EQ(12,     data2[4]);
    EXPECT_EQ(34,     data2[5]);
}
TEST(RoundTripTest, BinaryValue)
{
    int                 data = 68456231;
    std::stringstream   stream;

    stream << TA::binExport(data);

    std::string expected("\x00\x00\x00\x49" "\x04\x14\x8F\x27", 8);
    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        std::cout << "Loop: " << loop << "   E(" << std::hex << ((int)expected[loop]) << ")  A(" << std::hex << ((int)stream.str()[loop]) << ")\n";
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    int                 data2;
    stream >> TA::binImport(data2);
    EXPECT_EQ(68456231, data2);
}
#endif
TEST(RoundTripTest, JsonMap)
{   
    Base                base    { 10, 1024};
    std::stringstream   stream;

    stream << TA::jsonExport(base, TA::PrinterInterface::OutputType::Stream);

    std::string expected(R"({"ace":10,"val":1024})");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Base    base2 {};
    stream >> TA::jsonImport(base2);
    EXPECT_EQ(10,   base2.ace);
    EXPECT_EQ(1024, base2.val);
}

TEST(RoundTripTest, JsonParent)
{
    Derived             deri;
    deri.ace    = 10;
    deri.val    = 1024;
    deri.der    = 56789;
    deri.flt    = 234.875;
    std::stringstream   stream;

    stream << TA::jsonExport(deri, TA::PrinterInterface::OutputType::Stream);

    std::string expected(R"({"ace":10,"val":1024,"der":56789,"flt":234.875})");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Derived             deri2 {};
    stream >> TA::jsonImport(deri2);
    EXPECT_EQ(10,       deri2.ace);     // 56789
    EXPECT_EQ(1024,     deri2.val);     // 1131077632
    EXPECT_EQ(56789,    deri2.der);     // 10
    EXPECT_EQ(234.875,  deri2.flt);     // 1.43493e-42
}
TEST(RoundTripTest, JsonArray)
{
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::jsonExport(data, TA::PrinterInterface::OutputType::Stream);

    std::string expected(R"([10,1024,9,367,12,34])");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    std::vector<int>    data2 {};
    stream >> TA::jsonImport(data2);
    EXPECT_EQ(10,     data2[0]);
    EXPECT_EQ(1024,   data2[1]);
    EXPECT_EQ(9,      data2[2]);
    EXPECT_EQ(367,    data2[3]);
    EXPECT_EQ(12,     data2[4]);
    EXPECT_EQ(34,     data2[5]);
}
TEST(RoundTripTest, JsonValue)
{
    int                 data = 68456231;
    std::stringstream   stream;

    stream << TA::jsonExport(data, TA::PrinterInterface::OutputType::Stream);

    std::string expected("68456231");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";
    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        std::cout << "Loop: " << loop << "   E(" << std::hex << ((int)expected[loop]) << ")  A(" << std::hex << ((int)stream.str()[loop]) << ")\n";
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    int                 data2;
    stream >> TA::jsonImport(data2);
    EXPECT_EQ(68456231, data2);
}
#ifdef HAVE_YAML
TEST(RoundTripTest, YamlMap)
{   
    Base                base    { 10, 1024};
    std::stringstream   stream;

    stream << TA::yamlExport(base, TA::PrinterInterface::OutputType::Stream);

    std::string expected("--- {ace: 10, val: 1024}\n...\n");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Base    base2 {};
    stream >> TA::yamlImport(base2);
    EXPECT_EQ(10,   base2.ace);
    EXPECT_EQ(1024, base2.val);
}

TEST(RoundTripTest, YamlParent)
{
    Derived             deri;
    deri.ace    = 10;
    deri.val    = 1024;
    deri.der    = 56789;
    deri.flt    = 234.875;
    std::stringstream   stream;

    stream << TA::yamlExport(deri, TA::PrinterInterface::OutputType::Stream);

    std::string expected("--- {ace: 10, val: 1024, der: 56789, flt: 234.875}\n...\n");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    Derived             deri2 {};
    stream >> TA::yamlImport(deri2);
    EXPECT_EQ(10,       deri2.ace);     // 56789
    EXPECT_EQ(1024,     deri2.val);     // 1131077632
    EXPECT_EQ(56789,    deri2.der);     // 10
    EXPECT_EQ(234.875,  deri2.flt);     // 1.43493e-42
}
TEST(RoundTripTest, YamlArray)
{
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::yamlExport(data, TA::PrinterInterface::OutputType::Stream);

    std::string expected("--- [10, 1024, 9, 367, 12, 34]\n...\n");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";

    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    std::vector<int>    data2 {};
    stream >> TA::yamlImport(data2);
    EXPECT_EQ(10,     data2[0]);
    EXPECT_EQ(1024,   data2[1]);
    EXPECT_EQ(9,      data2[2]);
    EXPECT_EQ(367,    data2[3]);
    EXPECT_EQ(12,     data2[4]);
    EXPECT_EQ(34,     data2[5]);
}
TEST(RoundTripTest, YamlValue)
{
    int                 data = 68456231;
    std::stringstream   stream;

    stream << TA::yamlExport(data, TA::PrinterInterface::OutputType::Stream);

    std::string expected("--- 68456231\n...\n");
    std::cout << "EX: " << expected << "\n"
              << "AX: " << stream.str() << "\n";
    EXPECT_EQ(expected.size(), stream.str().size());
    for(int loop =0;loop < expected.size(); ++loop)
    {
        std::cout << "Loop: " << loop << "   E(" << std::hex << ((int)expected[loop]) << ")  A(" << std::hex << ((int)stream.str()[loop]) << ")\n";
        EXPECT_EQ(expected[loop], stream.str()[loop]);
    }

    int                 data2;
    stream >> TA::yamlImport(data2);
    EXPECT_EQ(68456231, data2);
}

#endif
