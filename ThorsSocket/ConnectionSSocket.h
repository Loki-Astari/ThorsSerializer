#ifndef THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_H
#define THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_H

#include "ThorsSocketConfig.h"
#include "ConnectionSSocketUtil.h"
#include "ConnectionSocket.h"
#include "ThorsLogging/ThorsLogging.h"

#include <utility>
#include <string>
#include <cstddef>
#include <openssl/ssl.h>


namespace ThorsAnvil::ThorsSocket::ConnectionType
{

class SSocket;

class SSLUtil
{
    SSLUtil();
    public:
        static SSLUtil& getInstance();

        SSLUtil(SSLUtil const&)                 = delete;
        SSLUtil& operator=(SSLUtil const&)      = delete;
};

class SSLctx
{
    private:
        friend class SSocket;
        SSL_CTX*            ctx;
    public:
        template<typename... Args>
        SSLctx(SSLMethodType methodType, Args&&... args);
               // ProtocolInfo
               // CipherInfo
               // CertificateInfo
               // CertifcateAuthorityInfo
               // ClientCAListInfo

        ~SSLctx();

        SSLctx(SSLctx const&)                   = delete;
        SSLctx& operator=(SSLctx const&)        = delete;

        SSLctx(SSLctx&& move)
            : ctx(std::exchange(move.ctx, nullptr))
        {}
        //SSLctx& operator=(SSLctx const&)        = delete;
};

template<typename... Args>
SSLctx::SSLctx(SSLMethodType methodType, Args&&... args)
               // ProtocolInfo protocolRange,
               //CipherInfo const& cipherList,
               //CertificateInfo const& certificate,
               //CertifcateAuthorityInfo const& certifcateAuthority,
               //ClientCAListInfo const& clientCAList)
    : ctx(nullptr)
{
    SSLUtil::getInstance();
    SSL_METHOD const*  method;
    if (methodType == SSLMethodType::Client) {
        method = MOCK_FUNC(TLS_client_method)(); // SSLv23_client_method();
    }
    else {
        method = MOCK_FUNC(TLS_server_method)();
    }

    if (method == nullptr)
    {
        ThorsLogAndThrow("ThorsAnvil::THorsSocket::SSLctx",
                         "SSLctx",
                         "TLS_client_method() failed: ", buildOpenSSLErrorMessage());
    }

    ctx = MOCK_FUNC(SSL_CTX_new)(method);
    if (ctx == nullptr)
    {
        ThorsLogAndThrow("ThorsAnvil::ThorsSocket::SSLctx",
                         "SSLctx",
                         "SSL_CTX_new() failed: ", buildOpenSSLErrorMessage());
    }

    (args.apply(ctx),...);
    //protocolRange.setProtocolInfo(ctx);
    //cipherList.setCipherInfo(ctx);
    //certificate.setCertificateInfo(ctx);
    //certifcateAuthority.setCertifcateAuthorityInfo(ctx);
    //clientCAList.setCertifcateAuthorityInfo(ctx);
}
class SSocket: public Socket
{
    SSL*        ssl;
    public:
        SSocket(SSLctx const& ctx, std::string const& host, int port, Blocking blocking, CertificateInfo&& info = CertificateInfo{});
        SSocket(int fd, SSLctx const& ctx, CertificateInfo&& info = CertificateInfo{});
        virtual ~SSocket();
        virtual void tryFlushBuffer()                               override;

        virtual IOData readFromStream(char* buffer, std::size_t size)        override;
        virtual IOData writeToStream(char const* buffer, std::size_t size)   override;

        virtual void close()                                        override;
        virtual bool isConnected()                          const   override;

        char const* getSSErrNoStr(int)  {return "";}
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionSSocket.source"
#endif

#endif
