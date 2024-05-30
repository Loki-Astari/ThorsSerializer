#ifndef THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_CONFIG_H
#define THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_CONFIG_H

#include "ThorsSocketConfig.h"
#include "OpenSSLMacroWrappers.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <functional>
#include <sstream>


namespace ThorsAnvil::ThorsSocket::ConnectionType
{

extern "C" int certificateInfo_PasswdCB(char* buf, int size, int /*rwflag*/, void* userdata);
int certificateInfo_PasswdCBNormal(char* buf, int size, int rwflag, void* userdata);
inline std::string buildOpenSSLErrorMessage(bool prefix = true)
{
    bool errorAdded = false;
    std::stringstream result;
    if (prefix) {
        result << "ConnectionType::SSocket: ";
    }
    for (long code = MOCK_FUNC(ERR_get_error)(); code != 0; code = MOCK_FUNC(ERR_get_error)())
    {
        errorAdded = true;
        result << "ErrorCode=" << code << ": msg: " << ERR_error_string(code, nullptr) << ":";
    }
    if (!errorAdded) {
        result << "No error codes found!";
    }
    return result.str();
}

enum class SSLMethodType {Client, Server};

enum Protocol { TLS_1_0, TLS_1_1, TLS_1_2, TLS_1_3 };

struct ProtocolInfo
{
    private:
        Protocol    minProtocol     = TLS_1_2;
        Protocol    maxProtocol     = TLS_1_3;

        int convertProtocolToOpenSSL(Protocol protocol) const;
    public:
        ProtocolInfo()
            : ProtocolInfo(TLS_1_2, TLS_1_3)
        {}
        ProtocolInfo(Protocol minProtocol, Protocol maxProtocol)
            : minProtocol(minProtocol)
            , maxProtocol(maxProtocol)
        {}

        void apply(SSL_CTX* ctx)   const;
        void apply(SSL* ssl)       const;
};

struct CipherInfo
{
    std::string         cipherList          =   "ECDHE-ECDSA-AES128-GCM-SHA256"     ":"
                                                "ECDHE-RSA-AES128-GCM-SHA256"       ":"
                                                "ECDHE-ECDSA-AES256-GCM-SHA384"     ":"
                                                "ECDHE-RSA-AES256-GCM-SHA384"       ":"
                                                "ECDHE-ECDSA-CHACHA20-POLY1305"     ":"
                                                "ECDHE-RSA-CHACHA20-POLY1305"       ":"
                                                "DHE-RSA-AES128-GCM-SHA256"         ":"
                                                "DHE-RSA-AES256-GCM-SHA384";
    std::string         cipherSuite         =   "TLS_AES_256_GCM_SHA384"            ":"
                                                "TLS_CHACHA20_POLY1305_SHA256"      ":"
                                                "TLS_AES_128_GCM_SHA256";
    void apply(SSL_CTX* ctx)    const;
    void apply(SSL* ssl)        const;
};

struct CertificateInfo
{
    public:
        using GetPasswordFunc = std::function<std::string(int)>;
    private:
        friend int ThorsAnvil::ThorsSocket::ConnectionType::certificateInfo_PasswdCBNormal(char*, int, int, void*);

        std::string     certificateFileName;
        std::string     keyFileName;
        GetPasswordFunc getPassword;

    public:
        CertificateInfo();
        CertificateInfo(std::string const& certificateFileName, std::string const& keyFileName, GetPasswordFunc&& getPassword = [](int){return "";});

        void apply(SSL_CTX* ctx)   const;
        void apply(SSL* ssl)       const;
};

enum AuthorityType { File, Dir, Store };

template<AuthorityType A>
struct CertifcateAuthorityDataInfo
{
    bool                        loadDefault = false;
    std::vector<std::string>    items;

    void apply(SSL_CTX* ctx)   const;
    int setDefaultCertifcateAuthorityInfo(SSL_CTX* ctx) const;
    int setOneCertifcateAuthorityInfo(SSL_CTX* ctx, char const*) const;
    std::string type() const;
};

struct CertifcateAuthorityInfo
{
    CertifcateAuthorityDataInfo<File>   file;
    CertifcateAuthorityDataInfo<Dir>    dir;
    CertifcateAuthorityDataInfo<Store>  store;

    void apply(SSL_CTX* ctx)   const;
};

template<AuthorityType A>
struct ClientCAListDataInfo
{
    std::vector<std::string>        items;

    int addCAToList(STACK_OF(X509_NAME)* certs, char const* item) const;
};

struct ClientCAListInfo
{
    bool                                verifyClientCA = false;
    ClientCAListDataInfo<File>          file;
    ClientCAListDataInfo<Dir>           dir;
    ClientCAListDataInfo<Store>         store;

    STACK_OF(X509_NAME)* buildCAToList()            const;
    void apply(SSL_CTX* ctx)   const;
    void apply(SSL* ssl)       const;
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionSSocketUtil.source"
#endif

#endif
