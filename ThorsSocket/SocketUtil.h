#ifndef THORSANVIL_THORSSOCKET_SOCKET_UTIL_H
#define THORSANVIL_THORSSOCKET_SOCKET_UTIL_H

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <sys/types.h>

namespace ThorsAnvil::ThorsSocket
{

struct IOData
{
    std::size_t     dataSize;
    bool            stillOpen;
    bool            blocked;
};

enum class Open     {Append, Truncate};
enum class Blocking {No, Yes};
enum class Mode     {Read, Write};

}

#endif
