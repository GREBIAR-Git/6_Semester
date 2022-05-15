#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>
enum TokenType
{
    Delimiter,
    Comma,
    Comparison,
    Assignment,
    OpenBracket,
    CloseBracket,
    OpenBraces,
    CloseBraces,
    MathSign,
    IOstring,
    IF,
    Else,
    Input,
    Output,
    Type,
    Identificator,
    Number,
    Error,
};

struct Token
{
    enum TokenType type;
    char* value;
    int pos;
};

char* NameType(enum TokenType type);

#endif