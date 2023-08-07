#ifndef THORSANVIL_NISSE_CORE_SOCKET_SOCKET_STREAM_H
#define THORSANVIL_NISSE_CORE_SOCKET_SOCKET_STREAM_H

#include "ThorsSocketConfig.h"
#include "Socket.h"
#include <istream>
#include <ostream>
#include <vector>
#include <functional>
#include <cstddef>

namespace ThorsAnvil::ThorsSocket
{

using Notifier = std::function<void()>;

inline void noActionNotifier(){}

// @class
// This is a wrapper class for a <code>DataSocket</code> that allows the socket to be treated like <code>std::streambuf</code>.
// This class overrides just enough virtual functions to make the <code>IOSocketStream</code> and <code>OSocketStream</code> useful.
// This class provides no public API and is designed to be used solely with the following stream objects.
class SocketStreamBufferBase: public std::streambuf
{
    private:
        typedef std::streambuf::traits_type traits;
        typedef traits::int_type            int_type;
        typedef traits::char_type           char_type;

        DataSocket&             stream;
        Notifier                noAvailableData;
        Notifier                flushing;
        std::vector<char>&      inBuffer;
        std::vector<char>&      outBuffer;
        std::size_t             inCount;
        std::size_t             outCount;

    public:
        virtual ~SocketStreamBufferBase() override;
        SocketStreamBufferBase(DataSocket& stream,
                           Notifier noAvailableData, Notifier flushing,
                           std::vector<char>& inBuffer, std::vector<char>& outBuffer);
        SocketStreamBufferBase(SocketStreamBufferBase&& move, std::vector<char>& inBuffer, std::vector<char>& outBuffer) noexcept;

        SocketStreamBufferBase(SocketStreamBufferBase const&)               = delete;
        SocketStreamBufferBase& operator=(SocketStreamBufferBase const&)    = delete;
        SocketStreamBufferBase& operator=(SocketStreamBufferBase&&)         = delete;

        void resizeInputBuffer(std::size_t inSize);
        void resizeOutputBuffer(std::size_t outSize);

    protected:
        virtual int_type        underflow() override;
        virtual std::streamsize xsgetn(char_type* s, std::streamsize count) override;

        virtual int_type        overflow(int_type ch = traits::eof()) override;
        virtual std::streamsize xsputn(char_type const* s,std::streamsize count) override;

        virtual int             sync() override;
        void                    clear();

        virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) override;
    protected:
        std::streamsize writeToStream(char_type const* source, std::streamsize count);
        std::streamsize readFromStream(char_type* dest, std::streamsize count, bool fill = true);
};

class SocketStreamBuffer: public SocketStreamBufferBase
{
    private:
        std::vector<char>       in;
        std::vector<char>       out;

    public:
        SocketStreamBuffer(DataSocket& stream,
                           Notifier noAvailableData, Notifier flushing,
                           std::vector<char>&& bufData = std::vector<char>(4000),
                           char const* currentStart = nullptr, char const* currentEnd = nullptr);
        SocketStreamBuffer(SocketStreamBuffer&& move) noexcept;
        ~SocketStreamBuffer();
};

// @class
// An implementation of <code>std::istream</code> that uses <code>SocketStreamBuffer</code> as the buffer.
// The <code>Notofer</code> is a primitive event callback mechanism.
// A blocking read call to these streams calls the <code>Notifier noData</code>.
// This is used by the <a href="#Server">Server</a> infrastructure to yield control back to the main event loop.
// <code>using Notifier = std::function<void()>;</code>
template<typename Buffer = SocketStreamBuffer>
class IOSocketStream: public std::istream, public std::ostream
{
    Buffer buffer;

    public:
        // @method
        IOSocketStream(DataSocket& stream,
                      Notifier noAvailableData, Notifier flushing,
                      std::vector<char>&& bufData, char const* currentStart, char const* currentEnd);
        // @method
        IOSocketStream(DataSocket& stream,
                      Notifier noAvailableData, Notifier flushing);
        // @method
        IOSocketStream(DataSocket& stream);
        // @method
        IOSocketStream(IOSocketStream&& move) noexcept;
};

}

#include "SocketStream.tpp"
#if THORS_SOCKET_HEADER_ONLY
#include "SocketStream.source"
#endif


#endif
