#ifndef BANK_ACCOUNT_TEST_H
#define BANK_ACCOUNT_TEST_H

#include "SerializeConfig.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include "ThorsIOUtil/Utility.h"
#include <vector>


namespace ThorsAnvil
{
    namespace Serialize
    {
template<typename T>
struct DefaultCustomSerializer
{
        virtual ~DefaultCustomSerializer() {}

        virtual void writeJson(ThorsAnvil::Serialize::JsonPrinter& /*printer*/, T const& object)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeJson",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the writeJson() method on the SerializationClass")
                                    );
        }
        virtual void readJson(ThorsAnvil::Serialize::JsonParser& /*parser*/, T& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readJson",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the readJson() method on the SerializationClass")
                                    );
        }

        virtual void writeYaml(ThorsAnvil::Serialize::YamlPrinter& /*printer*/, T const& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeYaml",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the writeYaml() method on the SerializationClass")
                                    );
        }
        virtual  void readYaml(ThorsAnvil::Serialize::YamlParser& /*parser*/, T& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readYaml",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the readYaml() method on the SerializationClass")
                                    );
        }

        virtual  std::size_t getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, T const& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "getPrintSizeBson",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the getPrintSizeBson() method on the SerializationClass")
                                    );
        }
        virtual char getBsonByteMark() {return '\x00';} // You should also override this see Bson specifications
        virtual void writeBson(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, T const& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeBson",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the writeBson() method on the SerializationClass")
                                    );
        }
        virtual void readBson(ThorsAnvil::Serialize::BsonParser& /*parser*/, char byteMarker, T& /*object*/)
        {
            throw CriticalException(
                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readBson",
                                                           "Using an unimplemented translation:\n",
                                                           "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                           "But have not implemented the readBson() method on the SerializationClass")
                                    );
        }
};
    }
}
namespace OnLineBank
{
    enum TransType {Error, Deposit, Withdraw, Correction};
    struct ID
    {
        long id;
        ID() : id(-1){}
        ID(long id): id(id){}
    };
    struct SerializeID: public ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>
    {
        virtual void writeJson(ThorsAnvil::Serialize::JsonPrinter& printer, ID const& object)   override
        {
            printer.stream() << object.id;
        }
        virtual void readJson(ThorsAnvil::Serialize::JsonParser& parser, ID& object)            override
        {
            parser.stream() >> object.id;
        }

        //virtual void writeYaml(ThorsAnvil::Serialize::YamlPrinter& printer, ID const& object)   override 
        //virtual void readYaml(ThorsAnvil::Serialize::YamlParser& parser, ID& object)            override

        // generic version we simply stream the integer value.
        static constexpr std::size_t sizeOfID = 12;
        virtual  std::size_t getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter& printer, ID const& /*object*/) override
        {
            return sizeOfID;
        }
        virtual char getBsonByteMark()   override   {return '\x07';}
        virtual void writeBson(ThorsAnvil::Serialize::BsonPrinter& printer, ID const& object)   override
        {
            printer.stream().write(reinterpret_cast<char const*>(&object.id), sizeof(object.id));
            printer.stream().write("            ", sizeOfID - sizeof(object.id));
        }
        virtual void readBson(ThorsAnvil::Serialize::BsonParser& parser, char byteMarker, ID& object)             override
        {
            parser.stream().read(reinterpret_cast<char*>(&object.id), sizeof(object.id));
            parser.stream().ignore(sizeOfID - sizeof(object.id));
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
        Transaction()
            : Transaction(0, 0, TransType::Error)
        {}
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
        protected:
            void update(int amount) {balance += amount;}
        public:
            BankAccount()
                : BankAccount(-1, -1, "Bad", false)
            {}
            BankAccount(ID const& id, int balance, std::string const& details, bool valid)
                : id(id)
                , balance(balance)
                , details(details)
                , valid(valid)
            {}
            virtual ~BankAccount()  {}
            int getAccountIdent()   {return id.id;}
            int getBalance()        {return balance;}
            bool isValid()          {return valid;}
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
                switch (type)
                {
                    case TransType::Withdraw:   update(-amount);break;
                    case TransType::Deposit:    update(amount);break;
                    case TransType::Correction: update(-getBalance() + amount);break;
                    default: break;
                }
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

ThorsAnvil_MakeEnum(OnLineBank::TransType, Error, Deposit, Withdraw, Correction);
ThorsAnvil_MakeTraitCustomSerialize(OnLineBank::ID, OnLineBank::SerializeID);
ThorsAnvil_MakeTrait(OnLineBank::Transaction, timeStamp, amount, type);
ThorsAnvil_Template_MakeTrait(1, OnLineBank::Flounder, data);
ThorsAnvil_MakeTrait(OnLineBank::BankAccount, id, balance, details, valid);
ThorsAnvil_ExpandTrait(OnLineBank::BankAccount, OnLineBank::CurrentAccount, actions);
ThorsAnvil_ExpandTrait(OnLineBank::BankAccount, OnLineBank::DepositAccount, withdrawlLimit);

#endif

