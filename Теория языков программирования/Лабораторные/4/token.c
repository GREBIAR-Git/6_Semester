#include "token.h"

char* NameType(enum TokenType type)
{
	switch (type)
	{
	case Create:
		return "Create";
	case Table:
		return "Table";
	case Name:
		return "Name";
	case OpenBrackets:
		return "OpenBrackets";
	case CloseBrackets:
		return "CloseBrackets";
	case Type:
		return "Type";
	case Attributes:
		return "Attributes";
	case Comma:
		return "Comma";
	case Primary:
		return "Primary";
	case Foreign:
		return "Foreign";
	case Key:
		return "Key";
	case References:
		return "References";
	case Error:
		return "Error";
	default:
		break;
	}
}
