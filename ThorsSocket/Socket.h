#ifndef THORSANVIL_THORSSOCKET_SOCKET_H
#define THORSANVIL_THORSSOCKET_SOCKET_H

#include "ThorsSocketConfig.h"
#include "SocketUtil.h"

#include <memory>
#include <functional>

namespace ThorsAnvil::ThorsSocket
{

class Connection;

class Socket
{
    std::unique_ptr<Connection>     connection;
    std::function<void()>           readYield;
    std::function<void()>           writeYield;

    public:
        Socket(std::unique_ptr<Connection>&& connection, std::function<void()>&& readYield = [](){}, std::function<void()>&& writeYield = [](){});

        Socket(Socket&& move)               noexcept;
        Socket& operator=(Socket&& move)    noexcept;

        void swap(Socket& other)            noexcept;

        Socket(Socket const&)               = delete;
        Socket& operator=(Socket const&)    = delete;

        bool isConnected()                  const;
        int  socketId(Mode rw)              const;      // Only useful for unit tests

        IOData getMessageData(void* buffer, std::size_t size);
        IOData putMessageData(void const* buffer, std::size_t size);

        void tryFlushBuffer();

        void close();
};
inline
void swap(Socket& lhs, Socket& rhs)
{
    lhs.swap(rhs);
}

}

#if THORS_SOCKET_HEADER_ONLY
#include "Socket.source"
#endif

#endif
