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
    typedef JsonParser      Parser;
    typedef JsonPrinter     Printer;
};

template<typename T>
Exporter<Json, T> jsonExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default, bool catchExceptions = false)
{
    return Exporter<Json, T>(value, characteristics, catchExceptions);
}
template<typename T>
Importer<Json, T> jsonImport(T& value, ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak, bool catchExceptions = false)
{
    return Importer<Json, T>(value, parseStrictness, catchExceptions);
}
    }
}

#endif
