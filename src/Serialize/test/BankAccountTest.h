#ifndef BANK_ACCOUNT_TEST_H
#define BANK_ACCOUNT_TEST_H

#include "SerializeConfig.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <vector>


namespace OnLineBank
{
    enum TransType {Deposit, Withdraw, Correction};
    struct ID
    {
        long id;
    };
    struct SerializeID
    {
        // generic version we simply stream the integer value.
        static std::size_t getPrintSize(ThorsAnvil::Serialize::PrinterInterface& /*printer*/, ID const& /*object*/)
        {
            std::cerr << "getPrintSize: Custom\n";
            return 0;
        }
        static void write(ThorsAnvil::Serialize::PrinterInterface& /*printer*/, ID const& /*object*/)
        {
            std::cerr << "Write: Custom\n";
        }
        static void read(ThorsAnvil::Serialize::ParserInterface& /*parser*/, ID& /*object*/)
        {
            std::cerr << "Read: Custom\n";
        }

        // For Bson we need to encode it for Bson (Note: This is a simple example not necessarily a good one).
        static std::size_t getPrintSize(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, ID const& /*object*/)
        {
            std::cerr << "BSON getPrintSize: Bson\n";
            return 0;
        }
        static void writer(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, ID& /*object*/)
        {
            std::cerr << "BSON: Write: Bson\n";
        }
        static void read(ThorsAnvil::Serialize::BsonParser& /*parser*/, ID& /*object*/)
        {
            std::cerr << "BSON: Read: Bson\n";
        }
    };

    template<typename T>
    struct Flounder
    {
        T   data;
    };

    struct Transaction
    {
        long        timeStamp;
        int         amount;
        TransType   type;
        Transaction() {}
        Transaction(long timeStamp, int amount, TransType type)
            : timeStamp(timeStamp)
            , amount(amount)
            , type(type)
        {}
    };
    class BankAccount
    {
            friend ThorsAnvil::Serialize::Traits<OnLineBank::BankAccount>;
            ID              id;
            int             balance;
            std::string     details;
            bool            valid;
        public:
            BankAccount() {}
            BankAccount(ID const& id, int balance, std::string const& details, bool valid)
                : id(id)
                , balance(balance)
                , details(details)
                , valid(valid)
            {}
            virtual ~BankAccount() {}
            int getAccountIdent() {return id.id;}
            ThorsAnvil_PolyMorphicSerializer(OnLineBank::BankAccount);
            // Normal Methods
    };
    class CurrentAccount: public BankAccount
    {
            friend ThorsAnvil::Serialize::Traits<OnLineBank::CurrentAccount>;
            std::vector<Transaction>    actions;
        public:
            using BankAccount::BankAccount;
            CurrentAccount() {}
            ThorsAnvil_PolyMorphicSerializer(OnLineBank::CurrentAccount);
            void addTransaction(long timeStamp, int amount, TransType type)
            {
                actions.emplace_back(timeStamp, amount, type);
            }
    };
    class DepositAccount: public BankAccount
    {
            friend ThorsAnvil::Serialize::Traits<OnLineBank::DepositAccount>;
            int withdrawlLimit;
        public:
            using BankAccount::BankAccount;
            DepositAccount() {}
            ThorsAnvil_PolyMorphicSerializer(OnLineBank::DepositAccount);
    };
}

ThorsAnvil_MakeEnum(OnLineBank::TransType, Deposit, Withdraw, Correction);
ThorsAnvil_MakeTraitCustomSerialize(OnLineBank::ID, OnLineBank::SerializeID);
ThorsAnvil_MakeTrait(OnLineBank::Transaction, timeStamp, amount, type);
ThorsAnvil_Template_MakeTrait(1, OnLineBank::Flounder, data);
ThorsAnvil_MakeTrait(OnLineBank::BankAccount, id, balance, details, valid);
ThorsAnvil_ExpandTrait(OnLineBank::BankAccount, OnLineBank::CurrentAccount, actions);
ThorsAnvil_ExpandTrait(OnLineBank::BankAccount, OnLineBank::DepositAccount, withdrawlLimit);

#endif

