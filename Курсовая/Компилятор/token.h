#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>
enum TokenType
{
    Start,
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
    Identificator,
    Number,
    Return,
    END,
    Error,
};

struct Token
{
    enum TokenType type;
    char* value;
    int pos;
    int line;
};

char* NameType(enum TokenType type);

#endif