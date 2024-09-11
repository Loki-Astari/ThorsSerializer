#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>


using namespace std::string_literals;
using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue38
{

struct Connection
{
    bool    active;
};

struct IPConnection: public Connection
{
    int     port;
};

struct IPv4Connection: public IPConnection
{
    std::string     v4Name;
};

struct IPv6Connection: public IPConnection
{
    std::string     v6Name;
    double          cost;
};

struct TcpConnection
{
    int             blocks;
};

struct UdpConnection
{
    int             listeners;
};

struct Tcp4Connection : public IPv4Connection, public TcpConnection
{
    std::vector<int>    data;
};
struct Tcp6Connection : public IPv6Connection, public TcpConnection
{
    std::vector<int>    sync;
};
struct Udp4Connection : public IPv4Connection, public UdpConnection
{
    std::vector<double>    fly;
};
struct Udp6Connection : public IPv6Connection, public UdpConnection
{
    std::vector<std::string>    fancy;
};

using Tcp4ConnectionParent = ThorsAnvil::Serialize::Parents<IPv4Connection, TcpConnection>;
using Tcp6ConnectionParent = ThorsAnvil::Serialize::Parents<IPv6Connection, TcpConnection>;
using Udp4ConnectionParent = ThorsAnvil::Serialize::Parents<IPv4Connection, UdpConnection>;
using Udp6ConnectionParent = ThorsAnvil::Serialize::Parents<IPv6Connection, UdpConnection>;

}


ThorsAnvil_MakeTrait(Issue38::Connection, active);
ThorsAnvil_ExpandTrait(Issue38::Connection, Issue38::IPConnection, port);
ThorsAnvil_ExpandTrait(Issue38::IPConnection, Issue38::IPv4Connection, v4Name);
ThorsAnvil_ExpandTrait(Issue38::IPConnection, Issue38::IPv6Connection, v6Name, cost);
ThorsAnvil_MakeTrait(Issue38::TcpConnection, blocks);
ThorsAnvil_MakeTrait(Issue38::UdpConnection, listeners);


ThorsAnvil_ExpandTrait(Issue38::Tcp4ConnectionParent, Issue38::Tcp4Connection, data);
ThorsAnvil_ExpandTrait(Issue38::Tcp6ConnectionParent, Issue38::Tcp6Connection, sync);
ThorsAnvil_ExpandTrait(Issue38::Udp4ConnectionParent, Issue38::Udp4Connection, fly);
ThorsAnvil_ExpandTrait(Issue38::Udp6ConnectionParent, Issue38::Udp6Connection, fancy);

#include <iostream>

TEST(Issue38TestString, JsonConnection)
{
    std::string stream = R"(
    {
        "active": true
    })";

    Issue38::Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonIPConnection)
{
    std::string stream = R"(
    {
        "port":   22,
        "active": true
    })";

    Issue38::IPConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonIPv4Connection)
{
    std::string stream = R"(
    {
        "v4Name": "LongPort",
        "port": 56,
        "active": true
    })";

    Issue38::IPv4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonIPv6Connection)
{
    std::string stream = R"(
    {
        "v6Name": "ShortPort",
        "cost": 12.500000,
        "port": 67,
        "active": true
    })";

    Issue38::IPv6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonTcpConnection)
{
    std::string stream = R"(
    {
        "blocks": 8
    })";

    Issue38::TcpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonUdpConnection)
{
    std::string stream = R"(
    {
        "listeners": 12
    })";

    Issue38::UdpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonTcp4Connection)
{
    std::string stream = R"(
    {
        "data": [15, 67],
        "v4Name": "LongPort",
        "port": 56,
        "active": true,
        "blocks": 8
    })";

    Issue38::Tcp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonTcp6Connection)
{
    std::string stream = R"(
    {
        "sync": [15, 67],
        "v6Name": "LongPort",
        "cost": 12.000000,
        "port": 56,
        "active": true,
        "blocks": 88
    })";

    Issue38::Tcp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonUdp4Connection)
{
    std::string stream = R"(
    {
        "fly": [13.000000, 14.000000, 12.500000],
        "v4Name": "ShortPort",
        "port": 67,
        "active": true,
        "listeners": 999
    })";

    Issue38::Udp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, JsonUdp6Connection)
{
    std::string stream = R"(
    {
        "fancy": ["long", "way", "down"],
        "v6Name": "LongPort",
        "cost": 88.000000,
        "port": 56,
        "active": true,
        "listeners": 101
    })";

    Issue38::Udp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    stream.erase(std::remove_if(std::begin(stream),  std::end(stream),  [](char x){return ::isspace(x);}), std::end(stream));
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonConnection)
{
    //NOTE INPUT  = R"( { "active": true })";
    std::string stream = "\x0E\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x00"s;

    Issue38::Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonIPConnection)
{
    //NOTE INPUT  = R"({ "active": true, "port":   22 })";
    std::string stream = "\x18\x00\x00\x00"
                        "\x10" "port\x00"   "\x16\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x00"s;

    Issue38::IPConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonIPv4Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 56, "v4Name": "LongPort" })";
    std::string stream = "\x2D\x00\x00\x00"
                        "\x02" "v4Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x00"s;

    Issue38::IPv4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonIPv6Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 67, "v6Name": "ShortPort", "cost": 12.5 })";
    std::string stream = "\x3C\x00\x00\x00"
                        "\x02" "v6Name\x00" "\x0A\x00\x00\x00" "ShortPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x29\x40"
                        "\x10" "port\x00"   "\x43\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x00"s;

    Issue38::IPv6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonTcpConnection)
{
    //NOTE INPUT  = R"( { "blocks": 8 })";
    std::string stream = "\x11\x00\x00\x00"
                        "\x10" "blocks\x00" "\x08\x00\x00\x00"
                        "\x00"s;

    Issue38::TcpConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonUdpConnection)
{
    //NOTE INPUT  = R"( { "listeners": 12 })";
    std::string stream = "\x14\x00\x00\x00"
                        "\x10" "listeners\x00"  "\x0C\x00\x00\x00"
                        "\x00"s;

    Issue38::UdpConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonTcp4Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 56, "v4Name": "LongPort", "blocks": 8, "data": [15, 67] })";
    std::string stream = "\x52\x00\x00\x00"
                        "\x04" "data\x00"
                                "\x13\x00\x00\x00"
                                "\x10" "0\x00"  "\x0E\x00\x00\x00"
                                "\x10" "1\x00"  "\x43\x00\x00\x00"
                                "\x00"
                        "\x02" "v4Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "blocks\x00" "\x08\x00\x00\x00"
                        "\x00"s;

    Issue38::Tcp4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonTcp6Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 56, "v6Name": "LongPort", "cost": 12, "blocks": 88, "sync": [15, 67] })";
    std::string stream = "\x60\x00\x00\x00"
                        "\x04" "sync\x00"
                                "\x13\x00\x00\x00"
                                "\x10" "0\x00"  "\x0E\x00\x00\x00"
                                "\x10" "1\x00"  "\x43\x00\x00\x00"
                                "\x00"
                        "\x02" "v6Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x28\x40"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "blocks\x00" "\x58\x00\x00\x00"
                        "\x00"s;

    Issue38::Tcp6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonUdp4Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 67, "v4Name": "ShortPort", "listeners": 999, "fly": [13, 14, 12.5] })";
    std::string stream = "\x68\x00\x00\x00"
                        "\x04" "fly\x00"
                                "\x26\x00\x00\x00"
                                "\x01" "0\x00"  "\x00\x00\x00\x00\x00\x00\x2A\x40"
                                "\x01" "1\x00"  "\x00\x00\x00\x00\x00\x00\x2C\x40"
                                "\x01" "2\x00"  "\x00\x00\x00\x00\x00\x00\x29\x40"
                                "\x00"
                        "\x02" "v4Name\x00" "\x0A\x00\x00\x00" "ShortPort\x00"
                        "\x10" "port\x00"   "\x43\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "listeners\x00" "\x08\x00\x00\x00"
                        "\x00"s;

    Issue38::Udp4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
TEST(Issue38TestString, BsonUdp6Connection)
{
    //NOTE INPUT  = R"( { "active": true, "port": 56, "v6Name": "LongPort", "cost": 88, "listeners": 101, "fancy": ["long", "way", "down"] })";
    std::string stream = "\x79\x00\x00\x00"
                        "\x04" "fancy\x00"
                                "\x28\x00\x00\x00"
                                "\x02" "0\x00"  "\x05\x00\x00\x00" "long\x00"
                                "\x02" "1\x00"  "\x04\x00\x00\x00" "way\x00"
                                "\x02" "2\x00"  "\x05\x00\x00\x00" "down\x00"
                                "\x00"
                        "\x02" "v6Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x56\x40"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "listeners\x00" "\x65\x00\x00\x00"
                        "\x00"s;

    Issue38::Udp6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::string     output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output;
    EXPECT_EQ(stream, result);
}
