#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <string>
#include <sstream>

namespace PointerTest
{
struct Tree
{
    int     value;
    Tree*   left    = nullptr;
    Tree*   right   = nullptr;
};
}
ThorsAnvil_MakeTrait(PointerTest::Tree, value, left, right);

TEST(PointerTestString, JsonBuildStringFromTree)
{
    PointerTest::Tree*   root = new PointerTest::Tree{34, new PointerTest::Tree{22, new PointerTest::Tree{10, nullptr, nullptr}, nullptr}, new PointerTest::Tree{50, nullptr, new PointerTest::Tree{70, nullptr, nullptr}}};
    std::string         data;
    data << ThorsAnvil::Serialize::jsonExporter(root, false);
    std::string result = data;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"value":34,"left":{"value":22,"left":{"value":10,"left":null,"right":null},"right":null},"right":{"value":50,"left":null,"right":{"value":70,"left":null,"right":null}}})");
}
TEST(PointerTestString, JsonBuildTreeFromString)
{
    std::string jsonStream(R"(
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
    PointerTest::Tree* root = nullptr;

    jsonStream >> ThorsAnvil::Serialize::jsonImporter(root, false);
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

TEST(PointerTestString, BsonBuildStringFromTree)
{
    PointerTest::Tree*   root = new PointerTest::Tree{34, new PointerTest::Tree{22, new PointerTest::Tree{10, nullptr, nullptr}, nullptr}, new PointerTest::Tree{50, nullptr, new PointerTest::Tree{70, nullptr, nullptr}}};
    std::string         data;
    data << ThorsAnvil::Serialize::bsonExporter(root, false);
    std::string result = data;


    static const char expectedRaw[]
                = "\x91\x00\x00\x00"
                      "\x10" "value\x00" "\x22\x00\x00\x00"
                      "\x03" "left\x00"
                            "\x3A\x00\x00\x00"
                                "\x10" "value\x00" "\x16\x00\x00\x00"
                                "\x03" "left\x00"
                                        "\x1D\x00\x00\x00"
                                            "\x10" "value\x00" "\x0A\x00\x00\x00"
                                            "\x0A" "left\x00"
                                            "\x0A" "right\x00"
                                        "\x00"
                                "\x0A" "right\x00"
                            "\x00"
                      "\x03" "right\x00"
                            "\x3A\x00\x00\x00"
                                "\x10" "value\x00" "\x32\x00\x00\x00"
                                "\x0A" "left\x00"
                                "\x03" "right\x00"
                                        "\x1D\x00\x00\x00"
                                            "\x10" "value\x00" "\x46\x00\x00\x00"
                                            "\x0A" "left\x00"
                                            "\x0A" "right\x00"
                                        "\x00"
                            "\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE OUTPUT R"({"value":34,"left":{"value":22,"left":{"value":10,"left":null,"right":null},"right":null},"right":{"value":50,"left":null,"right":{"value":70,"left":null,"right":null}}})");
}
TEST(PointerTestString, BsonBuildTreeFromString)
{
/*
NOTE INPUT
    std::string bson(R"(
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
*/
    static const char bsonRaw[]
                = "\x91\x00\x00\x00"
                      "\x10" "value\x00" "\x22\x00\x00\x00"
                      "\x03" "left\x00"
                            "\x3A\x00\x00\x00"
                                "\x10" "value\x00" "\x16\x00\x00\x00"
                                "\x03" "left\x00"
                                        "\x1D\x00\x00\x00"
                                            "\x10" "value\x00" "\x0A\x00\x00\x00"
                                            "\x0A" "left\x00"
                                            "\x0A" "right\x00"
                                        "\x00"
                                "\x0A" "right\x00"
                            "\x00"
                      "\x03" "right\x00"
                            "\x3A\x00\x00\x00"
                                "\x10" "value\x00" "\x32\x00\x00\x00"
                                "\x0A" "left\x00"
                                "\x03" "right\x00"
                                        "\x1D\x00\x00\x00"
                                            "\x10" "value\x00" "\x46\x00\x00\x00"
                                            "\x0A" "left\x00"
                                            "\x0A" "right\x00"
                                        "\x00"
                            "\x00"
                  "\x00";

    std::string bsonStream(std::begin(bsonRaw), std::end(bsonRaw) - 1);
    PointerTest::Tree* root = nullptr;

    bsonStream >> ThorsAnvil::Serialize::bsonImporter(root, false);
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

