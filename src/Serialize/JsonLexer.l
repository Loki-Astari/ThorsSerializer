
%option c++
%option noyywrap
%option prefix="JsonLexer"

%{

#define  IN_LEXER
#include "JsonLexemes.h"

%}

DIGIT           [0-9]
DIGIT1          [1-9]
INTNUM          {DIGIT1}{DIGIT}*
FRACT           "."{DIGIT}+
FLOAT           ({INTNUM}|0){FRACT}?
EXP             [eE][+-]?{DIGIT}+
NUMBER          -?{FLOAT}{EXP}?

UNICODE         \\u[A-Fa-f0-9]{4}
ESCAPECHAR      \\["\\/bfnrt]
CHAR            [^"\\]|{ESCAPECHAR}|{UNICODE}
STRING          \"{CHAR}*\"

VALUE_STRING    {STRING}
VALUE_INTEGER   {INTNUM}
VALUE_FLOAT     {NUMBER}

WHITESPACE      [ \t\n]


%%

\{              {return '{';}
\}              {return '}';}
\[              {return '[';}
\]              {return ']';}
,               {return ',';}
:               {return ':';}
true            {return ThorsAnvil::Serialize::JSON_TRUE;}
false           {return ThorsAnvil::Serialize::JSON_FALSE;}
null            {return ThorsAnvil::Serialize::JSON_NULL;}
{VALUE_STRING}  {return ThorsAnvil::Serialize::JSON_STRING;}
{VALUE_INTEGER} {return ThorsAnvil::Serialize::JSON_INTEGER;}
{VALUE_FLOAT}   {return ThorsAnvil::Serialize::JSON_FLOAT;}

{WHITESPACE}    {/*IGNORE*/}
.               {throw std::runtime_error("ThorsAnvil::Serialize::JsonLexer: Invalid Character in Lexer");}

%%




