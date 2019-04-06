---
layout: plain
generate: false
---
````C++
    std::cin << jsonImport(dst) << "\n";
...
    using ParseType = ThorsAnvil::Serialize::ParserInterface::ParseType;
    std::cin >> jsonImport(dst, ParseType::Strict);
````
By default the parser is forgiving; extra or missing fields are simply ignored. If you want to use **Strict** parsing then you specify this as part of the `jsonImport()`. In this mode all fields are required no additional fields are allowed. If either of these constraints are broken then an exception is thrown.
