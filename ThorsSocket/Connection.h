#ifndef THORSANVIL_DB_CONNECTION_H
#define THORSANVIL_DB_CONNECTION_H

#include "ThorsSocketConfig.h"
#include <memory>
#include <functional>
#include <string>
#include <cstddef>

namespace ThorsAnvil::ThorsSocket
{

class Connection;
using ConnectionItem    = std::unique_ptr<Connection>;
using ConnectionBuilder = std::function<ConnectionItem(int fd)>;

enum class Result
{
    OK,                     // Read / Write OK
    CriticalBug,            // Read / Write operation had a bug
    ResourceFail,           // Read / Write resource failure.
    Interupt,               // Read / Write was interrupted by OS (try again)
    Timeout,                // Read / Write would block
    ConnectionClosed,       // Read / Write connection closed (we reached the end)
    Unknown
};

using IOInfo            = std::pair<ssize_t, int>;
using IOResult          = std::pair<ssize_t, Result>;


class Connection
{
    public:
        Connection(int /*fd*/)  {}
        virtual ~Connection()   {}
        Connection(Connection const&)                               = delete;
        Connection& operator=(Connection const&)                    = delete;

        virtual bool isValid()                              const   = 0;
        virtual int  socketId()                             const   = 0;
        virtual void makeSocketNonBlocking()                        = 0;
        virtual void close()                                        = 0;
        virtual void shutdown()                                     = 0;
        virtual void bind(int port, int maxWaitingConnections)      = 0;
        virtual int  accept()                                       = 0;
        virtual void acceptEstablishConnection()                    = 0;
        virtual void connect(std::string const& host, int port)     = 0;

        virtual IOResult read(char* buffer, std::size_t size)       = 0;
        virtual IOResult write(char const* buffer, std::size_t size)= 0;

        virtual std::string errorMessage(ssize_t result)            = 0;
};

}

#endif
