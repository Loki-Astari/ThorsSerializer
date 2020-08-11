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
    std::string currentKey;
    public:
        BsonPrinter(std::ostream& output, PrinterConfig config = PrinterConfig{});
        virtual void openDoc()                                      override;
        virtual void closeDoc()                                     override;

        virtual void openMap(std::size_t size)                      override;
        virtual void closeMap()                                     override;
        virtual void openArray(std::size_t size)                    override;
        virtual void closeArray()                                   override;

        virtual void addKey(std::string const& key)                 override;

        virtual void addValue(short int value)                      override;
        virtual void addValue(int value)                            override;
        virtual void addValue(long int value)                       override;
        virtual void addValue(long long int value)                  override;

        virtual void addValue(unsigned short int value)             override;
        virtual void addValue(unsigned int value)                   override;
        virtual void addValue(unsigned long int value)              override;
        virtual void addValue(unsigned long long int value)         override;

        virtual void addValue(float value)                          override;
        virtual void addValue(double value)                         override;
        virtual void addValue(long double value)                    override;

        virtual void addValue(bool value)                           override;

        virtual void addValue(std::string const& value)             override;

        virtual void addRawValue(std::string const& value)          override;

        virtual void addNull()                                      override;
    private:

        void writeKey(char value);
        template<typename Int>
        void writeSize(Int size);
        template<std::size_t size, typename Int>
        void writeInt(Int value);
        template<std::size_t size, typename Float>
        void writeFloat(Float value);
        void writeBool(bool value);
        void writeString(std::string const& value);
        void writeNull();
        void writeBinary(std::string const& value);

        virtual bool        printerUsesSize()                       override;
        virtual std::size_t getSizeMap(std::size_t /*count*/)       override;
        virtual std::size_t getSizeArray(std::size_t /*count*/)     override;
        virtual std::size_t getSizeNull()                           override;
        virtual std::size_t getSizeValue(short)                     override;
        virtual std::size_t getSizeValue(int)                       override;
        virtual std::size_t getSizeValue(long int)                  override;
        virtual std::size_t getSizeValue(long long int)             override;
        virtual std::size_t getSizeValue(unsigned short)            override;
        virtual std::size_t getSizeValue(unsigned int)              override;
        virtual std::size_t getSizeValue(unsigned long int)         override;
        virtual std::size_t getSizeValue(unsigned long long int)    override;
        virtual std::size_t getSizeValue(float)                     override;
        virtual std::size_t getSizeValue(double)                    override;
        virtual std::size_t getSizeValue(long double)               override;
        virtual std::size_t getSizeValue(bool)                      override;
        virtual std::size_t getSizeValue(std::string const&)        override;
};

    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "BsonPrinter.source"
#endif

#endif
