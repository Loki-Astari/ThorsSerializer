
#ifndef   THORS_ANVIL_BINARY_REP_BINARY_FORMAT_H
#define   THORS_ANVIL_BINARY_REP_BINARY_FORMAT_H

/*
 *  We want to represent up to 128 bit values.
 *
 *  The standard already supports 16/32/64 byte values.
 *  We also need a 128 bit values so if required BinForm is defined as a class.
 *
 *  It supports only enough methods to do basic bit manipulation; it is not intended to be an all purpose
 *  unsigned integer class. It is supposed to be used as a bit object that can be serialized and de serialized
 *  with the help of functions provided in IntBinReph and FltBinRep.h
 */


#include <cmath>
namespace ThorsAnvil
{
    namespace BinaryRep
    {

typedef     std::uint16_t       BinForm16;
typedef     std::uint32_t       BinForm32;
typedef     std::uint64_t       BinForm64;
#if HAVE_UINT_128
typedef     std::uint128_t      BinForm128;
std::uint128_t BinForm128High(long long int)    {return value << 64;}
#else
template<int cmp = sizeof(long long int) <= 8>
inline constexpr BinForm64 hiWord(long long int value);
template<> inline constexpr BinForm64 hiWord<true >(long long int)            {return 0;}
template<> inline constexpr BinForm64 hiWord<false>(long long int value)      {return value >> 64;}
           inline constexpr BinForm64 loWord(long long int value)             {return value;}

struct BinForm128
{
#if WORDS_BIGENDIAN
    BinForm64    hi;
    BinForm64    lo;
    constexpr BinForm128(long long int value)
        : hi(hiWord(value))
        , lo(loWord(value))
    {}
#else
    BinForm64    lo;
    BinForm64    hi;
    constexpr BinForm128(long long int value)
        : lo(loWord(value))
        , hi(hiWord(value))
    {}
#endif
    BinForm128  operator<<(std::size_t move)     {BinForm128 result(*this); return result <<= move;}
    BinForm128& operator<<=(std::size_t move)
    {
        if (move >= 64)
        {
            hi  = lo;
            lo  = 0;
            hi  <<= (move - 64);
        }
        else
        {
            BinForm64  overflow    = (lo >> (64 - move));
            lo  <<= move;
            hi  <<= move;
            hi  |= overflow;
        }
        return *this;
    }
    BinForm128  operator>>(std::size_t move)     {BinForm128 result(*this); return result >>= move;}
    BinForm128& operator>>=(std::size_t move)
    {
        if (move >= 64)
        {
            lo  = hi;
            hi  = 0;
            lo  >>= (move - 64);
        }
        else
        {
            BinForm64  overflow    = (hi << (64 - move));
            hi  >>= move;
            lo  = (lo >> move) | overflow;
        }
        return *this;
    }
    BinForm128  operator|(BinForm128 const& value)    {BinForm128 result(*this); return result |= value;}
    BinForm128& operator|=(BinForm128 const& value)
    {
        lo  |= value.lo;
        hi  |= value.hi;
        return *this;
    }
    BinForm128  operator&(BinForm128 const& value)    {BinForm128 result(*this); return result &= value;}
    BinForm128& operator&=(BinForm128 const& value)
    {
        lo  &= value.lo;
        hi  &= value.hi;
        return *this;
    }
    explicit operator BinForm64()
    {
        return lo;
    }
    private:
    friend constexpr BinForm128 BinForm128High(BinForm64 value);
    constexpr BinForm128(BinForm64 hi, BinForm64 lo)
        : hi(hi)
        , lo(lo)
    {}
};
inline constexpr BinForm128 BinForm128High(BinForm64 value)
{
    return BinForm128(value, 0LL);
}
#endif

    }
}

#endif

