
#ifndef THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H
#define THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H

#include "../Traits.h"

enum RGB { Red, Green, Blue };
struct EumHolder
{
    RGB value;
};

class SerializeTestExtra
{
    public:
    int         theInteger;
    double      aNonRealValue;
    bool        test;
    std::string normalString;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestExtra>;
    public:
        SerializeTestExtra()
        {}
        SerializeTestExtra(int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : theInteger(theInteger)
            , aNonRealValue(aNonRealValue)
            , test(test)
            , normalString(normalString)
        {}
        ~SerializeTestExtra()
        {}
        SerializeTestExtra(SerializeTestExtra const&)             = delete;
        SerializeTestExtra& operator=(SerializeTestExtra const&)  = delete;
};

class SerializeTestChild: public SerializeTestExtra
{
    public:
    int data1;
    int data2;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestChild>;
    public:
        SerializeTestChild()
        {}
        SerializeTestChild(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : SerializeTestExtra(theInteger, aNonRealValue, test, normalString)
            , data1(data1)
            , data2(data2)
        {}
};

class SerializeTestMembers
{
    public:
    SerializeTestExtra member1;
    SerializeTestChild member2;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestMembers>;
    public:
        SerializeTestMembers()
        {}
        SerializeTestMembers(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : member1(theInteger, aNonRealValue, test, normalString)
            , member2(data1, data2, theInteger, aNonRealValue, test, normalString)
        {}
};

struct CornerCaseClass
{
    int value;
};

ThorsAnvil_MakeEnum(RGB, Red, Green, Blue);
ThorsAnvil_MakeTrait(EumHolder, value);
ThorsAnvil_MakeTrait(SerializeTestExtra, theInteger, aNonRealValue, test, normalString);
ThorsAnvil_ExpandTrait(SerializeTestExtra, SerializeTestChild, data1, data2);
ThorsAnvil_MakeTrait(SerializeTestMembers, member1, member2);
ThorsAnvil_MakeTrait(CornerCaseClass, value);


#endif

