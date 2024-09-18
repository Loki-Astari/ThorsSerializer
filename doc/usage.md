![ThorStream](../img/stream.jpg)

    TOC
        C++ API
            Reading
            Writing
            Configuration
        Declared Serializable:
            ThorsAnvil_MakeTrait(&lt;ClassName&gt;, &lt;FieldName&gt; ... )
            ThorsAnvil_ExpandTrait(&lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
            ThorsAnvil_Template_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
            ThorsAnvil_Template_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
            ThorsAnvil_TTemplate_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
            ThorsAnvil_TTemplate_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentType&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
        Override Field Names:
            ThorsAnvil_MakeOverride(&lt;ClassName&gt;, &lt;Override&gt; ...)
            ThorsAnvil_Template_MakeOverride(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;Override&gt; ...)
        Filtering Fields:
            std::optional
            Deprecated: ThorsAnvil_MakeFilter(&lt;ClassName&gt;, &lt;FieldName&gt;)
            Deprecated: ThorsAnvil_Template_MakeFilter(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt;)
        Pointer Fields:
            Allocation
            Polymorphic
        Custom Serialization:
            Depricated: ThorsAnvil_MakeTraitCustom(&lt;ClassName&gt;)
            ThorsAnvil_MakeTraitCustomSerialize(&lt;ClassName&gt;, &gt;CustomSerializationType&lt;)
        #Enum Handling:
            Depricated: ThorsAnvil_MakeEnum(EnumName, ...)
            Depricated: ThorsAnvil_MakeEnumFlag(EnumName, ...)
        Interesting std:: Types:
            std::map<std::string, V>
            std::optional
            std::unique_ptr
            std::shared_ptr
        Example
 
# C++ API

The serialization of objects works on all types that have been declared as `serializable`. The build in types are declared as serializable in `"ThorSerialize/Traits.h"`. The standard `std::` types are declared serializable in `"ThorSerialize/SerUtil.h"`. If you want to declare your own types as serializable please see documentation below.

## Reading

The interface for reading is by using the `<format>Exporter` object. Any types that have been declares as serializable can be exported to a stream interface.

```C++
    // BSON
    #include "ThorSerialize/BsonThor.h"
    ...
        MyType      myVar;
        std::cout << ThorsAnvil::Serialize::bsonExporter(myVar);

    #include "ThorSerialize/Json.h"
    ...
        MyType      myVar;
        std::cout << ThorsAnvil::Serialize::jsonExporter(myVar);

    #include "ThorSerialize/YamlThor.h"
    ...
        MyType      myVar;
        std::cout << ThorsAnvil::Serialize::yamlExporter(myVar);
```
## Writing

The interface for writing is by using the `<format>Importer` object. Any types that have been declares as serializable can be imported from a stream interface.

```C++
    // BSON
    #include "ThorSerialize/BsonThor.h"
    ...
        MyType      myVar;
        std::cin >> ThorsAnvil::Serialize::bsonImporter(myVar);

    #include "ThorSerialize/Json.h"
    ...
        MyType      myVar;
        std::cin >> ThorsAnvil::Serialize::jsonImporter(myVar);

    #include "ThorSerialize/YamlThor.h"
    ...
        MyType      myVar;
        std::cin >> ThorsAnvil::Serialize::yamlImporter(myVar);
```

## Configuration

### Exporter Configuration

The `<format>Exporter` class constructor takes an optional second parameter as configuration.

```C++
    namespace ThorsAnvil::Serialize
    {
        // Used by bsonExporter/jsonExporter/yamlExporter
        enum class OutputType {Default, Stream, Config};
        class PrinterConfig
        {
            public:
                PrinterConfig();
                PrinterConfig& setOutputType(OutputType p_characteristics)      {/*--Implementation Detail--*/  return *this;}
                PrinterConfig& setPolymorphicMarker(std::string const& p_poly)  {/*--Implementation Detail--*/  return *this;}
                PrinterConfig& setCatchExceptions(bool p_catchExceptions)       {/*--Implementation Detail--*/  return *this;}
        };
        // Used by bsonImporter/jsonImporter/yamlImporter
        enum class ParseType   {Weak, Strict, Exact};
        class ParserConfig
        {
            public:
                ParserConfig();
                ParserConfig& setParseStrictness(ParseType p_parseStrictness)   {/*--Implementation Detail--*/  return *this;}
                ParserConfig& setPolymorphicMarker(std::string const& p_poly)   {/*--Implementation Detail--*/  return *this;}
                ParserConfig& setCatchExceptions(bool p_catchExceptions)        {/*--Implementation Detail--*/  return *this;}
        };
    }
```

If you would like to override the default behavior for serialization you can pass a `PrinterConfig` object as the second parameter.

```C++
    std::cout << ThorsAnvil::Serialize::jsonExporter(myVar, PrinterConfig{}.setOutputType(OutputType::Stream);
    std::cin  << ThorsAnvil::Serialize::jsonImporter(myVar, ParserConfig{}.setParseStrictness(ParseType::Exact);
```

The values that can be overridden in the Configuration object are:

#### OutputType:

* Default:  
  The easiest to implement of Stream/Config for the output type (could change over time).
* Stream:  
  The most compressed version of the format.
* Config:  
  The most human readable version of the format.

Note: Only applies to JSON.

### Parse Strictness

The default parser strictness is `Weak`.

* Weak:  
    Extra fields are ignored. Only seen fields affect object.
* Strict:  
    Extra fields cause an exception. Note by default exceptions are caught and the stream marked bad.
* Exact:  
    Extra fields cause an exception. Missing fields cause an exception.

### Polymorphic Marker

Please see the section on `ThorsAnvil_PolyMorphicSerializer()` below.

As part of the serialized object (of polymorphic objects) we include type information. The default field name where type information is saved is `__type`. If your application needs to use the field name `__type` internally then you can override this default and provide your own option.

### Catch Exceptions

By default exceptions in serialization are caught.

When the serialization code encounters an "Exceptional" situation that it can not handle it logs that information (using [`loguru`](https://github.com/emilk/loguru)) and marks the stream as failed with `stream.setstate(std::ios::failbit);`. This behavior mimics the normal C++ stream pattern. If you would prefer an exception to be thrown when there is an issue you can set this parameter on the config object.

# Declared Serializable

All the following macros declare types (not objects) so should be placed in header (along with the class declarations).

* ThorsAnvil_MakeTrait(&lt;ClassName&gt;, &lt;FieldName&gt; ... )
* ThorsAnvil_Template_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
* ThorsAnvil_TTemplate_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
* ThorsAnvil_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
* ThorsAnvil_Template_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)
* ThorsAnvil_TTemplate_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

## ThorsAnvil_MakeTrait(&lt;ClassName&gt;, &lt;FieldName&gt; ... )
For standard structures you simply use the `ThorsAnvil_MakeTrait()` and pass the type name and a list of fields that you want to serialize:

```C++
    struct BankAccount
    {
        std::string     name;
        long            accountNumber;
        double          balnce;
    };
    ThorsAnvil_MakeTrait(BankAccount, name, accountNumber, balnce);
```

This declaration creates a specialization of the type `ThorsAnvil::Serialize::Traits<>`.

Note 1: The `ThorsAnvil_MakeTrait` must appear at the global scope (not inside a namespace), though your class can be inside a namespace.  
Note 2: The serialization code has no special access to your class. If you want the code to be able to serialize private member you need to declare the `Traits<>` class a friend to your class.  

```C++
    namespace MyAddressBook
    {
        class Address
        {
            private:
                friend class ThorsAnvil::Serialize::Traits<Address>;
                std::string     street;
                std::string     city;
        };
        struct Person
        {
            private:
                friend class ThorsAnvil::Serialize::Traits<Person>;
                std::string     name;
                Address         address;
        };
    }
    ThorsAnvil_MakeTrait(MyAddressBook::Address, street, city);
    ThorsAnvil_MakeTrait(MyAddressBook::Person,  name,   address);
```
## ThorsAnvil_ExpandTrait(&lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

This is like the original `ThorsAnvil_MakeTrait()` but your class inherits from another Serializable type.

```C++
    class Base
    {
        int         value1;
        int         value2;
    };
    class Extend: public Base
    {
        int         value3;
        int         value4;
    };
    ThorsAnvil_MakeTrait(Base,          value1, value2);
    ThorsAnvil_ExpandTrait(Base, Extend,value3, value4);
```

## ThorsAnvil_Template_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

If your class is a template type you will need to use `ThorsAnvil_Template_MakeTrait` which just takes the number of template arguments as the first parameter, but is otherwise identical to `ThorsAnvil_MakeTrait()`.

```C++
    template<typename T1, typename T2>
    class DataBase
    {
        T1      data;
        T2      base;
    };
    ThorsAnvil_Template_MakeTrait(2, DataBase, data, base);
```

## ThorsAnvil_Template_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentClassName&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

```C++
    template<typename T, Typename T2>
    class DataBaseFromExtend: public Extend
    {
        T1      data;
        T2      base;
    };
    ThorsAnvil_Template_ExpandTrait(2, DataBaseFromExtend, data, base);
```

## ThorsAnvil_TTemplate_MakeTrait(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

This is so rare. I would like to talk to you if you use it.  
Because it is so rare I don't have any real examples of its usage and the times I have used it I have removed it before the code is complete. So I want some real examples of usage so I can correctly define the interface.

Currently this is exactly the same as `ThorsAnvil_Template_MakeTrait` except the first template type is expected to be `template<typename>`.

```C++
    template<template<typename> typename C, typename V>
    class Storage
    {
        C<V>    store;
    };
    ThorsAnvil_TTemplate_MakeTrait(2, Storage, store);
```

## ThorsAnvil_TTemplate_ExpandTrait(&lt;TemplateCount&gt;, &lt;ParentType&gt;, &lt;ClassName&gt;, &lt;FieldName&gt; ...)

```C++
    template<template<typename> typename C, typename V>
    class StorageExpandsBase: public Base
    {
        C<V>    store;
    };
    ThorsAnvil_TTemplate_ExpandTrait(2, Base, StorageExpandsBase, store);
```

# Override Field Names:

The C++ language has limitations on field names. These limitations are not properties of these serialization formats so it is sometimes useful to provide overrides to field names.

The following declarations should be places in header files directly before the `ThorsAnvil_MakeTrait` and `ThorsAnvil_ExpandTrait` family of declarations.

* ThorsAnvil_MakeOverride(&lt;ClassName&gt;, &lt;Override&gt; ...)
* ThorsAnvil_Template_MakeOverride(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;Override&gt; ...)

## ThorsAnvil_MakeOverride(&lt;ClassName&gt;, &lt;Override&gt; ...)

```C++
    class MongoDB
    {
        std::string     database;
    };
    ThorsAnvil_Template_MakeOverride(MongoDB, {"database", "$db"});
    ThorsAnvil_MakeTrait(MongoDB, database);
```

You can provide multiple overrides. Each override is a `std::pair<std::string, std::string>` representing the `from` and `to` values.

When the `MongoDB` class is serialized it will use the field name `$db` (rather than `database`). This is useful as identifier names beginning with `$` is a non standard extension in C++ so you can not reliably use it in an identifier.

```JSON
    {"$db":"MyDataBaseName"}
```

## ThorsAnvil_Template_MakeOverride(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &lt;Override&gt; ...)

Same as `ThorsAnvil_MakeOverride` but for a template class.

# Filtering Fields:
## std::optional

A field that has the type `std::optional<T>` will only be serialized if there is a value in the variable.

## Deprecated: ThorsAnvil_MakeFilter(&lt;ClassName&gt;, &lt;FieldName&gt;)

This interface is deprecated.  
Maintained for backward compatibility only.  

Please use `std::optional` as an alternative.

### ThorsAnvil_Template_MakeFilter(&lt;TemplateCount&gt;, &lt;ClassName&gt;, &ltFieldName&gt)

Same as `ThorsAnvil_MakeFilter` but for template class.

# Pointer Fields:

When a field is a pointer type. Its value will be released by calling `delete`. If there is a data (not `Null`) then a new value will be created using the operator `new T{}`, then the data will be read onto the newly created object. Conversely if the input format describes `Null` value then the pointer will be set to `nullptr`.

## Override Allocation

This default behavior can be overridden with `ThorsAnvil_PointerAllocator(<ClassName>, <AllocationType>)` defining an allocator type that the serialization library will use. The expected interface for the allocator type is:


```C++
    struct Allocator
    {
        static ClassType* alloc();
        static void release(ClassType* value);
    };
```

An example usage:

```C++
    struct Node
    {
        int     value;
        Node*   left;
        Node*   right;
    };
    struct NodeAllocator
    {
        static Node* alloc()                {return Graph::addNode();}
        static void  release(Node* ptr)     {Graph::releaseNode(ptr);}
    };
    ThorsAnvil_MakeTrait(Node, value, left, right);
    ThorsAnvil_PointerAllocator(Node, NodeAllocator);
```

## Polymorphic

If the type `T` is polymorphic then simple allocation is not sufficient. You need to understand the type being created, to do this you need to store type information in the object. The serialization/de-serialization code will handle this automatically if you make some small additions.

Inside the class add the macro `ThorsAnvil_PolyMorphicSerializer`. This adds some virtual functions that are used in the serialization/de-serialization processes. Note: You should add this in a `public` section of your class.

```C++

    // In Header File.
    struct Transport
    {
        virtual ~Transport() = 0;
        ThorsAnvil_PolyMorphicSerializer(Transport);

        int         wheelCount;
    };
    struct Car
    {
        // Note: the 'WithOverride' just adds 'override' to any functions to prevent warnings.
        //       You should use it with all by the base class.
        ThorsAnvil_PolyMorphicSerializerWithOverride(Car);
        Engine      engineInfo;
    };
    struct Bike
    {
        ThorsAnvil_PolyMorphicSerializerWithOverride(Bike);
        bool        electric;
    };
    struct PersonTransport
    {
        std::string                 name;
        std::unique_ptr<Transport>  transport;
    };
    ThorsAnvil_MakeTrait(Transport,         wheelCount);
    ThorsAnvil_MakeTrait(Car,               engineInfo);
    ThorsAnvil_MakeTrait(Bike,              electric);
    ThorsAnvil_MakeTrait(PersonTransport,   name, transport);

```

# Custom Serialization:

Sometimes the standard techniques are not sufficient and you need to inject code into the processes.

## ThorsAnvil_MakeTraitCustom(&lt;ClassName&gt;)

This method is deprecated. Please do not use. It is maintained for backward compatibility. See `ThorsAnvil_MakeTraitCustomSerialize(<ClassName>, <CustomSerializationType>)` for details about replacement.

## ThorsAnvil_MakeTraitCustomSerialize(&lt;ClassName&gt;, &lt;CustomSerializationType&gt;)

The `CustomSerializationType` must implement the following interface.

```C++
    struct SerializableType
    {
        static std::size_t getPrintSizeBson(BsonPrinter& printer, <ClassName> const& object);
        static void writeCustom(PrinterInterface& printer, <ClassName> const& object);
        static void readCustom(ParserInterface& parser, <ClassName>& object);
    };
```

# Enum Handling

Enum's are now handled vie [MagicEnum](https://github.com/Neargye/magic_enum). The following functions are maintained only for backward compatibility.

## ThorsAnvil_MakeEnum(EnumName, ...)
## ThorsAnvil_MakeEnumFlag(EnumName, ...)

# Interesting std:: Types:

## std::map&lt;std::string, V&gt;

The generic serialization of `std::map<K, V>` / `std::unordered_map<K, V>` is serialized as an array of `std::pairs<K, V>`. Note The `std::pair<>` is serialized as a document with the values `first` and `second` (as you should expect). But for the special case where the map key is `std::string` the map is serialized as a document.

## std::optional

A standard optional field is only serialized if it has a value. i.e. Both the key and value are NOT placed on the output stream if there is no value stored in the variable.

## std::unique_ptr

The unique_ptr is serialized as if the object was a pointer. If the pointer is `nullptr` then we serialize `Null` to the stream (as supported by the output format) if the pointer is non null it will be serialized as if the value was a normal value.

## std::shared_ptr

I have not implemented the serialization of `std::shared_ptr`. This is relatively trivial to do like `std::unique_ptr`, but I want to handle situations where multiple pointers in the serialized object point at the same object. In this case I would like serialization/de-serialization to be able to handle this situation and de-serialize into a single object.

# Example:

## BankAccount.h

```C++
#include "Traits.h"
#include "Serialize.h"
#include "SerUtil.h"

#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"

#include "test/SerializeTest.h"
#include <vector>

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

        // generic version we simply stream the integer value.
        static constexpr std::size_t sizeOfID = 12;
        virtual  std::size_t getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter& printer, ID const& object) override
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
```

