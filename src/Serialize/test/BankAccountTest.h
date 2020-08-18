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
#include <vector>


namespace ThorsAnvil
{
    namespace Serialize
    {
template<typename T>
struct DefaultCustomSerializer
{
        virtual ~DefaultCustomSerializer() {}

        virtual  std::size_t getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, T const& /*object*/)
        {
            std::cerr << "Default getPrintSizeBson\n";
            throw CriticalException("Bad");
        }
        virtual void writeJson(ThorsAnvil::Serialize::JsonPrinter& /*printer*/, T const& object)
        {
            std::cerr << "Default writeJson\n";
            throw CriticalException("Bad");
        }
        virtual void readJson(ThorsAnvil::Serialize::JsonParser& /*parser*/, T& /*object*/)
        {
            std::cerr << "Default readJson\n";
            throw CriticalException("Bad");
        }

        virtual void writeYaml(ThorsAnvil::Serialize::YamlPrinter& /*printer*/, T const& /*object*/)
        {
            std::cerr << "Default writeYaml\n";
            throw CriticalException("Bad");
        }
        virtual  void readYaml(ThorsAnvil::Serialize::YamlParser& /*parser*/, T& /*object*/)
        {
            std::cerr << "Default readYaml\n";
            throw CriticalException("Bad");
        }

        virtual void writeBson(ThorsAnvil::Serialize::BsonPrinter& /*printer*/, T const& /*object*/)
        {
            std::cerr << "Default writeBson\n";
            throw CriticalException("Bad");
        }
        virtual void readBson(ThorsAnvil::Serialize::BsonParser& /*parser*/, T& /*object*/)
        {
            std::cerr << "Default readBson\n";
            throw CriticalException("Bad");
        }
};
    }
}
namespace OnLineBank
{
    enum TransType {Deposit, Withdraw, Correction};
    struct ID
    {
        long id;
        ID() : id(-1){}
        ID(long id): id(id){}
    };
    struct SerializeID: public ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>
    {
        // generic version we simply stream the integer value.
        virtual  std::size_t getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter& printer, ID const& /*object*/) override
        {
            std::cerr << "ID  getPrint Size\n";
            return 12;
        }
        virtual void writeJson(ThorsAnvil::Serialize::JsonPrinter& printer, ID const& object)   override
        {
            std::cerr << "ID writeJson\n";
            std::cerr << printer.stream().good() << " " << printer.stream().bad() << " " << printer.stream().eof() << " " << printer.stream().fail() << "\n";
            //printer.addPrefix() << object.id;
            printer.stream() << ": " << object.id;
            std::cerr << printer.stream().good() << " " << printer.stream().bad() << " " << printer.stream().eof() << " " << printer.stream().fail() << "\n";
        }
        virtual void readJson(ThorsAnvil::Serialize::JsonParser& parser, ID& object)            override
        {
            std::cerr << "ID readJson\n";
            std::cerr << parser.stream().good() << " " << parser.stream().bad() << " " << parser.stream().eof() << " " << parser.stream().fail() << "\n";
            parser.stream() >> object.id;
            std::cerr << "SECOND: >" << object.id << "<\n";
            std::cerr << parser.stream().good() << " " << parser.stream().bad() << " " << parser.stream().eof() << " " << parser.stream().fail() << "\n";
        }

        //virtual void writeYaml(ThorsAnvil::Serialize::YamlPrinter& printer, ID const& object)   override 
        //virtual void readYaml(ThorsAnvil::Serialize::YamlParser& parser, ID& object)            override

        virtual void writeBson(ThorsAnvil::Serialize::BsonPrinter& printer, ID const& object)   override
        {
            std::cerr << "ID  writeBson Size\n";
            printer.writeKey('\x07', 12);
            printer.stream().write(reinterpret_cast<char const*>(&object.id), sizeof(object.id));
            printer.stream().write("            ", 12 - sizeof(object.id));
        }
        virtual void readBson(ThorsAnvil::Serialize::BsonParser& parser, ID& object)             override
        {
            std::cerr << "ID  readBSON Size\n";
            parser.stream().read(reinterpret_cast<char*>(&object.id), sizeof(object.id));
            parser.stream().ignore(12 - sizeof(object.id));
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

