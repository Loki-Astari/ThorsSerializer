#ifndef THORS_ANVIL_THORSSOCKET_SOCKET_WRAPPER_H
#define THORS_ANVIL_THORSSOCKET_SOCKET_WRAPPER_H

#include "ThorsSocketConfig.h"
#include <utility>
#include <cstddef>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#ifdef __WINNT__
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#endif

using SocketAddr    = struct sockaddr;
using SocketStorage = struct sockaddr_storage;
using SocketAddrIn  = struct sockaddr_in;
using HostEnt       = struct hostent;

namespace ThorsAnvil::ThorsSocket
{
using IOInfo = std::pair<ssize_t, int>;
}

inline int closeWrapper(int fd)                                                     {return ::close(fd);}
inline int socketWrapper(int family, int type, int protocol)                        {return ::socket(family, type, protocol);}
inline int connectWrapper(int fd, SocketAddr* serverAddr, std::size_t sizeAddress)  {return ::connect(fd, serverAddr, sizeAddress);}
inline int bindWrapper(int fd, SocketAddr* serverAddr, std::size_t sizeAddress)     {return ::bind(fd, serverAddr, sizeAddress);}
inline int listnWrapper(int fd, int backlog)                                        {return ::listen(fd, backlog);}
inline int acceptWrapper(int sockfd, sockaddr* addr, socklen_t* len)                {return ::accept(sockfd, addr, len);}
inline int shutdownWrapper(int fd, int how)                                         {return ::shutdown(fd, how);}

#ifdef __WINNT__
inline ThorsAnvil::ThorsSocket::IOInfo readWrapper(int fd, void* buf, size_t count)
{
    ssize_t r = ::recv(fd, reinterpret_cast<char*>(buf), count, 0);
    if (r == SOCKET_ERROR)
    {
        /*
        wchar_t *s = NULL;
        FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, WSAGetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&s,
            0,
            NULL
        );
        fprintf(stderr, "%S\n", s);
        LocalFree(s);
        */

        if (WSAGetLastError() == WSAENOTSOCK)
        {
            r = ::_read(fd, reinterpret_cast<char*>(buf), count);
            return {r, errno};
        }
        return {-1, WSAGetLastError()};
    }
    return {r, 0};
}
inline ThorsAnvil::ThorsSocket::IOInfo writeWrapper(int fd, void const* buf, size_t count)
{
    ssize_t w = ::send(fd, reinterpret_cast<char const*>(buf), count, 0);
    if (w == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAENOTSOCK)
        {
            w = ::_write(fd, reinterpret_cast<char const*>(buf), count);
            return {w, w == -1 ? errno : 0};
        }
        return {-1, WSAGetLastError()};
    }
    return {w, 0};
}
inline int nonBlockingWrapper(int fd)
{
    u_long mode = 1;
    int e = ::ioctlsocket(fd, FIONBIO, &mode);
    if ((e == 0) || (WSAGetLastError() == WSAENOTSOCK))
    {
        // If not an error
        // Or the error was because it was not a socket (that we ignore).
        return 0;
    }
    return -1;
}
#else
inline ThorsAnvil::ThorsSocket::IOInfo readWrapper(int fd, void* buf, size_t count)         {ssize_t r = ::read(fd, buf, count); return {r, errno};}
inline ThorsAnvil::ThorsSocket::IOInfo writeWrapper(int fd, void const* buf, size_t count)  {ssize_t w = ::write(fd, buf, count);return {w, errno};}
inline int nonBlockingWrapper(int fd)                                                   {return ::fcntl(fd, F_SETFL, O_NONBLOCK);}
#endif

#endif
