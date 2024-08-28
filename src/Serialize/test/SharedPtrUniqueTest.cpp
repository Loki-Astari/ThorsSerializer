#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>

TEST(SharedPtrUniqueTest, MultipleCopiesOfSameSharedPtrJson)
{
    std::shared_ptr<int>    value = std::make_shared<int>(5);

    std::vector<std::shared_ptr<int>>   data;
    // Two copies of the shard pointer.
    data.emplace_back(value);
    data.emplace_back(value);
    data.emplace_back(value);
    data.emplace_back(value);

	std::stringstream	expected;
	expected << R"(
[5,
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	},
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	},
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	}])";

    std::stringstream   ss;
    ss << ThorsAnvil::Serialize::jsonExporter(data);

    EXPECT_EQ(expected.str(), ss.str());
}

TEST(SharedPtrUniqueTest, MultipleCopiesOfSameSharedPtrBson)
{
    std::shared_ptr<int>    value = std::make_shared<int>(5);

    std::vector<std::shared_ptr<int>>   data;
    // Two copies of the shard pointer.
    data.emplace_back(value);
    data.emplace_back(value);
    data.emplace_back(value);
    data.emplace_back(value);

    using namespace std::string_literals;
    std::string expected    = "\x69\x00\x00\x00"
                                "\x10" "0\x00"                  "\x05\x00\x00\x00"
                                "\x03" "1\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x00\x00\x00"
                                    "\x00"
                                "\x03" "2\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x00\x00\x00"
                                    "\x00"
                                "\x03" "3\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x00\x00\x00"
                                    "\x00"
                                "\x00"s;

    std::intmax_t   ptr = reinterpret_cast<std::intmax_t>(value.get());
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[33]);
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[64]);
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[95]);

    std::stringstream   ss;
    ss << ThorsAnvil::Serialize::bsonExporter(data);

    EXPECT_EQ(expected, ss.str());
}
