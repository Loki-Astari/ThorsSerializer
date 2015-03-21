
#include "gtest/gtest.h"
#include "IntBinRep.h"
#include "TestUtil.h"

using namespace ThorsAnvil::BinaryRep;

TEST(IntBinRepTest, CheckByteOrderOf16)
{
    BinForm16     value   = 0x1234;

    std::string         expected("\x12\x34", 2);
    checkValue(host2Net(value), expected);
}

TEST(IntBinRepTest, CheckByteOrderOf32)
{
    BinForm32     value   = 0x12345678;

    std::string         expected("\x12\x34\x56\x78", 4);
    checkValue(host2Net(value), expected);
}

TEST(IntBinRepTest, CheckByteOrderOf64)
{
    BinForm64     value   = 0x123456789ABCDEF0LL;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 8);
    checkValue(host2Net(value), expected);
}

TEST(IntBinRepTest, CheckByteOrderOf128With64Init)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 16);
    checkValue(host2Net(value), expected);
}

TEST(IntBinRepTest, CheckByteOrderOf128With128Init)
{
    BinForm128     value  = 0x123456789ABCDEF0LL;
    value  <<= 64;
    value   |= 0xF1E2D3C4B5A69780LL;

    std::string expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\xF1\xE2\xD3\xC4\xB5\xA6\x97\x80", 16);
    checkValue(host2Net(value), expected);
}

TEST(IntBinRepTest, CheckByteOrderForHost16)
{
    BinForm16     value   = 0x1234;
    EXPECT_EQ(net2Host(host2Net(value)), value);
}
TEST(IntBinRepTest, CheckByteOrderForHost32)
{
    BinForm32     value   = 0x12345678;
    EXPECT_EQ(net2Host(host2Net(value)), value);
}
TEST(IntBinRepTest, CheckByteOrderForHost64)
{
    BinForm64     value   = 0x123456789ABCDEF0LL;
    EXPECT_EQ(net2Host(host2Net(value)), value);
}

TEST(IntBinRepTest, CheckByteOrderForHost128With64Init)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    EXPECT_EQ(net2Host(host2Net(value)), value);
}

TEST(IntBinRepTest, CheckByteOrderForHost128With128Init)
{
    BinForm128     value  = 0x123456789ABCDEF0LL;
    value  <<= 64;
    value   |= 0xF1E2D3C4B5A69780LL;
    EXPECT_EQ(net2Host(host2Net(value)), value);
}

