#ifndef THORSANVIL_THORSSOCKET_SOCKET_UTIL_H
#define THORSANVIL_THORSSOCKET_SOCKET_UTIL_H

#include "SecureSocketUtil.h"

#include <cstddef>
#include <string_view>

#ifdef  __WINNT__
#define SOCKET_TYPE             SOCKET
#else
#define SOCKET_TYPE             int
#endif

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

struct FileInfo
{
    std::string_view    fileName;
    Open                open;
};
struct PipeInfo
{};
struct SocketInfo
{
    std::string_view    host;
    int                 port;
};

struct OpenSocketInfo
{
    SOCKET_TYPE         fd;
};

struct SSocketInfo: public SocketInfo
{
    SSLctx const&       ctx;
    CertificateInfo&&   certificate = CertificateInfo{};
};

struct OpenSSocketInfo: public OpenSocketInfo
{
    SSLctx const&       ctx;
    CertificateInfo&&   certificate = CertificateInfo{};
};

}

#endif
