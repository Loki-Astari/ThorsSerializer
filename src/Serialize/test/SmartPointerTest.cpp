#include "gtest/gtest.h"
#include "SmartPointerTest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <memory>

TEST(SmartPointerTest, CreateNormalPtrNull)
{
    std::stringstream           stream(R"(null)");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImport(data, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}
TEST(SmartPointerTest, CreateNormalPtrObject)
{
    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImport(data, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true))
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
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"(null)");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImport(data, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(data, nullptr);
}
TEST(SmartPointerTest, CreateUniquePtrObject)
{
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream(R"({"id": 456, "name": "This is a test"})");
    UniObject                   data;
    bool                        import = false;

    if (stream >> ThorsAnvil::Serialize::jsonImport(data, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true))
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
    std::stringstream           stream;
    SmartPtrTest::Object*       data = nullptr;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}
TEST(SmartPointerTest, SerializeNormalPtrObject)
{
    std::stringstream           stream;
    SmartPtrTest::Object*       data = new SmartPtrTest::Object{456, "This is a test"};
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
    delete data;
}
TEST(SmartPointerTest, SerializeUniquePtrNull)
{
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    UniObject                   data;
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), " null");
}
TEST(SmartPointerTest, SerializeUniquePtrObject)
{
    using UniObject = std::unique_ptr<SmartPtrTest::Object>;

    std::stringstream           stream;
    SmartPtrTest::Object*       data(new SmartPtrTest::Object{456, "This is a test"});
    bool                        import = false;

    if (stream << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream, true))
    {
        import = true;
    }
    EXPECT_EQ(import, true);
    EXPECT_EQ(stream.str(), R"({"id":456,"name":"This is a test"})");
}

