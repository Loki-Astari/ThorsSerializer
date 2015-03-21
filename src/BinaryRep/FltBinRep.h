
#ifndef   THORS_ANVIL_BINARY_REP_FLT_BIN_REP_H
#define   THORS_ANVIL_BINARY_REP_FLT_BIN_REP_H


#include <cmath>
#include "BinaryFormat.h"
#include "IntBinRep.h"
namespace ThorsAnvil
{
    namespace BinaryRep
    {

template<typename T>
struct FloatConverterTrait;

/*
    Single: -> Sign: 1 bit Exponent: 8 bits  Significand: 24  bits (23 explicitly stored)
    Double: -> Sign: 1 bit Exponent: 11 bits Significand: 53  bits (52 explicitly stored)
    Quad:   -> Sign: 1 bit Exponent: 15 bits Significand: 113 bits (112 explicitly stored)
*/
template<> struct FloatConverterTrait<float>
{
    static  BinForm32  notANumber()
    {   static constexpr BinForm32 value = 0x7f800000LL;
        return value;
    }
    typedef BinForm32 OutputType;
};
template<> struct FloatConverterTrait<double>
{
    static  BinForm64  notANumber()
    {   static constexpr BinForm64 value = 0x7FF0000000000000LL;
        return value;
    }
    typedef BinForm64 OutputType;
};
template<> struct FloatConverterTrait<long double>
{
    static  BinForm128  notANumber()
    {   static constexpr BinForm128 value = BinForm128High(0x7FFF000000000000LL);
        return value;
    }
    typedef BinForm128 OutputType;
};

// static constexpr long long    notANumber          = 0x0000000000000000LL;
// static constexpr long long    negativeInfinity    = 0x8000000000000000LL;
// static constexpr long long    positiveInfinity    = 0x7FFFFFFFFFFFFFFFLL;
// static constexpr short        expMarker           = static_cast<short>(0x7FFF);


template<typename T, bool ieee = std::numeric_limits<T>::is_iec559, std::size_t size = sizeof(T), std::size_t decimal = std::numeric_limits<T>::digits>
typename FloatConverterTrait<T>::OutputType convertIEEE(T value);

static_assert(std::numeric_limits<float>::is_iec559,       "Binary interface assumes float       is IEEE754");
template<>  inline BinForm32  convertIEEE<float, true, 4, 24>(float value)
{
    if (std::isnan(value))
    {   return host2Net(FloatConverterTrait<float>::notANumber());
    }
    return host2Net(*reinterpret_cast<BinForm32*>(&value));
}

static_assert(std::numeric_limits<double>::is_iec559,      "Binary interface assumes double      is IEEE754");
template<>  inline BinForm64  convertIEEE<double, true, 8, 53>(double value)
{
    if (std::isnan(value))
    {   return host2Net(FloatConverterTrait<double>::notANumber());
    }
    return host2Net(*reinterpret_cast<BinForm64*>(&value));
}

static_assert(std::numeric_limits<long double>::is_iec559, "Binary interface assumes long double is IEEE754");
template<>  inline BinForm128 convertIEEE<long double, true, 16, 113>(long double value)
{
    if (std::isnan(value))
    {   return host2Net(FloatConverterTrait<long double>::notANumber());
    }
    return host2Net(*reinterpret_cast<BinForm128*>(&value));
}
template<>  inline BinForm128 convertIEEE<long double, true, 16, 64>(long double value)
{
    static BinForm128         expMask     =  BinForm128High(0x0000FFFFFFFFFFFFULL) | BinForm128(0xFFFFFFFFFFFFFFFFULL);
    /* If this function is called it means you have an IEEE-754 integer
     * But it is not one of the interchange formats defined in  IEEE 754-2008
     *
     * This means we are using an extended format IEEE-754 (this is non transportable)
     *
     * The size of 64 means you are using IEEE-754 Extended 80 bit floating point format.
     * This function converts from 80 bits to 128 bits.
     *
     *  http://en.wikipedia.org/wiki/Extended_precision
     *  80 bit Extended Format:
     *      s eeeee eeeeeeeeee V vvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR 
     *          s:      1   Sign Bit
     *          e:     15   exponent
     *          V:      1   integer part of significant
     *          v:     63   fraction part of significant
     *          R:     48   Random junk on the end of the word
     *
     * http://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
     * 128 bit Quad format binary128
     *      s eeeee eeeeeeeeee vv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv
     *          s:      1   Sign Bit
     *          e:     15   exponent
     *          v:    112   fraction part of significant
     *
     *      Note: The Extended format uses an integer bit that is implied by the Quad precision value.
     *
     */
    if (std::isnan(value))
    {   return host2Net(FloatConverterTrait<long double>::notANumber());
    }

    /* Split the floating point into a real and an exponent */
    int             exponent;
    long double     significant = std::frexp(value, &exponent);

    // Build the sign bit.
    // Thats bit 127 (1 for negative 0 for positive)
    BinForm128         sign        = significant < 0 ? 1 : 0;
    sign <<= 127;

    // Build the exponent bits
    // Max of 15 bits with a boas of 16383 (2^15-1)
    // Bits: 
    BinForm64           exp         = exponent & 0x7FFF;   // Make sure we only use 15 bits.
    exp -= 1;                                           // The extended format exponent is one off
    exp += 16383;                                       // Add the bias
    exp <<= (64 - 16);

    /*
     * The long double is 128 bits (though only 80 are currently used).
     * So lets examine it as an integer so that we can manipulate the bits
     * in a more logical way
     */
    BinForm128&        sigBits     = *reinterpret_cast<BinForm128*>(&significant);

    /*
     * Remove the 1 bit representing the integer part of the float (this is not stored in the Quad Version).
     * The extended version uses the bottom 80 bits. So shift it up 48 bits to the top 128.
     * Mask of the exponent mart (so the top 16 bits are reset to zero)
     */
    sigBits <<=  1;
    sigBits <<= 48;
    sigBits &= expMask;


    // But the 3 part together into a single value.
    sigBits |= BinForm128High(exp);
    sigBits |= sign;

    return host2Net(sigBits);
}

    }
}

#endif

