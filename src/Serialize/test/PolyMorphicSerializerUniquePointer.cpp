
#include "gtest/gtest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <iostream>

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

ThorsAnvil_MakeTrait(Quantities, quantities);
ThorsAnvil_MakeTrait(AbstractTourResult, maxQuantities);
ThorsAnvil_ExpandTrait(AbstractTourResult, TourResult);
ThorsAnvil_MakeTrait(Tour, result);

TEST(PolyMorphicSerializerUniquePointerTest, QuantitiesEmpty)
{
    Quantities                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, Quantities)
{
    Quantities                  t{};
    std::string                 str = R"({"quantities":[15,23]})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResultEmpty)
{
    AbstractTourResult          t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResult)
{
    AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, AbstractTourResultWithQuantities)
{
    AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResultEmpty)
{
    TourResult                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResult)
{
    TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourResultWithQuantities)
{
    TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, TourEmpty)
{
    Tour                        t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(t);
    EXPECT_EQ(nullptr, t.result);
}

