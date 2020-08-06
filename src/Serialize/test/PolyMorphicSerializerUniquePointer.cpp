#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <iostream>

namespace PolyMorphicSerializerUniquePointerTest
{
struct Quantities
{
    std::vector<int>* quantities;

    ~Quantities()
    {
        delete quantities;
    }
};

struct AbstractTourResult
{
    std::unique_ptr<Quantities> maxQuantities { nullptr };
    virtual ~AbstractTourResult() = default;
    ThorsAnvil_PolyMorphicSerializer(AbstractTourResult);
};

struct TourResult : public AbstractTourResult
{
    ~TourResult() override                      = default;
    ThorsAnvil_PolyMorphicSerializer(TourResult);
};

struct Tour
{
    std::unique_ptr<TourResult> result { nullptr };
};
}

ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::Quantities, quantities);
ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::AbstractTourResult, maxQuantities);
ThorsAnvil_ExpandTrait(PolyMorphicSerializerUniquePointerTest::AbstractTourResult, PolyMorphicSerializerUniquePointerTest::TourResult);
ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::Tour, result);

TEST(PolyMorphicSerializerUniquePointerTest, QuantitiesEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, Quantities)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 str = R"({"quantities":[15,23]})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResult)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResult)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Tour                        t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.result);
}

