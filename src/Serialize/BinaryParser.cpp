#include "SerializeConfig.h"
#ifdef NETWORK_BYTE_ORDER
#include "BinaryParser.h"
#include "ThorsIOUtil/Utility.h"
#include <sstream>

using namespace ThorsAnvil::Serialize;

BinaryParserUtilBase::~BinaryParserUtilBase()
{}

BinaryParserUtilBase::BinaryParserUtilBase(bool root, ParserToken first, ParserToken last, ParserToken nextValue)
    : nextToken(first)
    , objClose(last)
    , objNextValue(nextValue)
    , position(0)
    , end(0)
    , root(root)
    , started(false)
    , finished(false)
{}

ParserToken BinaryParserUtilBase::getNextToken(ParserInterface& parser, ParserState& state)
{
    if (!started)
    {
        started     = true;
        end         = readSize(parser);
        if (root)
        {
            return ParserToken::DocStart;
        }
    }
    if (nextToken == ParserToken::MapStart || nextToken == ParserToken::ArrayStart)
    {
        ParserToken     result  = nextToken;
        nextToken = objNextValue;
        return result;
    }
    if (position < end)
    {
        switch (nextToken)
        {
            case ParserToken::Key:
                nextToken = ParserToken::Value;
                return ParserToken::Key;
            case ParserToken::Value:
                nextToken = objNextValue;
                ++position;
                return pushNextState(position - 1, parser, state, ParserToken::Value);
            default:
            {
                throw std::runtime_error(
                    Utility::buildErrorMessage("ThorsAnvil::Serialize::BinaryParserUtilBase::getNextToken:",
                                               " Was expecting Key/Value",
                                               " Got: ParserToken(",
                                               static_cast<int>(nextToken),
                                               ")");
            }
        }
    }
    if (!finished)
    {
        finished    = true;
        if (!root)
        {
            state.pop_back();
        }
        return objClose;
    }
    state.pop_back();
    return ParserToken::DocEnd;
}

#ifdef COVERAGE_TEST

/*
 * This code is only compiled into the unit tests for code coverage purposes
 * It is not part of the live code.
 */
#include "BinaryParser.tpp"
#include "test/BinaryParserTest.h"

template ThorsAnvil::Serialize::BinaryParserUtil<MapWithMap,      (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapOneValue,     (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapTwoValue,     (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapEmptyTest,    (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapWithArray,    (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapThreeValue,   (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapWithTwoMap,   (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<MapWithTwoArray, (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);

template ThorsAnvil::Serialize::BinaryParserUtil<Base,            (ThorsAnvil::Serialize::TraitType)3>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<Derived,         (ThorsAnvil::Serialize::TraitType)1>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<int,             (ThorsAnvil::Serialize::TraitType)2>::BinaryParserUtil(bool);

// Array Specialization
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<MapEmptyTest>,     (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<std::string>,      (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<std::vector<int>>, (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<int>,              (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<bool>,             (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::vector<double>,           (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
#endif
#endif
