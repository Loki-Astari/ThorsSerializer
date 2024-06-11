#ifndef THORSANVIL_THORSSOCKET_CONNECTION_FILE_H
#define THORSANVIL_THORSSOCKET_CONNECTION_FILE_H

#include "ThorsSocketConfig.h"
#include "ConnectionFileDescriptor.h"
#include <string>

namespace ThorsAnvil::ThorsSocket::ConnectionType
{

class File: public FileDescriptor
{
    int fd;
    public:
        File(std::string const& fileName, Open type, Blocking blocking);
        File(int fd);
        virtual ~File();

        virtual bool isConnected()                          const   override;
        virtual int  socketId(Mode mode)                    const   override;
        virtual void close()                                        override;

        virtual int getReadFD()                             const   override;
        virtual int getWriteFD()                            const   override;
};

}

#if THORS_SOCKET_HEADER_ONLY
#include "ConnectionFile.source"
#endif

#endif
