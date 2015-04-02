
#ifndef THORS_ANVIL_SERIALIZE_YAML_H
#define THORS_ANVIL_SERIALIZE_YAML_H

#include "../../config.h"
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
Exporter<Yaml, T> yamlExport(T const& value, PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default)
{
    return Exporter<Yaml, T>(value, characteristics);
}
template<typename T>
Importer<Yaml, T> yamlImport(T& value)
{
    return Importer<Yaml, T>(value);
}
    }
}

#endif

