
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
struct Udp4Connection : public IPv4Connection, public TcpConnection
{
    std::vector<double>    fly;
};
struct Udp6Connection : public IPv6Connection, public TcpConnection
{
    std::vector<std::string>    fancy;
};


ThorsAnvil_MakeTrait(Connection, active);
ThorsAnvil_ExpandTrait(Connection, IPConnection, port);
ThorsAnvil_ExpandTrait(IPConnection, IPv4Connection, v4Name);
ThorsAnvil_ExpandTrait(IPConnection, IPv6Connection, v6Name, cost);
ThorsAnvil_MakeTrait(TcpConnection, blocks);
ThorsAnvil_MakeTrait(UdpConnection, listeners);


ThorsAnvil_MakeTrait(Tcp4Connection, data);
ThorsAnvil_MakeTrait(Tcp6Connection, sync);
ThorsAnvil_MakeTrait(Udp4Connection, fly);
ThorsAnvil_MakeTrait(Udp6Connection, fancy);


TEST(Issue38Test, Connection)
{
}
TEST(Issue38Test, IPConnection)
{
}
TEST(Issue38Test, IPv4Connection)
{
}
TEST(Issue38Test, IPv6Connection)
{
}
TEST(Issue38Test, TcpConnection)
{
}
TEST(Issue38Test, UdpConnection)
{
}
TEST(Issue38Test, Tcp4Connection)
{
}
TEST(Issue38Test, Tcp6Connection)
{
}
TEST(Issue38Test, Udp4Connection)
{
}
TEST(Issue38Test, Udp6Connection)
{
}
