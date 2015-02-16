
#ifndef THORS_ANVIL_SERIALZIE_SER_VECTOR_H
#define THORS_ANVIL_SERIALZIE_SER_VECTOR_H

#include "Traits.h"
#include "Serialize.h"
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class Traits<std::vector<T>>
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
                {   throw std::runtime_error("ThorsAnvil::Serializer::SerVector::GetValueType::GetValueType<Value>: Expecting a normal value after the key");
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
    public:
        static constexpr TraitType type = TraitType::Array;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor() {}
                void operator()(PrinterInterface& printer, std::vector<T> const& object) const
                {
                    PutValueType<T>    putter(printer);
                    for(auto const& loop: object)
                    {
                        putter.putValue(loop);
                    }
                }
                void operator()(ParserInterface& parser, std::string const&, std::vector<T>& object) const
                {
                    T                       value;
                    GetValueType<T>         valueGetter(parser, value);
                    object.push_back(std::move(value));
                }
        };

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

    }
}

#endif


