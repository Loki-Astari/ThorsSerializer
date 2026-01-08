#include <gtest/gtest.h>
#include "BankAccountTest.h"
#include "JsonThor.h"

TEST(BuilderTest, jsonBuild)
{
    char const data[] = R"({"id": 12, "balance": 23, "details": "Mine", "valid":true, "actions":[{"timeStamp": 1, "amount": 2, "type": "Deposit"}, {"timeStamp": 2, "amount": 4, "type": "Withdraw"}]})";

    OnLineBank::CurrentAccount  account = ThorsAnvil::Serialize::jsonBuilder<OnLineBank::CurrentAccount>(std::string_view(data));

    EXPECT_EQ(12, account.getAccountIdent());
    EXPECT_EQ(23, account.getBalance());
}

TEST(BuilderTest, yamlBuild)
{
    char const data[] = R"(
id: 12
balance: 23
details: Mine
valid: true
actions:
  - timeStamp: 1
    amount: 2
    type: Deposit
  - timeStamp: 2
    amount: 4
    type: Withdraw
)";


    OnLineBank::CurrentAccount  account = ThorsAnvil::Serialize::yamlBuilder<OnLineBank::CurrentAccount>(std::string_view(data));

    EXPECT_EQ(12, account.getAccountIdent());
    EXPECT_EQ(23, account.getBalance());
}

TEST(BuilderTest, bsonBuild)
{
    char const data[] = "\xb5\x00\x00\x00\x07\x69\x64\x00\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x62\x61\x6c\x61\x6e\x63\x65\x00\x17\x00\x00\x00\x02\x64\x65\x74\x61\x69\x6c\x73\x00\x05\x00\x00\x00\x4d\x69\x6e\x65\x00\x08\x76\x61\x6c\x69\x64\x00\x01\x04\x61\x63\x74\x69\x6f\x6e\x73\x00\x70\x00\x00\x00\x03\x30\x00\x32\x00\x00\x00\x10\x74\x69\x6d\x65\x53\x74\x61\x6d\x70\x00\x01\x00\x00\x00\x10\x61\x6d\x6f\x75\x6e\x74\x00\x02\x00\x00\x00\x02\x74\x79\x70\x65\x00\x08\x00\x00\x00\x44\x65\x70\x6f\x73\x69\x74\x00\x00\x03\x31\x00\x33\x00\x00\x00\x10\x74\x69\x6d\x65\x53\x74\x61\x6d\x70\x00\x02\x00\x00\x00\x10\x61\x6d\x6f\x75\x6e\x74\x00\x04\x00\x00\x00\x02\x74\x79\x70\x65\x00\x09\x00\x00\x00\x57\x69\x74\x68\x64\x72\x61\x77\x00\x00\x00\x00";


    OnLineBank::CurrentAccount  account = ThorsAnvil::Serialize::bsonBuilder<OnLineBank::CurrentAccount>(std::string_view(data, data + 181));

    EXPECT_EQ(12, account.getAccountIdent());
    EXPECT_EQ(23, account.getBalance());
}
