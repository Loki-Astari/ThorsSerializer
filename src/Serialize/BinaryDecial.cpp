
#include <limits>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <climits>
#include <cstdint>
#include <cfloat>
#include <cmath>

static_assert(CHAR_BIT == 8,                                "currently supported only CHAR_BIT = 8");
static_assert(std::numeric_limits<float>::radix == 2,        "currently supported only std::numric_limits<float>::radix == 2");
static_assert(std::numeric_limits<double>::radix == 2,       "currently supported only std::numric_limits<double>::radix == 2");
static_assert(std::numeric_limits<long double>::radix == 2,  "currently supported only std::numric_limits<long double>::radix == 2");


/*
  Special cases:
  - +infinity: mantissa = 0x7FFFFFFFFFFFFFFF, exp = 0x7FFF
  - -infinity: mantissa = 0x8000000000000000, exp = 0x7FFF
  - NaN:       mantissa = 0x0000000000000000, exp = 0x7FFF
  - +/-0:      only one zero supported
*/

static constexpr long long    notANumber          = 0x0000000000000000LL;
static constexpr long long    negativeInfinity    = 0x8000000000000000LL;
static constexpr long long    positiveInfinity    = 0x7FFFFFFFFFFFFFFFLL;
static constexpr short        expMarker           = static_cast<short>(0x7FFF);

template<typename T>    // T => float/double/long double
void Double2Bytes(std::ostream& stream, T value)
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
T Bytes2Double(std::istream& stream)
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

int main()
{
    std::stringstream       stream;
    double result;
    
    Double2Bytes(stream, 0);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, +DBL_MIN);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, -DBL_MIN);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, +1.0);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, -1.0);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, +3.14159269);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, -3.14159269);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, +DBL_MAX);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, -DBL_MAX);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, +INFINITY);
    result = Bytes2Double<double>(stream);

    Double2Bytes(stream, -INFINITY);
    result = Bytes2Double<double>(stream);


    std::cout << "float DIGITS:  " << std::numeric_limits<float>::digits << "\n";
    std::cout << "double DIGITS:  " << std::numeric_limits<double>::digits << "\n";
    std::cout << "long double DIGITS:  " << std::numeric_limits<long double>::digits << "\n";
    return 0;
}
