#include "parser.h"
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
	enum TerminalType startTerm = Start;

	root = *NewNodeTerminal(startTerm);
	current = &root;
}

void ErrorRecovery()//надо вставить
{
	while (currentToken < tokenLength)
	{
		if (tokens[currentToken].type != Delimiter)
		{
			currentToken++;
		}
		else
		{
			currentToken++;
			break;
		}
	}

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
		printf("\n Successfully (A good program without errors well done)\n");
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
		struct Node* returnNode = AddChild(tokens[tempCurrentToken - 1], current);
		if (Is(Delimiter) || (Value1(returnNode) && Is(Delimiter)))
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
		if (FunctionDefinition())//нужно
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
	if (Condition())//нужно
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
			if (Input1(current))
			{
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
					if(While1())//нужно
					{
						currentToken = tempCurrentToken;
						return true;
					}
					else 
					{
						if(For1())//нужно
						{
							currentToken = tempCurrentToken;
							return true;
						}
						else 
						{
							if(FunctionDefinition())//нужно
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
									if (ClassDefinition())//нужно
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
		struct Node* funcNode = NewNode(tokens[tempCurrentToken - 1]);
		if (Is(Identificator))
		{
			struct Node* funcNodetemp = AddChild(tokens[tempCurrentToken - 1], funcNode);
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

							enum TerminalType body = Body;

							struct Node * returnCurrent = current;
							AddChildNode(funcNode, current);

							current = AddNextTerminal(body, funcNodetemp);
							if (Block())
							{
								current = returnCurrent;

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
		struct Node* funcNode = NewNode(tokens[tempCurrentToken - 1]);
		if(Is(Identificator))
		{
			struct Node* funcNodetemp = AddChild(tokens[tempCurrentToken - 1], funcNode);
			if (Is(OpenBracket))
			{
				enum TerminalType param = Params;
				struct Node * params = AddNextTerminal(param, funcNodetemp);
				if (ArgumentsFunctionDefinition(params))
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

								enum TerminalType body = Body;

								struct Node* returnCurrent = current;
								AddChildNode(funcNode, current);
								
								current = AddNextTerminal(body, funcNodetemp);

								if (Block())
								{
									current = returnCurrent;
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

bool ArrayFunctionDefinition(struct Node* arrayFunctionDefinition)
{
	if (Is(OpenBraces))
	{
		struct Node* arrayDefinition = NewNode(tokens[tempCurrentToken - 1]);

		enum TerminalType ParamsTerm = Params;


		struct Node* paramsNode = AddNextTerminal(ParamsTerm, arrayDefinition);
		if (Arguments(paramsNode))
		{
			if (Is(CloseBraces))
			{
				AddChildNode(arrayDefinition, arrayFunctionDefinition);
				AddChild(tokens[tempCurrentToken - 1], arrayFunctionDefinition);
				return true;
			}
		}
	}
}

bool FunctionCall(struct Node * functionCallNode)
{
	if(Is(Identificator))
	{
		enum TerminalType funcTerm = Function;
		struct Node* functionCallTemp = NewNodeTerminal(funcTerm);
	
		struct Node* functionCallChild = AddChild(tokens[tempCurrentToken - 1], functionCallTemp);
		enum TerminalType params = Params;

		functionCallChild = AddNextTerminal(params, functionCallChild);

		if(Is(OpenBracket))
		{
			if (Arguments(functionCallChild))
			{
				if (Is(CloseBracket))
				{
					if (Is(Delimiter))
					{
						AddChildNode(functionCallTemp, functionCallNode);
						currentToken = tempCurrentToken;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ArgumentsFunctionDefinition(struct Node * argumentsFunctionNode)
{
	if (Is(Identificator))
	{
		struct Node* argFuncTemp = NewNode(tokens[tempCurrentToken-1]);
		if (Is(Comma))
		{
			struct Node* commaNode = AddNext(tokens[tempCurrentToken - 1], argFuncTemp);
			//AddNext(Token[tempCurrentToken - 2], temp);
			//AddNext(Token[tempCurrentToken - 1], temp);
			if (ArgumentFunctionDefinition(commaNode))
			{
				AddChildNode(argFuncTemp, argumentsFunctionNode);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			AddChildNode(argFuncTemp, argumentsFunctionNode);
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool ArgumentFunctionDefinition(struct Node* argumentFunctionNode)
{
	if (Is(Identificator))
	{
		struct Node* argFuncTemp = NewNode(tokens[tempCurrentToken - 1]);
		if (Is(Comma))
		{
			struct Node* commaNode = AddNext(tokens[tempCurrentToken - 1], argFuncTemp);
			if (ArgumentFunctionDefinition(commaNode))
			{
				AddChildNode(argFuncTemp, argumentFunctionNode);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			AddChildNode(argFuncTemp, argumentFunctionNode);
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Arguments(struct Node* argumentsNode)
{
	if (Value1(argumentsNode))
	{
		if (Is(Comma))
		{
			struct Node * commaNode = AddChild(tokens[tempCurrentToken - 1], argumentsNode);
			if (Argument(commaNode))
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

bool Argument(struct Node* argumentNode)
{
	if (Value1(argumentNode))
	{
		if (Is(Comma))
		{
			struct Node * commaNode = AddChild(tokens[tempCurrentToken - 1], argumentNode);
			if (Argument(commaNode))
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
	struct Token assignment;
	assignment.value = "=";
	assignment.type = Assignment;
	struct Node* assignmentNode = NewNode(assignment);
	if (Identificator2(assignmentNode))
	{
		if (Is(Assignment))
		{
			AddChildNode(assignmentNode, current);
			currentToken = tempCurrentToken;
			if (ArithmeticExpressionMain(false) && Is(Delimiter))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (Input1(assignmentNode))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (FunctionCall(assignmentNode))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (ArrayFunctionDefinition(assignmentNode) && Is(Delimiter))
			{
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

bool Input1(struct Node * inputNode)
{
	if (Is(Input))
	{
		if (Is(OpenBracket))
		{
			if (Is(CloseBracket))
			{
				if (Is(Delimiter))
				{
					AddChild(tokens[tempCurrentToken - 4], inputNode);
					return true;
				}
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

bool Value1(struct Node* valueNode)
{
	int temp = tempCurrentToken;
	if (Is(Identificator) && Is(Dot) && Is(Identificator))
	{
		struct Node* temp = AddChild(tokens[tempCurrentToken - 3], valueNode);
		struct Node* forNext = AddChild(tokens[tempCurrentToken - 2], temp);
		AddNext(tokens[tempCurrentToken - 1], forNext);
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
		AddChild(tokens[tempCurrentToken - 1], valueNode);
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
	};
	return false;
}

bool Identificator2(struct Node* identificatorNode)
{
	int temp = tempCurrentToken;
	if (Is(Identificator) && Is(Dot) && Is(Identificator))
	{
		struct Node* temp = AddChild(tokens[tempCurrentToken - 3], identificatorNode);
		struct Node * forNext = AddChild(tokens[tempCurrentToken - 2], temp);
		AddNext(tokens[tempCurrentToken - 1], forNext);
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
		AddChild(tokens[tempCurrentToken - 1], identificatorNode);
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
		struct Node* ifNode = NewNode(tokens[currentToken]);
		enum TerminalType lo = LogicalOperationTerm;
		struct Node* loNode = AddChildTerminal(lo, ifNode);
		if (LogicalOperationMain() && Is(DoubleDot) && Is(Delimiter))//всунуть сюда loNode
		{
			tabCount += 1;
			needTabCount = tabCount;
			
			enum TerminalType body = Body;

			struct Node* returnCurrent = current;
			AddChildNode(ifNode, current);

			current = AddNextTerminal(body, loNode);

			if (Block())
			{
				current = returnCurrent;

				currentToken = tempCurrentToken;
				if (Is(Else))
				{
					struct Node* elseNode = NewNode(tokens[currentToken]);
					if(Is(DoubleDot) && Is(Delimiter))
					{
						tabCount += 1;
						needTabCount = tabCount;
						
						enum TerminalType body = Body;

						returnCurrent = current;
						AddChildNode(elseNode, current);

						current = AddChildTerminal(body, elseNode);

						if (Block())
						{
							current = returnCurrent;
							currentToken = tempCurrentToken;
						}
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
		struct Node* whileNode = NewNode(tokens[currentToken]);
		enum TerminalType lo = LogicalOperationTerm;
		struct Node* loNode = AddChildTerminal(lo, whileNode);
		if(LogicalOperationMain())//всунть loNode
		{
			if(Is(DoubleDot))
			{
				if(Is(Delimiter))
				{
					tabCount += 1;
					needTabCount = tabCount;

					enum TerminalType body = Body;

					struct Node* returnCurrent = current;
					AddChildNode(whileNode, current);

					current = AddNextTerminal(body, loNode);

					if(Block())
					{
						current = returnCurrent;
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
		struct Node* forNode = NewNode(tokens[currentToken]);
		if(Identificator2(forNode))
		{
			if(Is(In))
			{
				if(Identificator2(forNode))
				{
					if(Is(DoubleDot))
					{
						if(Is(Delimiter))
						{
							tabCount += 1;
							needTabCount = tabCount;
							
							enum TerminalType body = Body;

							struct Node* returnCurrent = current;
							AddChildNode(forNode, current);

							current = AddChildTerminal(body, forNode);

							if(Block())
							{
								current = returnCurrent;
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