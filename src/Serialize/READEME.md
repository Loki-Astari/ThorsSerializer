
#ThorSerialize

This is a framework for serializing C++ objects to/from stream in some "standard formats" efficiently.
Standard Formats: Currently supported are Json/Yaml


It is designed so that no intermediate format it used; the data is read directly from the object and placed on the stream, conversely the data is read directly from the stream into C++ objects. Note because C++ container con only hold fully formed objects the data is read into temporary object then inserted (moved if possible otherwise copied) into the container.

User defined classes require no additional code to be serialized, only a simple declaration that defines what member need to be serialized. The appropriate declarations for the standard containers has already been provided.

##Usage

There are two main functions for export and import that can be used with streams.

    <formatName>Export(<object>)    eg   jsonExport(o)
    <formatNAme>Import(<object>)    eg   jsonImport(o)

A simple example of usage would be (link against libThorSerialize14.dynlib)
    
    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/Json.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        std::vector<int>    data { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::cout << TS::jsonExport(data) << "\n";
    }

##User declared Types

User defined classes can be made serialize-able by defining a specialization of the class ThorsAnvil::Serialize::Traits<>.  
The macros `ThorsAnvil_MakeTrait` is provided to simplify this for most standard situations. Yes I know macros are nasty. But the idea is to make usage easier and hide the real work. So the macro takes the names of the members.

    #include "ThorSerialize/Traits.h"
    
    namespace TS = ThorsAnvil::Serialize;

    class MyClass
    {
        int             member1;
        double          data2;
        std::string     name;

        // To allow the serialization class access to private members
        // the traits must be a frined of the class. If the members are
        // all public then this is not needed.
        friend class TS::Traits<MyClass>;

        public:
            MyClass(int member1, double data2, std::string const& name)
                : member1(member1), data2(data2), name(name)
            {}
    };

    // This macros crates the appropriate Traits class specialized for the
    // user defined class allowing it to be used by jsonImport() and jsonExport()
    ThorsAnvil_MakeTrait(MyClass, member1, data2, name);

This is all that is need to make a class serialize-able.

    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/Json.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        MyClass     object(15, 100.123, "A string");
        std::cout << TS::jsonExport(object) << "\n";
    }

## Members

A serialize-able class can be a member/parent or contained in another serialize-able with no additional work.

    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/Json.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        std::vector<MyClass>    vec1{ {23, 89.99, "obj1"}, {67, 89.98. "obj2"}, {32, 23.45, "obj3"}};
        std::cout << TS::jsonExport(vec1) << "\n";
    }

## Inheriting


    










A framework for implementing parsers onto.

For each implementation we expect to see:

    File:               Class:              Description:
    ====================================================
    <Name>Printea.h     <Name>Printer       A class that implements the PrinterInterface (defined in Serialize.h)
    <Name>Parser.h      <Name>Parser        A class that implements the ParserInterface (defined in Serialize.h)
    <Name>.h            Name                A class "Name" that defines the names of the printer and parser types.
                        <name>Import        Import/Export function that simply wrap the Import/Export functions
                        <name>Export        generic function (using "Name") as input.

Other Files to make Serialization automatic:

    File:               Class:              Description:
    ====================================================
    Serialize.h         ParserInterface     An interface to parsing used by DeSerialize
                        PrinterInterface    An interface to printing used by Serialize
                        Serializer<T>       Generic serialize class that uses Traits<T> and <Name>PrinterInterface
                        DeSerializer<T>     Generic de-serializer class that uses Traits<T> and <Name>ParserInterface

    Exporter.h          Exporter (class)                        Used to interact with stream.
                        Export   (wrapper to create Exporter)   Specializations should just wrap these
    Importer.h          Importer (class)
                        Import   (wraooer to create Importer)

    Traits.h            Traits<T>
                        Macros: ThorsAnvil_MakeTrait    Simplifies the creation of Traits for user types.

    SerUtil.h           Traits<std::pair<A,B>>          Provides traits for all the standard containers.
                        Traits<std::array<T, N>>
                        Traits<std::list<T>>
                        Traits<std::vector<T>>
                        Traits<std::deque<T>>
                        Traits<std::set<T>>
                        Traits<std::multiset<T>>
                        Traits<std::map<K, V>>
                        Traits<std::multimap<K, V>>


    UnicodeIterator.h   Iterator for replacing escape characters with their actual encodings for use inside the application.
                        Should be used by the <XXX>Parser class on strings that can contain escape characters.
    

Usage:

    #include "Serialize.h"
    #include "JsonPrinter.h"
    #include "JsonParser.h"

    DeSerializer<DstType>       parser(jsonParser);

    parser.parse(object1);
    parser.parse(object2);

    Serializer<SrcType>         printer(yamlPrinter);

    printer.print(object1);
    printer.print(object2);

For simplicity we have stream adapters.

    #include "Serialize.h"
    #include "Json.h"
    #include "Yaml.h"

    namespace TS = ThorsAnvil::Serialize;

    std::cout << TS::jsonExport(object1);
    std::cin  >> TS::jsonImport(object1);

    std::cout << TS::yamlExport(object1);
    std::cin  >> TS::yamlImport(object1);

All standard types have a serialization defined for them. To add one for your class.

    class MyClass
    {
        int             value1;
        double          data;
        std::string     descriptions;

        friend class ThorsAnvil::Serialize::Traits<MyClass>;
        public:
            // STUFF
    };

    ThorsAnvil_MakeTrait(MyClass, value1, data, descriptions)




