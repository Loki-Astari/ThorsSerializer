# BinaryRep

Defines classes that can be used to help serialization of built in types in a consistent way.

## Types:

The following types are used to represent unsigned integers of various sizes for serialization.
```C++
    BinForm16
    BinForm32
    BinForm64
    BinForm128
```

Note 1: They are not designed as fully functional integer types (don't use them like that).
Note 2: The reason I don't use std::unint_nn is because there is not standard std::uint_128

## Float Functions

Convert floating point number to/from IEEE transportable format.
Then converts this to a big endian representation for platform neutral storage.
```C++
    inline BinForm32    host2NetIEEE(float)
    inline BinForm64    host2NetIEEE(double)
    inline BinForm128   host2NetIEEE(long double)

    inline float        net2HostIEEE(BinForm32)
    inline double       net2HostIEEE(BinForm64)
    inline long double  net2HostIEEE(BinForm128)
```

Note: This is highly experimental. I have done some research but I far from an expert.

Single/Double/Quad precision IEEE floating point numbers are portable and transportable.
On my mac book:
    float       =>  Single precision IEEE
    double      =>  Double precision IEEE
    long double =>  80 bit extended IEEE float point representation.

So the float/double can be transported with no alterations. The long double can not.
The code converts long-double values to Quad precision IEEE for transport. This code needs more eyes on it validate the correctness (especially with extremely small values).

This code uses template specialization to decide if conversion is required. Since I only need to specialize for `long double` the other specializations have not been written.

##Integer Functions

These functions convert integers to/from network byte order (big endian).
So that they can be serialized in a platform neutral format.
```C++
    inline BinForm16    host2Net(BinForm16  value)
    inline BinForm32    host2Net(BinForm32  value)
    inline BinForm64    host2Net(BinForm64  value)
    inline BinForm128   host2Net(BinForm128 value)

    inline BinForm16    net2Host(BinForm16  value)
    inline BinForm32    net2Host(BinForm32  value)
    inline BinForm64    net2Host(BinForm64  value)
    inline BinForm128   net2Host(BinForm128 value)
```


