
#ifndef THORS_ANVIL_SERIALIZATION_JSON_PRINTER_H
#define THORS_ANVIL_SERIALIZATION_JSON_PRINTER_H

#include "Serialize.h"

namespace ThorsAnvil
{
    namespace Serialization
    {

class JsonPrinter: public PrinterInterface
{
    std::vector<std::pair<int, TraitType>> state;
    public:
        JsonPrinter(std::ostream& output, OutputType characteristics = OutputType::Default);
        virtual void openDoc();
        virtual void closeDoc();

        virtual void openMap()          override;
        virtual void closeMap()         override;
        virtual void openArray()        override;
        virtual void closeArray()       override;

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

