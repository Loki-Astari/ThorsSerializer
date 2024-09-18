# ThorsSerializer

## Support for

* [Json](https://www.json.org/json-en.html)
* [Yaml](https://yaml.org/)
* [Bson](http://bsonspec.org/)

This code is the basis for [ThorsMongo](https://github.com/Loki-Astari/ThorsMongo) a C++ API for streaming objects to Mongo with zero client overhead.  


[![Code Review](http://www.zomis.net/codereview/shield/?qid=81920)](http://codereview.stackexchange.com/q/81920/507)
[![Code Review](http://www.zomis.net/codereview/shield/?qid=79281)](http://codereview.stackexchange.com/q/79281/507)
[![Code Review](http://www.zomis.net/codereview/shield/?qid=7567)](http://codereview.stackexchange.com/q/7567/507)
[![Code Review](http://www.zomis.net/codereview/shield/?qid=7536)](http://codereview.stackexchange.com/q/7536/507)

[![Brew package](https://img.shields.io/badge/Brew-package-blueviolet)](https://formulae.brew.sh/formula/thors-serializer)


## Benchmark Results
Conformance [mac](https://LokiAstari.com/Json/Conformance.osx.html) [linux](https://LokiAstari.com/Json/Conformance.linux.html)  
Performance [mac](https://LokiAstari.com/Json/Performance.osx.html) [linux](https://LokiAstari.com/Json/Performance.linux.html)  
For details see: [JsonBenchmark](https://github.com/Loki-Astari/JsonBenchmark)  

![ThorStream](img/stream.jpg)

Yet another JSON/YAML/BSON serialization library for C++.

Unlike other libraries this one does not require you to build DOM of you object before serialization. Using a declarative C++ style you define what C++ classes (and members) you want to serialize "ThorSerializer" will generate the appropriate code automagically.

* [Objective](doc/objective.md)
* [Trivial Example](doc/example0.md)
* [Simple Example](doc/example1.md)
* [Enum Example](doc/exampleE.md)
* [Bigger Example](doc/example2.md)
* [PolyMorphic Example](doc/example3.md)
* [Installing](doc/building.md)
* [Documentation Usage](doc/usage.md)
* [Documentation Internal](https://lokiastari.com/ThorsSerializer/)

## HomeBrew

Can be installed via brew on Mac and Linux

    brew install thors-serializer

* Mac: https://formulae.brew.sh/formula/thors-serializer
* Linux: https://formulae.brew.sh/formula-linux/thors-serializer

## Header Only

To install header only version

    git clone --single-branch --branch header-only https://github.com/Loki-Astari/ThorsMongo.git

Some dependencies:

    For All:    Magic Enum: https://github.com/Neargye/magic_enum
    For Json:   None        :-)
    For Yaml:   libYaml     https://github.com/yaml/libyaml

## Building With Visual Studio

To build on windows you will need to add the flag: [`/Zc:preprocessor`](https://learn.microsoft.com/en-us/cpp/build/reference/zc-preprocessor?view=msvc-170). These libraries make heavy use of VAR_ARG macros to generate code for you so require conforming pre-processor. See [Macro Expansion of __VA_ARGS__ Bug in Visual Studio?](https://stackoverflow.com/questions/78605945/macro-expansion-of-va-args-bug-in-visual-studio) for details.


## Contributors

Added the all-contributers bot to generate the table.


-----

[One Page](doc/full.md)

