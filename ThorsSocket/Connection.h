#ifndef THORSANVIL_THORSSOCKET_CONNECTION_H
#define THORSANVIL_THORSSOCKET_CONNECTION_H

#include "ThorsSocketConfig.h"
#include "ConnectionUtil.h"
#include "SocketUtil.h"
#include <memory>
#include <string>
#include <cstddef>

namespace ThorsAnvil::ThorsSocket
{

class Connection
{
    public:
        Connection()            {}
        virtual ~Connection()   {}
        Connection(Connection const&)                               = delete;
        Connection& operator=(Connection const&)                    = delete;

        virtual bool isConnected()                          const   = 0;
        virtual int  socketId(Mode)                         const   = 0;
        virtual void close()                                        = 0;
        virtual void tryFlushBuffer()                               = 0;

        virtual IOData readFromStream(char* buffer, std::size_t size)       = 0;
        virtual IOData writeToStream(char const* buffer, std::size_t size)  = 0;
};

}

#endif
