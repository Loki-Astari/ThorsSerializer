
A framework for implementing parsers onto.

Usage:

    DeSerializer<DstType>       parser(jsonParser);

    parser.parse(object1);
    parser.parse(object2);

    Serializer<SrcType>         printer(yamlPrinter);

    printer.print(object1);
    printer.print(object2);

For simplicity we have stream adapters.

    std::cout << ExportJson(object1);




