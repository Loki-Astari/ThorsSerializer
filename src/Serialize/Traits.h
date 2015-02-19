
#ifndef THORS_ANVIL_SERIALIZE_TRAITS_H
#define THORS_ANVIL_SERIALIZE_TRAITS_H

#include <string>
#include <tuple>

/*
 * Macros for counting the number of arguments
 * Currently set up for a max of 20.
 */
#define NUM_ARGS(...)          NUM_ARGS_(0, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01)
#define NUM_ARGS_(Zero, I1, I2, I3, I4 ,I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, A, ...)  A

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
#define REP_OF_01(Act, P1, P2)          EXPAND(Act, P1, P2)


/* 
 * The actions we apply with REP_*
 *
 * TypeAction:      Declares a type to hold the name and a pointer to the internal object.
 * ValueAction:     Declares an initialization of the Type putting the name and the pointer
 *                  into the object
 */
#define TypeAction(Type, Member)        std::pair<char const*, decltype(&Type::Member)>
#define ValueAction(Type, Member)       { QUOTE(Member), &Type::Member }


/*
 * Defines a trait for a user defined type.
 * Lists the members of the type that can be serialized.
 */
#define ThorsAnvil_MakeTrait_Base(DataType, Parent, TType, ...)         \
template<>                                                              \
class ::ThorsAnvil::Serialize::Traits<DataType>                         \
{                                                                       \
    public:                                                             \
        static constexpr TraitType type = TraitType::TType;             \
        Parent                                                          \
                                                                        \
        using Members = std::tuple<                                     \
                        REP_N(TypeAction, DataType, __VA_ARGS__)        \
                                    >;                                  \
                                                                        \
        static Members const& getMembers()                              \
        {                                                               \
            static constexpr Members members{                           \
                        REP_N(ValueAction, DataType, __VA_ARGS__)       \
                                            };                          \
            return members;                                             \
        }                                                               \
};                                                                      \
                                                                        \
static_assert(                                                                                      \
    ::ThorsAnvil::Serialize::Traits<DataType>::type != ThorsAnvil::Serialize::TraitType::Invalid,   \
    "The macro ThorsAnvil_MakeTrait must be used outside all namespace."                            \
)

#define ThorsAnvil_MakeTrait(DataType, ...)                             \
    ThorsAnvil_MakeTrait_Base(DataType, , Map, __VA_ARGS__)

#define ThorsAnvil_ExpandTrait(ParentType, DataType, ...)               \
    static_assert(                                                      \
        std::is_base_of<ParentType, DataType>::value,                   \
        "ParentType must be a base class of DataType");                 \
    static_assert(                                                      \
        ::ThorsAnvil::Serialize::Traits<ParentType>::type != ThorsAnvil::Serialize::TraitType::Invalid, \
        "Parent type must have Serialization Traits defined"            \
    );                                                                  \
    ThorsAnvil_MakeTrait_Base(DataType, typedef ParentType Parent;, Parent, __VA_ARGS__)


/*
 * Defines the generic type that all serialization types can expand on
 */
namespace ThorsAnvil
{
    namespace Serialize
    {

enum class TraitType {Invalid, Parent, Value, Map, Array};
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
} ;

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

