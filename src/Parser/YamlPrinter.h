
#ifndef THORS_ANVIL_SERIALIZATION_YAML_PRINTER_H
#define THORS_ANVIL_SERIALIZATION_YAML_PRINTER_H

#include "Serialize.h"
#include <yaml.h>

namespace ThorsAnvil
{
    namespace Serialization
    {

class YamlPrinter: public PrinterInterface
{
    yaml_emitter_t    emitter;
    bool              error;
    std::vector<std::pair<int, TraitType>> state;

    void checkYamlResultCode(int code, char const* method, char const* msg);
    void checkYamlResultCode(std::function<int(yaml_event_t&)> init, char const* method, char const* msg);
    template<typename T>
    void emit(T const& data);
    public:
        YamlPrinter(std::ostream& output, OutputType characteristics = OutputType::Default);
        ~YamlPrinter();
        virtual void openDoc();
        virtual void closeDoc();
        virtual void openMap();
        virtual void closeMap();
        virtual void openArray();
        virtual void closeArray();

        virtual void addKey(std::string const& key);
        virtual void addValue(bool value);
        virtual void addValue(int value);
        virtual void addValue(double value);
        virtual void addValue(std::nullptr_t);
        virtual void addValue(char const* value);
        virtual void addValue(std::string const& value);
};

    }
}

#endif

