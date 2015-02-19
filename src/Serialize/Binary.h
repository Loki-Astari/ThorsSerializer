
#ifndef THORS_ANVIL_SERIALIZE_BINARY_H
#define THORS_ANVIL_SERIALIZE_BINARY_H

#include "BinaryParser.h"
#include "BinaryPrinter.h"
#include "Exporter.h"
#include "Importer.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

struct Binary
{
    typedef BinaryParser      Parser;
    typedef BinaryPrinter     Printer;
};

template<typename T>
Exporter<Binary, T> jsonExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default)
{
    return Exporter<Binary, T>(value, characteristics);
}
template<typename T>
Importer<Binary, T> jsonImport(T& value)
{
    return Importer<Binary, T>(value);
}
    }
}

#endif

