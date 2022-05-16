#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>
enum TokenType
{
    Create,
    Table,
    Name,
    OpenBrackets,
    CloseBrackets,
    Type,
    Attributes,
    Comma,
    Primary,
    Foreign,
    Key,
    References,
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