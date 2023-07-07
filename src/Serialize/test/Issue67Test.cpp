#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>
#include <sstream>

struct Type1
{
    int a;
};
struct Type2
{
    static int b;
    static Type1 c;
};

int Type2::b = 12;
Type1 Type2::c;

namespace ThorsAnvil { namespace Serialize {
template<>
class Traits<Type1 >
{
    public:
        static constexpr TraitType type = TraitType::Map;
        using MyType = Type1;

        using Members = std::tuple<
                        std::pair<char const*, decltype(&Type1::a)>
                                    >;

        static Members const& getMembers()
        {
            static constexpr Members members{
                        { "a", &Type1::a }
                                            };
            return members;
        }

                                                                        \
        template<typename M>
        static std::size_t addSizeOneMember(PrinterInterface& printer, MyType const& /*object*/, M* staticObjPtr)
        {
            using MemberType    = std::decay_t<M>;
            if (staticObjPtr)
            {
                return Traits<MemberType>::getPrintSize(printer, *staticObjPtr, false);
            }
            return printer.getSizeNull();
        }
        template<typename M>
        static std::size_t addSizeOneMember(PrinterInterface& printer, MyType const& object, M MyType::* memPtr)
        {
            using MemberTypeDec = decltype(object.*memPtr);
            using MemberType    = std::decay_t<MemberTypeDec>;
            return Traits<MemberType>::getPrintSize(printer, object.*memPtr, false);
        }

        template<typename M>
        static std::pair<std::size_t, std::size_t> addSizeEachMemberItem(PrinterInterface& printer, MyType const& object, M item)
        {
            if (!Filter<MyType>::filter(object, item.first)) {
                return std::make_pair(0UL,0UL);
            }
            auto partSize   = addSizeOneMember(printer, object, item.second);
            auto nameSize   = std::strlen(Override<MyType>::nameOverride(item.first));
            return std::make_pair(partSize + nameSize, 1);
        }
        template<std::size_t... Seq>
        static std::pair<std::size_t, std::size_t> addSizeEachMember(PrinterInterface& printer, MyType const& object, std::index_sequence<Seq...> const&)
        {
            Members const& members = getMembers();
            std::initializer_list<std::pair<std::size_t, std::size_t>>  sizeData = {
                std::make_pair(std::size_t{0}, std::size_t{0}),
                addSizeEachMemberItem(printer, object, std::get<Seq>(members))...
            };
            return std::accumulate(std::begin(sizeData), std::end(sizeData), std::make_pair(0UL, 0UL),
                                   [](auto lhs, auto rhs){return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);});
        }

        static std::size_t getPrintSizeTotal(PrinterInterface& printer, MyType const& object, std::size_t& count, std::size_t& memberSize)
        {
            auto r = addSizeEachMember(printer, object, std::make_index_sequence<std::tuple_size_v<Members>>());
            memberSize  += r.first;
            count       += r.second;

            CalcSizeHelper<MyType>  calcHelper;
            return calcHelper.getPrintSize(printer, object, count, memberSize);
        }

        static std::size_t getPrintSize(PrinterInterface& printer, MyType const& object, bool poly)
        {
            return tryGetPolyMorphicPrintSize(printer, object, poly, 0);
        }
};
}}
static_assert(
    ::ThorsAnvil::Serialize::Traits<Type1>::type != ThorsAnvil::Serialize::TraitType::Invalid,
    "The macro ThorsAnvil_MakeTrait must be used outside all namespace."
);
namespace ThorsAnvil { namespace Serialize {
namespace
{
    ThorsAnvil_InitPolyMorphicType<Type1>    thorUniqueNameMartin1("Type1");
}
}}


// ThorsAnvil_MakeTrait_Base( , Map, 00, Type2, b, c, 1);
namespace ThorsAnvil { namespace Serialize {
template<>
class Traits<Type2 >
{
    public:
        static constexpr TraitType type = TraitType::Map;
        using MyType = Type2;

        using Members = std::tuple<
                        std::pair<char const*, decltype(&Type2::b)>,
                        std::pair<char const*, decltype(&Type2::c)>
                                    >;

        static Members const& getMembers()
        {
            static constexpr Members members{
                        { "b", &Type2::b },
                        { "c", &Type2::c }
                                            };
            return members;
        }

                                                                        \
        template<typename M>
        static std::size_t addSizeOneMember(PrinterInterface& printer, MyType const& /*object*/, M* staticObjPtr)
        {
            using MemberType    = std::decay_t<M>;
            if (staticObjPtr)
            {
                return Traits<MemberType>::getPrintSize(printer, *staticObjPtr, false);
            }
            return printer.getSizeNull();
        }
        template<typename M>
        static std::size_t addSizeOneMember(PrinterInterface& printer, MyType const& object, M MyType::* memPtr)
        {
            using MemberTypeDec = decltype(object.*memPtr);
            using MemberType    = std::decay_t<MemberTypeDec>;
            return Traits<MemberType>::getPrintSize(printer, object.*memPtr, false);
        }

        template<typename M>
        static std::pair<std::size_t, std::size_t> addSizeEachMemberItem(PrinterInterface& printer, MyType const& object, M item)
        {
            if (!Filter<MyType>::filter(object, item.first)) {
                return std::make_pair(0UL,0UL);
            }
            auto partSize   = addSizeOneMember(printer, object, item.second);
            auto nameSize   = std::strlen(Override<MyType>::nameOverride(item.first));
            return std::make_pair(partSize + nameSize, 1);
        }
        template<std::size_t... Seq>
        static std::pair<std::size_t, std::size_t> addSizeEachMember(PrinterInterface& printer, MyType const& object, std::index_sequence<Seq...> const&)
        {
            Members const& members = getMembers();
            std::initializer_list<std::pair<std::size_t, std::size_t>>  sizeData = {
                std::make_pair(std::size_t{0}, std::size_t{0}),
                addSizeEachMemberItem(printer, object, std::get<Seq>(members))...
            };
            return std::accumulate(std::begin(sizeData), std::end(sizeData), std::make_pair(0UL, 0UL),
                                   [](auto lhs, auto rhs){return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);});
        }

        static std::size_t getPrintSizeTotal(PrinterInterface& printer, MyType const& object, std::size_t& count, std::size_t& memberSize)
        {
            auto r = addSizeEachMember(printer, object, std::make_index_sequence<std::tuple_size_v<Members>>());
            memberSize  += r.first;
            count       += r.second;

            CalcSizeHelper<MyType>  calcHelper;
            return calcHelper.getPrintSize(printer, object, count, memberSize);
        }

        static std::size_t getPrintSize(PrinterInterface& printer, MyType const& object, bool poly)
        {
            return tryGetPolyMorphicPrintSize(printer, object, poly, 0);
        }
};
}}
static_assert(
    ::ThorsAnvil::Serialize::Traits<Type2>::type != ThorsAnvil::Serialize::TraitType::Invalid,
    "The macro ThorsAnvil_MakeTrait must be used outside all namespace."
);
namespace ThorsAnvil { namespace Serialize {
namespace
{
    ThorsAnvil_InitPolyMorphicType<Type2>   thorUniqueNameMartin2("Type2");
}
}}





TEST(Issue67Test, StaticMemberSerialization)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::jsonImporter;

    std::stringstream    fileStream;
    Type2 entity;
    fileStream >> jsonImporter(entity);
    fileStream << jsonExporter(entity);

}

