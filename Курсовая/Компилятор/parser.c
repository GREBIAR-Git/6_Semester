#include "parser.h"
#include "tree.h"
int tempCurrentToken;

int currentToken;

int tokenLength;

int tabCount = 0;

int needTabCount = 0;

struct Token * tokens;

enum StateSequence sequence = CommonSequence;

enum StateSequence prevSequence = CommonSequence;

//скобки в logical

void Parser(struct Token * token, int tokenQuantity)
{
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	if (Sequence())
	{
		printf("\nSuccessfully\n");
	}
	else
	{
		printf("\nSyntax error on the line: %d\n",tokens[currentToken].line+1);
	}
	printf("\nEND_PARSER\n");
}

bool Sequence()
{
	currentToken = tempCurrentToken;
	if(currentToken < tokenLength)
	{
		//printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	}
	if(currentToken >= tokenLength)
	{
		tabCount -= 1;
		printf("\nEND Sequence\n");
		return true;
	}
	else if (tokens[currentToken].type == END)
	{
		tabCount -= 1;
		//printf("\nEND Sequence\n");
		return true;
	}
	else 
	{
		tempCurrentToken = currentToken;
		if (needTabCount != 0)
		{
			int currentTab = 0;
			while (Is(Tab))
			{
				currentTab += 1;
			}
			tempCurrentToken = currentToken;
			if (currentTab != needTabCount)
			{
				if (currentTab > needTabCount)
				{
					printf("\nError - incorrect number of tabs(a lot of tabs)\n");
				}
				else
				{
					printf("\nError - incorrect number of tabs(small number of tabs)\n");
				}
				return false;
			}
			needTabCount = 0;
		}
		for (int i = 0; i < tabCount; i++)
		{
			if (!Is(Tab))
			{
				//printf("\nend Sequence\n");
				tempCurrentToken = currentToken;
				tabCount -= 1;
				return true;
			}
			//printf("\ntrue\n");
		}

		currentToken = tempCurrentToken;
		if (sequence == CommonSequence)
		{
			//printf("\n\n\n!!!!!!!Statement!!!!!!!\n\n\n");
			if (Statement() && Sequence())
			{
				sequence = CommonSequence;
				needTabCount = 0;
				return true;
			}
		}
		else if (sequence == ClassSequence)
		{
			//printf("\n\n\n!!!!!!!Class!!!!!!!\n\n\n");
			if (StatementClass() && Sequence())
			{
				prevSequence = CommonSequence;
				sequence = CommonSequence;
				needTabCount = 0;
				return true;
			}
		}
		else if (sequence == DefSequence)
		{
			//printf("\n\n\n!!!!!!!Def!!!!!!!\n\n\n");

			if (StatementDef() && Sequence())
			{
				sequence = prevSequence;
				needTabCount = 0;
				return true;
			}
		}
		return false;

	}
	printf("\nerror Sequence\n");
	return false;
}

bool StatementDef()
{
	if (Statement())
	{
		return true;
	}
	else
	{
		if (Return1())
		{
			currentToken = tempCurrentToken;
			//printf("Return1-true");
			return true;
		}
		return false;
	}
}

bool Return1()
{
	if (Is(Return))
	{
		if (Is(Delimiter) || (Value() && Is(Delimiter)))
		{
			return true;
		}
	}
	return false;
}

bool StatementClass()
{
	tempCurrentToken = currentToken;
	//printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	if (Is(Delimiter))
	{
		return true;
	}
	if (VariableDeclarationOrAssignment())
	{
		currentToken = tempCurrentToken;
		//printf("\nVariableDeclarationOrAssignment-true\n");
		return true;
	}
	else
	{
		if (FunctionDefinition())
		{
			currentToken = tempCurrentToken;
			//printf("\nFunctionDefinition-true\n");
			return true;
		}
	}
}

bool Statement()
{
	tempCurrentToken = currentToken;
	//printf("\nnew Sequence token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	if(Is(Delimiter))
	{
		return true;
	}
	//printf("\ntest-Condition\n");
	if (Condition())
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		//printf("\ntest-VariableDeclaration\n");
		tempCurrentToken = currentToken;
		if (VariableDeclarationOrAssignment())
		{
			currentToken = tempCurrentToken;
			return true;
		}
		else 
		{
			//printf("\ntest-Input1\n");
			tempCurrentToken = currentToken;
			if (Input1()&&Is(Delimiter))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			else
			{
				//printf("\ntest-Output1\n");
				tempCurrentToken = currentToken;
				if (Output1())
				{
					currentToken = tempCurrentToken;
					return true;
				}
				else
				{
					if(While1())
					{
						currentToken = tempCurrentToken;
						return true;
					}
					else 
					{
						if(For1())
						{
							currentToken = tempCurrentToken;
							return true;
						}
						else 
						{
							if(FunctionDefinition())
							{
								currentToken = tempCurrentToken;
								//printf("\nFunctionDefinition-true\n");
								return true;
							}
							else 
							{
								if(FunctionCall())
								{
									currentToken = tempCurrentToken;
									//printf("\nFunctionCall-true\n");
									return true;
								}
								else
								{
									if (ClassDefinition())
									{
										currentToken = tempCurrentToken;
										//printf("\nClassDefinition-true\n");
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool ClassDefinition()
{
	if (Is(Class))
	{
		if (Is(Identificator))
		{
			if (Is(OpenBracket))
			{
				if (Is(CloseBracket))
				{
					if (Is(DoubleDot))
					{
						if (Is(Delimiter))
						{
							tabCount += 1;
							needTabCount = tabCount;
							sequence = ClassSequence;
							if (Sequence())
							{
								currentToken = tempCurrentToken;
								return true;
							}
						}
					}
				}
			}
		}
	}
}

bool FunctionDefinition()
{
	tempCurrentToken = currentToken;
	if(Is(Def))
	{
		if(Is(Identificator))
		{
			if (Is(OpenBracket))
			{
				if (ArgumentsFunctionDefinition())
				{
					if (Is(CloseBracket))
					{
						if (Is(DoubleDot))
						{
							if (Is(Delimiter))
							{
								tabCount += 1;
								needTabCount = tabCount;
								prevSequence = sequence;
								sequence = DefSequence;
								if (Sequence())
								{
									currentToken = tempCurrentToken;
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool FunctionCall()
{
	if(Is(Identificator))
	{
		if(Is(OpenBracket))
		{
			if (Arguments())
			{
				if (Is(CloseBracket))
				{
					if (Is(Delimiter))
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

bool ArgumentsFunctionDefinition()
{
	if (Is(Identificator))
	{
		if (Is(Comma))
		{
			if (ArgumentsFunctionDefinition())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool Arguments()
{
	if (Identificator1())
	{
		if (Is(Comma))
		{
			if (Arguments())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool Condition()
{
	int tempCurrentToken1 = currentToken;
	tempCurrentToken = currentToken;

	if (Is(If) && LogicalOperation() && Is(DoubleDot) && Is(Delimiter))
	{
		tabCount += 1;
		needTabCount = tabCount;
		if (Sequence())
		{
			currentToken = tempCurrentToken;
			//printf("\nbefore ELSE current token - %s\n", NameType(tokens[tempCurrentToken].type));
			if (Is(Else) && Is(DoubleDot) && Is(Delimiter) && Sequence())
			{
				//printf("ELSE END\n");
				//printf("\ncurrent token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
				currentToken = tempCurrentToken;
			}
			//printf("Condition-true");
			return true;
		}
	}
	else
	{
		currentToken = tempCurrentToken1;
		//printf("Condition-false");
		return false;
	}
}

//пофиксить скобки до
bool LogicalExpression()
{
	//printf("\nLogicalExpression -start\n");
	//printf("\n#%dcurrent token - %s\n", tempCurrentToken, NameType(tokens[tempCurrentToken].type));
	if (ArithmeticExpressionMain(false))
	{
		//printf("\nbefore Comparison token - %s\n", NameType(tokens[currentToken].type));
		if(Is(Comparison))
		{
			if(LogicalExpression())
			{
				currentToken = tempCurrentToken;
			}
			else
			{
				//printf("LogicalExpression - false\n");
				return false;
			}
		}
		//printf("LogicalExpression -true\n");
		return true;
	}
	//printf("LogicalExpression - false\n");
	return false;
}

bool LogicalOperation()
{
	//printf("\nLogicalOperation\n");
	//printf("\nbefore LogicalOperation - %s\n", NameType(tokens[currentToken].type));
	if(LogicalExpression())
	{
		//printf("\nafte before LogicalOperation - %s\n", NameType(tokens[currentToken].type));
		if(Is(Logical)&&LogicalExpression())
		{
			//printf("\nafter after LogicalOperation - %s\n", NameType(tokens[currentToken].type));
			currentToken = tempCurrentToken; 
		}
		//printf("\nLogicalOperation-true\n");
		return true;
	}
	//printf("\nLogicalOperation-false\n");
	return false;
}

bool VariableDeclarationOrAssignment()
{
	tempCurrentToken = currentToken;
	if (Identificator1() && Is(Assignment) && ArithmeticExpressionMain(false) && Is(Delimiter))
	{
		//printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	tempCurrentToken = currentToken;
	if (Identificator1() && Is(Assignment) && Input1() && Is(Delimiter))
	{
		//printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	tempCurrentToken = currentToken;
	if(Identificator1() && Is(Assignment) && FunctionCall())
	{
		//printf("VariableDeclaration-true\n");
		currentToken = tempCurrentToken;
		return true;
	}
	//printf("VariableDeclaration-false\n");
	return false;
}

bool Output1()
{
	tempCurrentToken = currentToken;
	if (Is(Output))
	{
		if (Is(OpenBracket))
		{
			if (ArithmeticExpressionMain(true))
			{
				if (Is(Delimiter))
				{
					currentToken = tempCurrentToken;
					//printf("Output1-true\n");
				}
				return true;
			}
		}
	}
	//printf("Output1-false\n");
	return false;
}

bool ArithmeticExpressionMain(bool open1)
{

	int temp = tempCurrentToken;
	//printf("ArithmeticExpression-start\n");
	int bracketCountDifference = open1;
	//printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
	if (ArithmeticExpression(&bracketCountDifference))
	{
		if (bracketCountDifference == 0)
		{
			//printf("\ncountbracket:%d\n", bracketCountDifference);
			//printf("ArithmeticExpression-true\n");
			return true;
		}
		else
		{
			printf("\ncountbracket:%d\n", bracketCountDifference);
			printf("\nError - the difference in the number of opening brackets to the closing ones: %d\n", tokens[tempCurrentToken].pos);
		}
	}
	else
	{
		tempCurrentToken = temp;
		//printf("\ncountbracket:%d\n", bracketCountDifference);
		//printf("ArithmeticExpression-false\n");
		//printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		return false;
	}
	tempCurrentToken = temp;
	//printf("ArithmeticExpression-false\n");
	return false;
}

bool ArithmeticExpression(int * bracketCount)
{
	if (Is(OpenBracket))
	{
		(*bracketCount)++;
	}
	if (Value())
	{
		//printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		if (Is(MathSign) && ArithmeticExpression(bracketCount))
		{
			currentToken = tempCurrentToken;
		}
		//printf("\ncurrent token - %s\n", NameType(tokens[tempCurrentToken].type));
		if (Is(CloseBracket))
		{
			//printf("close");
			(*bracketCount)--;
			if ((*bracketCount) < 0)
			{
				printf("Error - missing opening parenthesis before: %d", tokens[tempCurrentToken].pos);
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Value()
{
	int temp = tempCurrentToken;
	if (Is(Identificator)&& Is(Dot)&& Is(Identificator))
	{
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Identificator) && Is(OpenBraces) && ArithmeticExpressionMain(false) && Is(CloseBraces))
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

bool Identificator1()
{
	int temp = tempCurrentToken;
	if (Is(Identificator) && Is(Dot) && Is(Identificator))
	{
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Identificator) && Is(OpenBraces) && ArithmeticExpressionMain(false) && Is(CloseBraces))
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

bool Input1()
{
	//printf("Input1-start\n");
	if (Is(Input))
	{
		if (Is(OpenBracket))
		{
			if (Is(CloseBracket))
			{
				//printf("Input1-true\n");
				return true;
			}
		}
	}
	//printf("Input1-false\n");
	return false;
}

bool While1()
{
	//printf("while start");
	if(Is(While))
	{
		if(LogicalOperation())
		{
			if(Is(DoubleDot))
			{
				if(Is(Delimiter))
				{
					tabCount += 1;
					needTabCount = tabCount;
					if(Sequence())
					{
						currentToken = tempCurrentToken;
						//printf("while true");
						return true;
					}
				}
			}
		}
	}
}

bool For1()
{
	tempCurrentToken = currentToken;
	//printf("for start");
	if(Is(For))
	{
		if(Identificator1())
		{
			if(Is(In))
			{
				if(Identificator1())
				{
					if(Is(DoubleDot))
					{
						if(Is(Delimiter))
						{
							tabCount += 1;
							needTabCount = tabCount;
							if(Sequence())
							{
								currentToken = tempCurrentToken;
								//printf("for true");
								return true;
							}
						}
					}
				}
			}
		}
	}
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