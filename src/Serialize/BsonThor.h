#ifndef THORS_ANVIL_SERIALIZE_BSON_H
#define THORS_ANVIL_SERIALIZE_BSON_H
/*
 * Defines the Bson Serialization interface
 *      ThorsAnvil::Serialize::Bson
 *      ThorsAnvil::Serialize::bsonExporter
 *      ThorsAnvil::Serialize::bsonImporter
 *
 * Usage:
 *      std::cout << bsonExporter(object); // converts object to Bson on an output stream
 *      std::cin  >> bsonImporter(object); // converts Bson to a C++ object from an input stream
 */

#include "BsonParser.h"
#include "BsonPrinter.h"
#include "Exporter.h"
#include "Importer.h"
#include "SerUtil.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

struct Bson
{
    using Parser  = BsonParser;
    using Printer = BsonPrinter;
};

// @function-api
// @param value                     The object to be serialized.
// @param config.characteristics    'Default': uses Config/Stream depending on global config. 'Config':  Is verbose and logical. 'Stream':  Remove all white space.
// @param config.polymorphicMarker  Jason object name for holding the polymorphic class name of the type. Default: __type
// @param config.catchExceptions    'false:    exceptions propogate.   'true':   parsing exceptions are stopped.
// @return                          Object that can be passed to operator<< for serialization.
template<typename T>
Exporter<Bson, T> bsonExporter(T const& value, PrinterInterface::PrinterConfig config = PrinterInterface::PrinterConfig{})
{
    if constexpr (Traits<T>::type == TraitType::Map || Traits<T>::type == TraitType::Parent)
    {
        config.parserInfo = static_cast<long>(BsonContainer::Map);
    }
    else if constexpr (Traits<T>::type == TraitType::Array)
    {
        config.parserInfo = static_cast<long>(BsonContainer::Array);
    }
    else
    {
        config.parserInfo = static_cast<long>(BsonContainer::Value);
    }
    return Exporter<Bson, T>(value, config);
}

// @function-api
// @param value                     The object to be de-serialized.
// @param config.parseStrictness    'Weak':    ignore missing extra fields. 'Strict': Any missing or extra fields throws exception.
// @param config.polymorphicMarker  Jason object name for holding the polymorphic class name of the type. Default: __type
// @param config.catchExceptions    'false:    exceptions propogate.        'true':   parsing exceptions are stopped.
// @return                          Object that can be passed to operator>> for de-serialization.
template<typename T>
Importer<Bson, T> bsonImporter(T& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{})
{
    if constexpr (Traits<T>::type == TraitType::Map || Traits<T>::type == TraitType::Parent)
    {
        config.parserInfo = static_cast<long>(BsonContainer::Map);
    }
    else if constexpr (Traits<T>::type == TraitType::Array)
    {
        config.parserInfo = static_cast<long>(BsonContainer::Array);
    }
    else
    {
        config.parserInfo = static_cast<long>(BsonContainer::Value);
    }
    return Importer<Bson, T>(value, config);
}

    }
}

#endif
