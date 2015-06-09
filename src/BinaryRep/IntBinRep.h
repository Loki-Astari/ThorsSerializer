
#ifndef   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H
#define   THORS_ANVIL_BINARY_REP_INT_BIN_REP_H

#include "BinaryFormat.h"
#include <arpa/inet.h>

namespace ThorsAnvil
{
    namespace BinaryRep
    {

inline BinForm64 BESwap(BinForm64 value)
{
#if !WORDS_BIGENDIAN
    BinForm32*   pointerToValue  = reinterpret_cast<BinForm32*>(&value);
    pointerToValue[0]   = htonl(pointerToValue[0]);
    pointerToValue[1]   = htonl(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}
inline BinForm128 BESwap(BinForm128 value)
{
#if !WORDS_BIGENDIAN
    BinForm64*   pointerToValue  = reinterpret_cast<BinForm64*>(&value);
    pointerToValue[0]   = BESwap(pointerToValue[0]);
    pointerToValue[1]   = BESwap(pointerToValue[1]);
    std::swap(pointerToValue[0], pointerToValue[1]);
#endif
    return value;
}

inline BinForm16    host2Net(BinForm16  value)      {return htons(value);}
inline BinForm32    host2Net(BinForm32  value)      {return htonl(value);}
inline BinForm64    host2Net(BinForm64  value)      {return BESwap(value);}
inline BinForm128   host2Net(BinForm128 value)      {return BESwap(value);}

inline BinForm16    net2Host(BinForm16  value)      {return ntohs(value);}
inline BinForm32    net2Host(BinForm32  value)      {return ntohl(value);}
inline BinForm64    net2Host(BinForm64  value)      {return BESwap(value);}
inline BinForm128   net2Host(BinForm128 value)      {return BESwap(value);}

    }
}

#endif

