#ifndef   THORS_ANVIL_BINARY_REP_FLT_BIN_REP_H
#define   THORS_ANVIL_BINARY_REP_FLT_BIN_REP_H


#include "BinaryFormat.h"
#include "IntBinRep.h"
#include <cmath>
#include <limits>
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
    {   static constexpr BinForm32 value = 0x7f800000ULL;
        return value;
    }
    using StorageType = BinForm32;
};
template<> struct FloatConverterTrait<double>
{
    static  BinForm64  notANumber()
    {   static constexpr BinForm64 value = 0x7FF0000000000000ULL;
        return value;
    }
    using StorageType = BinForm64;
};
template<> struct FloatConverterTrait<long double>
{
    static  BinForm128  notANumber()
    {   static constexpr BinForm128 value = binForm128High(0x7FFF000000000000ULL);
        return value;
    }
    using StorageType = BinForm128;
};

template<typename T>
struct Mixer
{
    typedef typename FloatConverterTrait<T>::StorageType StorageType;

    char        binValue[16];
    void*       getDataArea() {return binValue;}

    StorageType& getStorage() {return *reinterpret_cast<StorageType*>(getDataArea());}
    T&           getFloat()   {return *reinterpret_cast<T*>(getDataArea());}
};

template<typename T, bool ieee = std::numeric_limits<T>::is_iec559, std::size_t size = sizeof(T), std::size_t decimal = std::numeric_limits<T>::digits>
typename FloatConverterTrait<T>::StorageType host2NetIEEE(T value);
template<typename T, bool ieee = std::numeric_limits<T>::is_iec559, std::size_t size = sizeof(T), std::size_t decimal = std::numeric_limits<T>::digits>
T net2HostIEEE(typename FloatConverterTrait<T>::StorageType value);

template<typename T>
typename FloatConverterTrait<T>::StorageType host2NetIEEETransport(T value)
{
    if (std::isnan(value))
    {   return host2Net(FloatConverterTrait<T>::notANumber());
    }
    Mixer<T>         tmp;
    tmp.getFloat()    = value;

    return host2Net(tmp.getStorage());
}
template<typename T>
T net2HostIEEETransport(typename FloatConverterTrait<T>::StorageType value)
{
    static const typename FloatConverterTrait<T>::StorageType notANum    = host2Net(FloatConverterTrait<T>::notANumber());
    if (value == notANum)
    {   return std::numeric_limits<T>::quiet_NaN();
    }
    Mixer<T>    tmp;
    tmp.getStorage() = net2Host(value);

    return tmp.getFloat();
}

template<>  inline BinForm32  host2NetIEEE<float, true, 4, 24>(float value)                 {return host2NetIEEETransport(value);}
template<>  inline BinForm64  host2NetIEEE<double, true, 8, 53>(double value)               {return host2NetIEEETransport(value);}
template<>  inline BinForm128 host2NetIEEE<long double, true, 16, 113>(long double value)   {return host2NetIEEETransport(value);}

template<>  inline float        net2HostIEEE<float, true, 4, 24>(BinForm32 value)           {return net2HostIEEETransport<float>(value);}
template<>  inline double       net2HostIEEE<double, true, 8, 53>(BinForm64 value)          {return net2HostIEEETransport<double>(value);}
template<>  inline long double  net2HostIEEE<long double, true, 16, 113>(BinForm128 value)  {return net2HostIEEETransport<long double>(value);}

template<>  inline BinForm128 host2NetIEEE<long double, true, 16, 64>(long double value)
{
    static BinForm128         expMask     =  binForm128High(0x0000FFFFFFFFFFFFULL) | BinForm128(0xFFFFFFFFFFFFFFFFULL);
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
     *      RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR s eeeeeee eeeeeeee V vvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv
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
    Mixer<long double>  data;
    data.getFloat() = significant;
    BinForm128&        sigBits     = data.getStorage();

    /*
     * Remove the 1 bit representing the integer part of the float (this is not stored in the Quad Version).
     * The extended version uses the bottom 80 bits. So shift it up 48 bits to the top 128.
     * Mask of the exponent mart (so the top 16 bits are reset to zero)
     */
    sigBits <<=  1;
    sigBits <<= 48;
    sigBits &= expMask;


    // But the 3 part together into a single value.
    sigBits |= binForm128High(exp);
    sigBits |= sign;

    return host2Net(sigBits);
}
template<>  inline BinForm128 host2NetIEEE<long double, true, 12, 64>(long double value)
{
    /* If this function is called it means you have an IEEE-754 integer
     * But it is not one of the interchange formats defined in  IEEE 754-2008
     *
     * This means we are using an extended format IEEE-754 (this is non transportable)
     *
     * The size of 64 means you are using IEEE-754 Extended 80 bit floating point format.
     * This function converts from 80 bits to 128 bits.
     */
     return host2NetIEEE<long double, true, 16, 64>(value);
}
template<>  inline long double net2HostIEEE<long double, true, 16, 64>(BinForm128 value)
{
    static BinForm128         expMask     =  binForm128High(0x0000FFFFFFFFFFFFULL) | BinForm128(0xFFFFFFFFFFFFFFFFULL);
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
     *      RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR RRRRRRRR s eeeeeee eeeeeeee V vvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv vvvvvvvv
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
    static const BinForm128 notANum    = host2Net(FloatConverterTrait<long double>::notANumber());
    if (value == notANum)
    {   return std::numeric_limits<long double>::quiet_NaN();
    }
    Mixer<long double>  data;
    BinForm128&  sigBits = data.getStorage();

    sigBits             = net2Host(value);
    bool   negative     = (sigBits >> (128 - 1)) == 0 ? false : true;
    int    exp          = static_cast<unsigned long long int>(sigBits >> (128 - 16) & 0x7FFF);
    exp -= 16383;
    exp += 1;

    sigBits &= expMask;                     // Mask out everything but the significant
    sigBits >>= 48;                         // Move the significant down to correct place

    sigBits >>= 1;                          // This rep has an extra bit represent the integer part
    sigBits |= 0x8000000000000000ULL;       // that is always one so put it back.

    sigBits |= binForm128High(0x3FFE);      // The significant should be just above one so add the
                                            // correct bias to make that happen.

    // Put it all back together.
    long double significant = (negative ? -1 : 1) * data.getFloat();
    long double result      = std::ldexp(significant, exp);

    return result;
}
template<>  inline long double net2HostIEEE<long double, true, 12, 64>(BinForm128 value)
{
    return net2HostIEEE<long double, true, 16,64>(value);
}

    }
}

#endif
