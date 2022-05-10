#ifndef TOKEN_H
#define TOKEN_H
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

char* NameType(enum TokenType type)
{
    switch (type)
    {
    case Delimiter:
        return "Delimiter";
        break;
    case Comma:
        return "Comma";
    case Comparison:
        return "Comparison";
        break;
    case Assignment:
        return "Assignment";
        break;
    case OpenBracket:
        return "OpenBracket";
        break;
    case CloseBracket:
        return "CloseBracket";
        break;
    case OpenBraces:
        return "OpenBraces";
        break;
    case CloseBraces:
        return "CloseBraces";
        break;
    case MathSign:
        return "MathSign";
        break;
    case IOstring:
        return "IOstring";
        break;
    case IF:
        return "IF";
        break;
    case Else:
        return "ELSE";
        break;
    case Input:
        return "Input";
        break;
    case Output:
        return "Output";
        break;
    case Type:
        return "Type";
        break;
    case Identificator:
        return "Identificator";
        break;
    case Number:
        return "Number";
        break;
    default:
        break;
    }
}

#endif