#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
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
    ThorsAnvil_PolyMorphicSerializerWithOverride(TourResult);
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

TEST(PolyMorphicSerializerUniquePointerTestString, JsonQuantitiesEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 stream = R"({})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonQuantities)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 stream = R"({"quantities":[15,23]})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonAbstractTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 stream = R"({})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonAbstractTourResult)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 stream = R"({"maxQuantities":{}})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonAbstractTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 stream = R"({"maxQuantities":{"quantities":[34,56]}})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 stream = R"({})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonTourResult)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 stream = R"({"maxQuantities":{}})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 stream = R"({"maxQuantities":{"quantities":[34,56]}})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, JsonTourEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Tour                        t{};
    std::string                 stream = R"({})";;
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.result);
}

TEST(PolyMorphicSerializerUniquePointerTestString, BsonQuantitiesEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    //NOTE INPUT  = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonQuantities)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    //NOTE INPUT  = R"({"quantities":[15,23]})";;
    static const char strRaw[]
                    = "\x24\x00\x00\x00"
                      "\x04" "quantities\x00"
                            "\x13\x00\x00\x00"
                                "\x10" "0\x00" "\x0F\x00\x00\x00"
                                "\x10" "1\x00" "\x17\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonAbstractTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //NOTE INPUT  = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonAbstractTourResult)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //NOTE INPUT  = R"({"maxQuantities":{}})";;
    static const char strRaw[]
                    = "\x19\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x05\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonAbstractTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //NOTE INPUT  = R"({"maxQuantities":{"quantities":[34,56]}})";;
    static const char strRaw[]
                    = "\x38\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x24\x00\x00\x00"
                                "\x04" "quantities\x00"
                                    "\x13\x00\x00\x00"
                                        "\x10" "0\x00" "\x22\x00\x00\x00"
                                        "\x10" "1\x00" "\x38\x00\x00\x00"
                                    "\x00"
                            "\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //NOTE INPUT  = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonTourResult)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //NOTE INPUT  = R"({"maxQuantities":{}})";;
    static const char strRaw[]
                    = "\x19\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x05\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //NOTE INPUT  = R"({"maxQuantities":{"quantities":[34,56]}})";;
    static const char strRaw[]
                    = "\x38\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x24\x00\x00\x00"
                                "\x04" "quantities\x00"
                                    "\x13\x00\x00\x00"
                                        "\x10" "0\x00" "\x22\x00\x00\x00"
                                        "\x10" "1\x00" "\x38\x00\x00\x00"
                                    "\x00"
                            "\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTestString, BsonTourEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Tour                        t{};
    //NOTE INPUT  = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 stream(std::begin(strRaw), std::end(strRaw) - 1);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.result);
}


