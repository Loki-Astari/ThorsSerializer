#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "SmartPointerTest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <memory>

TEST(SmartPointerTest, CreateNormalPtrNull)
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

TEST(SmartPointerTest, CreateNormalPtrObject)
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

TEST(SmartPointerTest, CreateUniquePtrNull)
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

TEST(SmartPointerTest, CreateUniquePtrObject)
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

TEST(SmartPointerTest, CreateSharedPtrNull)
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

TEST(SmartPointerTest, CreateSharedPtrObject)
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

TEST(SmartPointerTest, SerializeNormalPtrNull)
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

TEST(SmartPointerTest, SerializeNormalPtrObject)
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

TEST(SmartPointerTest, SerializeUniquePtrNull)
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

TEST(SmartPointerTest, SerializeUniquePtrObject)
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

TEST(SmartPointerTest, SerializeSharedPtrNull)
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

TEST(SmartPointerTest, SerializeSharedPtrObject)
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

