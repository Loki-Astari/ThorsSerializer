#include <gtest/gtest.h>

#include "JsonThor.h"
#include "Serialize.h"
#include "CustomSerializer.h"

#include <variant>
#include <string>

using SerializableId                = std::variant<std::string, long>;
struct SerializableIdExtension
{
    using PrintableType = SerializableId;
    SerializableId          value;
    int                     type;
};
template<typename T>
requires std::is_same_v<std::remove_const_t<T>, ::SerializableIdExtension>
ThorsAnvil::Serialize::GetPrintableType_t<T>& streamableValue(T& object) {return object.value;}

template<typename T>
struct BlockOne
{
    T                   id;
    std::string         method;
    long                core;
};

using ThorsAnvil::Serialize::streamableValue;
class IdSerializer: public ThorsAnvil::Serialize::CustomSerializer
{
    /*
    struct IdWriter
    {
        ThorsAnvil::Serialize::Serializer&          parent;
        ThorsAnvil::Serialize::PrinterInterface&    printer;
        template<typename T>
        void operator()(T const& val) const
        {
            using Base = std::remove_cvref_t<T>;
            using Traits = ThorsAnvil::Serialize::Traits<Base>;
            Base const& val1 =  std::any_cast<Base>(val);
            ThorsAnvil::Serialize::SerializerForBlock<Traits::type, Base> serializer(parent, printer, val1);
            serializer.printMembers();
        }
    };
    struct IdSizer
    {
        ThorsAnvil::Serialize::PrinterInterface&    printer;
        template<typename T>
        std::size_t operator()(T const& val) const
        {
            using Base = std::remove_cvref_t<T>;
            using Traits = ThorsAnvil::Serialize::Traits<Base>;
            return Traits::getPrintSize(printer, val, true);
        }
    };
    */
    public:
    /*
        template<typename T>
        static std::size_t getPrintSize(ThorsAnvil::Serialize::PrinterInterface& printer, T const& object)
        {
            return std::visit(IdSizer{printer}, object);
        }
        template<typename T>
        static void writeCustom(ThorsAnvil::Serialize::Serializer& parent, ThorsAnvil::Serialize::PrinterInterface& printer, T const& object)
        {
            std::visit(IdWriter{parent, printer}, object);
        }
    */
        template<typename T>
        static void readCustom(ThorsAnvil::Serialize::DeSerializer& /*parent*/, ThorsAnvil::Serialize::ParserInterface& parser, T& object)
        {
            ThorsAnvil::Serialize::ParserToken    tokenType = parser.getToken();
            switch (parser.peekType())
            {
                case ThorsAnvil::Serialize::ValueType::Number:  {long value;        parser.getValue(value);streamableValue(object) = value;break;}
                case ThorsAnvil::Serialize::ValueType::String:  {std::string value; parser.getValue(value);streamableValue(object) = value;break;}
                default:
                    ThorsLogAndThrowDebug(std::runtime_error, "ThorsAnvil::Nisse::MCP::IdSerializer", "readCustom", "Expected integer or string for id");
            }
        }
};

ThorsAnvil_MakeTraitCustomSerialize(SerializableId, IdSerializer);
ThorsAnvil_MakeTraitCustomSerialize(SerializableIdExtension, IdSerializer);
ThorsAnvil_Template_MakeTrait(1, BlockOne, id, method, core);


TEST(CustomSerializeTest, GetLongId)
{
    std::string_view    input = "10";
    SerializableId      id  = 0;

    input >> ThorsAnvil::Serialize::jsonImporter(id);

    EXPECT_EQ(10, std::get<long>(id));
}

TEST(CustomSerializeTest, GetLongIdExtension)
{
    std::string_view    input = "10";
    SerializableIdExtension      id  = {0, 2};

    input >> ThorsAnvil::Serialize::jsonImporter(id);

    EXPECT_EQ(10, std::get<long>(id.value));
    EXPECT_EQ(2, id.type);
}

TEST(CustomSerializeTest, GetStringId)
{
    std::string_view    input = R"json("Discover")json";
    SerializableId      id  = 0;

    input >> ThorsAnvil::Serialize::jsonImporter(id);

    EXPECT_EQ("Discover", std::get<std::string>(id));
}

TEST(CustomSerializeTest, GetStringIdExtension)
{
    std::string_view    input = R"json("Discover")json";
    SerializableIdExtension      id  = {0, 4};

    input >> ThorsAnvil::Serialize::jsonImporter(id);

    EXPECT_EQ("Discover", std::get<std::string>(id.value));
    EXPECT_EQ(4, id.type);
}

TEST(CustomSerializeTest, BlockOneWithLongId)
{
    std::string_view    input = R"json({"id":10,"method":"this/thing","core":12})json";
    BlockOne<SerializableId>            data{0, "", 0};

    input >> ThorsAnvil::Serialize::jsonImporter(data);

    EXPECT_EQ(10, std::get<long>(data.id));
    EXPECT_EQ("this/thing", data.method);
    EXPECT_EQ(12, data.core);
}

TEST(CustomSerializeTest, BlockOneWithLongIdExtension)
{
    std::string_view    input = R"json({"id":10,"method":"this/thing","core":12})json";
    BlockOne<SerializableIdExtension>            data{{0,8}, "", 0};

    input >> ThorsAnvil::Serialize::jsonImporter(data);

    EXPECT_EQ(10, std::get<long>(data.id.value));
    EXPECT_EQ(8, data.id.type);
    EXPECT_EQ("this/thing", data.method);
    EXPECT_EQ(12, data.core);
}

TEST(CustomSerializeTest, BlockOneWithStringId)
{
    std::string_view   input = R"json({"id":"Discover","method":"this/thing","core":12})json";
    BlockOne<SerializableId>            data{0, "", 0};

    input >> ThorsAnvil::Serialize::jsonImporter(data);

    EXPECT_EQ("Discover", std::get<std::string>(data.id));
    EXPECT_EQ("this/thing", data.method);
    EXPECT_EQ(12, data.core);
}
TEST(CustomSerializeTest, BlockOneWithStringIdExtension)
{
    std::string_view   input = R"json({"id":"Discover","method":"this/thing","core":12})json";
    BlockOne<SerializableIdExtension>            data{{0,5}, "", 0};

    input >> ThorsAnvil::Serialize::jsonImporter(data);

    EXPECT_EQ("Discover", std::get<std::string>(data.id.value));
    EXPECT_EQ(5, data.id.type);
    EXPECT_EQ("this/thing", data.method);
    EXPECT_EQ(12, data.core);
}
