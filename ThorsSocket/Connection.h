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
using IOInfo            = std::pair<ssize_t, int>;


class Connection
{
    public:
        Connection(int /*fd*/)  {}
        virtual ~Connection()   {}
        Connection(Connection const&)                               = delete;
        Connection& operator=(Connection const&)                    = delete;
        virtual void accept()                                       = 0;
        virtual void connect(std::string const& host, int port)     = 0;
        virtual IOInfo read(char* buffer, std::size_t size)         = 0;
        virtual IOInfo write(char const* buffer, std::size_t size)  = 0;
};

}

#endif
