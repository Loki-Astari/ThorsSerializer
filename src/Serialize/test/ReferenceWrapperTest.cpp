#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"
#include <functional>

struct Marker
{
    int         value;
    std::string data;
};
template<typename T>
struct ReferenceWrapperTest
{
    ReferenceWrapperTest(T& val)
        : data(val)
    {}
    std::reference_wrapper<T>     data;
};

ThorsAnvil_Template_MakeTrait(1, ReferenceWrapperTest, data);
ThorsAnvil_MakeTrait(Marker, value, data);

TEST(ReferenceWrapperTest, JsonSimpleWrapperRead)
{
    bool                        import = false;
    int                         value = 0;
    ReferenceWrapperTest<int>   wrapper(value);
    std::stringstream           stream(R"({"data":12})");

    if (stream >> ThorsAnvil::Serialize::jsonImporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(12, value);
}
TEST(ReferenceWrapperTest, JsonComplexWrapperRead)
{
    bool                            import = false;
    Marker                          value{8, "Bob"};
    ReferenceWrapperTest<Marker>    wrapper(value);
    std::stringstream               stream(R"({"data":{"value":13,"data":"A string"}})");

    if (stream >> ThorsAnvil::Serialize::jsonImporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(13, value.value);
    EXPECT_EQ("A string", value.data);
}

TEST(ReferenceWrapperTest, YamlnSimpleWrapperRead)
{
    //bool                        import = false;
    int                         value = 9;
    ReferenceWrapperTest<int>   wrapper(value);
    std::stringstream           stream("---\ndata: 12\n...\n");

    if (stream >> ThorsAnvil::Serialize::yamlImporter(wrapper, ThorsAnvil::Serialize::ParserInterface::ParserConfig{false}))
    {
        //import = true;
    }
    //EXPECT_TRUE(import);
    EXPECT_EQ(12, value);
}
TEST(ReferenceWrapperTest, YamlnComplexWrapperRead)
{
    //bool                            import = false;
    Marker                          value{8, "Bob"};
    ReferenceWrapperTest<Marker>    wrapper(value);
    std::stringstream               stream("---\ndata:\n  value: 13\n  data: A string\n...\n");

    if (stream >> ThorsAnvil::Serialize::yamlImporter(wrapper, ThorsAnvil::Serialize::ParserInterface::ParserConfig{false}))
    {
        //import = true;
    }
    //EXPECT_TRUE(import);
    EXPECT_EQ(13, value.value);
    EXPECT_EQ("A string", value.data);
}

TEST(ReferenceWrapperTest, BsonSimpleWrapperRead)
{
    using namespace std::string_literals;
    bool                        import = false;
    int                         value = 0;
    ReferenceWrapperTest<int>   wrapper(value);
    std::string result  = "\x0F\x00\x00\x00"
                          "\x10" "data\x00"     "\x0C\x00\x00\x00"
                          "\x00"s;
    std::stringstream           stream(result);

    if (stream >> ThorsAnvil::Serialize::bsonImporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(12, value);
}
TEST(ReferenceWrapperTest, BsonComplexWrapperRead)
{
    using namespace std::string_literals;
    bool                            import = false;
    Marker                         value{0, "Bob"};
    ReferenceWrapperTest<Marker>   wrapper(value);
    std::string result  = "\x2E\x00\x00\x00"
                          "\x03" "data\x00"
                                "\x23\x00\x00\x00"
                                "\x10"  "value\x00"     "\x0D\x00\x00\x00"
                                "\x02"  "data\x00"      "\x09\x00\x00\x00"  "A string\x00"
                                "\x00"
                          "\x00"s;
    std::stringstream               stream(result);

    if (stream >> ThorsAnvil::Serialize::bsonImporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(13, value.value);
    EXPECT_EQ("A string", value.data);
}

TEST(ReferenceWrapperTest, JsonSimpleWrapperWrite)
{
    bool                        import = false;
    int                         value = 12;
    ReferenceWrapperTest<int>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::jsonExporter(wrapper, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(stream.str(), R"({"data":12})");
}
TEST(ReferenceWrapperTest, JsonComplexWrapperWrite)
{
    bool                            import = false;
    Marker                         value{13, "A string"};
    ReferenceWrapperTest<Marker>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::jsonExporter(wrapper, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(stream.str(), R"({"data":{"value":13,"data":"A string"}})");
}

TEST(ReferenceWrapperTest, YamlnSimpleWrapperWrite)
{
    bool                        import = false;
    int                         value = 12;
    ReferenceWrapperTest<int>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::yamlExporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(stream.str(), "---\ndata: 12\n...\n");
}
TEST(ReferenceWrapperTest, YamlnComplexWrapperWrite)
{
    bool                            import = false;
    Marker                         value{13, "A string"};
    ReferenceWrapperTest<Marker>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::yamlExporter(wrapper))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    EXPECT_EQ(stream.str(), "---\ndata:\n  value: 13\n  data: A string\n...\n");
}

TEST(ReferenceWrapperTest, BsonSimpleWrapperWrite)
{
    bool                        import = false;
    int                         value = 12;
    ReferenceWrapperTest<int>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::bsonExporter(wrapper, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    using namespace std::string_literals;
    std::string result  = "\x0F\x00\x00\x00"
                          "\x10" "data\x00"     "\x0C\x00\x00\x00"
                          "\x00"s;
    EXPECT_EQ(stream.str(), result);
}
TEST(ReferenceWrapperTest, BsonComplexWrapperWrite)
{
    bool                            import = false;
    Marker                         value{13, "A string"};
    ReferenceWrapperTest<Marker>   wrapper(value);

    std::stringstream   stream;
    if (stream << ThorsAnvil::Serialize::bsonExporter(wrapper, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_TRUE(import);
    using namespace std::string_literals;
    std::string result  = "\x2E\x00\x00\x00"
                          "\x03" "data\x00"
                                "\x23\x00\x00\x00"
                                "\x10"  "value\x00"     "\x0D\x00\x00\x00"
                                "\x02"  "data\x00"      "\x09\x00\x00\x00"  "A string\x00"
                                "\x00"
                          "\x00"s;
    EXPECT_EQ(stream.str(), result);
}

