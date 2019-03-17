
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>



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

TEST(Issue38Test, Connection)
{
    std::string input = R"(
    {
        "active": true
    })";
    std::stringstream stream(input);

    Issue38::Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, IPConnection)
{
    std::string input = R"(
    {
        "active": true,
        "port":   22
    })";
    std::stringstream stream(input);

    Issue38::IPConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, IPv4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v4Name": "LongPort"
    })";
    std::stringstream stream(input);

    Issue38::IPv4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, IPv6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 67,
        "v6Name": "ShortPort",
        "cost": 12.5
    })";
    std::stringstream stream(input);

    Issue38::IPv6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, TcpConnection)
{
    std::string input = R"(
    {
        "blocks": 8
    })";
    std::stringstream stream(input);

    Issue38::TcpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, UdpConnection)
{
    std::string input = R"(
    {
        "listeners": 12
    })";
    std::stringstream stream(input);

    Issue38::UdpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, Tcp4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v4Name": "LongPort",
        "blocks": 8,
        "data": [15, 67]
    })";
    std::stringstream stream(input);

    Issue38::Tcp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, Tcp6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v6Name": "LongPort",
        "cost": 12,
        "blocks": 88,
        "sync": [15, 67]
    })";
    std::stringstream stream(input);

    Issue38::Tcp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, Udp4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 67,
        "v4Name": "ShortPort",
        "listeners": 999,
        "fly": [13, 14, 12.5]
    })";
    std::stringstream stream(input);

    Issue38::Udp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, Udp6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v6Name": "LongPort",
        "cost": 88,
        "listeners": 101,
        "fancy": ["long", "way", "down"]
    })";
    std::stringstream stream(input);

    Issue38::Udp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImport(test);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExport(test);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
