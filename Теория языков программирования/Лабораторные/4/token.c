#include "token.h"

char* NameType(enum TokenType type)
{
	switch (type)
	{
	case Create:
		return "CREATE";
	case Table:
		return "TABLE";
	case Name:
		return "NAME";
	case OpenBrackets:
		return "OPENBRACKETS";
	case CloseBrackets:
		return "CLOSEBRACKETS";
	case Type:
		return "TYPE";
	case Attributes:
		return "ATTRIBUTES";
	case Comma:
		return "COMMA";
	case Primary:
		return "PRIMARY";
	case Foreign:
		return "FOREIGN";
	case Key:
		return "KEY";
	case References:
		return "REFERENCES";
	case Error:
		return "Error";
	case Empty:
		return "Empty";
	case Epsilon:
		return "Epsilon";
	default:
		break;
	}
}
