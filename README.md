[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)


Yet another JSON serialization library for C++

###Objective:

    The objective is to make serialization/de-serialization of C++ object to/from
    JSON trivial.

    This means:
        1) does not build a JSON object. Reads data directly into C++ object.
        2) In normal usage there should be NO need to write any code.
        3) User should not need to understand JSON or validate its input.
        4) Should work seamlessly with streams.
        5) Standard containers should automatically work

    I am not concerned about speed.
    Though my trivial test work just fine in terms of speed.
    
    The design was done with the primary goal of communicating with WEB-Servers
    that speak JSON. The main envisioned usage was for mobile devices were many
    small JSON objects are transfered in both directions.

###Example Usage with ThorsStream

https://gist.github.com/Loki-Astari/8201956

###Building Notes:

    I have moved away from trying to install tools/libs that are needed.
    Rather I am using auto-tools to validate the state of the system for tools/libs required.
    If you are missing any dependencies then this should generate errors during configuration
    that you must resolve.

    Build instructions:
    ###################
    ./configure
    make test
    make install

###Example: C++11 (see code in test.cpp for full code)

    /* A class that you want to serialize. */
    class MyClass
    {   
        int         data1;
        float       data2;
        std::string data3;

        // This is only required if the members are private.
        friend struct ThorsAnvil::Serialize::Json::JsonSerializeTraits<MyClass>;
    };  


    /*  
     * Though there is no code involved, you do need to set up
     * this structure to tell the library what fields need to be serialized.
     * To do this use the macro:  JsonSerializeTraits_MAKE()
     * Specifying parents to serialize(or void), your class, a list of members to serialize.
     */  
    JsonSerializeTraits_MAKE(void, MyClass, data1, data2, data3)
    
This allows us to import and export object of the above class really easily.

    MyCLass   data;
    data.data1  = 56;
    data.data2  = 23.456;
    data.data3  = "Hi there";
    
    std::cout << ThorsAnvil::Serializer::jsonExport(data) << "\n";

This generates:

    {"data1": 56 ,"data2": 23.456 ,"data3": "Hi there" }

It will also handle all standard containers automaticaly:

    std::vector<MyClass>   vec(4, data);
    std::cout << ThorsAnvil::Serializer::jsonExport(vec) << "\n";
    
    // Results in:
    [{"data1": 56 ,"data2": 23.456 ,"data3": "Hi there" }, {"data1": 56 ,"data2": 23.456 ,"data3": "Hi there" }, {"data1": 56 ,"data2": 23.456 ,"data3": "Hi there" }, {"data1": 56 ,"data2": 23.456 ,"data3": "Hi there" } ]
    
    





