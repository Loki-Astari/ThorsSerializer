#ifndef THORS_ANVIL_SERIALIZE_BINARY_H
#define THORS_ANVIL_SERIALIZE_BINARY_H
/*
 * Defines the Binary Serialization interface
 *      ThorsAnvil::Serialize::Binary
 *      ThorsAnvil::Serialize::binExport
 *      ThorsAnvil::Serialize::binImport
 *
 * Usage:
 *      std::cout << binExport(object); // converts object to Binary on an output stream
 *      std::cin  >> binImport(object); // converts Binary to a C++ object from an input stream
 */

#include "SerializeConfig.h"
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
            BinaryParserWrapper(std::istream& stream, ParserInterface::ParseType /*Ignored*/)
                : BinaryParser<X>(stream)
            {}
    };
    public:
    typedef BinaryParserWrapper<T>  Parser;
    typedef BinaryPrinter<T>        Printer;
};

template<typename T>
Exporter<Binary<T>, T> binExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default)
{
    return Exporter<Binary<T>, T>(value, characteristics);
}
template<typename T>
Importer<Binary<T>, T> binImport(T& value)
{
    return Importer<Binary<T>, T>(value, ParserInterface::ParseType::Strict);
}
    }
}

#endif
#endif
