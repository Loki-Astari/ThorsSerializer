#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "SmartPointerTest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>

TEST(SmartPointerTest, JsonCreateNormalPtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream           stream(R"(null)");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, JsonCreateNormalPtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
    delete data;
}

TEST(SmartPointerTest, JsonCreateUniquePtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, JsonCreateUniquePtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTest, JsonCreateSharedPtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, JsonCreateSharedPtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTest, JsonSerializeNormalPtrNull)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream           stream;
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, JsonSerializeNormalPtrObject)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream           stream;
    SmartPtrTest::Object*       data = new SmartPtrTest::Object{456, "This is a test"};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
    delete data;
}

TEST(SmartPointerTest, JsonSerializeUniquePtrNull)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, JsonSerializeUniquePtrObject)
{
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;
    using ThorsAnvil::Serialize::PrinterInterface;

    std::stringstream           stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
}

TEST(SmartPointerTest, JsonSerializeSharedPtrNull)
{
    using  ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, JsonSerializeSharedPtrObject)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
}

TEST(SmartPointerTest, BsonCreateNormalPtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream           stream(R"(null)");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, BsonCreateNormalPtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
    delete data;
}

TEST(SmartPointerTest, BsonCreateUniquePtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, BsonCreateUniquePtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTest, BsonCreateSharedPtrNull)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}

TEST(SmartPointerTest, BsonCreateSharedPtrObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::bsonImporter(data, ParserInterface::ParseType::Weak))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    ASSERT_NE(data.get(), nullptr);
    EXPECT_EQ(data->id, 456);
    EXPECT_EQ(data->name, "This is a test");
}

TEST(SmartPointerTest, BsonSerializeNormalPtrNull)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream           stream;
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, BsonSerializeNormalPtrObject)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream           stream;
    SmartPtrTest::Object*       data = new SmartPtrTest::Object{456, "This is a test"};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
    delete data;
}

TEST(SmartPointerTest, BsonSerializeUniquePtrNull)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, BsonSerializeUniquePtrObject)
{
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;
    using ThorsAnvil::Serialize::PrinterInterface;

    std::stringstream           stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
}

TEST(SmartPointerTest, BsonSerializeSharedPtrNull)
{
    using  ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Default))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}

TEST(SmartPointerTest, BsonSerializeSharedPtrObject)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    using UniObject = std::shared_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
}


