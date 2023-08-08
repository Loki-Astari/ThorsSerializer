#ifndef THORSANVIL_THORSSOCKET_SOCKET_H
#define THORSANVIL_THORSSOCKET_SOCKET_H

#include "ThorsSocketConfig.h"
#include "Connection.h"
#include "ConnectionNormal.h"
#include "ConnectionSSL.h"

#include <memory>
#include <functional>
#include <cstddef>
#include <utility>
#include <string>


namespace ThorsAnvil::ThorsSocket
{

// @class
// Base of all the socket classes.
// This class should not be directly created.
// All socket classes are movable but not copyable.
class BaseSocket
{
    protected:
        // Designed to be a base class not used used directly.
        BaseSocket(std::unique_ptr<Connection>&& connection, bool blocking = false);                    // Normal Socket
    public:
        virtual ~BaseSocket();
        bool isValid()                              const;
        int  socketId()                             const;      // Only useful for unit tests

        // Moveable but not Copyable
        // @method
        BaseSocket(BaseSocket&& move)               noexcept;
        // @method
        BaseSocket& operator=(BaseSocket&& move)    noexcept;
        // @method
        void swap(BaseSocket& other)                noexcept;
        BaseSocket(BaseSocket const&)               = delete;
        BaseSocket& operator=(BaseSocket const&)    = delete;

        // User can manually call close
        // @method
        void close();
        void makeSocketNonBlocking();
    protected:
        std::unique_ptr<Connection>     connection;
};

// @class
// Data sockets define the read/write interface to a socket.
// This class should not be directly created
class DataSocket: public BaseSocket
{
    private:
        std::function<void()>  readYield;
        std::function<void()>  writeYield;

    public:
        // @method
        DataSocket(std::unique_ptr<Connection>&& connection, bool blocking = false);

        // @method
        void setYield(std::function<void()>&& yr, std::function<void()>&& yw);

        // @method
        // Reads data from a sokcet into a buffer.
        // If the stream is blocking will not return until the requested amount of data has been read or there is no more data to read.
        // If the stream in non blocking will return if the read operation would block.
        // @return              This method returns a <code>std::pair&lt;bool, std::size_t&gt;</code>. The first member `bool` indicates if more data can potentially be read from the stream. If the socket was cut or the EOF reached then this value will be false. The second member `std::size_t` indicates exactly how many bytes were read from this stream.
        // @param buffer        The buffer data will be read into.
        // @param size          The size of the buffer.
        // @param alreadyGot    Offset into buffer (and amount size is reduced by) as this amount was read on a previous call).
        std::pair<bool, std::size_t> getMessageData(char* buffer, std::size_t size, std::size_t alreadyGot = 0);
        // @method
        // Writes data from a buffer to a sokcet.
        // If the stream is blocking will not return until the requested amount of data has been written or the socket was closed to writting.
        // If the stream in non blocking will return if the write operation would block.
        // @return              This method returns a <code>std::pair&lt;bool, std::size_t&gt;</code>. The first member `bool` indicates if more data can potentially be written to the stream. If the socket was cut or closed then this value will be false. The second member `std::size_t` indicates exactly how many bytes were written to this stream.
        // @param buffer        The buffer data will be written from.
        // @param size          The size of the buffer.
        // @param alreadyPut    Offset into buffer (and amount size is reduced by) as this amount was written on a previous call).
        std::pair<bool, std::size_t> putMessageData(char const* buffer, std::size_t size, std::size_t alreadyPut = 0);
        // @method
        // closes the write end of the socket and flushes (write) data.
        // @return              closes the write end of the socket and flushes (write) data.
        void        putMessageClose();
};

// @class
// Creates a connection to <code>host</code> on <code>port</code>.
// Note this class inherits from <code>DataSocket</code> so once created you can read/write to the socket.
class ConnectSocket: public DataSocket
{
    public:
        // @method
        ConnectSocket(ConnectionBuilder const& builder, std::string const& host, int port);
};

// @class
// A server socket that listens on a port for a connection
class ServerSocket: public BaseSocket
{
    public:
        static constexpr int maxConnectionBacklog = 5;
        // @method
        ServerSocket(int port, bool blocking = false, int maxWaitingConnections = maxConnectionBacklog);

        // @method
        // "Accept" a waiting connection request on the port and creates a two way socket for communication on another port.
        // If this is a non blocking socket and there is no waiting connection an exception is thrown.
        // If this is a blocking socket wait for a connection.
        // @return              A <code>DataSocket</code> is returned so data can be exchange across the socket.
        // @param blocking      Passed to the constructor of the <code>DataSocket</code> that is returned.
        DataSocket accept(ConnectionBuilder const& builder, bool blocking = false);
};

/*
 * Trivial wrappers for creating Normal (plain text) or SSL connections.
 */
class ServerSocketNormal: public ServerSocket
{
    public:
        using ServerSocket::ServerSocket;
        DataSocket accept(bool blocking = false)
        {
            return ServerSocket::accept([](int fd){return std::make_unique<ConnectionNormal>(fd);}, blocking);
        }
};
class ConnectSocketNormal: public ConnectSocket
{
    public:
        ConnectSocketNormal(std::string const& host, int port)
            : ConnectSocket([](int fd){return std::make_unique<ConnectionNormal>(fd);}, host, port)
        {}
};

class ServerSocketSSL: public ServerSocket
{
    SSLctx&     context;
    public:
        ServerSocketSSL(SSLctx& context, int port, bool blocking = false, int maxWaitingConnections = maxConnectionBacklog)
            : ServerSocket(port, blocking, maxWaitingConnections)
            , context(context)
        {}
        DataSocket accept(bool blocking = false)
        {
            return ServerSocket::accept([&context = this->context](int fd){return std::make_unique<ConnectionSSL>(context, fd);}, blocking);
        }
};
class ConnectSocketSSL: public ConnectSocket
{
    public:
        ConnectSocketSSL(SSLctx& context, std::string const& host, int port)
            : ConnectSocket([&context](int fd){return std::make_unique<ConnectionSSL>(context, fd);}, host, port)
        {}
};


}

#if THORS_SOCKET_HEADER_ONLY
#include "Socket.source"
#endif

#endif
