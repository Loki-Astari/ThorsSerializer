
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

BinaryParserUtilBase::ParserToken BinaryParserUtilBase::getNextToken(ParserInterface& parser, std::vector<std::unique_ptr<BinaryParserUtilBase>>& state)
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

#endif


