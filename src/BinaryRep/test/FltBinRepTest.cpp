
#include "gtest/gtest.h"
#include "FltBinRep.h"
#include "TestUtil.h"

using namespace ThorsAnvil::BinaryRep;

TEST(FltBinRepTest, FloatConverterTraitFloatNan)
{
    BinForm32      value   = FloatConverterTrait<float>::notANumber();
    std::string expected("\x7F\x80\x00\x00", 4);
    checkValue(host2Net(value), expected);
}
TEST(FltBinRepTest, FloatConverterTraitDoubleNan)
{
    BinForm64      value   = FloatConverterTrait<double>::notANumber();
    std::string expected("\x7F\xF0\x00\x00\x00\x00\x00\x00", 8);
    checkValue(host2Net(value), expected);
}
TEST(FltBinRepTest, FloatConverterTraitLongDoubleNan)
{
    BinForm128     value   = FloatConverterTrait<long double>::notANumber();
    std::string expected("\x7F\xFF\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2Net(value), expected);
}
TEST(FltBinRepTest, convertIEEEFloatNan)
{
    float      value   = std::numeric_limits<float>::quiet_NaN();
    std::string expected("\x7F\x80\x00\x00", 4);
    checkValue(host2NetIEEE(value), expected);
}
TEST(FltBinRepTest, convertIEEEDoubleNan)
{
    double      value   = std::numeric_limits<double>::quiet_NaN();
    std::string expected("\x7F\xF0\x00\x00\x00\x00\x00\x00", 8);
    checkValue(host2NetIEEE(value), expected);
}
TEST(FltBinRepTest, convertIEEELongDoubleNan)
{
    long double     value   = std::numeric_limits<long double>::quiet_NaN();
    std::string expected("\x7F\xFF\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    checkValue(host2NetIEEE(value), expected);
}
TEST(FltBinRepTest, convertIEEEFloat42)
{
    float      value   = 42.0F;
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
    checkValue(host2NetIEEE(value), expected);
}
TEST(FltBinRepTest, convertIEEEDouble165p75)
{
    double      value   = 165.75;
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
    checkValue(host2NetIEEE(value), expected);
}
TEST(FltBinRepTest, convertIEEELongDouble1Million234p875)
{
    long double     value   = 1000234.875L;
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
    checkValue(host2NetIEEE(value), expected);
}

