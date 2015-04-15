#include "../../config.h"

#include "gtest/gtest.h"
#include "test/BinaryParserTest.h"
#include "Binary.h"

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
    EXPECT_EQ(10,   base.ace);
    EXPECT_EQ(1024, base.val);
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
    EXPECT_EQ(10,       deri.ace);
    EXPECT_EQ(1024,     deri.val);
    EXPECT_EQ(56789,    deri.der);
    EXPECT_EQ(234.875,  deri.flt);
}
TEST(RoundTripTest, BinaryArray)
{
    std::vector<int>    data    { 10, 1024, 9, 367, 12, 34};
    std::stringstream   stream;

    stream << TA::binExport(data);

    std::string expected("\x1c\xa2\x7d\xce"     // THash of vector<int>
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
    EXPECT_EQ(10,     data[0]);
    EXPECT_EQ(1024,   data[1]);
    EXPECT_EQ(9,      data[2]);
    EXPECT_EQ(367,    data[3]);
    EXPECT_EQ(12,     data[4]);
    EXPECT_EQ(34,     data[5]);
}
TEST(RoundTripTest, BinaryValue)
{
}
#endif

