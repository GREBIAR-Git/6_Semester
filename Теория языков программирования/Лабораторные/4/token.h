#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>
enum TokenType
{
    Create,
    Table,
    Primary,
    Foreign,
    Key,
    References,
    Attributes,
    Type,
    Name,
    OpenBrackets,
    CloseBrackets,
    Comma,
    Error,
    Empty,
    Epsilon,
};

struct Token
{
    enum TokenType type;
    char* value;
    int pos;
};

char* NameType(enum TokenType type);

#endif