#ifndef THORSANVIL_SERIALIZER_STRING_OUTPUT_H
#define THORSANVIL_SERIALIZER_STRING_OUTPUT_H

#include "SerializeConfig.h"
#include <string>

namespace ThorsAnvil::Serialize
{

struct StringOutput
{
    std::string&    data;
    bool            ok;

    public:
        StringOutput(std::string& output)
            : data(output)
            , ok(true)
        {}
        bool write(char const* src, std::size_t size)
        {
            data += std::string_view(src, size);
            return true;
        }
        bool isOk() const
        {
            return ok;
        }
        void setFail()
        {
            ok = false;
        }
        template<typename T>
        void writeValue(T const& src)
        {
            using std::to_string;
            data += to_string(src);
        }
};

}

#endif
