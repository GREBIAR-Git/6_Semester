#include "parser.h"
#include "tree.h"
int tempCurrentToken;

int currentToken;

int tokenLength;

int tabCount = 0;

int needTabCount = 0;

struct Token * tokens;

enum StateBlock sequence = CommonBlock;

enum StateBlock prevBlock = CommonBlock;

struct Node root;

struct Node * current;

void InitFirstTree()
{
	struct Token tokenMain;
	tokenMain.value = "Main";
	tokenMain.type = Start;
	root = *NewNode(tokenMain);
	current = &root;
}

void Parser(struct Token * token, int tokenQuantity)
{
	InitFirstTree();

	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	if (Block())
	{
		printf("\nSuccessfully\n");
	}
	else
	{
		printf("\nSyntax error on the line: %d\n",tokens[currentToken].line+1);
	}
	Print2D(&root);
	printf("\nEND_PARSER\n");
}

bool Block()
{
	currentToken = tempCurrentToken;
	if(currentToken < tokenLength)
	{
		//printf("\nnew Block token - %s #%d\n", NameType(tokens[currentToken].type), currentToken);
	}
	if(currentToken >= tokenLength)
	{
		tabCount -= 1;
		return true;
	}
	else if (tokens[currentToken].type == END)
	{
		tabCount -= 1;
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
				current = current->parent;
				tempCurrentToken = currentToken;
				tabCount -= 1;
				return true;
			}
		}

		currentToken = tempCurrentToken;
		if (sequence == CommonBlock)
		{
			if (Statement() && Block())
			{
				sequence = CommonBlock;
				needTabCount = 0;
				return true;
			}
		}
		else if (sequence == ClassBlock)
		{
			if (StatementClass() && Block())
			{
				prevBlock = CommonBlock;
				sequence = CommonBlock;
				needTabCount = 0;
				return true;
			}
		}
		else if (sequence == DefBlock)
		{
			if (StatementDef() && Block())
			{
				sequence = prevBlock;
				needTabCount = 0;
				return true;
			}
		}
		return false;

	}
	printf("\nerror Block\n");
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
	if (Is(Delimiter))
	{
		return true;
	}
	if (VariableDeclarationOrAssignment())
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		if (FunctionDefinition())//�����
		{
			currentToken = tempCurrentToken;
			return true;
		}
	}
}

bool Statement()
{
	tempCurrentToken = currentToken;
	if(Is(Delimiter))
	{
		return true;
	}
	if (Condition())//�����
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		tempCurrentToken = currentToken;
		if (VariableDeclarationOrAssignment())
		{
			currentToken = tempCurrentToken;
			return true;
		}
		else 
		{
			tempCurrentToken = currentToken;
			if (Input1()&&Is(Delimiter))
			{
				AddChild(tokens[currentToken], current);
				currentToken = tempCurrentToken;
				return true;
			}
			else
			{
				tempCurrentToken = currentToken;
				if (Output1())
				{
					currentToken = tempCurrentToken;
					return true;
				}
				else
				{
					if(While1())//�����
					{
						currentToken = tempCurrentToken;
						return true;
					}
					else 
					{
						if(For1())//�����
						{
							currentToken = tempCurrentToken;
							return true;
						}
						else 
						{
							if(FunctionDefinition())//�����
							{
								currentToken = tempCurrentToken;
								return true;
							}
							else 
							{
								if(FunctionCall())
								{
									currentToken = tempCurrentToken;
									return true;
								}
								else
								{
									if (ClassDefinition())//�����
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
							sequence = ClassBlock;

							current = AddChild(tokens[currentToken], current);

							if (Block())
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

bool ArrayFunctionDefinition()
{
	if(Is(OpenBraces))
	{
		if(Arguments())
		{
			if(Is(CloseBraces))
			{
				return true;
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
								prevBlock = sequence;
								sequence = DefBlock;
								current = AddChild(tokens[currentToken], current);
								//printf("\n!2!%s!2!\n", NameType(root.data.type));
								if (Block())
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
						AddChild(tokens[currentToken], current);
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
			if (ArgumentFunctionDefinition())
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

bool ArgumentFunctionDefinition()
{
	if (Is(Identificator))
	{
		if (Is(Comma))
		{
			if (ArgumentFunctionDefinition())
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
		return false;
	}
}

bool Arguments()
{
	if (Value())
	{
		if (Is(Comma))
		{
			if (Argument())
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

bool Argument()
{
	if (Value())
	{
		if (Is(Comma))
		{
			if (Argument())
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
		return false;
	}
}

bool VariableDeclarationOrAssignment()
{
	tempCurrentToken = currentToken;
	
	if (Identificator1())
	{
		struct Token* token = &tokens[tempCurrentToken];
		if (Is(Assignment))
		{
			currentToken = tempCurrentToken;
			if (ArithmeticExpressionMain(false) && Is(Delimiter))
			{
				AddChild(*token, current);
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (Input1() && Is(Delimiter))
			{
				AddChild(*token, current);
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (FunctionCall())
			{
				AddChild(*token, current);
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (ArrayFunctionDefinition() && Is(Delimiter))
			{
				AddChild(*token, current);
				currentToken = tempCurrentToken;
				return true;
			}
		}
	}
	return false;
}

bool Output1()
{
	tempCurrentToken = currentToken;
	if (Is(Output))
	{
		struct Token* token = &tokens[currentToken];
		if (Is(OpenBracket))
		{
			if (ArithmeticExpressionMain(true))
			{
				if (Is(Delimiter))
				{
					AddChild(*token, current);
					currentToken = tempCurrentToken;
				}
				return true;
			}
		}
	}
	return false;
}

bool Input1()
{
	if (Is(Input))
	{
		if (Is(OpenBracket))
		{
			if (Is(CloseBracket))
			{
				return true;
			}
		}
	}
	return false;
}

bool LogicalOperationMain()
{
	int bracketCountDifference = 0;
	if (Is(OpenBracket))
	{
		bracketCountDifference++;
	}
	if (LogicalOperation(&bracketCountDifference))
	{
		if (Is(CloseBracket))
		{
			bracketCountDifference--;
		}
		if (bracketCountDifference == 0)
		{
			return true;
		}
		else
		{
			printf("\ncountbracket:! %d !\n", bracketCountDifference);
			printf("\nError - the difference in the number of opening brackets to the closing ones: %d\n", tokens[tempCurrentToken].pos);
		}
	}
	return false;
}

bool LogicalOperation(int * bracketCountDifference)
{
	if (Is(OpenBracket))
	{
		(*bracketCountDifference)++;
	}
	if (LogicalExpression(bracketCountDifference))
	{
		if (Is(Logical) && LogicalOperation(bracketCountDifference))
		{
			currentToken = tempCurrentToken;
		}
		if (Is(CloseBracket))
		{
			(* bracketCountDifference)--;
		}
		return true;
	}
	return false;
}

bool LogicalExpression(int * bracketCountDifference)
{
	if (Is(OpenBracket))
	{
		(*bracketCountDifference)++;
	}
	if (ArithmeticExpressionLO(bracketCountDifference))
	{
		if(Is(Comparison))
		{
			if(LogicalExpression(bracketCountDifference))
			{
				currentToken = tempCurrentToken;
			}
			else
			{
				return false;
			}
		}
		if (Is(CloseBracket))
		{
			(*bracketCountDifference)--;
		}
		return true;
	}
	return false;
}

bool ArithmeticExpressionLO(int * bracketCountDifference)
{
	int temp = tempCurrentToken;
	if (ArithmeticExpression(bracketCountDifference))
	{
		return true;
	}
	tempCurrentToken = temp;
	return false;
}

bool ArithmeticExpressionMain(bool open1)
{
	int temp = tempCurrentToken;
	int bracketCountDifference = open1;
	if (ArithmeticExpression(&bracketCountDifference))
	{
		if (bracketCountDifference == 0)
		{
			return true;
		}
		else
		{
			printf("\ncountbracket:%d\n", bracketCountDifference);
			printf("\nError - the difference in the number of opening brackets to the closing ones: %d\n", tokens[tempCurrentToken].pos);
		}
	}
	tempCurrentToken = temp;
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
		if (Is(MathSign) && ArithmeticExpression(bracketCount))
		{
			currentToken = tempCurrentToken;
		}
		if (Is(CloseBracket))
		{
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

bool Condition()
{
	int tempCurrentToken1 = currentToken;
	tempCurrentToken = currentToken;

	if (Is(If))
	{
		struct Token* token = &tokens[currentToken];
		if (LogicalOperationMain() && Is(DoubleDot) && Is(Delimiter))
		{
			tabCount += 1;
			needTabCount = tabCount;
			current = AddChild(*token, current);
			if (Block())
			{
				token = &tokens[currentToken];
				currentToken = tempCurrentToken;
				if (Is(Else) && Is(DoubleDot) && Is(Delimiter))
				{
					tabCount += 1;
					needTabCount = tabCount;
					current = AddChild(*token, current);
					if (Block())
					{
						currentToken = tempCurrentToken;
					}
				}
				return true;
			}
		}
	}
	else
	{
		currentToken = tempCurrentToken1;
		return false;
	}
}

bool While1()
{
	if(Is(While))
	{
		struct Token* token = &tokens[currentToken];
		if(LogicalOperationMain())
		{
			if(Is(DoubleDot))
			{
				if(Is(Delimiter))
				{
					tabCount += 1;
					needTabCount = tabCount;
					current = AddChild(*token, current);
					if(Block())
					{
						currentToken = tempCurrentToken;
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
							current = AddChild(tokens[currentToken], current);
							//printf("\n!2!%s!2!\n", NameType(root.data.type));
							if(Block())
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

bool Is(enum TokenType type)
{
	if (tokens[tempCurrentToken].type == type)
	{
		tempCurrentToken++;
		return true;
	}
	return false;
}