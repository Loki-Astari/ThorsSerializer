#include <gtest/gtest.h>
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <ranges>

class MyRange
{
    std::vector<int>    data{1,2,3,4,5,6,7,8};
    public:
        std::size_t size() const    {return data.size();}
        auto begin() const          {return std::begin(data);}
        auto end()   const          {return std::end(data);}
};

TEST(RangeTest, rangeAsJsonArray)
{
    std::stringstream str;
    MyRange       range;

    str << ThorsAnvil::Serialize::jsonExporter(range);

    EXPECT_EQ("\n[1, 2, 3, 4, 5, 6, 7, 8]", str.str());
}

TEST(RangeTest, rangeAsJsonArrayRValue)
{
    std::stringstream str;

    str << ThorsAnvil::Serialize::jsonExporter(MyRange{});

    EXPECT_EQ("\n[1, 2, 3, 4, 5, 6, 7, 8]", str.str());
}

TEST(RangeTest, rangeAsJsonArrayStream)
{
    std::stringstream str;
    MyRange       range;

    str << ThorsAnvil::Serialize::jsonExporter(range, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ("[1,2,3,4,5,6,7,8]", str.str());
}

TEST(RangeTest, rangeAsJsonArrayStreamRValue)
{
    std::stringstream str;

    str << ThorsAnvil::Serialize::jsonExporter(MyRange{}, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ("[1,2,3,4,5,6,7,8]", str.str());
}

TEST(RangeTest, rangeAsYamlArray)
{
    std::stringstream str;
    MyRange       range;

    str << ThorsAnvil::Serialize::yamlExporter(range);

    EXPECT_EQ(R"(---
- 1
- 2
- 3
- 4
- 5
- 6
- 7
- 8
...
)", str.str());
}

TEST(RangeTest, rangeAsYamlArrayRValue)
{
    std::stringstream str;

    str << ThorsAnvil::Serialize::yamlExporter(MyRange{});

    EXPECT_EQ(R"(---
- 1
- 2
- 3
- 4
- 5
- 6
- 7
- 8
...
)", str.str());
}

TEST(RangeTest, rangeAsYamlArrayStream)
{
    std::stringstream str;
    MyRange       range;

    str << ThorsAnvil::Serialize::yamlExporter(range, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ("--- [1, 2, 3, 4, 5, 6, 7, 8]\n...\n", str.str());
}

TEST(RangeTest, rangeAsYamlArrayStreamRValue)
{
    std::stringstream str;

    str << ThorsAnvil::Serialize::yamlExporter(MyRange{}, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ("--- [1, 2, 3, 4, 5, 6, 7, 8]\n...\n", str.str());
}

TEST(RangeTest, rangeAsBsonArray)
{
    std::stringstream str;
    MyRange       range;

    str << ThorsAnvil::Serialize::bsonExporter(range);

    char result[] = "\x3d\x00\x00\x00"                  // 61
                "\x10" "0\x00"    "\x01\x00\x00\x00"    // 7
                "\x10" "1\x00"    "\x02\x00\x00\x00"    // 14
                "\x10" "2\x00"    "\x03\x00\x00\x00"    // 21
                "\x10" "3\x00"    "\x04\x00\x00\x00"    // 28
                "\x10" "4\x00"    "\x05\x00\x00\x00"    // 35
                "\x10" "5\x00"    "\x06\x00\x00\x00"    // 42
                "\x10" "6\x00"    "\x07\x00\x00\x00"    // 49
                "\x10" "7\x00"    "\x08\x00\x00\x00"    // 56
                "\x00"                                  // 57
                "\x00";                                 // Buffer for testing not expected result

    EXPECT_EQ(61, str.str().size());
    for (int loop = 0; loop < 61; ++loop) {
        std::cerr << "Loop: " << loop << "\n";
        EXPECT_EQ(result[loop], str.str()[loop]);
    }
}

TEST(RangeTest, rangeAsBsonArrayRValue)
{
    std::stringstream str;

    str << ThorsAnvil::Serialize::bsonExporter(MyRange{});

    char result[] = "\x3d\x00\x00\x00"                  // 61
                "\x10" "0\x00"    "\x01\x00\x00\x00"    // 7
                "\x10" "1\x00"    "\x02\x00\x00\x00"    // 14
                "\x10" "2\x00"    "\x03\x00\x00\x00"    // 21
                "\x10" "3\x00"    "\x04\x00\x00\x00"    // 28
                "\x10" "4\x00"    "\x05\x00\x00\x00"    // 35
                "\x10" "5\x00"    "\x06\x00\x00\x00"    // 42
                "\x10" "6\x00"    "\x07\x00\x00\x00"    // 49
                "\x10" "7\x00"    "\x08\x00\x00\x00"    // 56
                "\x00"                                  // 57
                "\x00";                                 // Buffer for testing not expected result

    EXPECT_EQ(61, str.str().size());
    for (int loop = 0; loop < 61; ++loop) {
        std::cerr << "Loop: " << loop << "\n";
        EXPECT_EQ(result[loop], str.str()[loop]);
    }
}
