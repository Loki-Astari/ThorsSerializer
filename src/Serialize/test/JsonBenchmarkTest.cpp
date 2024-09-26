#include "gtest/gtest.h"
#include "JsonThor.h"
#include "Traits.h"
#include "test/TwitterTest.h"
#include "test/CountryTest.h"
#include "test/CatalogTest.h"
#include <fstream>

namespace JsonBenchmarkTest
{
    using FailArray = std::vector<std::string>;
    struct FailMap
    {
        std::string  data1;;
    };
    using ValFloat  = std::vector<double>;
    using ValStr    = std::vector<std::string>;
    using Round01   = std::vector<int*>;
    using Round02   = std::vector<bool>;
    using Round04   = std::vector<int>;
    using Round05   = std::vector<std::string>;
    using Round13   = std::vector<std::int64_t>;
    using Round20   = std::vector<double>;
    using Round24   = std::vector<long double>;
    struct Round07
    {};
    struct Round09
    {
        std::optional<int*> a;
        std::string         foo;
    };
};

ThorsAnvil_MakeTrait(JsonBenchmarkTest::FailMap, data1);
ThorsAnvil_MakeTrait(JsonBenchmarkTest::Round07);
ThorsAnvil_MakeTrait(JsonBenchmarkTest::Round09, a, foo);
ThorsAnvil::Serialize::ParserConfig		config{ThorsAnvil::Serialize::ParserConfig{}.setCatchExceptions(false).setValidateNoTrailingData()};
ThorsAnvil::Serialize::PrinterConfig	configOut{ThorsAnvil::Serialize::PrinterConfig{}.setOutputType(ThorsAnvil::Serialize::OutputType::Stream)};

TEST(JsonBenchmarkTest, fail02)
{
    auto action = [&]()
    {
        std::stringstream               s(R"(["Unclosed array")");
        JsonBenchmarkTest::FailArray    data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}


TEST(JsonBenchmarkTest, fail03)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({unquoted_key: "keys must be quoted"})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail04)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["extra comma",])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail05)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["double extra comma",,])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail06)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([   , "<-- missing value"])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail07)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Comma after the close"],)");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail08)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Extra close"]])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail09)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Extra comma": true,})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail10)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Extra value after close": true} "misplaced quoted value")");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail11)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Illegal expression": 1 + 2})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail12)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Illegal invocation": alert()})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail13)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Numbers cannot have leading zeroes": 013})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail14)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Numbers cannot be hex": 0x14})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail15)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Illegal backslash escape: \x15"])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail16)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([\naked])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail17)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Illegal backslash escape: \017"])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail19)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Missing colon" null})");
        JsonBenchmarkTest::FailMap   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail20)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Double colon":: null})");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail21)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Comma instead of colon", null)");
        JsonBenchmarkTest::FailMap     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail22)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Colon instead of comma": false])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail23)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Bad value", truth])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail24)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(['single quote'])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail25)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["	 tab	character	  in	 string	 "])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail26)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["tab\   character\   in\  string\  "])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail27)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["line
break"])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail28)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["line\
break"])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail29)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0e])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail30)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0e+])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail31)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0e+-1])");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail32)
{
    auto action = [&]()
    {
        std::stringstream              s(R"({"Comma instead if closing brace": true,)");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, fail33)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["mismatch"})");
        JsonBenchmarkTest::FailArray   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
    };
    EXPECT_THROW(
        action(),
        std::exception
    );
}

TEST(JsonBenchmarkTest, float01)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float02)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-0.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float03)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float04)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float05)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.5);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float06)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1.5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1.5);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float07)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([3.1416])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 3.1416);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float08)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1E10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1E10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float09)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1e10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float10)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1E+10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1E+10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float11)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1E-10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1E-10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float12)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1E10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1E10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float13)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1e10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1e10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float14)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1E+10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1E+10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float15)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1E-10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1E-10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float16)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.234E+10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.234E+10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float17)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.234E-10])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.234E-10);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float18)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.79769e+308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.79769e+308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float19)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.22507e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.22507e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float20)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1.79769e+308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -1.79769e+308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float21)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-2.22507e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -2.22507e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float22)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([4.9406564584124654e-324])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 4.9406564584124654e-324);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float23)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.2250738585072009e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072009e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float24)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.2250738585072014e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072014e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float25)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.7976931348623157e+308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.7976931348623157e+308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float26)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e-10000])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float27)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([18446744073709551616])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 18446744073709551616.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float28)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-9223372036854775809])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -9223372036854775809.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float29)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.9868011474609375])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.9868011474609375);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float30)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([123e34])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 123e34);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float31)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([45913141877270640000.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 45913141877270640000.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float32)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.2250738585072011e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072011e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float33)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e-00011111111111])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float34)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([-1e-00011111111111])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], -0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float35)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e-214748363])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float36)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e-214748364])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float37)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1e-21474836311])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float38)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.017976931348623157e+310])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.7976931348623157e+308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float39)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.2250738585072012e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072014e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float40)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.22507385850720113605740979670913197593481954635164564e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072009e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float41)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.22507385850720113605740979670913197593481954635164565e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072014e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float42)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.999999999999999944488848768742172978818416595458984375])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float43)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.999999999999999944488848768742172978818416595458984374])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 0.99999999999999989);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float44)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([0.999999999999999944488848768742172978818416595458984376])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float45)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.00000000000000011102230246251565404236316680908203125])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float46)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.00000000000000011102230246251565404236316680908203124])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float47)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1.00000000000000011102230246251565404236316680908203126])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1.00000000000000022);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float48)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([72057594037927928.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 72057594037927928.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float49)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([72057594037927936.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 72057594037927936.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float50)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([72057594037927932.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 72057594037927936.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float51)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([7205759403792793199999e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 72057594037927928.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float52)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([7205759403792793200001e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 72057594037927936.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float53)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([9223372036854774784.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 9223372036854774784.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float54)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([9223372036854775808.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 9223372036854775808.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float55)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([9223372036854775296.0])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 9223372036854775808.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float56)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([922337203685477529599999e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 9223372036854774784.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float57)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([922337203685477529600001e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 9223372036854775808.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float58)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([10141204801825834086073718800384])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 10141204801825834086073718800384.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float59)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([10141204801825835211973625643008])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 10141204801825835211973625643008.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float60)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([10141204801825834649023672221696])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 10141204801825835211973625643008.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float61)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1014120480182583464902367222169599999e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 10141204801825834086073718800384.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float62)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([1014120480182583464902367222169600001e-5])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 10141204801825835211973625643008.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float63)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([5708990770823838890407843763683279797179383808])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 5708990770823838890407843763683279797179383808.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float64)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([5708990770823839524233143877797980545530986496])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 5708990770823839524233143877797980545530986496.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float65)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([5708990770823839207320493820740630171355185152])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 5708990770823839524233143877797980545530986496.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float66)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([5708990770823839207320493820740630171355185151999e-3])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 5708990770823838890407843763683279797179383808.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float67)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([5708990770823839207320493820740630171355185152001e-3])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 5708990770823839524233143877797980545530986496.0);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float68)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 1E308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, float69)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([2.225073858507201136057409796709131975934819546351645648023426109724822222021076945516529523908135087914149158913039621106870086438694594645527657207407820621743379988141063267329253552286881372149012981122451451889849057222307285255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647565300009245888316433037779791869612049497390377829704905051080609940730262937128958950003583799967207254304360284078895771796150945516748243471030702609144621572289880258182545180325707018860872113128079512233426288368622321503775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886445804001034933970427567186443383770486037861622771738545623065874679014086723327636718751234567890123456789012345678901e-308])");
        JsonBenchmarkTest::ValFloat   data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], 2.2250738585072014e-308);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string01)
{
    auto action = [&]()
    {
        std::stringstream              s(R"([""])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string02)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Hello"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "Hello");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string03)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["Hello\nWorld"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], R"(Hello
World)");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string05)
{
    auto action = [&]()
    {
        using namespace std::string_literals;

        std::stringstream              s(R"(["Hello\u0000World"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "Hello World"s);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string06)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["\"\\/\b\f\n\r\t"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "\"\\/\b\f\n\r\t");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string08)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["\u0024"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "$");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string09)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["\u00A2"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "¢");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string10)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["\u20AC"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "€");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, string11)
{
    auto action = [&]()
    {
        std::stringstream              s(R"(["\uD834\uDD1E"])");
        JsonBenchmarkTest::ValStr      data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);
        EXPECT_EQ(data[0], "𝄞");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round01)
{
    auto action = [&]()
    {
        std::string                    input(R"([null])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round01     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}
TEST(JsonBenchmarkTest, round02)
{
    auto action = [&]()
    {
        std::string                    input(R"([true])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round02     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round03)
{
    auto action = [&]()
    {
        std::string                    input(R"([false])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round02     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round04)
{
    auto action = [&]()
    {
        std::string                    input(R"([0])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round05)
{
    auto action = [&]()
    {
        std::string                    input(R"(["foo"])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round05     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round06)
{
    auto action = [&]()
    {
        std::string                    input(R"([])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round05     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round07)
{
    auto action = [&]()
    {
        std::string                    input(R"({})");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round07     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round08)
{
    auto action = [&]()
    {
        std::string                    input(R"([0,1])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round09)
{
    auto action = [&]()
    {
        std::string                    input(R"({"foo":"bar"})");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round09     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round10)
{
    auto action = [&]()
    {
        std::string                    input(R"({"a":null,"foo":"bar"})");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round09     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round11)
{
    auto action = [&]()
    {
        std::string                    input(R"([-1])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round12)
{
    auto action = [&]()
    {
        std::string                    input(R"([-2147483648])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round13)
{
    auto action = [&]()
    {
        std::string                    input(R"([-1234567890123456789])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round13     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round14)
{
    auto action = [&]()
    {
        std::string                    input(R"([-9223372036854775808])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round13     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round15)
{
    auto action = [&]()
    {
        std::string                    input(R"([1])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round16)
{
    auto action = [&]()
    {
        std::string                    input(R"([2147483647])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round04     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round17)
{
    auto action = [&]()
    {
        std::string                    input(R"([4294967295])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round13     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round18)
{
    auto action = [&]()
    {
        std::string                    input(R"([1234567890123456789])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round13     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round19)
{
    auto action = [&]()
    {
        std::string                    input(R"([9223372036854775807])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round13     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round20)
{
    auto action = [&]()
    {
        std::string                    input(R"([0.0])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round21)
{
    auto action = [&]()
    {
        std::string                    input(R"([-0.0])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action();
    );
}

TEST(JsonBenchmarkTest, round22)
{
    auto action = [&]()
    {
        std::string                    input(R"([1.2345])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round23)
{
    auto action = [&]()
    {
        std::string                    input(R"([-1.2345])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round24)
{
    auto action = [&]()
    {
        std::string                    input(R"([5e-324])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round24     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << std::setprecision(0) << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round25)
{
    auto action = [&]()
    {
        std::string                    input(R"([2.225073858507201e-308])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << std::setprecision(16) << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round26)
{
    auto action = [&]()
    {
        std::string                    input(R"([2.2250738585072014e-308])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << std::setprecision(17) << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, round27)
{
    auto action = [&]()
    {
        std::string                    input(R"([1.7976931348623157e+308])");
        std::stringstream              s(input);
        JsonBenchmarkTest::Round20     data;
        s >> ThorsAnvil::Serialize::jsonImporter(data, config);

        std::stringstream              out;
        out << std::setprecision(17) << ThorsAnvil::Serialize::jsonExporter(data, configOut);
        EXPECT_EQ(input, out.str());
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, performanceTwitter)
{
    using ThorsAnvil::Serialize::ParseType;

    auto action = []()
    {
        TwitterTest::Twitter    value;
        std::ifstream           input("test/data/twitter.json");

        input >> ThorsAnvil::Serialize::jsonImporter(value, config);

        EXPECT_EQ(value.statuses[0].user.screen_name, "ayuu0123");
        EXPECT_EQ(value.statuses[0].entities.user_mentions[0].screen_name, "aym0566x");
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, performanceCountry)
{
    using ThorsAnvil::Serialize::ParseType;

    auto action = []()
    {
        CountryTest::Country    value;
        std::ifstream           input("test/data/canada.json");

        input >> ThorsAnvil::Serialize::jsonImporter(value, config);

        EXPECT_EQ(value.features[0].properties.name, "Canada");
        EXPECT_EQ(value.features[0].geometry.coordinates[0][0][1], 43.420273000000009);
    };
    EXPECT_NO_THROW(
        action()
    );
}

TEST(JsonBenchmarkTest, performanceCatalog)
{
    using ThorsAnvil::Serialize::ParseType;

    auto action = []()
    {
        CatalogTest::Perform    value;
        std::ifstream           input("test/data/citm_catalog.json");

        input >> ThorsAnvil::Serialize::jsonImporter(value, config);

        EXPECT_EQ(value.events["138586341"].name, "30th Anniversary Tour");
        EXPECT_EQ(value.performances[0].prices[0].amount, 90250);
    };
    EXPECT_NO_THROW(
        action()
    );
}


