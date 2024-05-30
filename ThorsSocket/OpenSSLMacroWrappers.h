#ifndef THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_CONFIG_WRAPPER_H
#define THORSANVIL_THORSSOCKET_CONNECTION_SECURE_SOCKET_CONFIG_WRAPPER_H

#include <openssl/ssl.h>

inline STACK_OF(X509_NAME)* sk_X509_NAME_new_null_wrapper()                            {return sk_X509_NAME_new_null();}
inline void                 sk_X509_NAME_free_wrapper(STACK_OF(X509_NAME)* list)       {sk_X509_NAME_free(list);}
inline void                 sk_X509_NAME_pop_free_wrapper(STACK_OF(X509_NAME)* list)   {sk_X509_NAME_pop_free(list, X509_NAME_free);}

#endif
