#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "SmartPointerTest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>

TEST(SmartPointerTestString, JsonCreateNormalPtrNull)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string                 stream(R"(null)");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTestString, JsonCreateNormalPtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string                 stream(R"({"id": 456, "name": "This is a test"})");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
    delete data;
}

TEST(SmartPointerTestString, JsonCreateUniquePtrNull)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::string                 stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTestString, JsonCreateUniquePtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::string                 stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTestString, JsonCreateSharedPtrNull)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::string                 stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTestString, JsonCreateSharedPtrObjectOriginal)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::string                 stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ThorsAnvil::Serialize::ParserConfig{ParseType::Weak}.setUseOldSharedPtr()))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTestString, JsonCreateSharedPtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::string                 stream(R"({"sharedPtrName":1,"data":{"id": 456, "name": "This is a test"}})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTestString, JsonSerializeNormalPtrNull)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string      stream;
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "null");
}

TEST(SmartPointerTestString, JsonSerializeNormalPtrObject)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string      stream;
    SmartPtrTest::Object*       data = new SmartPtrTest::Object{456, "This is a test"};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, R"({"id":456,"name":"This is a test"})");
    delete data;
}

TEST(SmartPointerTestString, JsonSerializeUniquePtrNull)
{
    using ThorsAnvil::Serialize::OutputType;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::string      stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "null");
}

TEST(SmartPointerTestString, JsonSerializeUniquePtrObject)
{
    using ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, R"({"id":456,"name":"This is a test"})");
}

TEST(SmartPointerTestString, JsonSerializeSharedPtrNull)
{
    using  ThorsAnvil::Serialize::OutputType;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::string      stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "null");
}

TEST(SmartPointerTestString, JsonSerializeSharedPtrObject)
{
    using ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, R"({"id":456,"name":"This is a test"})");
}

using namespace std::string_literals;
// BSON does not support null at the top level.
//      but it should be able to cope with nullptr
//      as a member. So wrapping this test.
TEST(SmartPointerTestString, BsonCreateNormalPtrNull)
{
    using ThorsAnvil::Serialize::ParseType;
    ThorsAnvil::Serialize::ParserConfig config(ParseType::Weak);
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);
    //NOTE INPUT (R"(null)");
    std::string input = "\x0B\x00\x00\x00"
                        "\x0A" "data\x00"
                        "\x00"s;
    std::string                 stream(input);
    Wrapper                     wrap;
    wrap.data = new SmartPtrTest::Object;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(wrap, config))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(wrap.data, nullptr);
}

TEST(SmartPointerTestString, BsonCreateNormalPtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    //NOTE INPUT (R"({"id": 456, "name": "This is a test"})");
    std::string                 input = "\x26\x00\x00\x00"
                                        "\x10" "id\x00"      "\xc8\x01\x00\x00"
                                        "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                                        "\x00"s;
    std::string                 stream(input);
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
    delete data;
}

TEST(SmartPointerTestString, BsonCreateUniquePtrNull)
{
    using ThorsAnvil::Serialize::ParseType;

    //NOTE INPUT (R"(null)");
    std::string                 input = "\x0B\x00\x00\x00"
                                        "\x0A" "data\x00"
                                        "\x00"s;
    std::string                 stream(input);
    WrapperUni                  wrap;
    bool                        import = false;

    wrap.data = std::make_unique<SmartPtrTest::Object>();
    if (stream >> ThorsAnvil::Serialize::bsonImporter(wrap, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(wrap.data, nullptr);
}

TEST(SmartPointerTestString, BsonCreateUniquePtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    //NOTE INPUT (R"({"id": 456, "name": "This is a test"})");
    std::string                 input = "\x26\x00\x00\x00"
                                        "\x10" "id\x00"      "\xc8\x01\x00\x00"
                                        "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                                        "\x00"s;
    std::string                 stream(input);
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTestString, BsonCreateSharedPtrNull)
{
    using ThorsAnvil::Serialize::ParseType;

    //NOTE INPUT (R"(null)");
    std::string                 input = "\x0B\x00\x00\x00"
                                        "\x0A" "data\x00"
                                        "\x00"s;
    std::string                 stream(input);
    WrapperShared               wrap;
    bool                        import = false;

    wrap.data = std::make_unique<SmartPtrTest::Object>();
    if (stream >> ThorsAnvil::Serialize::bsonImporter(wrap, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(wrap.data, nullptr);
}

TEST(SmartPointerTestString, BsonCreateSharedPtrObjectOriginal)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    //NOTE INPUT (R"({"id": 456, "name": "This is a test"})");
    std::string                 input = "\x26\x00\x00\x00"
                                            "\x10" "id\x00"      "\xc8\x01\x00\x00"
                                            "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                                            "\x00"s;
    std::string                 stream(input);
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ThorsAnvil::Serialize::ParserConfig{ParseType::Weak}.setUseOldSharedPtr()))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}
TEST(SmartPointerTestString, BsonCreateSharedPtrObject)
{
    using ThorsAnvil::Serialize::ParseType;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    //NOTE INPUT (R"({"id": 456, "name": "This is a test"})");
    std::string                 input = "\x48\x00\x00\x00"
                                        "\x12" "sharedPtrName\x00"  "\x00\x00\x00\x00\x04\x03\x02\x01"
                                        "\x03" "data\x00"
                                                "\x26\x00\x00\x00"
                                                "\x10" "id\x00"      "\xc8\x01\x00\x00"
                                                "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                                                "\x00"
                                        "\x00"s;
    std::string                 stream(input);
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTestString, BsonSerializeNormalPtrNull)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string      stream;
    Wrapper                     wrap;
    bool                        import = false;

    wrap.data = nullptr;
    if (stream << ThorsAnvil::Serialize::bsonExporter(wrap, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x0B\x00\x00\x00"
                            "\x0A" "data\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, "null");
}

TEST(SmartPointerTestString, BsonSerializeNormalPtrObject)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string      stream;
    SmartPtrTest::Object*       data = new SmartPtrTest::Object{456, "This is a test"};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x26\x00\x00\x00"
                            "\x10" "id\x00"      "\xc8\x01\x00\x00"
                            "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, R"({"id":456,"name":"This is a test"})");
    delete data;
}

TEST(SmartPointerTestString, BsonSerializeUniquePtrNull)
{
    using ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    WrapperUni                  wrap;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(wrap, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x0B\x00\x00\x00"
                            "\x0A" "data\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, "null");
}

TEST(SmartPointerTestString, BsonSerializeUniquePtrObject)
{
    using ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x26\x00\x00\x00"
                            "\x10" "id\x00"      "\xc8\x01\x00\x00"
                            "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, R"({"id":456,"name":"This is a test"})");
}

TEST(SmartPointerTestString, BsonSerializeSharedPtrNull)
{
    using  ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    WrapperShared               wrap{nullptr};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(wrap, OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x0B\x00\x00\x00"
                            "\x0A" "data\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, "null");
}

TEST(SmartPointerTestString, BsonSerializeSharedPtrObject)
{
    using ThorsAnvil::Serialize::OutputType;

    std::string      stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream, "\x26\x00\x00\x00"
                            "\x10" "id\x00"      "\xc8\x01\x00\x00"
                            "\x02" "name\x00"    "\x0F\x00\x00\x00" "This is a test\x00"
                            "\x00"s);
    //NOTE OUTPUT  (stream, R"({"id":456,"name":"This is a test"})");
}


