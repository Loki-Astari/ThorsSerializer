
#ifndef   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H
#define   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H


namespace ThorsAnvil
{
    namespace BinaryRep
    {

inline BinForm64 thor_htobe64(BinForm64 value)
{
#if !WORDS_BIGENDIAN
    BinForm32*   pointerToValue  = reinterpret_cast<BinForm32*>(&value);
    pointerToValue[0]   = htonl(pointerToValue[0]);
    pointerToValue[1]   = htonl(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}
inline BinForm128 thor_htobe128(BinForm128 value)
{
#if !WORDS_BIGENDIAN
    BinForm64*   pointerToValue  = reinterpret_cast<BinForm64*>(&value);
    pointerToValue[0]   = thor_htobe64(pointerToValue[0]);
    pointerToValue[1]   = thor_htobe64(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}

    }
}

#endif

