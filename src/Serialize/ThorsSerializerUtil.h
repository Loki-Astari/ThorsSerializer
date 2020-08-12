#ifndef THORS_ANVIL_SERIALIZER_THORSSERIALIZERUTIL_H
#define THORS_ANVIL_SERIALIZER_THORSSERIALIZERUTIL_H

#include <type_traits>
#include <string>
#include <iostream>
#include <cstddef>

namespace ThorsAnvil
{
    namespace Serialize
    {

extern std::string const defaultPolymorphicMarker;

/*
 * Defines the generic type that all serialization types can expand on
 */
enum class TraitType {Invalid, Parent, Value, Map, Array, Enum, Pointer, Serialize};

template<typename T>
class Traits;

template <typename, typename = void>
struct HasParent: std::false_type
{};

template <class T>
struct HasParent<T, std::enable_if_t<(sizeof(typename Traits<T>::Parent) >= 0)>>: std::true_type
{};

/*
 * A class for holding multiple header types.
 * Multiple enheritance is a rare case but it does happen (has been requested).
 * Because we are using macros I can allow a comma seporated list of parents so we have to
 * group the types into a single unique type "Parents". Then we will specialize the parsing
 * and printing code to handle this as a special case.
 */
template<typename... P>
struct Parents: public std::tuple<P...> {};

/*
 * To help the macros check the parent type we need to extract the type.
 * There is a special case when we use "Parents" to get the first type
 */
template<typename T>
struct GetPrimaryParentType
{
    using type = T;
};
template<typename... Args>
struct GetPrimaryParentType<Parents<Args...>>
{
    using type = typename std::tuple_element<0, std::tuple<Args...>>::type;
};

class ParserInterface
{
    public:
        enum class ParseType   {Weak, Strict, Exact};
        enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};
        struct ParserConfig
        {
            ParserConfig(ParseType parseStrictness = ParseType::Weak,
                         std::string const& polymorphicMarker = defaultPolymorphicMarker,
                         bool catchExceptions = true)
                : parseStrictness(parseStrictness)
                , polymorphicMarker(polymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            ParserConfig(std::string const& polymorphicMarker, bool catchExceptions = true)
                : parseStrictness(ParseType::Weak)
                , polymorphicMarker(polymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            ParserConfig(bool catchExceptions)
                : parseStrictness(ParseType::Weak)
                , polymorphicMarker(defaultPolymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            ParserConfig(ParseType parseStrictness, bool catchExceptions)
                : parseStrictness(parseStrictness)
                , polymorphicMarker(defaultPolymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            ParseType       parseStrictness;
            std::string     polymorphicMarker;
            bool            catchExceptions;
            long            parserInfo;
        };

        std::istream&   input;
        ParserToken     pushBack;
        ParserConfig    config;

        ParserInterface(std::istream& input, ParserConfig  config = ParserConfig{})
            : input(input)
            , pushBack(ParserToken::Error)
            , config(config)
        {}
        virtual ~ParserInterface() {}
                ParserToken     getToken();
                void            pushBackToken(ParserToken token);
        virtual ParserToken     getNextToken()          = 0;
        virtual std::string     getKey()                = 0;

        virtual void    ignoreDataValue()                {}

        virtual void    getValue(short int&)             = 0;
        virtual void    getValue(int&)                   = 0;
        virtual void    getValue(long int&)              = 0;
        virtual void    getValue(long long int&)         = 0;

        virtual void    getValue(unsigned short int&)    = 0;
        virtual void    getValue(unsigned int&)          = 0;
        virtual void    getValue(unsigned long int&)     = 0;
        virtual void    getValue(unsigned long long int&)= 0;

        virtual void    getValue(float&)                 = 0;
        virtual void    getValue(double&)                = 0;
        virtual void    getValue(long double&)           = 0;

        virtual void    getValue(bool&)                  = 0;

        virtual void    getValue(std::string&)           = 0;

        virtual bool    isValueNull()                    = 0;

        virtual std::string getRawValue()                = 0;

        void    ignoreValue();
    private:
        void    ignoreTheValue();
        void    ignoreTheMap();
        void    ignoreTheArray();

};

class PrinterInterface
{
    public:
        enum class OutputType {Default, Stream, Config};
        struct PrinterConfig
        {
            PrinterConfig(OutputType characteristics = OutputType::Default,
                          std::string const& polymorphicMarker = defaultPolymorphicMarker,
                          bool catchExceptions = true)
                : characteristics(characteristics)
                , polymorphicMarker(polymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            PrinterConfig(std::string const& polymorphicMarker,
                          bool catchExceptions = true)
                : characteristics(OutputType::Default)
                , polymorphicMarker(polymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            PrinterConfig(bool catchExceptions)
                : characteristics(OutputType::Default)
                , polymorphicMarker(defaultPolymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            PrinterConfig(OutputType characteristic, bool catchExceptions)
                : characteristics(characteristic)
                , polymorphicMarker(defaultPolymorphicMarker)
                , catchExceptions(catchExceptions)
                , parserInfo(0)
            {}
            OutputType      characteristics;
            std::string     polymorphicMarker;
            bool            catchExceptions;
            long            parserInfo;
        };
        // Default:     What ever the implementation likes.
        // Stream:      Compressed for over the wire protocol.
        // Config:      Human readable (potentially config file like)

        std::ostream&   output;
        PrinterConfig   config;

        PrinterInterface(std::ostream& output, PrinterConfig config = PrinterConfig{})
            : output(output)
            , config(config)
        {}
        virtual ~PrinterInterface() {}
        virtual void openDoc()                          = 0;
        virtual void closeDoc()                         = 0;
        virtual void openMap(std::size_t size)          = 0;
        virtual void closeMap()                         = 0;
        virtual void openArray(std::size_t size)        = 0;
        virtual void closeArray()                       = 0;

        virtual void    addKey(std::string const& key)  = 0;

        virtual void    addValue(short int)             = 0;
        virtual void    addValue(int)                   = 0;
        virtual void    addValue(long int)              = 0;
        virtual void    addValue(long long int)         = 0;

        virtual void    addValue(unsigned short int)    = 0;
        virtual void    addValue(unsigned int)          = 0;
        virtual void    addValue(unsigned long int)     = 0;
        virtual void    addValue(unsigned long long int)= 0;

        virtual void    addValue(float)                 = 0;
        virtual void    addValue(double)                = 0;
        virtual void    addValue(long double)           = 0;

        virtual void    addValue(bool)                  = 0;

        virtual void    addValue(std::string const&)    = 0;

        virtual void    addRawValue(std::string const&) = 0;

        virtual void    addNull()                       = 0;

        void addValue(void*)        = delete;
        void addValue(void const*)  = delete;

        virtual bool        printerUsesSize()                       {return false;}
        virtual std::size_t getSizeMap(std::size_t /*count*/)       {return 0;}
        virtual std::size_t getSizeArray(std::size_t /*count*/)     {return 0;}
        virtual std::size_t getSizeNull()                           {return 0;}
        virtual std::size_t getSizeValue(short int)                 {return 0;}
        virtual std::size_t getSizeValue(int)                       {return 0;}
        virtual std::size_t getSizeValue(long int)                  {return 0;}
        virtual std::size_t getSizeValue(long long int)             {return 0;}
        virtual std::size_t getSizeValue(unsigned short int)        {return 0;}
        virtual std::size_t getSizeValue(unsigned int)              {return 0;}
        virtual std::size_t getSizeValue(unsigned long int)         {return 0;}
        virtual std::size_t getSizeValue(unsigned long long int)    {return 0;}
        virtual std::size_t getSizeValue(float)                     {return 0;}
        virtual std::size_t getSizeValue(double)                    {return 0;}
        virtual std::size_t getSizeValue(long double)               {return 0;}
        virtual std::size_t getSizeValue(bool)                      {return 0;}
        virtual std::size_t getSizeValue(std::string const&)        {return 0;}
};

template<typename T, bool = HasParent<T>::value>
struct CalcSizeHelper
{
    std::size_t getPrintSize(PrinterInterface& printer, T const& /*object*/, std::size_t& count, std::size_t& memberSize)
    {
        return memberSize + printer.getSizeMap(count);
    }
};
template<typename T>
struct CalcSizeHelper<T, true>
{
    std::size_t getPrintSize(PrinterInterface& printer, T const& object, std::size_t& count, std::size_t& memberSize)
    {
        return ThorsAnvil::Serialize::Traits<typename Traits<T>::Parent>::getPrintSizeTotal(printer, object, count, memberSize);
    }
};

/*
 * Basic Types:
 * ============
 *
 * Traits<short int>
 * Traits<int>
 * Traits<long int>
 * Traits<long long int>
 * Traits<unsigned short int>
 * Traits<unsigned int>
 * Traits<unsigned long int>
 * Traits<unsigned long long int>
 *
 * Traits<float>
 * Traits<double>
 * Traits<long double>
 *
 * Traits<bool>
 *
 * Traits<std::string>
 *
 * Partial Types:
 * ==============
 * Pointer Types
 *  Traits<T*>
 *
 * Special Thor Types
 * ==================
 *  Traits<Parents<>>
 *
 */

/*
 * Declare types that can be read/written directly by the parser/printer
 * as value types. Other compound types need to use the Serializer/Deserializer
 */

#define THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(TYPE)                \
template<>                                                          \
class Traits<TYPE>                                                  \
{                                                                   \
    public:                                                         \
        static constexpr TraitType type = TraitType::Value;         \
        static std::size_t getPrintSize(PrinterInterface& printer, TYPE const& value) \
        {                                                           \
            return printer.getSizeValue(value);                     \
        }                                                           \
}

THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(short int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(long int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(long long int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(unsigned short int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(unsigned int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(unsigned long int);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(unsigned long long int);

THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(float);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(double);
THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(long double);

THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(bool);

THORSANVIL_TRAITS_FOR_BASIC_TYPE_VALUE(std::string);

#if 0
template<> class Traits<short int>              {public: THORSANVIL_TRAITS_FOR_VALUE(short int)};
template<> class Traits<int>                    {public: THORSANVIL_TRAITS_FOR_VALUE(int)};
template<> class Traits<long int>               {public: THORSANVIL_TRAITS_FOR_VALUE(long int)};
template<> class Traits<long long int>          {public: THORSANVIL_TRAITS_FOR_VALUE(long long int)};

template<> class Traits<unsigned short int>     {public: THORSANVIL_TRAITS_FOR_VALUE(unsigned short int)};
template<> class Traits<unsigned int>           {public: THORSANVIL_TRAITS_FOR_VALUE(unsigned int)};
template<> class Traits<unsigned long int>      {public: THORSANVIL_TRAITS_FOR_VALUE(unsigned long int)};
template<> class Traits<unsigned long long int> {public: THORSANVIL_TRAITS_FOR_VALUE(unsigned long long int)};

template<> class Traits<float>                  {public: THORSANVIL_TRAITS_FOR_VALUE(float)};
template<> class Traits<double>                 {public: THORSANVIL_TRAITS_FOR_VALUE(double)};
template<> class Traits<long double>            {public: THORSANVIL_TRAITS_FOR_VALUE(long double)};

template<> class Traits<bool>                   {public: THORSANVIL_TRAITS_FOR_VALUE(bool)};

template<> class Traits<std::string>            {public: THORSANVIL_TRAITS_FOR_VALUE(std::string const&)};
#endif

/*
 * A specialization for pointer objects.
 * They are a pointer type. When serialized a pointer will emit:
 *      If the pointer is nullptr:      A "null" object.
 *      Otherwise de-reference the pointer and emit like normal.
 *
 * If the de-referenced type has a Traits class then it will be normally
 * serialized. Otherwise there will be an error.
 */
template<typename T>
class Traits<T*>
{
    public:
        static constexpr TraitType type = TraitType::Pointer;
        static T*   alloc()         {return new T;}
        static void release(T* p)   {delete p;}
        static std::size_t getPrintSize(PrinterInterface& printer, T* object)
        {
            if (object)
            {
                return Traits<T>::getPrintSize(printer, *object);
            }
            return printer.getSizeNull();
        }
};

/*
 * Specialization of Parents so we can handle them in normal streaming operations
 */
template<typename... Args>
class Traits<Parents<Args...>>
{
    public:
        static constexpr TraitType type = TraitType::Parent;

        template<typename ChildType, std::size_t Index>
        static std::size_t getPrintSizeTotalParent(PrinterInterface& printer, ChildType const& object, std::size_t& count, std::size_t& memberSize)
        {
            using Parent = typename std::tuple_element<Index, std::tuple<Args...>>::type;
            return Traits<Parent>::getPrintSizeTotal(printer, static_cast<Parent const&>(object), count, memberSize);
        }

        template<typename ChildType, std::size_t... Seq>
        static std::size_t getPrintSizeTotalAllParents(PrinterInterface& printer, ChildType const& object, std::size_t& count, std::size_t& memberSize, std::index_sequence<Seq...> const&)
        {
            auto sums = {0UL, getPrintSizeTotalParent<ChildType, Seq>(printer, object, count, memberSize)...};
            return *(sums.end() - 1);
        }

        template<typename ChildType>
        static std::size_t getPrintSizeTotal(PrinterInterface& printer, ChildType const& object, std::size_t& count, std::size_t& memberSize)
        {
            return getPrintSizeTotalAllParents(printer, object, count, memberSize, std::make_index_sequence<sizeof...(Args)>());
        }
};

    }
}

#endif
