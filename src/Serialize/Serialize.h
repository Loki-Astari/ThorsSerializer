
#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_H
#define THORS_ANVIL_SERIALIZE_SERIALIZE_H

#include <iostream>
#include "Traits.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

class ParserInterface
{
    public:
        enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};
        std::istream&   input;
        ParserToken     pushBack;

        ParserInterface(std::istream& input)
            : input(input)
            , pushBack(ParserToken::Error)
        {}
        virtual ~ParserInterface() {}
                ParserToken     getToken();
                void            pushBackToken(ParserToken token);
        virtual ParserToken     getNextToken()          = 0;
        virtual std::string     getKey()                = 0;
        virtual void    getValue(bool& value)           = 0;
        virtual void    getValue(int& value)            = 0;
        virtual void    getValue(double& value)         = 0;
        virtual void    getValue(std::nullptr_t)        = 0;
        virtual void    getValue(char*& value)          = 0;
        virtual void    getValue(std::string& value)    = 0;
};
class PrinterInterface
{
    public:
        enum class OutputType {Default, Stream, Config};
        // Default:     What ever the implementation likes.
        // Stream:      Compressed for over the wire protocol.
        // Config:      Human readable (potentially config file like)

        std::ostream&   output;
        OutputType      characteristics;

        PrinterInterface(std::ostream& output, OutputType characteristics = OutputType::Default)
            : output(output)
            , characteristics(characteristics)
        {}
        virtual ~PrinterInterface() {}
        virtual void openDoc()      = 0;
        virtual void closeDoc()     = 0;
        virtual void openMap()      = 0;
        virtual void closeMap()     = 0;
        virtual void openArray()    = 0;
        virtual void closeArray()   = 0;

        virtual void addKey(std::string const& key)     = 0;
        virtual void addValue(bool value)               = 0;
        virtual void addValue(int value)                = 0;
        virtual void addValue(double value)             = 0;
        virtual void addValue(std::nullptr_t)           = 0;
        virtual void addValue(char const* value)        = 0;
        virtual void addValue(std::string const& value) = 0;
};

class Serializer;
class DeSerializer;

template<TraitType type, typename T>
class ApplyActionToParent
{
    public:
        // Default do nothing.
        void printParentMembers(Serializer&, T const&)                      {}
        void scanParentMember(DeSerializer&, std::string const&, T&)        {}
};

template<TraitType traitType, typename T>
class DeSerializationForBlock
{
    static_assert(
        traitType != TraitType::Invalid,
        "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>"
    );
};

template<typename T, typename M, TraitType type = Traits<M>::type>
class DeSerializeMember
{
    using ParserToken = ParserInterface::ParserToken;
    public:
        DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo);
};

class DeSerializer
{
    using ParserToken = ParserInterface::ParserToken;
    ParserInterface&    parser;
    bool                root;

    template<typename T, typename Members, std::size_t... Seq>
    void scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&);

    template<typename T, typename... Members>
    void scanMembers(std::string const& key, T& object, std::tuple<Members...> const& members);

    template<typename T, typename Action>
    void scanMembers(std::string const& key, T& object, Action action);
    public:
        DeSerializer(ParserInterface& parser, bool root = true);
        ~DeSerializer();

        template<typename T>
        void parse(T& object);

        template<typename T>
        void scanObjectMembers(std::string const& key, T& object);
};

template<TraitType traitType, typename T>
class SerializerForBlock
{
    static_assert(
        traitType != TraitType::Invalid,
        "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>"
    );
};

template<typename T, typename M, TraitType type = Traits<typename std::remove_cv<M>::type>::type>
class SerializeMember
{
    public:
        SerializeMember(PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo);
};

class Serializer
{
    PrinterInterface& printer;
    bool              root;

    template<typename T, typename Members, std::size_t... Seq>
    void printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&);

    template<typename T, typename... Members>
    void printMembers(T const& object, std::tuple<Members...> const& members);

    template<typename T, typename Action>
    void printMembers(T const& object, Action action);

    public:
        Serializer(PrinterInterface& printer, bool root = true);
        ~Serializer();

        template<typename T>
        void print(T const& object);

        template<typename T>
        void printObjectMembers(T const& object);
};

    }
}

#ifndef COVERAGE_TEST
#include "Serialize.tpp"
#endif

#endif

