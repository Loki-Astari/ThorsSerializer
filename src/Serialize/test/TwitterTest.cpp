#include "SerializeConfig.h"
#include "SerUtil.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "test/TwitterTest.h"
#include <fstream>

TEST(TwitterTest, ReadTwitterObject)
{
    using ThorsAnvil::Serialize::ParseType;
    std::ifstream           input("test/data/twitter.json");
    std::string             data;
    std::getline(input, data, static_cast<char>(-1));

    for (int loop = 0; loop < 10; ++loop)
    {
        bool                    importDone = false;
        TwitterTest::Twitter    value;

        if (data >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
            importDone = true;
        }
        EXPECT_EQ(importDone, true);
        EXPECT_EQ(value.statuses[0].user.screen_name, "ayuu0123");
    }
}

