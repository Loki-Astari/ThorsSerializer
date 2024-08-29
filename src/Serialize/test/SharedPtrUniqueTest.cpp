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
[
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(,
		"data": 5
	},
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	},
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	},
	{
		"sharedPtrName": )" << reinterpret_cast<std::intmax_t>(value.get()) << R"(
	}
])";

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
    std::string expected    = "\x8B\x00\x00\x00"
                                "\x03" "0\x00"
                                    "\x26\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x00\x00\x00"
                                    "\x10" "data\x00"           "\x05\x00\x00\x00"
                                    "\x00"
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
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[26]);
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[67]);
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[98]);
    std::copy(reinterpret_cast<char*>(&ptr), reinterpret_cast<char*>(&ptr) + sizeof(ptr), &expected[129]);

    std::stringstream   ss;
    ss << ThorsAnvil::Serialize::bsonExporter(data);

    EXPECT_EQ(expected, ss.str());
}

TEST(SharedPtrUniqueTest, ReadMultipleCopiesOfSameSharedPtrJson)
{
    std::shared_ptr<int>    value = std::make_shared<int>(5);

    std::stringstream   ss(R"(
[
	{
		"sharedPtrName": 123456,
		"data": 5
	},
	{
		"sharedPtrName": 123456
	},
	{
		"sharedPtrName": 123456
	},
	{
		"sharedPtrName": 123456
	}
])");

    std::vector<std::shared_ptr<int>>   data;
    ss >> ThorsAnvil::Serialize::jsonImporter(data);

    EXPECT_EQ(4, data.size());
    EXPECT_EQ(5, *data[0]);
    EXPECT_EQ(4, data[0].use_count());
}

TEST(SharedPtrUniqueTest, ReadMultipleCopiesOfSameSharedPtrBson)
{
    std::shared_ptr<int>    value = std::make_shared<int>(5);


    using namespace std::string_literals;
    std::stringstream input("\x8B\x00\x00\x00"
                                "\x03" "0\x00"
                                    "\x26\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x03\x02\x01"
                                    "\x10" "data\x00"           "\x05\x00\x00\x00"
                                    "\x00"
                                "\x03" "1\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x03\x02\x01"
                                    "\x00"
                                "\x03" "2\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x03\x02\x01"
                                    "\x00"
                                "\x03" "3\x00"
                                    "\x1c\x00\x00\x00"
                                    "\x12" "sharedPtrName\00"   "\x00\x00\x00\x00\x00\x03\x02\x01"
                                    "\x00"
                                "\x00"s);

    std::vector<std::shared_ptr<int>>   data;
    input >> ThorsAnvil::Serialize::bsonImporter(data);

    EXPECT_EQ(4, data.size());
    EXPECT_EQ(5, *data[0]);
    EXPECT_EQ(4, data[0].use_count());
}


