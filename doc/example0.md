[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](../img/stream.jpg)

## Example-0 [See doc/example0.cpp](example0.cpp)
````c++
    #include <iostream>
    #include <vector>
    #include "ThorSerialize/JsonThor.h"

    int main()
    {
        std::vector<int>    data;
        using ThorsAnvil::Serialize::jsonImporter;
        using ThorsAnvil::Serialize::jsonExporter;

        std::cin >> jsonImporter(data);
        std::cout << jsonExporter(data) << "\n";
    }
````

### Build and run
````bash
    > g++ -std=c++17 example0.cpp -lThorSerialize17 -lThorsLogging17
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > echo "[1,2,3,4,5]" | ./a.out
        [ 1, 2, 3, 4, 5]
    > 
````
