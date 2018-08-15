#ifndef THORS_ANVIL_SERIALIZE_YAML_H
#define THORS_ANVIL_SERIALIZE_YAML_H
/*
 * Defines the Yaml Serialization interface
 *      ThorsAnvil::Serialize::Yaml
 *      ThorsAnvil::Serialize::yamlExport
 *      ThorsAnvil::Serialize::yamlImport
 *
 * Usage:
 *      std::cout << yamlExport(object); // converts object to Yaml on an output stream
 *      std::cin  >> yamlImport(object); // converts Yaml to a C++ object from an input stream
 */

#include "SerializeConfig.h"
#ifdef HAVE_YAML

#include "YamlParser.h"
#include "YamlPrinter.h"
#include "Exporter.h"
#include "Importer.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

struct Yaml
{
    typedef YamlParser      Parser;
    typedef YamlPrinter     Printer;
};

template<typename T>
Exporter<Yaml, T> yamlExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default, bool catchExceptions = false)
{
    return Exporter<Yaml, T>(value, characteristics, catchExceptions);
}
template<typename T>
Importer<Yaml, T> yamlImport(T& value, ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak, bool catchExceptions = false)
{
    return Importer<Yaml, T>(value, parseStrictness, catchExceptions);
}
    }
}

#endif
#endif
