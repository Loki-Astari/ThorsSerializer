[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](../img/stream.jpg)

# Install Instructions:
## From [Homebrew](https://brew.sh/)
````bash
brew tap Loki-Astari/ThorsAnvil
brew install ThorsSerializer
````

#### What is installed:
* `/usr/local/include/ThorSerialize/*`
* `/usr/local/include/ThorBinaryRep/*`
* `/usr/local/lib/libThorSerialize17.so`
* `/usr/local/lib/libThorSerialize17D.so`
* `/usr/local/lib/libyaml.so`
* `/usr/local/share/man/man3/*`

## From [GitHub](https://github.com/Loki-Astari/ThorsSerializer)

The basic script for installing everything is:

````bash
    > git clone git@github.com:Loki-Astari/ThorsSerializer.git
    > cd ThorsSerializer
    > ./configure --disable-binary
    > make
    > sudo make install
````

But installing everything requires a cuople of extra libraries and some development tools. You may not need all these tools (try and use brew if you don't).

### Yaml
By default it also installs the yaml serialization library. Underneath this uses libyaml this must be install first. If you don't need yaml support then add `--disable-yaml` to the `configure` command above.

### Development

If you want to submit "pull requests" you are going to need vera++. Vera++ is a style checkecker and is automatically run as part of the build processes. The build will fail if you don't adhere to the style requirements of the porject (you must adhere to the style guide for a pull request to be accepted).

If you are simply building for yourself you may not care about the style guide. In this case you can switch it off by adding `--disable-vera` to the `configure` command above.

If you do want to use `vera++` there are several requirements:

* boost 
* boost-python
* cmake
* tcl/tk

I install all the above with:
````bash
    brew install boost --with-python
    brew install boost-python
    brew install cmake
    brew install tcl-tk
    # Have to create unversioned boost_python libs.
    for a in /usr/local/lib/libboost_python[0-9][0-9]* ; do sudo ln -s ${a} ${a/[0-9][0-9]/}; done
````

### Description
By default installation will be in `/usr/local/include` and `/usr/local/lib`. You can override this with the normal auto-tools defaults. Use `./configure --help` to get details.

#### What is installed:
* `/usr/local/include/ThorSerialize/*`
* `/usr/local/include/ThorBinaryRep/*`
* `/usr/local/lib/libThorSerialize17.so`
* `/usr/local/lib/libThorSerialize17D.so`
* `/usr/local/share/man/man3/*`

Note:
libThorSerialize17.so is build using `-O3` and thus is fully optimized and debug symbols have been stripped.  
libThorSerialize17D.so is build using `-g` and is useful for debugging purposes.


### What is Downloaded
The configuration processes will download the generic makefiles (using git) from [ThorMaker](https://github.com/Loki-Astari/ThorMaker) which in turn will download and build [google's gtest](https://github.com/google/googletest) and [vera++](https://github.com/Loki-Astari/vera-plusplus) library that is used in running the unit tests.

## Requirements
This library uses features from C++14 so you will need a compiler that supports this. The generic makefile also does code coverage tests so your compiler will also need to support a code coverage tool that has an interface similar to `gcov`.



