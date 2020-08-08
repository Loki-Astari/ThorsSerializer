#ifndef THORS_ANVIL_SERIALIZE_BSON_PRINTER_H
#define THORS_ANVIL_SERIALIZE_BSON_PRINTER_H
/*
 * BsonaryPrinter<T>
 *  See documentation in BsonParser.h
 */

#include "Serialize.h"
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

class BsonPrinter: public PrinterInterface
{
    std::vector<std::pair<int, TraitType>> state;
    public:
        BsonPrinter(std::ostream& output, PrinterConfig config = PrinterConfig{});
        virtual void openDoc()                              override;
        virtual void closeDoc()                             override;

        virtual void openMap()                              override;
        virtual void closeMap()                             override;
        virtual void openArray(std::size_t size)            override;
        virtual void closeArray()                           override;

        virtual void addKey(std::string const& key)         override;

        virtual void addValue(short int value)              override;
        virtual void addValue(int value)                    override;
        virtual void addValue(long int value)               override;
        virtual void addValue(long long int value)          override;

        virtual void addValue(unsigned short int value)     override;
        virtual void addValue(unsigned int value)           override;
        virtual void addValue(unsigned long int value)      override;
        virtual void addValue(unsigned long long int value) override;

        virtual void addValue(float value)                  override;
        virtual void addValue(double value)                 override;
        virtual void addValue(long double value)            override;

        virtual void addValue(bool value)                   override;

        virtual void addValue(std::string const& value)     override;

        virtual void addRawValue(std::string const& value)  override;

        virtual void addNull()                              override;
};

    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "BsonPrinter.source"
#endif

#endif
