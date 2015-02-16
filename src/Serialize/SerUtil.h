
#ifndef THORS_ANVIL_SERIALIZE_SER_UTIL_H
#define THORS_ANVIL_SERIALIZE_SER_UTIL_H

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename V, TraitType type = Traits<V>::type>
class GetValueType
{
    public:
        GetValueType(ParserInterface& parser, V& value)
        {
            DeSerializer            deSerializer(parser, false);
            deSerializer.parse(value);
        }
};

template<typename V>
class GetValueType<V, TraitType::Value>
{
    public:
        GetValueType(ParserInterface& parser, V& value)
        {
            if (parser.getToken() != ThorsAnvil::Serialize::ParserInterface::ParserToken::Value)
            {   throw std::runtime_error("ThorsAnvil::Serializer::SerMap::GetValueType::GetValueType<Value>: Expecting a normal value after the key");
            }
            parser.getValue(value);
        }
};

template<typename V, TraitType type = Traits<V>::type>
class PutValueType
{
    Serializer      serializer;
    public:
        PutValueType(PrinterInterface& printer)
            : serializer(printer, false)
        {}
        void putValue(V const& value)
        {
            serializer.print(value);
        }
};
template<typename V>
class PutValueType<V, TraitType::Value>
{
    PrinterInterface&   printer;
    public:
        PutValueType(PrinterInterface& printer)
            : printer(printer)
        {}

        void putValue(V const& value)
        {
            printer.addValue(value);
        }
};
    }
}

#endif
