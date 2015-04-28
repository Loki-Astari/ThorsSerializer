
#ifndef THORS_ANVIL_SERIALIZE_JSON_LEXER_H
#define THORS_ANVIL_SERIALIZE_JSON_LEXER_H

/*
 * Wrapper for including FlexLexer.h
 * This is provided as part of the flex application that buildes
 * a tokenzier (see FlexLexer.l)
 */
#define yyFlexLexer JsonLexerFlexLexer
#include <FlexLexer.h>

#endif

