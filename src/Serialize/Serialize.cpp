#include "Serialize.h"

using ThorsAnvil::Serialize::ParserInterface;

void ParserInterface::ignoreValue()
{
    if (parseStrictness == ParseType::Strict)
    {   throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreValue: In Strict parser mode not allowed to ignore values.");
    }

    ignoreTheValue();
}

void ParserInterface::ignoreTheMap()
{
    for (ParserToken token = getNextToken(); token != ParserToken::MapEnd; token = getNextToken())
    {
        std::cout << "Ignoring Next Map Item\n";
        if (token != ParserToken::Key)
        {   throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheMap: Invalid token found. (Expecting Key)");
        }
        ignoreTheValue();
    }
}

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
            case ParserToken::Value:     break;
            case ParserToken::MapStart:  ignoreTheMap();    break;
            case ParserToken::ArrayStart:ignoreTheArray();  break;
            default:
                throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheArray: Invalid token found: Unknown");
        }
        token = getNextToken();
    }
}

void ParserInterface::ignoreTheValue()
{
    ParserToken token = getNextToken();
    switch (token)
    {
        case ParserToken::Error:     throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: Error");
        case ParserToken::Key:       throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: Key");
        case ParserToken::MapEnd:    throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: MapEnd");
        case ParserToken::ArrayEnd:  throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::ignoreTheValue: Invalid token found: ArrayEnd");
        case ParserToken::Value:     break;
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


template void ThorsAnvil::Serialize::Serializer::print<Base>(Base const&);
template void ThorsAnvil::Serialize::Serializer::print<Derived>(Derived const&);
template void ThorsAnvil::Serialize::Serializer::print<int>(int const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<Base>(Base&);
template void ThorsAnvil::Serialize::DeSerializer::parse<Derived>(Derived&);
template void ThorsAnvil::Serialize::DeSerializer::parse<int>(int&);


template void ThorsAnvil::Serialize::Serializer::print<SerializeTestExtra>(SerializeTestExtra const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestChild>(SerializeTestChild const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestMembers>(SerializeTestMembers const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestExtra>(SerializeTestExtra&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestChild>(SerializeTestChild&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestMembers>(SerializeTestMembers&);


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

template void ThorsAnvil::Serialize::Serializer::print<RGB>(RGB const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<RGB>(RGB&);
template void ThorsAnvil::Serialize::Serializer::print<EumHolder>(EumHolder const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<EumHolder>(EumHolder&);

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

template void ThorsAnvil::Serialize::Serializer::print<Thing>(Thing const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<ThingVersion>(ThingVersion&);

#endif
