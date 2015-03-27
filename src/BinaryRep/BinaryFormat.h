
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
    constexpr BinForm128()
        : hi(0)
        , lo(0)
    {}
    constexpr BinForm128(long long int value)
        : hi(hiWord(value))
        , lo(loWord(value))
    {}
#else
    BinForm64    lo;
    BinForm64    hi;
    constexpr BinForm128()
        : lo(0)
        , hi(0)
    {}
    constexpr BinForm128(long long int value)
        : lo(loWord(value))
        , hi(hiWord(value))
    {}
#endif
    friend bool operator==(BinForm128 const& lhs, BinForm128 const& rhs)
    {
        return lhs.lo == rhs.lo && lhs.hi == rhs.hi;
    }
    friend bool operator!=(BinForm128 const& lhs, BinForm128 const& rhs)
    {
        return !(lhs == rhs);
    }
    friend BinForm128  operator<<(BinForm128 const& lhs, std::size_t move)     {BinForm128 result(lhs); return result <<= move;}
    friend BinForm128& operator<<=(BinForm128& lhs, std::size_t move)
    {
        if (move >= 64)
        {
            lhs.hi  = lhs.lo;
            lhs.lo  = 0;
            lhs.hi  <<= (move - 64);
        }
        else
        {
            BinForm64  overflow    = (lhs.lo >> (64 - move));
            lhs.lo  <<= move;
            lhs.hi  <<= move;
            lhs.hi  |= overflow;
        }
        return lhs;
    }
    friend BinForm128  operator>>(BinForm128 const& lhs, std::size_t move)     {BinForm128 result(lhs); return result >>= move;}
    friend BinForm128& operator>>=(BinForm128& lhs, std::size_t move)
    {
        if (move >= 64)
        {
            lhs.lo  = lhs.hi;
            lhs.hi  = 0;
            lhs.lo  >>= (move - 64);
        }
        else
        {
            BinForm64  overflow    = (lhs.hi << (64 - move));
            lhs.hi  >>= move;
            lhs.lo  = (lhs.lo >> move) | overflow;
        }
        return lhs;
    }
    friend BinForm128  operator|(BinForm128 const& lhs, BinForm128 const& value)    {BinForm128 result(lhs); return result |= value;}
    friend BinForm128& operator|=(BinForm128& lhs, BinForm128 const& value)
    {
        lhs.lo  |= value.lo;
        lhs.hi  |= value.hi;
        return lhs;
    }
    friend BinForm128  operator&(BinForm128 const& lhs, BinForm128 const& value)    {BinForm128 result(lhs); return result &= value;}
    friend BinForm128& operator&=(BinForm128& lhs, BinForm128 const& value)
    {
        lhs.lo  &= value.lo;
        lhs.hi  &= value.hi;
        return lhs;
    }
    explicit operator unsigned long long()
    {
        return ((static_cast<unsigned long long>(hi) << 32) << 32) + lo;
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

