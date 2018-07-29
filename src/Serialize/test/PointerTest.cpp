
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>

struct Tree
{
    int     value;
    Tree*   left;
    Tree*   right;
};
ThorsAnvil_MakeTrait(Tree, value, left, right);
namespace ThorsAnvil
{
    namespace Serialize
    {

    }
}

TEST(PointerTest, test1)
{
    Tree*   root = new Tree{34, new Tree{22, new Tree{10, nullptr, nullptr}, nullptr}, new Tree{50, nullptr, new Tree{70, nullptr, nullptr}}};
    std::cout << ThorsAnvil::Serialize::jsonExport(root);




#if 0
    std::string         inputStr(R"({"normalMember":7,"staticMember":14})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    StaticMember        data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
#endif
}

