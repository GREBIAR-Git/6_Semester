#include "token.h"

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
    case MathSign:
        return "MathSign";
        break;
    case IOstring:
        return "IOstring";
        break;
    case KeyWord:
        return "KeyWord";
        break;
    case IO:
        return "IO";
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
