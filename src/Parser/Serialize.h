
#ifndef THORS_ANVIL_SERIALIZATION_SERIALIZE_H
#define THORS_ANVIL_SERIALIZATION_SERIALIZE_H

namespace ThorsAnvil
{
    namespace Serialization
    {

class ParserInterface
{
    public:
        virtual ~ParserInterface() {}
};
class PrinterInterface
{
    public:
        virtual ~PrinterInterface() {}
};

template<typename T>
class DeSerializer
{
    public:
        DeSerializer(ParserInterface const&)
        {}

        void parse(T&)
        {}
};

template<typename T>
class Serializer
{
    public:
        Serializer(PrinterInterface const&)
        {}

        void print(T const&)
        {}
};

    }
}

#endif

