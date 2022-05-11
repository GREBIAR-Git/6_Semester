#include "parser.h"
int tempCurrentToken;

int currentToken;

int bracketCountDifference;// разница открытых и закрытых скобок 

int tokenLength;

struct Token * tokens;

void Parser(struct Token * token, int tokenQuantity)
{
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTARTPARSER\n");
	if (Sequence())
	{
		printf("No one error");
	}
	else
	{
		printf("error");
	}
}

bool Sequence()
{
	currentToken = tempCurrentToken;
	printf("\nnew Sequence\n");
	printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	printf("\n%d", sizeof(tokens));
	printf("\n%d", tokenLength);
	if(currentToken >= tokenLength)
	{
		printf("\nend Sequence\n");
		return true;
	}
	else if (tokens[currentToken].type == CloseBraces)
	{
		printf("\nend Sequence\n");
		return true;
	}
	else if (Statement() && Sequence())
	{
		printf("\nend Sequence\n");
		return true;
	}
	printf("\nerror Sequence\n");
	return false;
}

bool Statement()
{
	tempCurrentToken = currentToken;
	printf("\ntest-Condition\n");
	if (Condition())
	{
		currentToken = tempCurrentToken;
		printf("Statement-true");
		return true;
	}
	else
	{
		printf("\ntest-VariableDeclaration\n");
		tempCurrentToken = currentToken;
		if (VariableDeclaration())
		{
			currentToken = tempCurrentToken;
			printf("Statement-true");
			return true;
		}
		else 
		{
			printf("\ntest-Assignment1\n");
			tempCurrentToken = currentToken;
			if (Assignment1())
			{
				currentToken = tempCurrentToken;
				printf("Statement-true");
				return true;
			}
			else
			{
				printf("\ntest-Input1\n");
				tempCurrentToken = currentToken;
				if (Input1())
				{
					currentToken = tempCurrentToken;
					printf("Statement-true");
					return true;
				}
				else
				{
					printf("\ntest-Output1\n");
					tempCurrentToken = currentToken;
					if (Output1())
					{
						currentToken = tempCurrentToken;
						printf("Statement-true");
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Condition()
{
	printf("Condition -start");
	int tempCurrentToken1 = currentToken;
	tempCurrentToken = currentToken;

	if (Is(IF) && Is(OpenBracket) && LogicalExpression() && Is(OpenBraces) && Sequence() && Is(CloseBraces))
	{
		currentToken = tempCurrentToken;
		printf("\nbefore ELSE current token - %s\n", NameType(tokens[tempCurrentToken].type));
		if (Is(Else) && Is(OpenBraces) && Sequence() && Is(CloseBraces))
		{
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("\ncurrent token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
			currentToken = tempCurrentToken;
			printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		}
		printf("Condition-true");
		return true;
	}
	else
	{
		printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		currentToken = tempCurrentToken1;
		printf("Condition-false");
		return false;
	}
}

bool LogicalExpression()
{
	printf("\nLogicalExpression -start\n");
	printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
	if (ArithmeticExpressionMain())
	{
		if (currentToken < tempCurrentToken)
		{
			printf("min");
			currentToken = tempCurrentToken;
		}
		printf("\nbefore Comparison token - %s\n", NameType(tokens[currentToken].type));
		if(Is(Comparison) && LogicalExpression())
		{
			if (currentToken < tempCurrentToken)
			{
				currentToken = tempCurrentToken;
			}
		}
		printf("\nLogicalExpression next token - %s\n", NameType(tokens[currentToken].type));
		printf("LogicalExpression -true\n");
		return true;
	}
	printf("LogicalExpression -false\n");
	return false;
}


bool VariableDeclaration()
{
	tempCurrentToken = currentToken;
	if (Is(Type) && Is(Identificator) && Is(Delimiter))
	{
		printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		tempCurrentToken = currentToken;
		if (Is(Type) && Assignment1())
		{
			currentToken = tempCurrentToken;
			printf("VariableDeclaration-false\n");
			return true;
		}
	}
	return false;
}

bool Assignment1()
{
	/*tempCurrentToken = currentToken;
	if (Value() && Assignment1() && ArithmeticExpressionMain() && Is(Delimiter))
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		return false;
	}*/
	return false;
}

bool Output1()
{
	tempCurrentToken = currentToken;
	printf("Output-start\n");
	if (Is(Output))
	{
		if (Is(OpenBracket))
		{
			if (Is(IOstring))
			{
				//Output1Arguments();
				if (Is(CloseBracket))
				{
					if (Is(Delimiter))
					{
						currentToken = tempCurrentToken;
						printf("Output1-true\n");
					}
					return true;
				}
			}
		}
	}
	printf("Output1-false\n");
	return false;
}

bool Output1Arguments()
{
	tempCurrentToken = currentToken;
	if (Is(Comma) && ArithmeticExpressionMain())
	{

		Output1Arguments();
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		return false;
	}
}

bool ArithmeticExpressionMain()
{
	printf("ArithmeticExpression-start\n");
	bracketCountDifference = 0;
	currentToken = tempCurrentToken;
	printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
	if (ArithmeticExpression())
	{
		if (bracketCountDifference == 0|| bracketCountDifference == -1)
		{
			printf("\ncountbracket:%d\n", bracketCountDifference);
			printf("ArithmeticExpression-true\n");
			return true;
		}
		else
		{
			printf("Error - the difference in the number of opening brackets to the closing ones: %d", tokens[tempCurrentToken].pos);
		}
	}
	else
	{
		printf("\ncountbracket:%d\n", bracketCountDifference);
		printf("ArithmeticExpression-false\n");
		printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		return false;
	}
	return false;
}

bool ArithmeticExpression()
{
	if (Is(OpenBracket))
	{
		bracketCountDifference++;
	}
	if (Value())
	{
		printf("value\n");
		if (Is(MathSign) && ArithmeticExpression())
		{
			printf("2x\n");
			currentToken = tempCurrentToken;
		}
		if (Is(CloseBracket))
		{
			printf("close b\n");
			bracketCountDifference--;
			if (bracketCountDifference < -1)
			{
				printf("Error - missing opening parenthesis before: %d", tokens[tempCurrentToken].pos);
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Value()//значение 
{
	if (Is(Identificator))
	{
		return true;
	}
	if (Is(Number))
	{
		return true;
	}
	return false;
}

bool Input1()
{
	printf("Input1-start\n");
	tempCurrentToken = currentToken;
	if (Is(Input))
	{
		if (Is(OpenBracket))
		{
			if (Is(IOstring))
			{
				if (Is(Comma))
				{
					if (Is(Identificator))
					{
						if (Is(CloseBracket))
						{
							if (Is(Delimiter))
							{
								printf("Input1-true\n");
								currentToken = tempCurrentToken;
								return true;
							}
						}
					}
				}
			}
		}
	}
	printf("Input1-false\n");
	return false;
}

bool Is(enum TokenType type)
{
	if (tokens[tempCurrentToken].type == type)
	{
		tempCurrentToken++;
		return true;
	}
	return false;
}