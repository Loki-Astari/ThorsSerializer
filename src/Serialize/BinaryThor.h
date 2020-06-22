#ifndef THORS_ANVIL_SERIALIZE_BINARY_H
#define THORS_ANVIL_SERIALIZE_BINARY_H
/*
 * Defines the Binary Serialization interface
 *      ThorsAnvil::Serialize::Binary
 *      ThorsAnvil::Serialize::binExporter
 *      ThorsAnvil::Serialize::binImporter
 *
 * Usage:
 *      std::cout << binExporter(object); // converts object to Binary on an output stream
 *      std::cin  >> binImporter(object); // converts Binary to a C++ object from an input stream
 */

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
    private:
    template<typename X>
    class BinaryParserWrapper: public BinaryParser<X>
    {
        public:
            BinaryParserWrapper(std::istream& stream, ParserInterface::ParserConfig /*Ignored*/)
                : BinaryParser<X>(stream, ParserInterface::ParserConfig{ParserInterface::ParseType::Strict})
            {}
    };
    public:
    using Parser  = BinaryParserWrapper<T>;
    using Printer = BinaryPrinter<T>;
};

// @function-api
// @param value             The object to be serialized.
// @return                  Object that can be passed to operator<< for serialization.
template<typename T>
Exporter<Binary<T>, T> binExporter(T const& value, PrinterInterface::PrinterConfig config = PrinterInterface::PrinterConfig{})
{
    return Exporter<Binary<T>, T>(value, config);
}
template<typename T>
[[deprecated]] Exporter<Binary<T>, T> binExport(T const& value, PrinterInterface::PrinterConfig config = PrinterInterface::PrinterConfig{}, bool catchExceptions = false)
{
    config.catchExceptions = catchExceptions;
    return binExporter(value, config);
}
// @function-api
// @param value             The object to be de-serialized.
// @return                  Object that can be passed to operator>> for de-serialization.
template<typename T>
Importer<Binary<T>, T> binImporter(T& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{ParserInterface::ParseType::Strict})
{
    return Importer<Binary<T>, T>(value, config);
}
template<typename T>
[[deprecated]] Importer<Binary<T>, T> binImport(T& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{ParserInterface::ParseType::Strict}, bool catchExceptions = false)
{
    config.catchExceptions = catchExceptions;
    return binImporter(value, config);
}
    }
}

#endif
#endif
