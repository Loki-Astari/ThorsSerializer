#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedMultiMapTestString, Jsonserialize)
{
    std::unordered_multimap<int, double>  data;
    data.insert(std::make_pair(56, 78.901));
    data.insert(std::make_pair(56, 901));

    std::string       stream;
    stream << TS::jsonExporter(data);
    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    std::cerr << ">" << result << "<\n";

    bool test = result == R"([{"first":56,"second":78.901000},{"first":56,"second":901.000000}])"
             || result == R"([{"first":56,"second":901.000000},{"first":56,"second":78.901000}])";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTestString, JsondeSerialize)
{
    std::unordered_multimap<int, double>  data;

    std::string        stream(R"([{"first":64,"second":12}, {"first":118,"second":14}, {"first":118,"second": 112}])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(64) != data.end());
    EXPECT_TRUE(data.find(118) != data.end());
    EXPECT_EQ(data.count(118), 2);
}

TEST(SerUnorderedMultiMapTestString, JsonserializeStringKey)
{
    std::unordered_multimap<std::string, double>  data;
    data.insert(std::make_pair("AStringKey", 78.902));
    data.insert(std::make_pair("TestValue",  22.903));
    data.insert(std::make_pair("TestValue",  903));

    std::string       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test =  result == R"({"AStringKey":78.902000,"TestValue":22.903000,"TestValue":903.000000})"
              || result == R"({"AStringKey":78.902000,"TestValue":903.000000,"TestValue":22.903000})"
              || result == R"({"TestValue":22.903000,"AStringKey":78.902000,"TestValue":903.000000})"
              || result == R"({"TestValue":22.903000,"TestValue":903.000000,"AStringKey":78.902000})"
              || result == R"({"TestValue":903.000000,"AStringKey":78.902000,"TestValue":22.903000})"
              || result == R"({"TestValue":903.000000,"TestValue":22.903000,"AStringKey":78.902000})";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTestString, JsondeSerializeStringKey)
{
    std::unordered_multimap<std::string, bool>  data;

    std::string        stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true, "1":true, "1":false})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find("OneFileDay") != data.end());
    EXPECT_TRUE(data.find("TheLastStand") != data.end());
    EXPECT_TRUE(data.find("OfMiceAndMen") != data.end());
    EXPECT_TRUE(data.find("1") != data.end());
    EXPECT_EQ(data.count("1"), 2);
}

TEST(SerUnorderedMultiMapTestString, Bsonserialize)
{
    std::unordered_multimap<int, double>  data;
    data.insert(std::make_pair(56, 78.901));
    data.insert(std::make_pair(56, 901));

    std::string       stream;
    stream << TS::bsonExporter(data);
    std::string result = stream;

    static const char expectedRaw1[]
                = "\x4B\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                        "\x00"
                  "\x03" "1\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x28\x8c\x40"
                        "\x00"
                  "\x00";
    static const char expectedRaw2[]
                = "\x4B\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x28\x8c\x40"
                        "\x00"
                  "\x03" "1\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                        "\x00"
                  "\x00";
    std::string expected1(std::begin(expectedRaw1), std::end(expectedRaw1) - 1);
    std::string expected2(std::begin(expectedRaw2), std::end(expectedRaw2) - 1);
    bool test = result == expected1 || result == expected2;
    //NOTE OUTPUT  R"([{"first":56,"second":78.901},{"first":56,"second":901}])"
    //NOTE OUTPUT  R"([{"first":56,"second":901},{"first":56,"second":78.901}])";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTestString, BsondeSerialize)
{
    std::unordered_multimap<int, double>  data;

    //NOTE INPUT (R"([{"first":64,"second":12}, {"first":118,"second":14}, {"first":118,"second": 112}])");
    static const char inputRaw[]
                = "\x62\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x1C\x00\x00\x00"
                        "\x10" "first\x00"  "\x40\x00\x00\x00"
                        "\x10" "second\x00" "\x0C\x00\x00\x00"
                        "\x00"
                  "\x03" "1\x00"
                        "\x1C\x00\x00\x00"
                        "\x10" "first\x00"  "\x76\x00\x00\x00"
                        "\x10" "second\x00" "\x0E\x00\x00\x00"
                        "\x00"
                  "\x03" "2\x00"
                        "\x1C\x00\x00\x00"
                        "\x10" "first\x00"  "\x76\x00\x00\x00"
                        "\x10" "second\x00" "\x70\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string        stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(64) != data.end());
    EXPECT_TRUE(data.find(118) != data.end());
    EXPECT_EQ(data.count(118), 2);
}

TEST(SerUnorderedMultiMapTestString, BsonserializeStringKey)
{
    std::unordered_multimap<std::string, double>  data;
    data.insert(std::make_pair("AStringKey", 78.902));
    data.insert(std::make_pair("TestValue",  22.903));
    data.insert(std::make_pair("TestValue",  903));

    std::string       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream;

    static const char expectedRaw1[]
                = "\x3F\x00\x00\x00"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x00";
    static const char expectedRaw2[]
                = "\x3F\x00\x00\x00"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x00";
    static const char expectedRaw3[]
                = "\x3F\x00\x00\x00"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x00";
    static const char expectedRaw4[]
                = "\x3F\x00\x00\x00"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x00";
    static const char expectedRaw5[]
                = "\x3F\x00\x00\x00"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x00";
    static const char expectedRaw6[]
                = "\x3F\x00\x00\x00"
                  "\x01" "TestValue\x00"    "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x00";
    std::string expected1(std::begin(expectedRaw1), std::end(expectedRaw1) - 1);
    std::string expected2(std::begin(expectedRaw2), std::end(expectedRaw2) - 1);
    std::string expected3(std::begin(expectedRaw3), std::end(expectedRaw3) - 1);
    std::string expected4(std::begin(expectedRaw4), std::end(expectedRaw4) - 1);
    std::string expected5(std::begin(expectedRaw5), std::end(expectedRaw5) - 1);
    std::string expected6(std::begin(expectedRaw6), std::end(expectedRaw6) - 1);

    //NOTE OUTPUT  R"({"AStringKey":78.902,"TestValue":22.903,"TestValue":903})"
    //NOTE OUTPUT  R"({"AStringKey":78.902,"TestValue":903,"TestValue":22.903})"
    //NOTE OUTPUT  R"({"TestValue":22.903,"AStringKey":78.902,"TestValue":903})"
    //NOTE OUTPUT  R"({"TestValue":22.903,"TestValue":903,"AStringKey":78.902})"
    //NOTE OUTPUT  R"({"TestValue":903,"AStringKey":78.902,"TestValue":22.903})"
    //NOTE OUTPUT  R"({"TestValue":903,"TestValue":22.903,"AStringKey":78.902})";
    bool test = result == expected1 || result == expected2 || result == expected3
             || result == expected4 || result == expected5 || result == expected6;
    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTestString, BsondeSerializeStringKey)
{
    std::unordered_multimap<std::string, bool>  data;

    //NOTE INPUT (R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true, "1":true, "1":false})");
    static const char inputRaw[]
                = "\x38\x00\x00\x00"
                  "\x08" "OneFileDay\x00"    "\x01"
                  "\x08" "TheLastStand\x00"  "\x00"
                  "\x08" "OfMiceAndMen\x00"  "\x01"
                  "\x08" "1\x00"             "\x01"
                  "\x08" "1\x00"             "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string        stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find("OneFileDay") != data.end());
    EXPECT_TRUE(data.find("TheLastStand") != data.end());
    EXPECT_TRUE(data.find("OfMiceAndMen") != data.end());
    EXPECT_TRUE(data.find("1") != data.end());
    EXPECT_EQ(data.count("1"), 2);
}


