
#include "BinaryParser.h"

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
        switch(nextToken)
        {
            case ParserToken::Key:
                nextToken = ParserToken::Value;
                return ParserToken::Key;
            case ParserToken::Value:
                nextToken = objNextValue;
                ++position;
                return pushNextState(position - 1, parser, state, ParserToken::Value);
            default:
                throw std::runtime_error("KKK");
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
template ThorsAnvil::Serialize::BinaryParserUtil<std::__1::vector<MapEmptyTest, std::__1::allocator<MapEmptyTest> >, (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >, (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::__1::vector<std::__1::vector<int, std::__1::allocator<int> >, std::__1::allocator<std::__1::vector<int, std::__1::allocator<int> > > >, (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::__1::vector<bool, std::__1::allocator<bool> >,     (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
template ThorsAnvil::Serialize::BinaryParserUtil<std::__1::vector<double, std::__1::allocator<double> >, (ThorsAnvil::Serialize::TraitType)4>::BinaryParserUtil(bool);
#endif


