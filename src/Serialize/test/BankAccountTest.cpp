#include "gtest/gtest.h"
#include "BankAccountTest.h"

TEST(BankAccountTest, CustomTest)
{
    OnLineBank::CurrentAccount  account(OnLineBank::ID{234}, 888, "This is an account", true);

    account.addTransaction(1, 32, OnLineBank::Deposit);
    account.addTransaction(2, 12, OnLineBank::Withdraw);
}

