[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](https://raw.github.com/Loki-Astari/ThorsSerializer/ReWriteDocumentation/img/stream.jpg)


#Building Instructions:

    git clone git@github.com:Loki-Astari/ThorsSerializer.git
    cd ThorsSerializer
    ./configure --disable-binary
    make
    sudo make install

## Description

By default installation will be in `/usr/local/\[include/lib\]`. You can override this with the normal auto-tools defaults. Use `./configure --help` to get details.

###What is installed:

* /usr/local/include/ThorSerialize/*
* /usr/local/include/ThorBinaryRep/*
* /use/local/lib/libThorSerialize14.so
* /use/local/lib/libThorSerialize14D.so


Note:
libThorSerialize14.so is build using -O3 and thus is fully optimized and debug symbols have been stripped.  
libThorSerialize14D.so is build using -g and is useful for debugging purposes.


###What is Downloaded

The configuration processes will download the generic makefiles (using git) from [ThorMaker](https://github.com/Loki-Astari/ThorMaker) which in turn will download and build google's gtest library that is used in running the unit tests.

##Requirements

This library uses features from C++14 so you will need a compiler that supports this. The generic makefile also does code coverage tests so your compiler will also need to support a code coverage tool that has an interface similar to gcov.

It has been tested on [travis-ci.org](https://travis-ci.org/Loki-Astari/ThorsSerializer) using clang 3.5 and g++ 4.9 (on mac and ubuntu). Though clang 3.4 also supports C++14 its code coverage tool is very basic and the generic makefiles will fail when attempting to perform code coverage tests.


