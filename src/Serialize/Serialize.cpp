#include "SerializeConfig.h"
#include "Serialize.h"

using ThorsAnvil::Serialize::ParserInterface;

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreValue()
{
    if (config.parseStrictness != ParseType::Weak)
    {   throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreValue: In Strict parser mode not allowed to ignore values.");
    }

    ignoreTheValue();
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheMap()
{
    for (ParserToken token = getNextToken(); token != ParserToken::MapEnd; token = getNextToken())
    {
        ignoreDataValue();
        if (token != ParserToken::Key)
        {   throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheMap: Invalid token found. (Expecting Key)");
        }
        ignoreTheValue();
    }
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheArray()
{
    ParserToken token = getNextToken();
    while (token != ParserToken::ArrayEnd)
    {
        switch (token)
        {
            case ParserToken::Error:     throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheArray: Invalid token found: Error");
            case ParserToken::Key:       throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheArray: Invalid token found: Key");
            case ParserToken::MapEnd:    throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheArray: Invalid token found: MapEnd");
            case ParserToken::Value:     ignoreDataValue(); break;
            case ParserToken::MapStart:  ignoreTheMap();    break;
            case ParserToken::ArrayStart:ignoreTheArray();  break;
            default:
                throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheArray: Invalid token found: Unknown");
        }
        token = getNextToken();
    }
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheValue()
{
    ParserToken token = getNextToken();
    switch (token)
    {
        case ParserToken::Error:     throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: Error");
        case ParserToken::Key:       throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: Key");
        case ParserToken::MapEnd:    throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: MapEnd");
        case ParserToken::ArrayEnd:  throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: ArrayEnd");
        case ParserToken::Value:     ignoreDataValue(); break;
        case ParserToken::MapStart:  ignoreTheMap();    break;
        case ParserToken::ArrayStart:ignoreTheArray();  break;
        default:
            throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: Unknown");
    }
}

#ifdef COVERAGE_TEST
/*
 * This code is only compiled into the unit tests for code coverage purposes
 * It is not part of the live code.
 */
#include "Serialize.tpp"
#include "SerUtil.h"
#include "JsonThor.h"
#include "test/SerializeTest.h"
#include "test/BinaryParserTest.h"
#include "test/IgnoreUneededData.h"
#include "test/ExceptionTest.h"
#include "test/Twitter.h"
#include "test/SmartPointerTest.h"


template void ThorsAnvil::Serialize::Serializer::print<BinaryParserTest::Base>(BinaryParserTest::Base const&);
template void ThorsAnvil::Serialize::Serializer::print<BinaryParserTest::Derived>(BinaryParserTest::Derived const&);
template void ThorsAnvil::Serialize::Serializer::print<int>(int const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<BinaryParserTest::Base>(BinaryParserTest::Base&);
template void ThorsAnvil::Serialize::DeSerializer::parse<BinaryParserTest::Derived>(BinaryParserTest::Derived&);
template void ThorsAnvil::Serialize::DeSerializer::parse<int>(int&);


template void ThorsAnvil::Serialize::Serializer::print<SerializeTest::SerializeTestExtra>(SerializeTest::SerializeTestExtra const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTest::SerializeTestChild>(SerializeTest::SerializeTestChild const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTest::SerializeTestMembers>(SerializeTest::SerializeTestMembers const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::SerializeTestExtra>(SerializeTest::SerializeTestExtra&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::SerializeTestChild>(SerializeTest::SerializeTestChild&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::SerializeTestMembers>(SerializeTest::SerializeTestMembers&);


template void ThorsAnvil::Serialize::Serializer::print<std::array<int, 12ul>>(std::array<int, 12ul> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::pair<int, double>>(std::pair<int, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::list<int>>(std::list<int> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::deque<int>>(std::deque<int> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::vector<int>>(std::vector<int> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::set<int>>(std::set<int> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::multiset<int>>(std::multiset<int> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::map<int, double>>(std::map<int, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::multimap<int, double>>(std::multimap<int, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::map<std::string, double>>(std::map<std::string, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::multimap<std::string, double>>(std::multimap<std::string, double> const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<std::array<int, 0ul>>(std::array<int, 0ul>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::array<int, 12ul>>(std::array<int, 12ul>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::pair<int, double>>(std::pair<int, double>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::list<int>>(std::list<int>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::deque<int>>(std::deque<int>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::vector<int>>(std::vector<int>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::set<int>>(std::set<int>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::multiset<int>>(std::multiset<int>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::map<int, double>>(std::map<int, double>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::multimap<int, double>>(std::multimap<int, double>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::map<std::string, bool>>(std::map<std::string, bool>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::multimap<std::string, bool>>(std::multimap<std::string, bool>&);

template void ThorsAnvil::Serialize::Serializer::print<SerializeTest::RGB>(SerializeTest::RGB const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::RGB>(SerializeTest::RGB&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTest::EumHolder>(SerializeTest::EumHolder const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::EumHolder>(SerializeTest::EumHolder&);

template void ThorsAnvil::Serialize::Serializer::print<std::tuple<int, double>>(std::tuple<int, double> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::tuple<int, double>>(std::tuple<int, double>&);

template void ThorsAnvil::Serialize::Serializer::print<std::unordered_set<int>>(std::unordered_set<int> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_set<int>>(std::unordered_set<int>&);

template void ThorsAnvil::Serialize::Serializer::print<std::unordered_map<std::string, double>>(std::unordered_map<std::string, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::unordered_map<int, double>>(std::unordered_map<int, double> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_map<std::string, bool>>(std::unordered_map<std::string, bool>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_map<int, double>>(std::unordered_map<int, double>&);

template void ThorsAnvil::Serialize::Serializer::print<std::unordered_multiset<int>>(std::unordered_multiset<int> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_multiset<int>>(std::unordered_multiset<int>&);

template void ThorsAnvil::Serialize::Serializer::print<std::unordered_multimap<std::string, double>>(std::unordered_multimap<std::string, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::unordered_multimap<int, double>>(std::unordered_multimap<int, double> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_multimap<std::string, bool>>(std::unordered_multimap<std::string, bool>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unordered_multimap<int, double>>(std::unordered_multimap<int, double>&);

template void ThorsAnvil::Serialize::Serializer::print<std::initializer_list<int>>(std::initializer_list<int> const&);

template void ThorsAnvil::Serialize::Serializer::print<IgnoreUneededData::Thing>(IgnoreUneededData::Thing const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<IgnoreUneededData::ThingVersion>(IgnoreUneededData::ThingVersion&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::CornerCaseClass>(SerializeTest::CornerCaseClass&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTest::CornerCaseClass*>(SerializeTest::CornerCaseClass*&);
template void ThorsAnvil::Serialize::Serializer::print<ExceptionTest::ThrowablePrint>(ExceptionTest::ThrowablePrint const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<ExceptionTest::ThrowablePrint>(ExceptionTest::ThrowablePrint&);

template void ThorsAnvil::Serialize::DeSerializer::parse<std::string>(std::string&);
template void ThorsAnvil::Serialize::Serializer::print<std::string>(std::string const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<TwitterTest::Twitter>(TwitterTest::Twitter&);
template void ThorsAnvil::Serialize::Serializer::print<TwitterTest::Twitter>(TwitterTest::Twitter const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SmartPtrTest::Object*>(SmartPtrTest::Object*&);
template void ThorsAnvil::Serialize::Serializer::print<SmartPtrTest::Object*>(SmartPtrTest::Object* const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::unique_ptr<SmartPtrTest::Object>>(std::unique_ptr<SmartPtrTest::Object>&);
template void ThorsAnvil::Serialize::Serializer::print<std::unique_ptr<SmartPtrTest::Object>>(std::unique_ptr<SmartPtrTest::Object> const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<std::shared_ptr<SmartPtrTest::Object>>(std::shared_ptr<SmartPtrTest::Object>&);
template void ThorsAnvil::Serialize::Serializer::print<std::shared_ptr<SmartPtrTest::Object>>(std::shared_ptr<SmartPtrTest::Object> const&);

#endif
