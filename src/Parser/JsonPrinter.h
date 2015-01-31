
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

