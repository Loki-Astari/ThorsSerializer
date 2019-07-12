#ifndef THORS_ANVIL_SERIALIZE_JSON_H
#define THORS_ANVIL_SERIALIZE_JSON_H
/*
 * Defines the Json Serialization interface
 *      ThorsAnvil::Serialize::Json
 *      ThorsAnvil::Serialize::jsonExport
 *      ThorsAnvil::Serialize::jsonImport
 *
 * Usage:
 *      std::cout << jsonExport(object); // converts object to Json on an output stream
 *      std::cin  >> jsonImport(object); // converts Json to a C++ object from an input stream
 */

#include "SerializeConfig.h"
#include "JsonParser.h"
#include "JsonPrinter.h"
#include "Exporter.h"
#include "Importer.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

struct Json
{
    using Parser  = JsonParser;
    using Printer = JsonPrinter;
};

// @function-api
// @param value             The object to be serialized.
// @param characteristics   'Default': is verbose and logical. 'Stream': remove all white space.
// @param catchExceptions   'false:    exceptions propogate.   'true':   parsing exceptions are stopped.
// @return                  Object that can be passed to operator<< for serialization.
template<typename T>
Exporter<Json, T> jsonExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default, bool catchExceptions = false)
{
    return Exporter<Json, T>(value, characteristics, catchExceptions);
}
// @function-api
// @param value             The object to be de-serialized.
// @param parseStrictness   'Weak':    ignore missing extra fields. 'Strict': Any missing or extra fields throws exception.
// @param catchExceptions   'false:    exceptions propogate.        'true':   parsing exceptions are stopped.
// @return                  Object that can be passed to operator>> for de-serialization.
template<typename T>
Importer<Json, T> jsonImport(T& value, ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak, bool catchExceptions = false)
{
    return Importer<Json, T>(value, parseStrictness, catchExceptions);
}
    }
}

#endif
