#ifndef THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_H
#define THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_H

#include "ThorsSocketConfig.h"
#include "ConnectionSocket.h"

#include <cstddef>

inline STACK_OF(X509_NAME)* sk_X509_NAME_new_null_wrapper()                            {return sk_X509_NAME_new_null();}
inline void                 sk_X509_NAME_free_wrapper(STACK_OF(X509_NAME)* list)       {sk_X509_NAME_free(list);}
inline void                 sk_X509_NAME_pop_free_wrapper(STACK_OF(X509_NAME)* list)   {sk_X509_NAME_pop_free(list, X509_NAME_free);}

namespace ThorsAnvil::ThorsSocket::ConnectionType
{

class SSocket;

class SSocketBase: public Socket
{
    protected:
        SSL*        ssl;
        SSocketBase(SSocketInfo const& socketInfo, Blocking blocking);
        SSocketBase(OpenSSocketInfo const& socketInfo);
    public:
        virtual ~SSocketBase();
        virtual void tryFlushBuffer()                               override;

        virtual IOData readFromStream(char* buffer, std::size_t size)        override;
        virtual IOData writeToStream(char const* buffer, std::size_t size)   override;

        virtual void close()                                        override;
        virtual bool isConnected()                          const   override;

        char const* getSSErrNoStr(int)  {return "";}
    private:
        void initSSocket(SSLctx const& ctx, CertificateInfo&& info);
};

class SSocketClient: public SSocketBase
{
    public:
        SSocketClient(SSocketInfo const& socketInfo, Blocking blocking);
        SSocketClient(OpenSSocketInfo const& socketInfo);
    private:
        void initSSocketClient();
};


}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionSSocket.source"
#endif

#endif
