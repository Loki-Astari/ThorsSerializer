
#ifndef THORS_ANVIL_SERIALIZE_IMPORTER_H
#define THORS_ANVIL_SERIALIZE_IMPORTER_H

#include "Serialize.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename Format, typename T>
class Importer
{
    T& value;
    public:
        Importer(T& value)
            : value(value)
        {}
        friend std::istream& operator>>(std::istream& stream, Importer const& data)
        {
            typename Format::Parser     parser(stream);
            DeSerializer<T>             deSerializer(parser);

            deSerializer.parse(data.value);
            return stream;
        }
};

template<typename Format, typename T>
Importer<Format, T> Import(T const& value)
{
    return Importer<Format, T>(value);
}


    }
}

#endif

