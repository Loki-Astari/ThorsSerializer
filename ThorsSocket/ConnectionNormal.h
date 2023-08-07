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
    int fd;
    public:
        ConnectionNormal(int fd);
        virtual ~ConnectionNormal()                                 override;
        virtual void accept()                                       override;
        virtual void connect(std::string const& host, int port)     override;
        virtual IOInfo read(char* buffer, std::size_t size)         override;
        virtual IOInfo write(char const* buffer, std::size_t size)  override;
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionNormal.source"
#endif

#endif
