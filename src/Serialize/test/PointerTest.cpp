
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

TEST(PointerTest, BuildStringFromTree)
{
    Tree*   root = new Tree{34, new Tree{22, new Tree{10, nullptr, nullptr}, nullptr}, new Tree{50, nullptr, new Tree{70, nullptr, nullptr}}};
    std::cout << ThorsAnvil::Serialize::jsonExport(root);
}
TEST(PointerTest, BuildTreeFromString)
{
    std::string json(R"(
{
	"value": 34,
	"left":
	{
		"value": 22,
		"left":
		{
			"value": 10,
			"left": null,
			"right": null
		},
		"right": null
	},
	"right":
	{
		"value": 50,
		"left": null,
		"right":
		{
			"value": 70,
			"left": null,
			"right": null
		}
	}
})");
    std::stringstream   jsonStream(json);
    Tree* root = nullptr;

    jsonStream >> ThorsAnvil::Serialize::jsonImport(root);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 34);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->value, 22);
    ASSERT_NE(root->left->left, nullptr);
    EXPECT_EQ(root->left->left->value, 10);
    EXPECT_EQ(root->left->left->left, nullptr);
    EXPECT_EQ(root->left->left->right, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->value, 50);
    EXPECT_EQ(root->right->left, nullptr);
    ASSERT_NE(root->right->right, nullptr);
    EXPECT_EQ(root->right->right->value, 70);
    EXPECT_EQ(root->right->right->left, nullptr);
    EXPECT_EQ(root->right->right->right, nullptr);
}




#if 0
    std::string         inputStr(R"({"normalMember":7,"staticMember":14})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    StaticMember        data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
#endif
