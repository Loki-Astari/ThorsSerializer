
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

ThorsAnvil_MakeTrait(SerializeTestExtra, Map, theInteger, aNonRealValue, test, aCStringObject, normalString);


#endif

