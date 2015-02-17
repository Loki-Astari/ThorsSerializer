
#ifndef THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H
#define THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H

#include "../Traits.h"

class SerializeTestExtra
{
    public:
    int         theInteger;
    double      aNonRealValue;
    bool        test;
    char*       aCStringObject;
    std::string normalString;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestExtra>;
    public:
        SerializeTestExtra()
            : aCStringObject(nullptr)
        {}
        SerializeTestExtra(int theInteger, double aNonRealValue, bool test, std::string const& aCStringObject, std::string const& normalString)
            : theInteger(theInteger)
            , aNonRealValue(aNonRealValue)
            , test(test)
            , aCStringObject(new char[aCStringObject.size()+1])
            , normalString(normalString)
        {
            strcpy(this->aCStringObject, aCStringObject.c_str());
        }
        ~SerializeTestExtra()
        {
            delete [] aCStringObject;
        }
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
        SerializeTestChild(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& aCStringObject, std::string const& normalString)
            : SerializeTestExtra(theInteger, aNonRealValue, test, aCStringObject, normalString)
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
        SerializeTestMembers(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& aCStringObject, std::string const& normalString)
            : member1(theInteger, aNonRealValue, test, aCStringObject, normalString)
            , member2(data1, data2, theInteger, aNonRealValue, test, aCStringObject, normalString)
        {}
};

ThorsAnvil_MakeTrait(SerializeTestExtra, theInteger, aNonRealValue, test, aCStringObject, normalString);
ThorsAnvil_ExpandTrait(SerializeTestExtra, SerializeTestChild, data1, data2);
ThorsAnvil_MakeTrait(SerializeTestMembers, member1, member2);


#endif

