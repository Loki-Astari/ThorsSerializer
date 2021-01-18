
#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"

struct FilterTestType
{
    std::string     m1;
    std::string     m2;

    std::map<std::string, bool> filter;
};

ThorsAnvil_MakeTrait(FilterTestType, m1, m2);
ThorsAnvil_MakeTraitName_Filter(FilterTestType, filter);

TEST(FilterMemberTests, FilterOutZeroMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterMemberTests, FilterOutM1Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterMemberTests, FilterOutM2Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}
TEST(FilterMemberTests, FilterOutAllMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}
