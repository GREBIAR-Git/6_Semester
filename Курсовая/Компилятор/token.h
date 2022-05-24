#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>
enum TokenType
{
    Delimiter,// \n
    Tab,// \t
    Comma,// ,
    Dot,// .
    DoubleDot,// :
    Bool, // true false
    OpenBraces,//[
    CloseBraces,//]
    OpenBracket,//(
    CloseBracket,//)
    Comparison,//< > == != >= <=
    Logical,// and or not
    Assignment,// = += -= *= /= %=
    MathSign,// + - * / %
    If, // if
    Else, // else 
    For, // for
    In, // in
    While, // while
    Input, // input
    Output, // print
    Def, // def
    Class, // class
    Variable,
    Number,
    Return,
    END,
    Error,
};

enum NonTerminalType
{
    Terminal,
    BlockTerm,
    Function,
    Params,
    LogicalOperationTerm,
};

struct Token
{
    enum TokenType type;
    char* value;
    int pos;
    int line;
};

char* NameNonTerminalType(enum NonTerminalType type);

char* NameType(enum TokenType type);

#endif