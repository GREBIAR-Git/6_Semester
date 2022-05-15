#include "token.h"

char* NameType(enum TokenType type)
{
    switch (type)
    {
    case Delimiter:
        return "Delimiter";
    case Comma:
        return "Comma";
    case Comparison:
        return "Comparison";
    case Assignment:
        return "Assignment";
    case OpenBracket:
        return "OpenBracket";
    case CloseBracket:
        return "CloseBracket";
    case OpenBraces:
        return "OpenBraces";
    case CloseBraces:
        return "CloseBraces";
    case MathSign:
        return "MathSign";
    case IOstring:
        return "IOstring";
    case IF:
        return "IF";
    case Else:
        return "ELSE";
    case Input:
        return "Input";
    case Output:
        return "Output";
    case Type:
        return "Type";
    case Identificator:
        return "Identificator";
    case Number:
        return "Number";
    default:
        break;
    }
}
