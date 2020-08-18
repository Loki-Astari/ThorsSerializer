#include "gtest/gtest.h"
#include "BankAccountTest.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

TEST(BankAccountTest, JsonExportCustomField)
{
    bool    serializeOK     = false;
    bool    deserializeOK   = false;

    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream outputStream;
    if (outputStream << ThorsAnvil::Serialize::jsonExporter(src))
    {
        serializeOK = true;
    }

    std::string result = outputStream.str();

    auto find = result.find(R"("id":234)");

    std::stringstream inputStream(result);

    OnLineBank::CurrentAccount dst;
    if (inputStream >>ThorsAnvil::Serialize::jsonImporter(dst))
    {
        deserializeOK = true;
    }

    auto account = dst.getAccountIdent();
    EXPECT_EQ(account, 234);
    EXPECT_TRUE(serializeOK);
    EXPECT_TRUE(deserializeOK);
}

TEST(BankAccountTest, BsonExportCustomField)
{
    bool    serializeOK     = false;
    bool    deserializeOK   = false;

    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream outputStream;
    if (outputStream << ThorsAnvil::Serialize::bsonExporter(src))
    {
        serializeOK = true;
    }

    std::string result = outputStream.str();

    std::stringstream inputStream(result);

    OnLineBank::CurrentAccount dst;
    if (inputStream >> ThorsAnvil::Serialize::bsonImporter(dst))
    {
        deserializeOK = true;
    }

    auto account = dst.getAccountIdent();
    EXPECT_EQ(account, 234);
    EXPECT_TRUE(serializeOK);
    EXPECT_TRUE(deserializeOK);
}

