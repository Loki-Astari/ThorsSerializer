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
    using Parser  = YamlParser;
    using Printer = YamlPrinter;
};

// @function-api
// @param value             The object to be serialized.
// @param characteristics   'Default': is verbose and logical. 'Stream': remove all white space.
// @param catchExceptions   'false:    exceptions propogate.   'true':   parsing exceptions are stopped.
// @return                  Object that can be passed to operator<< for serialization.
template<typename T>
Exporter<Yaml, T> yamlExport(T const& value, PrinterInterface::PrinterConfig config = PrinterInterface::PrinterConfig{}, bool catchExceptions = false)
{
    return Exporter<Yaml, T>(value, config, catchExceptions);
}
// @function-api
// @param value             The object to be de-serialized.
// @param parseStrictness   'Weak':    ignore missing extra fields. 'Strict': Any missing or extra fields throws exception.
// @param catchExceptions   'false:    exceptions propogate.        'true':   parsing exceptions are stopped.
// @return                  Object that can be passed to operator>> for de-serialization.
template<typename T>
Importer<Yaml, T> yamlImport(T& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{}, bool catchExceptions = false)
{
    return Importer<Yaml, T>(value, config, catchExceptions);
}
    }
}

#endif
#endif
