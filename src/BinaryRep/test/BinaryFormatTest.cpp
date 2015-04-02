
#include "gtest/gtest.h"
#include "BinaryFormat.h"
#include "IntBinRep.h"

using namespace ThorsAnvil::BinaryRep;

template<typename T>
void checkValue(T const& value, std::string const& expected);

TEST(BinaryFormatTest, Construct128)
{
    BinForm128  value   = 0xFF; // 16 byte
    EXPECT_EQ(0xFF, static_cast<unsigned long long int>(value));
}

TEST(BinaryFormatTest, Equality128)
{
    BinForm128  value   = 0xFF;
    EXPECT_TRUE(value == 0xFF);
    EXPECT_TRUE(value != 0xFE);
}

TEST(BinaryFormatTest, CheckByteOrderOf128)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value |=  0x9A12BC34DE56F078;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\x9A\x12\xBC\x34\xDE\x56\xF0\x78", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftLeftMoreThan64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 68;

    std::string         expected("\x23\x45\x67\x89\xAB\xCD\xEF\x00"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftLeft64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftLeftLess64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 32;

    std::string         expected("\x00\x00\x00\x00\x12\x34\x56\x78"  "\x9A\xBC\xDE\xF0\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftRightMoreThan64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 68;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftRight64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 64;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, ShiftRightLess64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 32;

    std::string         expected("\x00\x00\x00\x00\x12\x34\x56\x78"  "\x9A\xBC\xDE\xF0\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryFormatTest, BinaryOrLow)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;

    BinForm128     value   = value1 | value2;

    std::string expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\xFC\x3F\x3C\xFF\x3C\xFF\xBE\x7D", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinaryOrHigh)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 64;
    value2 <<= 64; 

    BinForm128     value   = value1 | value2;

    std::string expected("\xFC\x3F\x3C\xFF\x3C\xFF\xBE\x7D"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinaryOrStraddle)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 32;
    value2 <<= 32; 

    BinForm128     value   = value1 | value2;

    std::string expected("\x00\x00\x00\x00\xFC\x3F\x3C\xFF"  "\x3C\xFF\xBE\x7D\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinaryAndLo)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;

    BinForm128     value   = value1 & value2;

    std::string expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x30\x0C\x3C\x00\x00\x3C\x28\x14", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinaryAndHigh)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 64;
    value2 <<= 64;

    BinForm128     value   = value1 & value2;

    std::string expected("\x30\x0C\x3C\x00\x00\x3C\x28\x14"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinaryAndStraddle)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 32;
    value2 <<= 32;

    BinForm128     value   = value1 & value2;

    std::string expected("\x00\x00\x00\x00\x30\x0C\x3C\x00"  "\x00\x3C\x28\x14\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryFormatTest, BinForm128HighCheck)
{
    BinForm128     value  = BinForm128High(0x12345678FFFFFFFFLL);

    std::string expected("\x12\x34\x56\x78\xFF\xFF\xFF\xFF"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

