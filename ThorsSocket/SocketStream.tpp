#ifndef THORSANVIL_NISSE_CORE_SOCKET_SOCKET_STREAM_TPP
#define THORSANVIL_NISSE_CORE_SOCKET_SOCKET_STREAM_TPP

#ifndef THORSANVIL_NISSE_CORE_SOCKET_SOCKET_STREAM_H
#error "Don't include this file directly. Include SocketStream.h"
#endif

namespace ThorsAnvil::ThorsSocket
{

template<typename Buffer>
IOSocketStream<Buffer>::IOSocketStream(DataSocket& stream)
    : std::istream(nullptr)
    , buffer(stream, noActionNotifier, noActionNotifier)
{
    std::istream::rdbuf(&buffer);
}

template<typename Buffer>
IOSocketStream<Buffer>::IOSocketStream(DataSocket& stream,
                             Notifier noAvailableData, Notifier flushing)
    : std::istream(nullptr)
    , buffer(stream, noAvailableData, flushing)
{
    std::istream::rdbuf(&buffer);
}

template<typename Buffer>
IOSocketStream<Buffer>::IOSocketStream(DataSocket& stream,
                             Notifier noAvailableData, Notifier flushing,
                             std::vector<char>&& bufData, char const* currentStart, char const* currentEnd)
    : std::istream(nullptr)
    , buffer(stream,
             noAvailableData, flushing,
             std::move(bufData), currentStart, currentEnd)
{
    rdbuf(&buffer);
}

template<typename Buffer>
IOSocketStream<Buffer>::IOSocketStream(IOSocketStream&& move) noexcept
    : std::istream(nullptr)
    , buffer(std::move(move.buffer))
{
    rdbuf(&buffer);
}

}

#endif
