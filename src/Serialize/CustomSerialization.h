#ifndef THORSANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_H
#define THORSANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_H

#include "SerializeConfig.h"
#include "Serialize.h"

#include <cstddef>

namespace ThorsAnvil::Serialize
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
struct DefaultCustomSerializer: public CustomSerializerBreakerFix<T>
{
        virtual ~DefaultCustomSerializer() {}

        virtual void writeCustomOld(PrinterInterface& printer, T const& object)    const override;
        virtual void readCustomOld(ParserInterface& parser, T& object)             const override;

        virtual void writeJson(JsonPrinter& printer, T const& object)           const;
        virtual void readJson(JsonParser& parser, T& object)                    const;
        virtual void writeYaml(YamlPrinter& printer, T const& object)           const;
        virtual void readYaml(YamlParser& parser, T& object)                    const;

        virtual char getBsonByteMark()                                          const{return '\x00';} // You should also override this see Bson specifications
        virtual void writeBson(BsonPrinter& printer, T const& object)           const;
        virtual void readBson(BsonParser& parser, char byteMarker, T& object)   const;

        virtual std::size_t getPrintSizeBson(BsonPrinter& printer, T const& object) const override;
        virtual std::size_t getPrintSizeJson(PrinterInterface& printer, T const& object) const override;
};

}

#include "CustomSerialization.tpp"

#endif
