
#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "BinaryDecial.h"
#include <limits>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <cmath>

static_assert(CHAR_BIT == 8,                                 "currently supported only CHAR_BIT = 8");
static_assert(std::numeric_limits<float>::radix == 2,        "currently supported only std::numric_limits<float>::radix == 2");
static_assert(std::numeric_limits<double>::radix == 2,       "currently supported only std::numric_limits<double>::radix == 2");
static_assert(std::numeric_limits<long double>::radix == 2,  "currently supported only std::numric_limits<long double>::radix == 2");


/*
  Special cases:
  - +infinity: mantissa = 0x7FFFFFFFFFFFFFFF, exp = 0x7FFF
  - -infinity: mantissa = 0x8000000000000000, exp = 0x7FFF
  - NaN:       mantissa = 0x0000000000000000, exp = 0x7FFF
  - +/-0:      only one zero supported

    Single: -> Sign: 1 bit Exponent: 8 bits  Significand: 24  bits (23 explicitly stored)
    Double: -> Sign: 1 bit Exponent: 11 bits Significand: 53  bits (52 explicitly stored)
    Quad:   -> Sign: 1 bit Exponent: 15 bits Significand: 113 bits (112 explicitly stored)

*/

static constexpr long long    notANumber          = 0x0000000000000000LL;
static constexpr long long    negativeInfinity    = 0x8000000000000000LL;
static constexpr long long    positiveInfinity    = 0x7FFFFFFFFFFFFFFFLL;
static constexpr short        expMarker           = static_cast<short>(0x7FFF);

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>    // T => float/double/long double
inline void writeFloatingPoint(std::ostream& stream, T value)
{
    if (std::isnan(value))
    {
        stream.write(reinterpret_cast<char const*>(&expMarker),  2);
        stream.write(reinterpret_cast<char const*>(&notANumber), 8);
        return;
    }
    if (std::isinf(value))
    {

        long long infinity    = std::signbit(value)
                                    ? negativeInfinity
                                    : positiveInfinity;
        stream.write(reinterpret_cast<char const*>(&expMarker),  2);
        stream.write(reinterpret_cast<char const*>(&infinity),   8);
        return;
    }

    // value = <significant> * 2 ^ <exponent>
    int     exponent;
    double  significant = std::frexp(value, &exponent);
    
    // significant => -0.5  => -1 or 0.5 => 1
    // We can raise significant to the power of n (where n is the number of bits in the float point significant)
    // without overflowing. The result will also be an integer.
    significant      = std::ldexp(significant, std::numeric_limits<T>::digits);
    long long sigInt = std::trunc(significant);
    short     expInt = exponent;

    if ((expInt < std::numeric_limits<T>::min_exponent) || (expInt > std::numeric_limits<T>::max_exponent))
    {
        throw std::runtime_error("FP: Failed to serialize");
    }

    stream.write(reinterpret_cast<char const*>(&expInt), 2);      // 16 it value
    stream.write(reinterpret_cast<char const*>(&sigInt), 8);      // 64 bit value
}

template<typename T>
inline T readFloatingPoint(std::istream& stream)
{
    short       expInt  = 0;
    long long   sigInt  = 0;

    stream.read(reinterpret_cast<char*>(&expInt), 2);
    stream.read(reinterpret_cast<char*>(&sigInt), 8);

    if (expInt == expMarker)
    {
        switch(sigInt)
        {
            case notANumber:        return std::numeric_limits<T>::quiet_NaN();
            case negativeInfinity:  return -1 * std::numeric_limits<T>::infinity();
            case positiveInfinity:  return +1 * std::numeric_limits<T>::infinity();
            default:    throw std::runtime_error("FP: Failed to de-serialize (bad special case)");
        }
    }

    if ((expInt < std::numeric_limits<T>::min_exponent) || (expInt > std::numeric_limits<T>::max_exponent))
    {
        throw std::runtime_error("FP: Failed to de-serialize (bad exponent)");
    }

    T significant   = std::ldexp(sigInt, -std::numeric_limits<T>::digits);
    T value         = std::ldexp(significant, expInt);

    return value;
}
    }
}

template void           ThorsAnvil::Serialize::writeFloatingPoint<float>(std::ostream& stream, float value);
template void           ThorsAnvil::Serialize::writeFloatingPoint<double>(std::ostream& stream, double value);
template void           ThorsAnvil::Serialize::writeFloatingPoint<long double>(std::ostream& stream, long double value);

template float          ThorsAnvil::Serialize::readFloatingPoint<float>(std::istream& stream);
template double         ThorsAnvil::Serialize::readFloatingPoint<double>(std::istream& stream);
template long double    ThorsAnvil::Serialize::readFloatingPoint<long double>(std::istream& stream);

#endif
