
#include "gtest/gtest.h"
#include "THashTest.h"
#include "BinaryTHash.h"
#include "BinaryParserTest.h"

namespace TS=ThorsAnvil::Serialize;

TEST(THashTest, hashFundamental)
{
    std::size_t     shortH              = TS::thash<short>();
    std::size_t     intH                = TS::thash<int>();
    std::size_t     longH               = TS::thash<long>();
    std::size_t     longlongH           = TS::thash<long long>();

    std::size_t     ushortH             = TS::thash<unsigned short>();
    std::size_t     uintH               = TS::thash<unsigned int>();
    std::size_t     ulongH              = TS::thash<unsigned long>();
    std::size_t     ulonglongH          = TS::thash<unsigned long long>();

    std::size_t     floatH              = TS::thash<float>();
    std::size_t     doubleH             = TS::thash<double>();
    std::size_t     longdoubleH         = TS::thash<long double>();

    std::size_t     boolH               = TS::thash<bool>();
    std::size_t     stringH             = TS::thash<std::string>();

    std::size_t     vectorIntH          = TS::thash<std::vector<int>>();
    std::size_t     emptyMapH           = TS::thash<BinaryParserTest::MapEmptyTest>();
    std::size_t     OneMapH             = TS::thash<BinaryParserTest::MapOneValue>();


    EXPECT_EQ(shortH,           TS::thash<short>());
    EXPECT_EQ(intH,             TS::thash<int>());
    EXPECT_EQ(longH,            TS::thash<long>());
    EXPECT_EQ(longlongH,        TS::thash<long long>());

    EXPECT_EQ(ushortH,          TS::thash<unsigned short>());
    EXPECT_EQ(uintH,            TS::thash<unsigned int>());
    EXPECT_EQ(ulongH,           TS::thash<unsigned long>());
    EXPECT_EQ(ulonglongH,       TS::thash<unsigned long long>());

    EXPECT_EQ(floatH,           TS::thash<float>());
    EXPECT_EQ(doubleH,          TS::thash<double>());
    EXPECT_EQ(longdoubleH,      TS::thash<long double>());

    EXPECT_EQ(boolH,            TS::thash<bool>());
    EXPECT_EQ(stringH,          TS::thash<std::string>());

    EXPECT_NE(shortH,           intH);
    EXPECT_NE(shortH,           longH);
    EXPECT_NE(shortH,           longlongH);
    EXPECT_NE(shortH,           ushortH);
    EXPECT_NE(shortH,           uintH);
    EXPECT_NE(shortH,           ulongH);
    EXPECT_NE(shortH,           ulonglongH);
    EXPECT_NE(shortH,           floatH);
    EXPECT_NE(shortH,           doubleH);
    EXPECT_NE(shortH,           longdoubleH);
    EXPECT_NE(shortH,           boolH);
    EXPECT_NE(shortH,           stringH);

    EXPECT_NE(intH,             longH);
    EXPECT_NE(intH,             longlongH);
    EXPECT_NE(intH,             ushortH);
    EXPECT_NE(intH,             uintH);
    EXPECT_NE(intH,             ulongH);
    EXPECT_NE(intH,             ulonglongH);
    EXPECT_NE(intH,             floatH);
    EXPECT_NE(intH,             doubleH);
    EXPECT_NE(intH,             longdoubleH);
    EXPECT_NE(intH,             boolH);
    EXPECT_NE(intH,             stringH);

    EXPECT_NE(longH,            longlongH);
    EXPECT_NE(longH,            ushortH);
    EXPECT_NE(longH,            uintH);
    EXPECT_NE(longH,            ulongH);
    EXPECT_NE(longH,            ulonglongH);
    EXPECT_NE(longH,            floatH);
    EXPECT_NE(longH,            doubleH);
    EXPECT_NE(longH,            longdoubleH);
    EXPECT_NE(longH,            boolH);
    EXPECT_NE(longH,            stringH);

    EXPECT_NE(longlongH,        ushortH);
    EXPECT_NE(longlongH,        uintH);
    EXPECT_NE(longlongH,        ulongH);
    EXPECT_NE(longlongH,        ulonglongH);
    EXPECT_NE(longlongH,        floatH);
    EXPECT_NE(longlongH,        doubleH);
    EXPECT_NE(longlongH,        longdoubleH);
    EXPECT_NE(longlongH,        boolH);
    EXPECT_NE(longlongH,        stringH);

    EXPECT_NE(ushortH,          uintH);
    EXPECT_NE(ushortH,          ulongH);
    EXPECT_NE(ushortH,          ulonglongH);
    EXPECT_NE(ushortH,          floatH);
    EXPECT_NE(ushortH,          doubleH);
    EXPECT_NE(ushortH,          longdoubleH);
    EXPECT_NE(ushortH,          boolH);
    EXPECT_NE(ushortH,          stringH);

    EXPECT_NE(uintH,            ulongH);
    EXPECT_NE(uintH,            ulonglongH);
    EXPECT_NE(uintH,            floatH);
    EXPECT_NE(uintH,            doubleH);
    EXPECT_NE(uintH,            longdoubleH);
    EXPECT_NE(uintH,            boolH);
    EXPECT_NE(uintH,            stringH);

    EXPECT_NE(ulongH,           ulonglongH);
    EXPECT_NE(ulongH,           floatH);
    EXPECT_NE(ulongH,           doubleH);
    EXPECT_NE(ulongH,           longdoubleH);
    EXPECT_NE(ulongH,           boolH);
    EXPECT_NE(ulongH,           stringH);

    EXPECT_NE(ulonglongH,       floatH);
    EXPECT_NE(ulonglongH,       doubleH);
    EXPECT_NE(ulonglongH,       longdoubleH);
    EXPECT_NE(ulonglongH,       boolH);
    EXPECT_NE(ulonglongH,       stringH);

    EXPECT_NE(floatH,           doubleH);
    EXPECT_NE(floatH,           longdoubleH);
    EXPECT_NE(floatH,           boolH);
    EXPECT_NE(floatH,           stringH);

    EXPECT_NE(doubleH,          longdoubleH);
    EXPECT_NE(doubleH,          boolH);
    EXPECT_NE(doubleH,          stringH);

    EXPECT_NE(longdoubleH,      boolH);
    EXPECT_NE(longdoubleH,      stringH);

    EXPECT_NE(boolH,            stringH);
}

TEST(THashTest, hashCompound)
{
    /*
     * The actual type does not matter for binary objects.
     * The only thing that actually matters is that the types are in a specific order.
     * What is also nice (but nor required is that field names match up).
     *
     * To help check this as long as the hash of the type on both ends match then
     * it is safe* to de-serialize into the destination object.
     */
    EXPECT_EQ(TS::thash<THashTest::T1>(),      TS::thash<THashTest::T2>());
    EXPECT_NE(TS::thash<THashTest::T1>(),      TS::thash<THashTest::D1>());
}


