
#ifndef THORS_ANVIL_SERIALIZE_IMPORTER_H
#define THORS_ANVIL_SERIALIZE_IMPORTER_H
/*
 * The Importer simply wrap an object of type T so that when de-serialized
 * it creates an object of type DeSerializer and calls it appropriately.
 */

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
            DeSerializer                deSerializer(parser);

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

