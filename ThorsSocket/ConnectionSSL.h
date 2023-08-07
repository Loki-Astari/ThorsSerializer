#ifndef THORSANVIL_THORSSOCKET_CONNECTION_SSL_H
#define THORSANVIL_THORSSOCKET_CONNECTION_SSL_H

#include "ThorsSocketConfig.h"
#include "ConnectionNormal.h"
#include <cstddef>
#include <string>

#include <openssl/ssl.h>

namespace ThorsAnvil::ThorsSocket
{

class SSLUtil
{
    SSLUtil();
    public:
        static SSLUtil& getInstance();
        static std::string errorMessage();
        static std::string sslError(SSL* ssl, int ret);

        SSLUtil(SSLUtil const&)                 = delete;
        SSLUtil& operator=(SSLUtil const&)      = delete;
};

enum class SSLMethodType {Client, Server};
class SSLctx;
class ConnectionSSL;
class SSLMethod
{
    friend class SSLctx;
    const SSL_METHOD* method;
    public:
        SSLMethod(SSLMethodType type);

        SSLMethod(SSLMethod const&)             = delete;
        SSLMethod& operator=(SSLMethod const&)  = delete;
};

class SSLctx
{
    friend class ConnectionSSL;
    SSL_CTX*            ctx;
    public:
        SSLctx(SSLMethod& method);
        SSLctx(SSLMethod& method, std::string const& certFile, std::string const& keyFile);
        ~SSLctx();

        SSLctx(SSLctx const&)                   = delete;
        SSLctx& operator=(SSLctx const&)        = delete;
};

class ConnectionSSL: public ConnectionNormal
{
    SSL*                ssl;
    public:
        ConnectionSSL(SSLctx const& ctx, int fd);
        ~ConnectionSSL();

        virtual void accept()                                           override;
        virtual void connect(std::string const& host, int port)         override;
    // BUG:
    // This function is for StreamSimple.
    // It needs to be factored out.
        void doConnect();
        virtual IOInfo read(char* buffer, std::size_t len)              override;
        virtual IOInfo write(char const* buffer, std::size_t len)       override;
    private:
        int  errorCode(int ret);
    // BUG: Next function needs to be public for StreamSimple.
    //      When we refactor that class make this private again.
    public:
        int  nativeErrorCode(int ret);
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionSSL.source"
#endif

#endif
