
#ifndef THORS_ANVIL_SERIALIZE_YAML_PRINTER_H
#define THORS_ANVIL_SERIALIZE_YAML_PRINTER_H

#include "../../config.h"
#ifdef  HAVE_YAML

#include "Serialize.h"
#include <yaml.h>

namespace ThorsAnvil
{
    namespace Serialize
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
        virtual void openDoc()      override;
        virtual void closeDoc()     override;
        virtual void openMap()      override;
        virtual void closeMap()     override;
        virtual void openArray()    override;
        virtual void closeArray()   override;

        virtual void addKey(std::string const& key)         override;
        virtual void addValue(bool value)                   override;
        virtual void addValue(int value)                    override;
        virtual void addValue(double value)                 override;
        virtual void addValue(std::nullptr_t)               override;
        virtual void addValue(char const* value)            override;
        virtual void addValue(std::string const& value)     override;
};

    }
}

#endif
#endif

