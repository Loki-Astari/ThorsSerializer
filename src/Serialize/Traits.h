#ifndef THORS_ANVIL_SERIALIZE_TRAITS_H
#define THORS_ANVIL_SERIALIZE_TRAITS_H
/*
 *  This file is all about defineing the template type Traits<T>
 *
 *  Two macros are provides to facilitate the building of Traits<T>
 *  specializations for user defined types.
 *
 *      ThorsAnvil_MakeTrait(DataType, ...)
 *      ThorsAnvil_ExpandTrait(ParentType, DataType, ...)
 *      ThorsAnvil_MakeEnum(<EnumType>, <EnumValues>...)
 *
 * See README.md for examples.
 */

#include <string>
#include <tuple>

/*
 * Macros for counting the number of arguments
 * Currently set up for a max of 20.
 */
#define NUM_ARGS(...)          NUM_ARGS_(0, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00, Ignore)
#define NUM_ARGS_(Zero, One, I1, I2, I3, I4 ,I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, A, ...)  A

/*
 * Macros to quote the parameter
 * Used below by the actions.
 */
#define QUOTE_(A)                       A
#define QUOTE(A)                        QUOTE_(#A)

/*
 * Macro to force expansion of a macro that takes two parameters.
 * Used by REP_*
 */
#define EXPAND_(Result)                 Result
#define EXPAND(Act, P1, P2)             EXPAND_(Act(P1, P2))
#define ALT_EXPAND_(Result)             Result
#define ALT_EXPAND(Act, Ex, Id)         EXPAND_(Act(Ex, Id))

/*
 * Macros that that applies the action `Act` (a two parameter macro)
 * To P1 (first argument)
 * and a list of second arguments (placing a comma between each macro).
 *
 * Because NUM_ARGS is limited to 20, This expansion is also limited to 20
 */
#define REP_N(Act, P1, ...)             REP_OF_N(Act, P1, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define REP_OF_N(Act, P1, Count, ...)   REP_OF_N_(Act, P1, Count, __VA_ARGS__)
#define REP_OF_N_(Act, P1, Count, ...)  REP_OF_ ## Count(Act, P1, __VA_ARGS__)

#define REP_OF_20(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_19(Act, P1, __VA_ARGS__)
#define REP_OF_19(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_18(Act, P1, __VA_ARGS__)
#define REP_OF_18(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_17(Act, P1, __VA_ARGS__)
#define REP_OF_17(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_16(Act, P1, __VA_ARGS__)
#define REP_OF_16(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_15(Act, P1, __VA_ARGS__)
#define REP_OF_15(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_14(Act, P1, __VA_ARGS__)
#define REP_OF_14(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_13(Act, P1, __VA_ARGS__)
#define REP_OF_13(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_12(Act, P1, __VA_ARGS__)
#define REP_OF_12(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_11(Act, P1, __VA_ARGS__)
#define REP_OF_11(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_10(Act, P1, __VA_ARGS__)
#define REP_OF_10(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_09(Act, P1, __VA_ARGS__)
#define REP_OF_09(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_08(Act, P1, __VA_ARGS__)
#define REP_OF_08(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_07(Act, P1, __VA_ARGS__)
#define REP_OF_07(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_06(Act, P1, __VA_ARGS__)
#define REP_OF_06(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_05(Act, P1, __VA_ARGS__)
#define REP_OF_05(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_04(Act, P1, __VA_ARGS__)
#define REP_OF_04(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_03(Act, P1, __VA_ARGS__)
#define REP_OF_03(Act, P1, P2, ...)     EXPAND(Act, P1 ,P2), REP_OF_02(Act, P1, __VA_ARGS__)
#define REP_OF_02(Act, P1, P2, ...)     EXPAND(Act, P1, P2), REP_OF_01(Act, P1, __VA_ARGS__)
#define REP_OF_01(Act, P1, P2, One)     EXPAND(Act, P1, P2)
#define REP_OF_00(Act, P1, One)         LAST_ ## Act(P1)

#define ALT_REP_OF_N(Act, E, P, S, Count)  ALT_REP_OF_N_(Act, E, P, S, Count)
#define ALT_REP_OF_N_(Act, E, P, S, Count) ALT_REP_OF_ ## Count(Act, E, P, S)

#define ALT_REP_OF_20(Act, E, P, S)     P ALT_EXPAND(Act, E, 20), ALT_REP_OF_19(Act, E,  , S)
#define ALT_REP_OF_19(Act, E, P, S)     P ALT_EXPAND(Act, E, 19), ALT_REP_OF_18(Act, E,  , S)
#define ALT_REP_OF_18(Act, E, P, S)     P ALT_EXPAND(Act, E, 18), ALT_REP_OF_17(Act, E,  , S)
#define ALT_REP_OF_17(Act, E, P, S)     P ALT_EXPAND(Act, E, 17), ALT_REP_OF_16(Act, E,  , S)
#define ALT_REP_OF_16(Act, E, P, S)     P ALT_EXPAND(Act, E, 16), ALT_REP_OF_15(Act, E,  , S)
#define ALT_REP_OF_15(Act, E, P, S)     P ALT_EXPAND(Act, E, 15), ALT_REP_OF_14(Act, E,  , S)
#define ALT_REP_OF_14(Act, E, P, S)     P ALT_EXPAND(Act, E, 14), ALT_REP_OF_13(Act, E,  , S)
#define ALT_REP_OF_13(Act, E, P, S)     P ALT_EXPAND(Act, E, 13), ALT_REP_OF_12(Act, E,  , S)
#define ALT_REP_OF_12(Act, E, P, S)     P ALT_EXPAND(Act, E, 12), ALT_REP_OF_11(Act, E,  , S)
#define ALT_REP_OF_11(Act, E, P, S)     P ALT_EXPAND(Act, E, 11), ALT_REP_OF_10(Act, E,  , S)
#define ALT_REP_OF_10(Act, E, P, S)     P ALT_EXPAND(Act, E, 10), ALT_REP_OF_09(Act, E,  , S)
#define ALT_REP_OF_09(Act, E, P, S)     P ALT_EXPAND(Act, E, 09), ALT_REP_OF_08(Act, E,  , S)
#define ALT_REP_OF_08(Act, E, P, S)     P ALT_EXPAND(Act, E, 08), ALT_REP_OF_07(Act, E,  , S)
#define ALT_REP_OF_07(Act, E, P, S)     P ALT_EXPAND(Act, E, 07), ALT_REP_OF_06(Act, E,  , S)
#define ALT_REP_OF_06(Act, E, P, S)     P ALT_EXPAND(Act, E, 06), ALT_REP_OF_05(Act, E,  , S)
#define ALT_REP_OF_05(Act, E, P, S)     P ALT_EXPAND(Act, E, 05), ALT_REP_OF_04(Act, E,  , S)
#define ALT_REP_OF_04(Act, E, P, S)     P ALT_EXPAND(Act, E, 04), ALT_REP_OF_03(Act, E,  , S)
#define ALT_REP_OF_03(Act, E, P, S)     P ALT_EXPAND(Act, E, 03), ALT_REP_OF_02(Act, E,  , S)
#define ALT_REP_OF_02(Act, E, P, S)     P ALT_EXPAND(Act, E, 02), ALT_REP_OF_01(Act, E,  , S)
#define ALT_REP_OF_01(Act, E, P, S)     P ALT_EXPAND(Act, E, 01) S
#define ALT_REP_OF_00(Act, E, P, S)     LAST_ ## Act(E, 00)

/*
 * The actions we apply with REP_*
 *
 * THOR_TYPEACTION:      Declares a type to hold the name and a pointer to the internal object.
 * THOR_VALUEACTION:     Declares an initialization of the Type putting the name and the pointer
 *                  into the object
 */
#define THOR_TEMPLATE_PARAM                     00
#define BUILDTEMPLATETYPEPARAMEXP               BUILDTEMPLATETYPEPARAM(THOR_TYPENAMEPARAMACTION, THOR_TEMPLATE_PARAM)
#define BUILDTEMPLATETYPEVALUEEXP               BUILDTEMPLATETYPEVALUE(THOR_TYPENAMEVALUEACTION, THOR_TEMPLATE_PARAM)
#define BUILDTEMPLATETYPEPARAM(Act, Count)      ALT_REP_OF_N(Act, ,  ,  , Count)
#define BUILDTEMPLATETYPEVALUE(Act, Count)      ALT_REP_OF_N(Act, , <, >, Count)


#define THOR_TYPEACTION(Type, Member)           std::pair<char const*, decltype(&Type BUILDTEMPLATETYPEVALUEEXP ::Member)>
#define THOR_VALUEACTION(Type, Member)          { QUOTE(Member), &Type BUILDTEMPLATETYPEVALUEEXP ::Member }
#define THOR_NAMEACTION(Type, Member)           #Member
#define LAST_THOR_TYPEACTION(Type)              void*
#define LAST_THOR_VALUEACTION(Type)             {nullptr}
#define LAST_THOR_NAMEACTION(Type)              nullptr

#define THOR_TYPENAMEPARAMACTION(Ex, Id)        typename T ## Id
#define THOR_TYPENAMEVALUEACTION(Ex, Id)        T ## Id
#define THOR_CHECK_ASSERT(Ex, Id)
#define LAST_THOR_TYPENAMEPARAMACTION(Ex, Id)
#define LAST_THOR_TYPENAMEVALUEACTION(Ex, Id)
#define LAST_THOR_CHECK_ASSERT(Ex, Id)          DO_ASSERT(Ex)

/*
 * Defines a trait for a user defined type.
 * Lists the members of the type that can be serialized.
 */
#define DO_ASSERT(DataType)                                             \
static_assert(                                                          \
    ::ThorsAnvil::Serialize::Traits<DataType>::type != ThorsAnvil::Serialize::TraitType::Invalid,   \
    "The macro ThorsAnvil_MakeTrait must be used outside all namespace."\
)

#define ThorsAnvil_MakeTrait_Base(Parent, TType, DataType, ...)         \
namespace ThorsAnvil { namespace Serialize {                            \
template<BUILDTEMPLATETYPEPARAMEXP>                                     \
class Traits<DataType BUILDTEMPLATETYPEVALUEEXP >                       \
{                                                                       \
    public:                                                             \
        static constexpr TraitType type = TraitType::TType;             \
        Parent                                                          \
                                                                        \
        using Members = std::tuple<                                     \
                        REP_N(THOR_TYPEACTION, DataType, __VA_ARGS__)        \
                                    >;                                  \
                                                                        \
        static Members const& getMembers()                              \
        {                                                               \
            static constexpr Members members{                           \
                        REP_N(THOR_VALUEACTION, DataType, __VA_ARGS__)       \
                                            };                          \
            return members;                                             \
        }                                                               \
};                                                                      \
}}                                                                      \
ALT_REP_OF_N(THOR_CHECK_ASSERT, DataType, , , THOR_TEMPLATE_PARAM)

#define ThorsAnvil_MakeTrait(...)                                       \
    ThorsAnvil_MakeTrait_Base( , Map, __VA_ARGS__, 1)

#define ThorsAnvil_ExpandTrait_With_Ext(ParentType, DataType, ...)      \
    static_assert(                                                      \
        std::is_base_of<ParentType, DataType>::value,                   \
        "ParentType must be a base class of DataType");                 \
    static_assert(                                                      \
        ::ThorsAnvil::Serialize::Traits<ParentType>::type != ThorsAnvil::Serialize::TraitType::Invalid, \
        "Parent type must have Serialization Traits defined"            \
    );                                                                  \
    ThorsAnvil_MakeTrait_Base(typedef ParentType Parent;, Parent, DataType, __VA_ARGS__)

#define ThorsAnvil_ExpandTrait(ParentType, ...)                         \
    ThorsAnvil_ExpandTrait_With_Ext(ParentType, __VA_ARGS__, 1)

#define ThorsAnvil_MakeEnum(EnumName, ...)                              \
namespace ThorsAnvil { namespace Serialize {                            \
template<>                                                              \
class Traits<EnumName>                                                  \
{                                                                       \
    public:                                                             \
        static constexpr    TraitType       type = TraitType::Enum;     \
        static char const* const* getValues()                           \
        {                                                               \
            static constexpr char const* values[] = {                   \
                        REP_N(THOR_NAMEACTION, 0, __VA_ARGS__, 1)       \
                                                    };                  \
            return values;                                              \
        }                                                               \
        static std::size_t getSize()                                    \
        {                                                               \
            return NUM_ARGS(__VA_ARGS__, 1);                            \
        }                                                               \
        static EnumName getValue(std::string const& val, std::string const& msg) \
        {                                                               \
            char const* const* values = getValues();                    \
            std::size_t        size   = getSize();                      \
            for (std::size_t loop = 0;loop < size; ++loop)              \
            {                                                           \
                if (val == values[loop]) {                              \
                    return static_cast<EnumName>(loop);                 \
                }                                                       \
            }                                                           \
            throw std::runtime_error(msg + " Invalid Enum Value");      \
        }                                                               \
};                                                                      \
}}                                                                      \
DO_ASSERT(EnumName)


/*
 * Defines the generic type that all serialization types can expand on
 */
namespace ThorsAnvil
{
    namespace Serialize
    {

enum class TraitType {Invalid, Parent, Value, Map, Array, Enum};
template<typename T>
class Traits
{
    public:
        // By default if a traits type is not defined for a type
        // You get this default implementation.
        // This just says that it is invalid to serialize this type
        // static_asserts sprinkled through the code will provide
        // appropriate error messages based on this being invalid.
        static constexpr TraitType type = TraitType::Invalid;

        // For types that are Map/Array/Parent we can also define
        // members that need be serialized via types. To achieve this
        // they  define a static getMembers() function.
        // static Members const& getMembers()
        //
        // I would have made this a type declaration but I could
        // not get it to bind correctly without an explicit
        // instantiation (if you know how please let me know).
        //
        // So I use a static member function with a static variable
        // which can be defined in-line within the traits class and
        // does not need a separate declaration in a compilation unit.
};

/*
 * Declare types that can be read/written directly by the parser/printer
 * as value types. Other compound types need to use the Serializer/Deserializer
 */
template<> class Traits<short int>              {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<int>                    {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<long int>               {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<long long int>          {public: static constexpr TraitType type = TraitType::Value;};

template<> class Traits<unsigned short int>     {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<unsigned int>           {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<unsigned long int>      {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<unsigned long long int> {public: static constexpr TraitType type = TraitType::Value;};

template<> class Traits<float>                  {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<double>                 {public: static constexpr TraitType type = TraitType::Value;};
template<> class Traits<long double>            {public: static constexpr TraitType type = TraitType::Value;};

template<> class Traits<bool>                   {public: static constexpr TraitType type = TraitType::Value;};

template<> class Traits<std::string>            {public: static constexpr TraitType type = TraitType::Value;};

    }
}

#endif
