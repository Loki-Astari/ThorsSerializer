#ifndef THORS_ANVIL_THORSSOCKET_CONNECTION_NORMAL_H
#define THORS_ANVIL_THORSSOCKET_CONNECTION_NORMAL_H

#include "ThorsSocketConfig.h"
#include "SocketWrapper.h"
#include "Connection.h"
#include <string>
#include <cstddef>

namespace ThorsAnvil::ThorsSocket
{

class ConnectionNormal: public Connection
{
    static constexpr int invalidSocketId      = -1;

    int fd;
    public:
        ConnectionNormal(int fd);
        virtual ~ConnectionNormal()                                 override;

        virtual bool isValid()                              const   override;
        virtual int  socketId()                             const   override;
        virtual void makeSocketNonBlocking()                        override;
        virtual void close()                                        override;
        virtual void shutdown()                                     override;
        virtual void bind(int port, int maxWaitingConnections)      override;
        virtual int  accept()                                       override;
        virtual void acceptEstablishConnection()                    override {}
        virtual void connect(std::string const& host, int port)     override;

        virtual IOResult read(char* buffer, std::size_t size)       override;
        virtual IOResult write(char const* buffer, std::size_t size)override;

        virtual std::string errorMessage(ssize_t result)            override;
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionNormal.source"
#endif

#endif
