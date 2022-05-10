#include <stdbool.h>
#include "token.h"
int tempCurrentToken;

int currentToken;

int bracketCountDifference;// разница открытых и закрытых скобок 

bool Sequence();
bool Statement();
bool Condition();
bool LogicalExpression();
bool VariableDeclaration();
bool Assignment1();
bool Output1();
bool Output1Arguments();
bool ArithmeticExpressionMain();
bool ArithmeticExpression();
bool Value();
bool Input1();
bool Is(enum TokenType type);


void Parser()
{
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
	if(currentToken >= (sizeof(tokens) / sizeof(struct Token)))
	{
		return true;
	}
	else if (Statement() && Sequence())
	{
		return true;
	}
	return false;
}

bool Statement()
{
	tempCurrentToken = currentToken;
	printf("\ntest-Condition\n");
	if (Condition())
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		printf("\ntest-VariableDeclaration\n");
		tempCurrentToken = currentToken;
		if (VariableDeclaration())
		{
			currentToken = tempCurrentToken;
			return true;
		}
		else 
		{
			printf("\ntest-Assignment1\n");
			tempCurrentToken = currentToken;
			if (Assignment1())
			{
				currentToken = tempCurrentToken;
				return true;
			}
			else
			{
				printf("\ntest-Input1\n");
				tempCurrentToken = currentToken;
				if (Input1())
				{
					currentToken = tempCurrentToken;
					return true;
				}
				else
				{
					printf("\ntest-Output1\n");
					tempCurrentToken = currentToken;
					if (Output1())
					{
						currentToken = tempCurrentToken;
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

	if (Is(IF) && Is(OpenBracket) && LogicalExpression() && Is(CloseBracket) && Is(OpenBraces) && Sequence() && Is(CloseBraces))
	{
		currentToken = tempCurrentToken;
		if (Is(Else) && Sequence())
		{
			currentToken = tempCurrentToken;
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
	if (ArithmeticExpression())
	{
		if (bracketCountDifference == 0)
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
		if (Is(MathSign) && ArithmeticExpression())
		{
			currentToken = tempCurrentToken;
		}
		if (Is(CloseBracket))
		{
			bracketCountDifference--;
			if (bracketCountDifference < 0)
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
	tempCurrentToken = currentToken;
	if (Is(Identificator)
	{
		currentToken = tempCurrentToken;
			return true;
	}
	tempCurrentToken = currentToken;
	if (Is(Number)))
	{
		currentToken = tempCurrentToken;
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