#ifndef THORS_ANVIL_SERIALIZE_BSON_H
#define THORS_ANVIL_SERIALIZE_BSON_H
/*
 * Defines the Bson Serialization interface
 *      ThorsAnvil::Serialize::Bson
 *      ThorsAnvil::Serialize::bsonExporter
 *      ThorsAnvil::Serialize::bsonImporter
 *
 * Usage:
 *      std::cout << bsonExporter(object); // converts object to Bson on an output stream
 *      std::cin  >> bsonImporter(object); // converts Bson to a C++ object from an input stream
 */

#include "BsonParser.h"
#include "BsonPrinter.h"
#include "Exporter.h"
#include "Importer.h"
#include "SerUtil.h"
#include "ThorsIOUtil/Utility.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T, TraitType trait = Traits<T>::type>
struct BsonBaseTypeGetter
{
    static constexpr BsonContainer value = BsonContainer::Value;
    static void validate(T const&){}
};
template<typename T>
struct BsonBaseTypeGetter<T, TraitType::Map>
{
    static constexpr BsonContainer value = BsonContainer::Map;
    static void validate(T const&){}
};
template<typename T>
struct BsonBaseTypeGetter<T, TraitType::Parent>
{
    static constexpr BsonContainer value = BsonContainer::Map;
    static void validate(T const&){}
};
template<typename T>
struct BsonBaseTypeGetter<T, TraitType::Array>
{
    static constexpr BsonContainer value = BsonContainer::Array;
    static void validate(T const&){}
};
template<typename T>
struct BsonBaseTypeGetter<T, TraitType::Pointer>
{
    using ElementType = typename std::pointer_traits<T>::element_type;
    static constexpr BsonContainer value = BsonBaseTypeGetter<ElementType>::value;
    static void validate(T const& pointer)
    {
        if (!pointer)
        {
            throw std::runtime_error(
                        ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonBaseTypeGetter<T, Pointer>", "validate",
                                                               "Bson does not support serialization of null at the top level")
                                                              );
        }
    }
};

/*
 * BSON Elements
 *  '\x01'      POD: float/double
 *  '\x02'      std::string
 *  '\x03'      All the following work:
 *                  Structure
 *                  std::map<std::string, V>/std::unordered_map<std::string, V>
 *                  std::multimap<std::string, V>/std::unordered_multimap<std::string, V>
 *  '\x04'      All the following work:
 *                  std::vector<V>
 *                  std::array<V>
 *                  initializer_list<V>
 *                  std::list<V>
 *                  std::dequeu<V>
 *                  std::set<V>/std::multiset<V>
 *                  std::unordered_set<V>/std::unordered_multiset<V>
 *                  std::map<K, V>/std::unordered_map<K, V>             => Key Value pairs
 *                  std::multimap<K, V>/std::unordered_multimap<K, V>   => Key Value pairs
 *  '\x05'      Use DataInterface and BinarySerializer for Serialization
 *  '\x07'      Use ObjectID        or Use NormalSerializationInterface and ObjectIDSerializer for Serialization
 *  '\x08'      POD bool
 *  '\x09'      Use UTCDateTome     or Use NormalSerializationInterface and DataTimeSerializer
 *  '\x0A'      nullptr
 *  '\x0B'      use RegExInterface and RegExSerializer for Serialization
 *  '\x0D'      use DataInterface and JavascriptSerializer for Serialization
 *  '\x10'      Integer types that are shorter or equal to 32 bits: short/int/long
 *  '\x11'      use NormalSerializationInterface and TimeStampSerializer for Serialization
 *  '\x12'      Integer types that are longer or equal to 64 bits:  long long
 *  '\x13'      POD long double (if long double is IEEE compliant)
 *
 * Not Implemented yet.
 *  '\xFF' e_name Min key
 *  '\x7F' e_name Max key
 *
 * Deprecated in standard and not used.
 *  '\x06'
 *  '\x0C'
 *  '\x0E'
 *  '\x0F'
 *
 *
 * For the terms:
 *  Use <X>Interface and <Y> for Serialization
 *  This means make the type you want to serialize implement the interface X (described below)
 *  Then add the following declaration:
 *      class MyType: public <X>Interface
 *      {
 *          Note: You don't actually want to inherit from these interfaces.
 *                This is a Duck type interface. You wan to implement the functions
 *                specified by the interface only.
 *      };
 *
 *      ThorsAnvil_MakeTraitCustomSerialize(MyType, <Y>);
 *
 * The special one here is the 'NormalSerialization* interface.
 * Rather than implement a specific interface you simply implement symetric serialization functions.
 * i.e. overload the `operator<<` and `operator>>`
 */

#if 0
class NormalSerializationInterface
{
    friend std::ostream& operator<<(std::ostream& stream, ObjectID const& data);
    friend std::istream& operator<<(std::istream& stream, ObjectID& data);
};
class DataInterface
{
    public:
        std::size_t getSize()                   = 0;
        void        resize(std::size_t size)    = 0;
        char*       getBuffer()                 = 0;
};
class RegExInterface
{
    public:
        std::string& pattern()                  = 0;
        std::string& options()                  = 0;
};
#endif

template<typename T, char type, std::size_t size>
class FixedSizeStreamableObjectSerializer: public DefaultCustomSerializer<T>
{
    // Assumes T implements the DuckInterface "NormalSerializationInterface" (see above)
    // Note: You should pay special attention to the size (number of bytes these object should write).
    public:
        virtual char getBsonByteMark() override                                                         {return type;}
        virtual std::size_t getPrintSizeBson(BsonPrinter& /*printer*/, T const& /*object*/) override    {return size;}
        virtual void writeBson(BsonPrinter& printer, T const& object) override                          {printer.stream() << std::uppercase << object << std::nouppercase;}
        virtual void readBson(BsonParser& parser, char /*byteMarker*/, T& object) override              {parser.stream() >> std::uppercase >> object >> std::nouppercase;}
};

// Specializations of FixedSizeStreamableObjectSerializer
template<typename T> class ObjectIDSerializer:  public FixedSizeStreamableObjectSerializer<T, '\x07', 12> {};
template<typename T> class DataTimeSerializer:  public FixedSizeStreamableObjectSerializer<T, '\x09', 8>  {};
template<typename T> class TimeStampSerializer: public FixedSizeStreamableObjectSerializer<T, '\x11', 8>{};

template<typename T, char encodeType = '\x08'>
class BinarySerializer: public DefaultCustomSerializer<T>
{
    // Assumes T implements the DuckInterface "DataInterface" (see above)
    public:
        virtual char getBsonByteMark() override                                                         {return '\x05';}
        virtual std::size_t getPrintSizeBson(BsonPrinter& /*printer*/, T const& object) override        {return object.getSize();}
        virtual void writeBson(BsonPrinter& printer, T const& object) override
        {
            std::int32_t    size    = object.getSize();
            char            type    = encodeType;
            printer.writeSize<std::int32_t>(size);
            printer.stream().write(&type, 1);
            printer.stream().write(object.getBuffer(), object.getSize());
        }
        virtual void readBson(BsonParser& parser, char /*byteMarker*/, T& object) override
        {
            std::int32_t    size    = parser.readSize<4, std::int32_t>();
            char            type;
            object.resize(size);
            parser.stream().read(&type, 1);
            parser.stream().read(object.getBuffer(), size);
        }
};

template<typename T>
class JavascriptSerializer: public DefaultCustomSerializer<T>
{
    // Assumes T implements the DuckInterface "DataInterface" (see above)
    public:
        virtual char getBsonByteMark() override                                                         {return '\x0D';}
        virtual std::size_t getPrintSizeBson(BsonPrinter& /*printer*/, T const& object) override        {return 4 + object.size() + 1;}
        virtual void writeBson(BsonPrinter& printer, T const& object) override
        {
            std::int32_t    size = object.size();
            printer.writeSize<std::int32_t>(size + 1);
            printer.stream().write(object.getBuffer(), size);
            printer.stream().write("", 1);
        }
        virtual void readBson(BsonParser& parser, char /*byteMarker*/, T& object) override
        {
            std::int32_t    size = parser.readSize<4, std::int32_t>();
            object.resize(size);
            parser.stream().read(object.getBuffer(), size);
            object.resize(size - 1);
        }
};

template<typename T>
class RegExSerializer: public DefaultCustomSerializer<T>
{
    // Assumes T implements the DuckInterface "RegExInterface" (see above)
        virtual char getBsonByteMark() override                                                         {return '\x0B';}
        virtual std::size_t getPrintSizeBson(BsonPrinter& /*printer*/, T const& object) override        {return object.pattern().size() + 1 + object.options().size() + 1;}
        virtual void writeBson(BsonPrinter& printer, T const& object) override
        {
            printer.stream().write(object.pattern().data(), object.pattern().size());
            printer.stream().write("", 1);
            printer.stream().write(object.options().data(), object.options().size());
            printer.stream().write("", 1);
        }
        virtual void readBson(BsonParser& parser, char /*byteMarker*/, T& object) override
        {
            std::getline(parser.stream(), object.pattern(), '\0');
            std::getline(parser.stream(), object.options(), '\0');
        }
};

#include <chrono>
#include <iomanip>
#include <iostream>
#include <arpa/inet.h>
class StreamFormatterNoChange
{
    mutable std::ios*               stream;
    mutable std::ios_base::fmtflags flags;
    mutable std::streamsize         precision;
    public:
        StreamFormatterNoChange()
            : stream(nullptr)
        {}
        ~StreamFormatterNoChange()
        {
            if (stream)
            {
                stream->flags(flags);
                stream->precision(precision);
            }
        }
        void saveStream(std::ios& s) const
        {
            stream    = &s;
            flags     = s.flags();
            precision = s.precision();
        }
        friend std::ostream& operator<<(std::ostream& stream, StreamFormatterNoChange const& formatter)
        {
            formatter.saveStream(stream);
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, StreamFormatterNoChange const& formatter)
        {
            formatter.saveStream(stream);
            return stream;
        }
};

#if 0
std::uint64_t htonll(std::uint64_t value)
{
#if __BIG_ENDIAN__
    return value;
#else
    return (static_cast<std::uint64_t>(htonl(value & 0xFFFFFFFF)) << 32)) | (static_cast<std::uint64_t>(htonl((value >> 32) & 0xFFFFFFFF));
#endif
}
std::int64_t ntohll(std::int64_t value)
{
#if __BIG_ENDIAN__
    return value;
#else
    return (static_cast<std::uint64_t>(ntohl(value & 0xFFFFFFFF)) << 32)) | (static_cast<std::uint64_t>(ntohl((value >> 32) & 0xFFFFFFFF));
#endif
}
#endif

class ObjectID
{
    // 4 byte timestamp
    // 5 byte random
    // 3 byte incrementing counter.
    static int classCounter; // = rand();

    std::int32_t    timestamp;
    std::int64_t    random;
    std::int32_t    counter;
    public:
        static int getNextCounter()
        {
            return (classCounter++) % 0xFFF;
        }
        ObjectID(std::int32_t timestamp = duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(), std::int64_t random = std::rand(), std::int32_t counter = ObjectID::getNextCounter())
            : timestamp(timestamp)
            , random(random)
            , counter(counter)
        {}
        bool operator==(ObjectID const& rhs) const
        {
            return std::tie(timestamp, random, counter) == std::tie(rhs.timestamp, rhs.random, rhs.counter);
        }
        friend std::ostream& operator<<(std::ostream& stream, ObjectID const& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                std::int64_t netRandom    = htonll(data.random);
                std::int32_t netTimestamp = htonl(data.timestamp);
                std::int32_t netCounter   = htonl(data.counter);
                stream.write(reinterpret_cast<char const*>(&netTimestamp), 4);
                stream.write(reinterpret_cast<char const*>(&netRandom) + 3, 5);
                stream.write(reinterpret_cast<char const*>(&netCounter) + 1, 3);
            }
            else
            {
                stream << StreamFormatterNoChange{}
                       << std::hex << std::setfill('0')
                       << std::setw( 8) << data.timestamp << " "
                       << std::setw(10) << data.random    << " "
                       << std::setw( 6) << data.counter;
            }
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, ObjectID& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                std::int64_t netRandom    = 0;
                std::int32_t netTimestamp = 0;
                std::int32_t netCounter   = 0;
                stream.read(reinterpret_cast<char*>(&netTimestamp), 4);
                stream.read(reinterpret_cast<char*>(&netRandom) + 3, 5);
                stream.read(reinterpret_cast<char*>(&netCounter) + 1, 3);
                data.random    = ntohll(netRandom);
                data.timestamp = ntohl(netTimestamp);
                data.counter   = ntohl(netCounter);
            }
            else
            {
                stream >> StreamFormatterNoChange{} >> std::hex >> data.timestamp >> data.random >> data.counter;
            }
            return stream;
        }
};
class UTCDateTome
{
    // Time in ms since the epoch
    std::int64_t    datetime;
    public:
        UTCDateTome(std::int64_t datetime = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
            : datetime(datetime)
        {}
        friend std::ostream& operator<<(std::ostream& stream, UTCDateTome const& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                stream.write(reinterpret_cast<char const*>(&data.datetime), 8);
            }
            else
            {
                stream << StreamFormatterNoChange{} << std::hex << std::setw(16) << std::setfill('0') << data.datetime;
            }
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, UTCDateTome& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                stream.read(reinterpret_cast<char*>(&data.datetime), 8);
            }
            else
            {
                stream >> StreamFormatterNoChange{} >> std::hex >> data.datetime;
            }
            return stream;
        }
};

class BsonTimeStamp
{
    // First 4 bytes are an increment
    // Second 4 are a timestamp (seconds since the epoch)
    std::int32_t    increment;
    std::int32_t    timestamp;
    public:
        BsonTimeStamp(std::time_t timestamp = duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(), int inc = 0)
            : increment(inc)
            , timestamp(timestamp)
        {}
        UTCDateTome asDateTime()
        {
            return UTCDateTome(timestamp * 1000);
        }
        friend std::ostream& operator<<(std::ostream& stream, BsonTimeStamp const& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                stream.write(reinterpret_cast<char const*>(&data.increment), 4);
                stream.write(reinterpret_cast<char const*>(&data.timestamp), 4);
            }
            else
            {
                stream << StreamFormatterNoChange{}
                       << std::hex << std::setw(8) << std::setfill('0')
                       << data.timestamp << " "
                       << data.increment;
            }
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, BsonTimeStamp& data)
        {
            if (stream.flags() & std::ios_base::uppercase)
            {
                stream.read(reinterpret_cast<char*>(&data.increment), 4);
                stream.read(reinterpret_cast<char*>(&data.timestamp), 4);
            }
            else
            {
                stream >> StreamFormatterNoChange{} >> std::hex >> data.timestamp >> data.increment;
            }
            return stream;
        }
};
    }
}

ThorsAnvil_MakeTraitCustomSerialize(ThorsAnvil::Serialize::ObjectID,       ObjectIDSerializer<ObjectID>);
ThorsAnvil_MakeTraitCustomSerialize(ThorsAnvil::Serialize::UTCDateTome,    DataTimeSerializer<UTCDateTome>);
ThorsAnvil_MakeTraitCustomSerialize(ThorsAnvil::Serialize::BsonTimeStamp,  TimeStampSerializer<BsonTimeStamp>);

namespace ThorsAnvil
{
    namespace Serialize
    {

struct Bson
{
    using Parser  = BsonParser;
    using Printer = BsonPrinter;
};

// @function-api
// @param value                     The object to be serialized.
// @param config.characteristics    'Default': uses Config/Stream depending on global config. 'Config':  Is verbose and logical. 'Stream':  Remove all white space.
// @param config.polymorphicMarker  Jason object name for holding the polymorphic class name of the type. Default: __type
// @param config.catchExceptions    'false:    exceptions propogate.   'true':   parsing exceptions are stopped.
// @return                          Object that can be passed to operator<< for serialization.
template<typename T>
Exporter<Bson, T> bsonExporter(T const& value, PrinterInterface::PrinterConfig config = PrinterInterface::PrinterConfig{})
{
    config.parserInfo = static_cast<long>(BsonBaseTypeGetter<T>::value);
    BsonBaseTypeGetter<T>::validate(value);

    return Exporter<Bson, T>(value, config);
}

// @function-api
// @param value                     The object to be de-serialized.
// @param config.parseStrictness    'Weak':    ignore missing extra fields. 'Strict': Any missing or extra fields throws exception.
// @param config.polymorphicMarker  Jason object name for holding the polymorphic class name of the type. Default: __type
// @param config.catchExceptions    'false:    exceptions propogate.        'true':   parsing exceptions are stopped.
// @return                          Object that can be passed to operator>> for de-serialization.
template<typename T>
Importer<Bson, T> bsonImporter(T& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{})
{
    config.parserInfo = static_cast<long>(BsonBaseTypeGetter<T>::value);

    return Importer<Bson, T>(value, config);
}

    }
}

#endif
