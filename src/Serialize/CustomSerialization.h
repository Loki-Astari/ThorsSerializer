#ifndef THORS_ANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_H
#define THORS_ANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_H

#include <cstdlib>

namespace ThorsAnvil
{
    namespace Serialize
    {

class PrinterInterface;
class ParserInterface;
class JsonPrinter;
class JsonParser;
class YamlPrinter;
class YamlParser;
class BsonPrinter;
class BsonParser;

template<typename T>
struct DefaultCustomSerializer
{
        virtual ~DefaultCustomSerializer() {}

        void writeCustom(PrinterInterface& printer, T const& object);
        void readCustom(ParserInterface& parser, T& object);

        virtual void writeJson(JsonPrinter& printer, T const& object);
        virtual void readJson(JsonParser& parser, T& object);
        virtual void writeYaml(YamlPrinter& printer, T const& object);
        virtual void readYaml(YamlParser& parser, T& object);
        virtual std::size_t getPrintSizeBson(BsonPrinter& printer, T const& object);
        virtual char getBsonByteMark() {return '\x00';} // You should also override this see Bson specifications
        virtual void writeBson(BsonPrinter& printer, T const& object);
        virtual void readBson(BsonParser& parser, char byteMarker, T& object);
};
    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "CustomSerialization.source"
#endif

#ifndef COVERAGE_TEST
#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_H
#include "CustomSerialization.tpp"
#endif
#endif

#endif
