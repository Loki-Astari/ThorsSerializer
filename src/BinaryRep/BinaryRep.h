
#ifndef   THORS_ANVIL_BINARY_REP_BINARY_REP_H
#define   THORS_ANVIL_BINARY_REP_BINARY_REP_H


#include <cmath>
namespace ThorsAnvil
{
    namespace BinaryRep
    {

static_assert(sizeof(short)       * CHAR_BIT <= 16, "Binary interface assumes short       are not larger than 16 bits");
static_assert(sizeof(int)         * CHAR_BIT <= 32, "Binary interface assumes int         are not larger than 32 bits");
static_assert(sizeof(long)        * CHAR_BIT <= 64, "Binary interface assumes long        are not larger than 64 bits");
static_assert(sizeof(long long)   * CHAR_BIT <= 128,"Binary interface assumes long long   are not larger than 128 bits");

static_assert(sizeof(float)       * CHAR_BIT <= 32, "Binary interface assumes float       are not larger than 32  bits");
static_assert(sizeof(double)      * CHAR_BIT <= 64, "Binary interface assumes double      are not larger than 64  bits");
static_assert(sizeof(long double) * CHAR_BIT <= 128, "Binary interface assumes long double are not larger than 128 bits");

static_assert(static_cast<unsigned char>(true)  == '\x01',    "Binary interface assumes true has value of 1");
static_assert(static_cast<unsigned char>(false) == '\x00',    "Binary interface assumes false has value of 0");


typedef     std::uint16_t       UInt16;
typedef     std::uint32_t       UInt32;
typedef     std::uint64_t       UInt64;
#if HAVE_UINT_128
typedef     std::uint128_t      UInt128;
std::uint128_t UInt128High(long long int)    {return value << 64;}
#else
template<int cmp = sizeof(long long int) <= 8>
inline constexpr UInt64 hiWord(long long int value);
template<> inline constexpr UInt64 hiWord<true >(long long int)            {return 0;}
template<> inline constexpr UInt64 hiWord<false>(long long int value)      {return value >> 64;}
           inline constexpr UInt64 loWord(long long int value)             {return value;}

struct UInt128
{
#if WORDS_BIGENDIAN
    UInt64    hi;
    UInt64    lo;
    constexpr UInt128(long long int value)
        : hi(hiWord(value))
        , lo(loWord(value))
    {}
#else
    UInt64    lo;
    UInt64    hi;
    constexpr UInt128(long long int value)
        : lo(loWord(value))
        , hi(hiWord(value))
    {}
#endif
    UInt128  operator<<(std::size_t move)     {UInt128 result(*this); return result <<= move;}
    UInt128& operator<<=(std::size_t move)
    {
        if (move >= 64)
        {
            hi  = lo;
            lo  = 0;
            hi  <<= (move - 64);
        }
        else
        {
            UInt64  overflow    = (lo >> (64 - move));
            lo  <<= move;
            hi  <<= move;
            hi  |= overflow;
        }
        return *this;
    }
    UInt128  operator>>(std::size_t move)     {UInt128 result(*this); return result >>= move;}
    UInt128& operator>>=(std::size_t move)
    {
        if (move >= 64)
        {
            lo  = hi;
            hi  = 0;
            lo  >>= (move - 64);
        }
        else
        {
            UInt64  overflow    = (hi << (64 - move));
            hi  >>= move;
            lo  = (lo >> move) | overflow;
        }
        return *this;
    }
    UInt128  operator|(UInt128 const& value)    {UInt128 result(*this); return result |= value;}
    UInt128& operator|=(UInt128 const& value)
    {
        lo  |= value.lo;
        hi  |= value.hi;
        return *this;
    }
    UInt128  operator&(UInt128 const& value)    {UInt128 result(*this); return result &= value;}
    UInt128& operator&=(UInt128 const& value)
    {
        lo  &= value.lo;
        hi  &= value.hi;
        return *this;
    }
    explicit operator UInt64()
    {
        return lo;
    }
    private:
    friend constexpr UInt128 UInt128High(UInt64 value);
    constexpr UInt128(UInt64 hi, UInt64 lo)
        : hi(hi)
        , lo(lo)
    {}
};
inline constexpr UInt128 UInt128High(UInt64 value)
{
    return UInt128(value, 0LL);
}
#endif
inline UInt64 thor_htobe64(UInt64 value)
{
#if !WORDS_BIGENDIAN
    UInt32*   pointerToValue  = reinterpret_cast<UInt32*>(&value);
    pointerToValue[0]   = htonl(pointerToValue[0]);
    pointerToValue[1]   = htonl(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}
inline UInt128 thor_htobe128(UInt128 value)
{
#if !WORDS_BIGENDIAN
    UInt64*   pointerToValue  = reinterpret_cast<UInt64*>(&value);
    pointerToValue[0]   = thor_htobe64(pointerToValue[0]);
    pointerToValue[1]   = thor_htobe64(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}

template<typename T>
struct FloatConverterTrait;

/*
    Single: -> Sign: 1 bit Exponent: 8 bits  Significand: 24  bits (23 explicitly stored)
    Double: -> Sign: 1 bit Exponent: 11 bits Significand: 53  bits (52 explicitly stored)
    Quad:   -> Sign: 1 bit Exponent: 15 bits Significand: 113 bits (112 explicitly stored)
*/
template<> struct FloatConverterTrait<float>
{
    static  UInt32  notANumber()
    {   static constexpr UInt32 value = 0x7f800000LL;
        return value;
    }
    typedef UInt32 OutputType;
};
template<> struct FloatConverterTrait<double>
{
    static  UInt64  notANumber()
    {   static constexpr UInt64 value = 0x7FF0000000000000LL;
        return value;
    }
    typedef UInt64 OutputType;
};
template<> struct FloatConverterTrait<long double>
{
    static  UInt128  notANumber()
    {   static constexpr UInt128 value = UInt128High(0x7FFF000000000000LL);
        return value;
    }
    typedef UInt128 OutputType;
};

// static constexpr long long    notANumber          = 0x0000000000000000LL;
// static constexpr long long    negativeInfinity    = 0x8000000000000000LL;
// static constexpr long long    positiveInfinity    = 0x7FFFFFFFFFFFFFFFLL;
// static constexpr short        expMarker           = static_cast<short>(0x7FFF);


template<typename T, bool ieee = std::numeric_limits<T>::is_iec559, std::size_t size = sizeof(T), std::size_t decimal = std::numeric_limits<T>::digits>
typename FloatConverterTrait<T>::OutputType convertIEEE(T value);

static_assert(std::numeric_limits<float>::is_iec559,       "Binary interface assumes float       is IEEE754");
template<>  inline UInt32  convertIEEE<float, true, 4, 24>(float value)
{
    if (std::isnan(value))
    {   return FloatConverterTrait<float>::notANumber();
    }
    return *reinterpret_cast<UInt32*>(&value);
}

static_assert(std::numeric_limits<double>::is_iec559,      "Binary interface assumes double      is IEEE754");
template<>  inline UInt64  convertIEEE<double, true, 8, 53>(double value)
{
    if (std::isnan(value))
    {   return FloatConverterTrait<double>::notANumber();
    }
    return *reinterpret_cast<UInt64*>(&value);
}

static_assert(std::numeric_limits<long double>::is_iec559, "Binary interface assumes long double is IEEE754");
template<>  inline UInt128 convertIEEE<long double, true, 16, 113>(long double value)
{
    if (std::isnan(value))
    {   return FloatConverterTrait<long double>::notANumber();
    }
    return *reinterpret_cast<UInt128*>(&value);
}
template<>  inline UInt128 convertIEEE<long double, true, 16, 64>(long double value)
{
    static UInt128         expMask     =  UInt128High(0x0000FFFFFFFFFFFFULL) | UInt128(0xFFFFFFFFFFFFFFFFULL);
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
    {   return FloatConverterTrait<long double>::notANumber();
    }

    /* Split the floating point into a real and an exponent */
    int             exponent;
    long double     significant = std::frexp(value, &exponent);

    // Build the sign bit.
    // Thats bit 127 (1 for negative 0 for positive)
    UInt128         sign        = significant < 0 ? 1 : 0;
    sign <<= 127;

    // Build the exponent bits
    // Max of 15 bits with a boas of 16383 (2^15-1)
    // Bits: 
    UInt64           exp         = exponent & 0x7FFF;   // Make sure we only use 15 bits.
    exp -= 1;                                           // The extended format exponent is one off
    exp += 16383;                                       // Add the bias
    exp <<= (64 - 16);

    /*
     * The long double is 128 bits (though only 80 are currently used).
     * So lets examine it as an integer so that we can manipulate the bits
     * in a more logical way
     */
    UInt128&        sigBits     = *reinterpret_cast<UInt128*>(&significant);

    /*
     * Remove the 1 bit representing the integer part of the float (this is not stored in the Quad Version).
     * The extended version uses the bottom 80 bits. So shift it up 48 bits to the top 128.
     * Mask of the exponent mart (so the top 16 bits are reset to zero)
     */
    sigBits <<=  1;
    sigBits <<= 48;
    sigBits &= expMask;


    // But the 3 part together into a single value.
    sigBits |= UInt128High(exp);
    sigBits |= sign;

    return sigBits;
}

    }
}

#endif

