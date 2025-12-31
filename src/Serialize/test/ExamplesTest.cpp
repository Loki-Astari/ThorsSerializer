#include "PrinterConfig.h"
#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"
#include "YamlThor.h"

TEST(ExamplesTest, TrivialExample0)
{
    std::vector<int>    data;
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::stringstream   ss("[1,2,3,4,5]");
    ss >> jsonImporter(data);

    std::stringstream   outss;
    outss << jsonExporter(data) << "\n";
    EXPECT_EQ(R"(
[1, 2, 3, 4, 5]
)", outss.str());
}

struct Shirt
{
    int     red;
    int     green;
    int     blue;
};
class TeamMember
{
    std::string     name;
    int             score;
    int             damage;
    Shirt           team;
    public:
        TeamMember(std::string const& name, int score, int damage, Shirt const& team)
            : name(name)
            , score(score)
            , damage(damage)
            , team(team)
        {}
        // Define the trait as a friend to get accesses to private
        // Members.
        friend class ThorsAnvil::Serialize::Traits<TeamMember>;

        std::string const& getName()    const {return name;}
        int                 getScore()  const {return score;}
        int                 getDamage() const {return damage;}
        Shirt const&        getTeam()   const {return team;}
};

// Declare the traits.
// Specifying what members need to be serialized.
ThorsAnvil_MakeTrait(Shirt, red, green, blue);
ThorsAnvil_MakeTrait(TeamMember, name, score, damage, team);

TEST(ExamplesTest, SimpleExample1Json)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << jsonExporter(mark);
    EXPECT_EQ(R"(
{
    "name": "mark",
    "score": 10,
    "damage": 5,
    "team":
    {
        "red": 255,
        "green": 0,
        "blue": 0
    }
})", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << jsonExporter(john);
    EXPECT_EQ(R"(
{
    "name": "John",
    "score": 13,
    "damage": 0,
    "team":
    {
        "red": 0,
        "green": 0,
        "blue": 255
    }
})", outss.str());
}

TEST(ExamplesTest, SimpleExample1Yaml)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::yamlExporter;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << yamlExporter(mark);

    EXPECT_EQ(R"(---
name: mark
score: 10
damage: 5
team:
  red: 255
  green: 0
  blue: 0
...
)", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << yamlExporter(john);
    EXPECT_EQ(R"(---
name: John
score: 13
damage: 0
team:
  red: 0
  green: 0
  blue: 255
...
)", outss.str());
}

TEST(ExamplesTest, SimpleExample2Json)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::PrinterConfig;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << jsonExporter(mark);
    EXPECT_EQ(R"(
{
    "name": "mark",
    "score": 10,
    "damage": 5,
    "team":
    {
        "red": 255,
        "green": 0,
        "blue": 0
    }
})", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << jsonExporter(john, PrinterConfig{ThorsAnvil::Serialize::OutputType::Config, 2});
    EXPECT_EQ(R"(
{
  "name": "John",
  "score": 13,
  "damage": 0,
  "team":
  {
    "red": 0,
    "green": 0,
    "blue": 255
  }
})", outss.str());
}
TEST(ExamplesTest, SimpleExample2Yaml)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::yamlExporter;
    using ThorsAnvil::Serialize::PrinterConfig;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << yamlExporter(mark);

    EXPECT_EQ(R"(---
name: mark
score: 10
damage: 5
team:
  red: 255
  green: 0
  blue: 0
...
)", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << yamlExporter(john, PrinterConfig{ThorsAnvil::Serialize::OutputType::Config, 4});
    EXPECT_EQ(R"(---
name: John
score: 13
damage: 0
team:
    red: 0
    green: 0
    blue: 255
...
)", outss.str());
}
TEST(ExamplesTest, SimpleExample3Json)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::PrinterConfig;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << jsonExporter(mark);
    EXPECT_EQ(R"(
{
    "name": "mark",
    "score": 10,
    "damage": 5,
    "team":
    {
        "red": 255,
        "green": 0,
        "blue": 0
    }
})", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << jsonExporter(john, PrinterConfig{ThorsAnvil::Serialize::OutputType::Config, 2, 10});
    EXPECT_EQ(R"(
          {
            "name": "John",
            "score": 13,
            "damage": 0,
            "team":
            {
              "red": 0,
              "green": 0,
              "blue": 255
            }
          })", outss.str());
          }
TEST(ExamplesTest, SimpleExample3Yaml)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::yamlExporter;
    using ThorsAnvil::Serialize::PrinterConfig;

    TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
    // Use the export function to serialize
    std::stringstream   ss;
    ss << yamlExporter(mark);

    EXPECT_EQ(R"(---
name: mark
score: 10
damage: 5
team:
  red: 255
  green: 0
  blue: 0
...
)", ss.str());

    TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
    std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
    input >> jsonImporter(john);
    EXPECT_EQ("John", john.getName());
    EXPECT_EQ(13, john.getScore());
    EXPECT_EQ(0, john.getDamage());
    EXPECT_EQ(0, john.getTeam().red);
    EXPECT_EQ(0, john.getTeam().green);
    EXPECT_EQ(255, john.getTeam().blue);

    std::stringstream   outss;
    outss << yamlExporter(john, PrinterConfig{ThorsAnvil::Serialize::OutputType::Config, 4, 10});
    EXPECT_EQ(R"(          ---
          name: John
          score: 13
          damage: 0
          team:
              red: 0
              green: 0
              blue: 255
          ...
          )", outss.str());
}


/* A class that you want to serialize. */
class MyClass
{
    int         data1;
    float       data2;
    std::string data3;
    public:
        MyClass(int data1, float data2, std::string const& data3)
            : data1(data1)
            , data2(data2)
            , data3(data3)
        {}

    // This is only required if the members are private.
    friend class ThorsAnvil::Serialize::Traits<MyClass>;
};


/*
 * Though there is no code involved, you do need to set up
 * this structure to tell the library what fields need to be serialized.
 * To do this use the macro:  ThorsAnvil_MakeTrait()
 * Specifying your class, and a list of members to serialize.
 */
ThorsAnvil_MakeTrait(MyClass, data1, data2, data3);

TEST(ExamplesTest, BiggerExample2)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::OutputType;

    MyClass   data {56, 23.456, "Hi there"};


    // This generates a simple JSON Object (wordy)
    std::stringstream ss1;
    ss1 << jsonExporter(data);
    EXPECT_EQ(R"(
{
    "data1": 56,
    "data2": 23.456,
    "data3": "Hi there"
})", ss1.str());

    // This generates a compact JSON 
    std::stringstream ss2;
    ss2 << jsonExporter(data, OutputType::Stream);
    EXPECT_EQ(R"({"data1":56,"data2":23.456,"data3":"Hi there"})", ss2.str());

    // Standard containers work automatically.
    // As long as the type held by the container has had an appropriate
    // Traits declaration.
    std::vector<MyClass>   vec(4, data);
    std::stringstream ss3;
    ss3 << jsonExporter(vec);
    EXPECT_EQ(R"(
[
    {
        "data1": 56,
        "data2": 23.456,
        "data3": "Hi there"
    },
    {
        "data1": 56,
        "data2": 23.456,
        "data3": "Hi there"
    },
    {
        "data1": 56,
        "data2": 23.456,
        "data3": "Hi there"
    },
    {
        "data1": 56,
        "data2": 23.456,
        "data3": "Hi there"
    }
])", ss3.str());
}


    struct Vehicle
    {
        Vehicle(){}
        Vehicle(int speed)
            : speed(speed)
        {}
        virtual ~Vehicle() {}
        int     speed;
        ThorsAnvil_PolyMorphicSerializer(Vehicle);
    };
    struct Car: public Vehicle
    {
        Car(){}
        Car(int speed, std::string const& make)
            : Vehicle(speed)
            , make(make)
        {}
        std::string     make;
        ThorsAnvil_PolyMorphicSerializer(Car);
    };
    struct Bike: public Vehicle
    {
        Bike(){}
        Bike(int speed, int stroke)
            : Vehicle(speed)
            , stroke(stroke)
        {}
        int     stroke;
        ThorsAnvil_PolyMorphicSerializer(Bike);
    };

    ThorsAnvil_MakeTrait(Vehicle, speed);
    ThorsAnvil_ExpandTrait(Vehicle, Car, make);
    ThorsAnvil_ExpandTrait(Vehicle, Bike, stroke);

TEST(ExamplesTest, PolyMorphicExample3)
{
    Vehicle*    init = new Bike(15, 2);

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(init);
    EXPECT_EQ(R"(
{
    "__type": "Bike",
    "stroke": 2,
    "speed": 15
})", stream.str());

    Vehicle*    result = nullptr;
    std::stringstream    stream2;
    stream2 << ThorsAnvil::Serialize::jsonExporter(result);
    EXPECT_EQ("null", stream2.str());

    stream >> ThorsAnvil::Serialize::jsonImporter(result);
    std::stringstream    stream3;
    stream3 << ThorsAnvil::Serialize::jsonExporter(result);
    EXPECT_EQ(stream.str(), stream3.str());
}

class Car1
{
    public:
        Car1(std::string color, uint16_t speed, uint32_t price) :
            Color(color),
            Speed(speed),
            Price(price){};

        std::string getColor(){return Color;};
        uint16_t getSpeed(){return Speed;};
        uint32_t getPrice(){return Price;};
    private:
        // Note: Member names must match JSON names.
        friend class ThorsAnvil::Serialize::Traits<Car1>;
        std::string Color;
        uint16_t    Speed;
        uint32_t    Price;
};
struct AllCars
{
    std::map<std::string, Car1>      myCars;
};


ThorsAnvil_MakeTrait(Car1, Color, Price, Speed);
ThorsAnvil_MakeTrait(AllCars, myCars);


TEST(ExamplesTest, Exampl4)
{
    std::map<std::string, Car1>      myGarage;
    myGarage.emplace("car1", Car1{"red", 200, 10000});
    myGarage.emplace("car2", Car1{"blue", 666, 16000});
    myGarage.emplace("car3", Car1{"yellow", 50, 7500});
    myGarage.emplace("car4", Car1{"green", 10, 750});

    std::stringstream ss;

    using ThorsAnvil::Serialize::jsonExporter;
    ss << jsonExporter(myGarage);
    EXPECT_EQ(R"(
{
    "car1":
    {
        "Color": "red",
        "Price": 10000,
        "Speed": 200
    },
    "car2":
    {
        "Color": "blue",
        "Price": 16000,
        "Speed": 666
    },
    "car3":
    {
        "Color": "yellow",
        "Price": 7500,
        "Speed": 50
    },
    "car4":
    {
        "Color": "green",
        "Price": 750,
        "Speed": 10
    }
})", ss.str());
}


/* A class that you want to serialize. */
class MyClass1
{
    std::string     H;
    int             N;
    int             D1;
    int             D2;
    friend class ThorsAnvil::Serialize::Traits<MyClass1>;

    public:
        MyClass1(std::string const& h, int n, int d1, int d2)
            : H(h)
            , N(n)
            , D1(d1)
            , D2(d2)
        {}
};


/*
 * Though there is no code involved, you do need to set up
 * this structure to tell the library what fields need to be serialized.
 * To do this use the macro:  ThorsAnvil_MakeTrait()
 * Specifying your class, and a list of members to serialize.
 */
ThorsAnvil_MakeTrait(MyClass1, H, N, D1, D2);


TEST(ExamplesTest, Example6)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::OutputType;
    using namespace std::string_literals;

    MyClass1   data {"1"s, 3, 3, 150};


    // This generates a simple JSON Object (wordy)
    std::stringstream ss1;
    ss1 << jsonExporter(data);

    EXPECT_EQ(R"(
{
    "H": "1",
    "N": 3,
    "D1": 3,
    "D2": 150
})", ss1.str());

    // This generates a compact JSON 
    std::stringstream ss2;
    ss2 << jsonExporter(data, OutputType::Stream);
    EXPECT_EQ(R"({"H":"1","N":3,"D1":3,"D2":150})", ss2.str());
}

    struct Component
    {
        std::string                 type;
        std::vector<std::string>    axis;
    };
    struct Data
    {
        std::vector<Component>      components;
    };

    // Declare the traits.
    // Specifying what members need to be serialized.
    ThorsAnvil_MakeTrait(Component, type, axis);
    ThorsAnvil_MakeTrait(Data, components);


TEST(ExamplesTest, Example7)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    Data                data1;
    Data                data2;
    // See: https://github.com/Loki-Astari/ThorsSerializer/blob/master/doc/example7.json
    std::stringstream       file(R"({
    "components": [
        {
            "type": "mesh",
            "axis": ["x","y","z"]
        }
    ]
}
{
    "components": [
        {
            "type": "mesh",
            "axis": ["x","y",z]
        }
    ]
})");

    file >> jsonImporter(data1);
    EXPECT_EQ(data1.components[0].type, "mesh");
    EXPECT_EQ(data1.components[0].axis[0], "x");
    EXPECT_EQ(data1.components[0].axis[1], "y");
    EXPECT_EQ(data1.components[0].axis[2], "z");

    std::stringstream ss1;
    ss1 << jsonExporter(data1);
    EXPECT_EQ(R"(
{
    "components":
    [
        {
            "type": "mesh",
            "axis":
            ["x", "y", "z"]
        }
    ]
})", ss1.str());

    file >> jsonImporter(data2);
    EXPECT_FALSE(static_cast<bool>(file));
}

class Identifier
{
    public:
    std::string     name;
    std::string     bar;
    std::string     foo;
};
class Properties
{
    public:
    std::string     category;
    std::string     time;
    std::string     shouldRetry;
    std::string     Id;
};
class Data1
{
    public:
    std::string     operation;
    Identifier      identifier;
    Properties      properties;
};

ThorsAnvil_MakeTrait(Identifier, name, bar, foo);
ThorsAnvil_MakeTrait(Properties, category, time, shouldRetry, Id);
ThorsAnvil_MakeTrait(Data1, operation, identifier, properties);

TEST(ExamplesTest, Example8)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::vector<Data1>   objects;

    std::stringstream    file(R"(
[
    {
        "operation": "test",
        "identifier": {
            "name": "1",
            "bar": "sandbox",
            "foo": "foo"
        },
        "properties": {
            "category": "xxx",
            "time": "yyy",
            "shouldRetry": "False",
            "Id": "vvvv"
        }
    }
])");

    file >> jsonImporter(objects);
    EXPECT_TRUE(static_cast<bool>(file));
    EXPECT_EQ(objects[0].operation, "test");
    EXPECT_EQ(objects[0].identifier.name, "1");
    EXPECT_EQ(objects[0].identifier.bar, "sandbox");
    EXPECT_EQ(objects[0].identifier.foo, "foo");
    EXPECT_EQ(objects[0].properties.category, "xxx");
    EXPECT_EQ(objects[0].properties.time, "yyy");
    EXPECT_EQ(objects[0].properties.shouldRetry, "False");
    EXPECT_EQ(objects[0].properties.Id, "vvvv");

    std::stringstream ss;
    ss << jsonExporter(objects);
    EXPECT_EQ(R"(
[
    {
        "operation": "test",
        "identifier":
        {
            "name": "1",
            "bar": "sandbox",
            "foo": "foo"
        },
        "properties":
        {
            "category": "xxx",
            "time": "yyy",
            "shouldRetry": "False",
            "Id": "vvvv"
        }
    }
])", ss.str());
}

enum class EnumType : int {
    A, B, C
};

struct MyStruct {
    EnumType    e;
    std::string s;
};

// ThorsAnvil_MakeEnum is still supported for backwards compatibility.
// But this functionality has been replaces by magic_enum
// Please see: https://github.com/Neargye/magic_enum

ThorsAnvil_MakeEnum(EnumType, A, B, C);
ThorsAnvil_MakeTrait(MyStruct, e, s);

TEST(ExamplesTest, ExampleE)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::OutputType;

    MyStruct    val;
    std::stringstream inputss(R"({"e": "A", "s": "This string"}{"e": "B", "s": "Another string"}{"e": "C", "s": "Last string"})");

    inputss >> jsonImporter(val);
    EXPECT_EQ(val.e, EnumType::A);
    EXPECT_EQ(val.s, "This string");

    inputss >> jsonImporter(val);
    EXPECT_EQ(val.e, EnumType::B);
    EXPECT_EQ(val.s, "Another string");

    inputss >> jsonImporter(val);
    EXPECT_EQ(val.e, EnumType::C);
    EXPECT_EQ(val.s, "Last string");

    std::stringstream ss;
    ss << jsonExporter(val);
    EXPECT_EQ(R"(
{
    "e": "C",
    "s": "Last string"
})", ss.str());

    std::stringstream ss2;
    ss2 << jsonExporter(val, OutputType::Stream);
    EXPECT_EQ(R"({"e":"C","s":"Last string"})", ss2.str());
}
