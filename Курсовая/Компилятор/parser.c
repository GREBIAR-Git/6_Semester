#include "parser.h"
#include "tree.h"
int tempCurrentToken;

int currentToken;

int bracketCountDifference;

int tokenLength;

struct Token * tokens;

void Parser(struct Token * token, int tokenQuantity)
{
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	if (Sequence())
	{
		printf("PARSER - No one error\n");
	}
	else
	{
		printf("PARSER - Error\n");
	}
	printf("\nEND_PARSER\n");
}

bool Sequence()
{
	currentToken = tempCurrentToken;
	//printf("\n\n\n\nnew Sequence\n");
	//printf("\nall tokenLength -%d", tokenLength);
	//printf("\ncurrentToken -%d", currentToken);
	if(currentToken < tokenLength)
	{
		printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	}
	//printf("\n%d", sizeof(tokens));
	if(currentToken >= tokenLength)
	{
		//printf("\nend Sequence\n");
		return true;
	}
	else if (tokens[currentToken].type == CloseBraces)
	{
		//printf("\nend Sequence\n");
		return true;
	}
	else if (Statement() && Sequence())
	{
		//printf("\nend Sequence\n");
		return true;
	}
	printf("\nerror Sequence\n");
	return false;
}

bool Statement()
{
	tempCurrentToken = currentToken;
	printf("\ntest-Condition\n");
	printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	if(Is(Delimiter))
	{
		return true;
	}
	if (Condition())
	{
		currentToken = tempCurrentToken;
		printf("Statement-true");
		return true;
	}
	else
	{
		printf("\ntest-VariableDeclaration\n");
		printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
		tempCurrentToken = currentToken;
		if (VariableDeclarationOrAssignment())
		{
			currentToken = tempCurrentToken;
			printf("Statement-true");
			return true;
		}
		else 
		{
			printf("\ntest-Input1\n");
			printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
			tempCurrentToken = currentToken;
			if (Input1()&&Is(Delimiter))
			{
				currentToken = tempCurrentToken;
				printf("Statement-true");
				return true;
			}
			else
			{
				printf("\ntest-Output1\n");
				printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
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
	return false;
}

bool Condition()
{
	printf("Condition -start");
	int tempCurrentToken1 = currentToken;
	tempCurrentToken = currentToken;

	if (Is(If) && LogicalExpression() && Is(DoubleDot) && Is(Delimiter) && Sequence())
	{
		currentToken = tempCurrentToken;
		printf("\nbefore ELSE current token - %s\n", NameType(tokens[tempCurrentToken].type));
		if (Is(Else) && Is(DoubleDot) && Is(Delimiter) && Sequence())
		{
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("ELSE END\n");
			printf("\ncurrent token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
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
	if (ArithmeticExpressionMain(false))
	{
		/*if (currentToken < tempCurrentToken)
		{
			//printf("min");
			currentToken = tempCurrentToken;
		}*/
		printf("\nbefore Comparison token - %s\n", NameType(tokens[currentToken].type));
		if(Is(Comparison))
		{
			if(LogicalExpression())
			{
				
			}
			else
			{
				printf("LogicalExpression - false\n");
				return false;
			}
			/*if (currentToken < tempCurrentToken)
			{
				currentToken = tempCurrentToken;
			}*/
		}
		printf("\nLogicalExpression next token - %s\n", NameType(tokens[currentToken].type));
		printf("LogicalExpression -true\n");
		return true;
	}
	printf("LogicalExpression - false\n");
	return false;
}

bool VariableDeclarationOrAssignment()
{
	tempCurrentToken = currentToken;
	if (Is(Identificator) && Is(Assignment) && ArithmeticExpressionMain(false) && Is(Delimiter))
	{
		printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
	printf("!!!!!!!!!!!");
	tempCurrentToken = currentToken;
	if (Is(Identificator) && Is(Assignment) && Input1() && Is(Delimiter))
	{
		printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	printf("&&&&&&&&&&&&");
	/*else
	{
		tempCurrentToken = currentToken;
		if (Is(Type) && Assignment1())
		{
			currentToken = tempCurrentToken;
			printf("VariableDeclaration-false\n");
			return true;
		}
	}*/
	printf("VariableDeclaration-false\n");
	return false;
}

//✓
bool Output1()
{
	tempCurrentToken = currentToken;
	printf("Output-start\n");
	if (Is(Output))
	{
		if (Is(OpenBracket))
		{
			if (ArithmeticExpressionMain(true))
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
	printf("Output1-false\n");
	return false;
}
//✓
bool ArithmeticExpressionMain(bool open1)
{

	int temp = tempCurrentToken;
	printf("ArithmeticExpression-start\n");
	bracketCountDifference = open1;
	printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
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
		tempCurrentToken = temp;
		printf("\ncountbracket:%d\n", bracketCountDifference);
		printf("ArithmeticExpression-false\n");
		printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		return false;
	}
	tempCurrentToken = temp;
	printf("ArithmeticExpression-false\n");
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
//✓
bool Value()
{
	int temp = tempCurrentToken;
	if (Is(Identificator)&& Is(Dot)&& Is(Identificator))
	{
		return true;
	}
	else if (Is(Identificator) && Is(OpenBraces) && ArithmeticExpressionMain(false) && Is(CloseBraces))
	{
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Identificator) || Is(Number) || Is(Bool))
	{
		return true;
	}
	return false;
}
//✓
bool Identificator1()
{
	int temp = tempCurrentToken;
	if (Is(Identificator) && Is(Dot) && Is(Identificator))
	{
		return true;
	}
	else if (Is(Identificator) && Is(OpenBraces) && ArithmeticExpressionMain(false) && Is(CloseBraces))
	{
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Identificator))
	{
		return true;
	}
	return false;
}
//✓
bool Input1()
{
	printf("Input1-start\n");
	if (Is(Input))
	{
		if (Is(OpenBracket))
		{
			if (Is(CloseBracket))
			{
				printf("Input1-true\n");
				return true;
			}
		}
	}
	printf("Input1-false\n");
	return false;
}
//✓
bool Is(enum TokenType type)
{
	if (tokens[tempCurrentToken].type == type)
	{
		tempCurrentToken++;
		return true;
	}
	return false;
}