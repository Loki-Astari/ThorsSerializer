---
layout: plain
generate: false
---
````C++
    std::cout << jsonExport(mark) << "\n";
...
    {
        "name": "mark",
        "score": 10,
        "damage": 5,
        "team":
        {
            "red": 66,
            "green": 42,
            "blue": 23
        }
    }
...
    using OutputType = ThorsAnvil::Serialize::PrinterInterface::OutputType;
    std::cout << jsonExport(mark, OutputType::Stream) << "\n";
...
{"name":"mark","score":10,"damage":5,"team":{"red":66,"green":42,"blue":23}}
````
By default the generated JSON is verbose and easy for humans to read. This also makes it longer than required. You can compact the output by `OutputType::Stream` in the `jsonFormat()`.
