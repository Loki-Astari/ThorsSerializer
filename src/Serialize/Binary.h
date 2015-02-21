
#ifndef THORS_ANVIL_SERIALIZE_BINARY_H
#define THORS_ANVIL_SERIALIZE_BINARY_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "BinaryParser.h"
#include "BinaryPrinter.h"
#include "Exporter.h"
#include "Importer.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
struct Binary
{
    typedef BinaryParser<T>      Parser;
    typedef BinaryPrinter<T>     Printer;
};

template<typename T>
Exporter<Binary, T> jsonExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default)
{
    return Exporter<Binary, T>(value, characteristics);
}
template<typename T>
Importer<Binary, T> jsonImport(T& value)
{
    return Importer<Binary<T>, T>(value);
}
    }
}

#endif
#endif

