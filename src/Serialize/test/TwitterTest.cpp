#include "gtest/gtest.h"
#include "JsonThor.h"
#include "test/Twitter.h"
#include <fstream>

TEST(TwitterTest, ReadTwitterObject)
{
    std::ifstream           input("test/data/twitter.json");
    TwitterTest::Twitter    value;
    bool                    importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
    EXPECT_EQ(value.statuses[0].user.screen_name, "ayuu0123");
}

