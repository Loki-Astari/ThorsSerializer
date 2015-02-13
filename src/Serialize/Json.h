
#ifndef THORS_ANVIL_SERIALIZE_JSON_H
#define THORS_ANVIL_SERIALIZE_JSON_H

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
Exporter<Json, T> jsonExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default)
{
    return Exporter<Json, T>(value, characteristics);
}
template<typename T>
Importer<Json, T> jsonImport(T& value)
{
    return Importer<Json, T>(value);
}
    }
}

#endif

