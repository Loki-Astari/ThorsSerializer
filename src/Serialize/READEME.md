
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

    ThorsAnvil_MakeTrait(MyClass, TraitsType::Map, value1, data, descriptions)




