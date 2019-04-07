---
layout: plain
generate: false
---
````C++
    using OutputType = ThorsAnvil::Serialize::PrinterInterface::OutputType;
    while(std::cout << jsonExport(12, OutputType::Default, true) << "\n")
    {
        // Successfully wrote an object to the output
    }
    ...
    using ParseType = ThorsAnvil::Serialize::ParserInterface::ParseType;
    while(std::cin >> jsonImport(dst, ParseType::Weak, true))
    {
        // Successfully read an object from the input
    }
````
By default the ThorsSerializer will throw an exception when it encounters a parsing error (it also sets the stream state to fail). If you would prefer for the stream to swallow the exception (but still set the stream state to fail) then you can modify this behavior in `jsonImport()` and `jsonExport()`.
