
#ifndef   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H
#define   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H


namespace ThorsAnvil
{
    namespace BinaryRep
    {

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

    }
}

#endif

