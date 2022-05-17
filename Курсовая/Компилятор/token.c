#include "token.h"

char* NameType(enum TokenType type)
{
    switch (type)
    {
    case Delimiter:
        return "Delimiter";
    case Tab:
        return "Tab";
    case Comma:
        return "Comma";
    case Dot:
        return "Dot";
    case DoubleDot:
        return "Double Dot";
    case Bool:
        return "Bool";
    case OpenBraces:
        return "Open Braces";
    case CloseBraces:
        return "Close Braces";
    case OpenBracket:
        return "Open Bracket";
    case CloseBracket:
        return "Close Bracket";
    case Comparison:
        return "Comparison";
    case Logical:
        return "Logical";
    case Assignment:
        return "Assignment";
    case MathSign:
        return "MathSign";
    case If:
        return "If";
    case Else:
        return "Else:";
    case For:
        return "For";
    case In:
        return "In";
    case While:
        return "While";
    case Def:
        return "Def";
    case Class:
        return "Class";
    case Input:
        return "Input";
    case Output:
        return "Output";
    case Identificator:
        return "Identificator";
    case Number:
        return "Number";
    case Error:
        return "Error";
    default:
        break;
    }
}
