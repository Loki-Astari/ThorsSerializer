#BinaryRep

Defines classes that can be used to help serialization of built in types in a consistent way.

##Types:

The following types are used to represent unsigned integers of various sizes for serialization.
Note: They are not designed as fully functional integer types (don't use them like that).

    BinForm16
    BinForm32
    BinForm64
    BinForm128


##Float Functions

Convert floating point number to/from IEEE transportable format.
Then converts this to a big endian representation for platform neutral storage.

    inline BinForm32  host2NetIEEE(float)
    inline BinForm64  host2NetIEEE(double)
    inline BinForm128 host2NetIEEE(long double)

##Integer Functions

These functions convert integers to/from network byte order (big endian).
So that they can be serialized in a platform neutral format.

    inline BinForm16  host2Net(BinForm16  value)
    inline BinForm32  host2Net(BinForm32  value)
    inline BinForm64  host2Net(BinForm64  value)
    inline BinForm128 host2Net(BinForm128 value)


