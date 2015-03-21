
#include "gtest/gtest.h"
#include "BinaryRep.h"

using namespace ThorsAnvil::BinaryRep;

template<typename T>
void checkValue(T const& value, std::string const& expected)
{
    std::stringstream   stream;
    stream.write(reinterpret_cast<char const*>(&value), sizeof(T));

    std::string         result(sizeof(T), '\x00');
    stream.read(&result[0], sizeof(T));

    EXPECT_EQ(sizeof(T), expected.size());

    for(int loop = 0;loop < expected.size(); ++loop)
    {   EXPECT_EQ(expected[loop], result[loop]);
    }
}

TEST(BinaryRepTest, CheckByteOrderOf64)
{
    BinForm64     value   = 0x123456789ABCDEF0LL;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 8);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, CheckByteOrderOf128With64Init)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, CheckByteOrderOf128)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value |=  0x9A12BC34DE56F078;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\x9A\x12\xBC\x34\xDE\x56\xF0\x78", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftLeftMoreThan64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 68;

    std::string         expected("\x23\x45\x67\x89\xAB\xCD\xEF\x00"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftLeft64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;

    std::string         expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftLeftLess64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 32;

    std::string         expected("\x00\x00\x00\x00\x12\x34\x56\x78"  "\x9A\xBC\xDE\xF0\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftRightMoreThan64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 68;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x01\x23\x45\x67\x89\xAB\xCD\xEF", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftRight64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 64;

    std::string         expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x12\x34\x56\x78\x9A\xBC\xDE\xF0", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, ShiftRightLess64)
{
    BinForm128     value   = 0x123456789ABCDEF0LL;
    value <<= 64;
    value >>= 32;

    std::string         expected("\x00\x00\x00\x00\x12\x34\x56\x78"  "\x9A\xBC\xDE\xF0\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}

TEST(BinaryRepTest, BinaryOrLow)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;

    BinForm128     value   = value1 | value2;

    std::string expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\xFC\x3F\x3C\xFF\x3C\xFF\xBE\x7D", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinaryOrHigh)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 64;
    value2 <<= 64; 

    BinForm128     value   = value1 | value2;

    std::string expected("\xFC\x3F\x3C\xFF\x3C\xFF\xBE\x7D"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinaryOrStraddle)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 32;
    value2 <<= 32; 

    BinForm128     value   = value1 | value2;

    std::string expected("\x00\x00\x00\x00\xFC\x3F\x3C\xFF"  "\x3C\xFF\xBE\x7D\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinaryAndLo)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;

    BinForm128     value   = value1 & value2;

    std::string expected("\x00\x00\x00\x00\x00\x00\x00\x00"  "\x30\x0C\x3C\x00\x00\x3C\x28\x14", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinaryAndHigh)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 64;
    value2 <<= 64;

    BinForm128     value   = value1 & value2;

    std::string expected("\x30\x0C\x3C\x00\x00\x3C\x28\x14"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinaryAndStraddle)
{
    BinForm128     value1  = 0x3C3C3C3C3C3C3C3CLL;
    BinForm128     value2  = 0xF00F3CC300FFAA55LL;
    value1 <<= 32;
    value2 <<= 32;

    BinForm128     value   = value1 & value2;

    std::string expected("\x00\x00\x00\x00\x30\x0C\x3C\x00"  "\x00\x3C\x28\x14\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BinForm128HighCheck)
{
    BinForm128     value  = BinForm128High(0x12345678FFFFFFFFLL);

    std::string expected("\x12\x34\x56\x78\xFF\xFF\xFF\xFF"  "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(BinaryRepTest, BigEndianOrder)
{
    BinForm128     value1 = 0x123456789ABCDEF0LL;
    value1 <<= 64;
    value1  |= 0xF1E2D3C4B5A69780LL;

    BinForm128     value  = host2Net(value1);
    std::string expected("\x12\x34\x56\x78\x9A\xBC\xDE\xF0"  "\xF1\xE2\xD3\xC4\xB5\xA6\x97\x80", 16);
    checkValue(value, expected);
}
TEST(BinaryRepTest, FloatConverterTraitFloatNan)
{
    BinForm32      value   = host2Net(FloatConverterTrait<float>::notANumber());
    std::string expected("\x7F\x80\x00\x00", 4);
    checkValue(value, expected);
}
TEST(BinaryRepTest, FloatConverterTraitDoubleNan)
{
    BinForm64      value   = host2Net(FloatConverterTrait<double>::notANumber());
    std::string expected("\x7F\xF0\x00\x00\x00\x00\x00\x00", 8);
    checkValue(value, expected);
}
TEST(BinaryRepTest, FloatConverterTraitLongDoubleNan)
{
    BinForm128     value   = host2Net(FloatConverterTrait<long double>::notANumber());
    std::string expected("\x7F\xFF\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEEFloatNan)
{
    BinForm32      value   = host2Net(convertIEEE(std::numeric_limits<float>::quiet_NaN()));
    std::string expected("\x7F\x80\x00\x00", 4);
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEEDoubleNan)
{
    BinForm64      value   = host2Net(convertIEEE(std::numeric_limits<double>::quiet_NaN()));
    std::string expected("\x7F\xF0\x00\x00\x00\x00\x00\x00", 8);
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEELongDoubleNan)
{
    BinForm128     value   = host2Net(convertIEEE(std::numeric_limits<long double>::quiet_NaN()));
    std::string expected("\x7F\xFF\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEEFloat42)
{
    BinForm32      value   = host2Net(convertIEEE(42.0F));
    std::string expected("\x42\x28\x00\x00", 4);
    // http://en.wikipedia.org/wiki/Single-precision_floating-point_format#mediaviewer/File:Float_example.svg
    // S-EEE EEEE E-DDD DDDD DDDD DDDD DDDD DDDD
    // 0 100 0010 0 010 1000 0000 0000 0000 0000
    //
    // S = 0
    // E = 1000 0100 => 4 + 128 = 132 (Bias 127)    => 5
    // S = .0101         (Integer part is implied)  => 1.0101
    // Value = 1.0101 * 2^5 => 101010
    //                      => 32 + 8 + 2
    //                      => 42 :-)
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEEDouble165p75)
{
    BinForm64      value   = host2Net(convertIEEE(165.75));
    std::string expected("\x40\x64\xB8\x00\x00\x00\x00\x00", 8);
    // http://en.wikipedia.org/wiki/Double-precision_floating-point_format#mediaviewer/File:IEEE_754_Double_Floating_Point_Format.svg
    // S-EEE EEEE EEEE DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD
    // 0 100 0000 0110 0100 1011 1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    //
    // S = 0
    // E = 100 0000 0110  => 2 + 4 + 1024 => 1030 (Bias 1023) =>    7
    // S = .010010111        (Integer part implied) => 1.010010111
    // Value = 1.010010111 * 2^7 => 10100101.11
    //                           => 128 + 32 + 4 + 1 + (1/2) + (1/4)
    //                           => 165.75 :-)
    checkValue(value, expected);
}
TEST(BinaryRepTest, convertIEEELongDouble1Million234p875)
{
    BinForm128     value   = host2Net(convertIEEE(1000234.875L));
    std::string expected("\x40\x12\xE8\x65\x5C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    // http://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format#mediaviewer/File:IEEE_754_Quadruple_Floating_Point_Format.svg
    // S-EEE EEEE EEEE EEEE DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD DDDD
    // 0 100 0000 0001 0010 1110 1000 0110 0101 0101 1100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    //
    // S = 0
    // E = 100 0000 0001 0010 => 2 + 16 + 16384 => 16402 (Bias 16383) => 19
    // S = .1110 1000 0110 0101 0101 1100 (Integer part implied) => 1.1110 1000 0110 0101 0101 1100
    // Value = 1.1110 1000 0110 0101 0101 1100 * 2^11 => 1111 0100 0011 0010 1010 .1110
    //                                                => 524288 + 262144 + 131072 + 65536 + 16384 + 512 + 256 + 32 + 8 + 2 + 1/2 + 1/4 + 1/8
    //                                                => 1000234.875
    checkValue(value, expected);
}

