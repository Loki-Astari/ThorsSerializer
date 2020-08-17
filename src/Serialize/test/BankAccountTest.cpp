#include "gtest/gtest.h"
#include "BankAccountTest.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

TEST(BankAccountTest, JsonExportCustomField)
{
    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream outputStream;
    outputStream << ThorsAnvil::Serialize::jsonExporter(src);

    std::string result = outputStream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));

    auto find = result.find(R"("id":234)");
    EXPECT_NE(find, std::string::npos);

    std::stringstream inputStream(result);

    OnLineBank::CurrentAccount dst;
    inputStream >>ThorsAnvil::Serialize::jsonImporter(dst);

    auto account = dst.getAccountIdent();
    EXPECT_EQ(account, 234);
}

TEST(BankAccountTest, BsonExportCustomField)
{
    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream outputStream;
    outputStream << ThorsAnvil::Serialize::bsonExporter(src);

    std::string result = outputStream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));

    std::stringstream inputStream(result);

    OnLineBank::CurrentAccount dst;
    inputStream >>ThorsAnvil::Serialize::bsonImporter(dst);

    auto account = dst.getAccountIdent();
    EXPECT_EQ(account, 234);
}

