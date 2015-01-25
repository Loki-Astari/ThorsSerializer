
#ifndef THORS_ANVIL_SERIALIZATION_SERIALIZE_H
#define THORS_ANVIL_SERIALIZATION_SERIALIZE_H

#include <iostream>

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

enum class TraitType {Invalid, Parent, Value, Map, Array};
template<typename T>
class Traits
{
    public:
        static constexpr TraitType type = TraitType::Invalid;
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

template<TraitType traitType>
class SerializerForBlock
{
    static_assert(traitType != TraitType::Invalid, "Invalid Serialization TraitType. This usually means you have not define ThorsAnvil::Serialization::Traits<Your Type>");
    PrinterInterface const&     printer;
    public:
         SerializerForBlock(PrinterInterface const& printer);
        ~SerializerForBlock();
};

// Need to define this for TraitType::Parent
// But have not examined that yet

template<> SerializerForBlock<TraitType::Value>::SerializerForBlock(PrinterInterface const& printer)   :printer(printer)   {}
template<> SerializerForBlock<TraitType::Value>::~SerializerForBlock()                                                     {}

template<> SerializerForBlock<TraitType::Map>::SerializerForBlock(PrinterInterface const& printer)     :printer(printer)   {std::cout << "{";}
template<> SerializerForBlock<TraitType::Map>::~SerializerForBlock()                                                       {std::cout << "}";}

template<> SerializerForBlock<TraitType::Array>::SerializerForBlock(PrinterInterface const& printer)   :printer(printer)   {std::cout << "[";}
template<> SerializerForBlock<TraitType::Array>::~SerializerForBlock()                                                     {std::cout << "]";}

template<typename T>
class Serializer
{
    PrinterInterface const& printer;
    public:
        Serializer(PrinterInterface const& printer)
            : printer(printer)
        {}

        void print(T const&)
        {
            SerializerForBlock<Traits<T>::type>     block(printer);
        }
};

    }
}

#endif

