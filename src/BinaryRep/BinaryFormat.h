
#ifndef   THORS_ANVIL_BINARY_REP_BINARY_FORMAT_H
#define   THORS_ANVIL_BINARY_REP_BINARY_FORMAT_H


#include <cmath>
namespace ThorsAnvil
{
    namespace BinaryRep
    {

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

    }
}

#endif

