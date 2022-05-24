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
	enum NonTerminalType RootTerm = BlockTerm;

	root = *NewNodeTerminal(RootTerm);
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
		printf("\nSuccessfully (A good program without errors well done)\n");
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
		if (Is(Delimiter) || (Value(returnNode) && Is(Delimiter)))
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
	if (AssignmentOperation())
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		if (FunctionDefinition())
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
	if (Condition())
	{
		currentToken = tempCurrentToken;
		return true;
	}
	else
	{
		tempCurrentToken = currentToken;
		if (AssignmentOperation())
		{
			currentToken = tempCurrentToken;
			return true;
		}
		else 
		{
			tempCurrentToken = currentToken;
			if (InputCommand(current))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			else
			{
				tempCurrentToken = currentToken;
				if (OutputCommand())
				{
					currentToken = tempCurrentToken;
					return true;
				}
				else
				{
					if(WhileLoop())
					{
						currentToken = tempCurrentToken;
						return true;
					}
					else 
					{
						if(ForLoop())
						{
							currentToken = tempCurrentToken;
							return true;
						}
						else 
						{
							if(FunctionDefinition())
							{
								currentToken = tempCurrentToken;
								return true;
							}
							else 
							{
								if(FunctionCall(current))
								{
									currentToken = tempCurrentToken;
									return true;
								}
								else
								{
									if (ClassDefinition())
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
		if (Is(Variable))
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

							enum NonTerminalType body = BlockTerm;

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
		if(Is(Variable))
		{
			struct Node* funcNodetemp = AddChild(tokens[tempCurrentToken - 1], funcNode);
			if (Is(OpenBracket))
			{
				enum NonTerminalType param = Params;
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

								enum NonTerminalType body = BlockTerm;

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

bool ArrayDefinition(struct Node* ArrayDefinition)
{
	if (Is(OpenBraces))
	{
		struct Node* arrayDefinition = NewNode(tokens[tempCurrentToken - 1]);

		enum NonTerminalType ParamsTerm = Params;


		struct Node* paramsNode = AddChildTerminal(ParamsTerm, arrayDefinition);
		if (Arguments(paramsNode))
		{
			if (Is(CloseBraces))
			{
				AddChildNode(arrayDefinition, ArrayDefinition);
				AddChild(tokens[tempCurrentToken - 1], arrayDefinition);
				return true;
			}
		}
	}
}

bool FunctionCall(struct Node * functionCallNode)
{
	if(Is(Variable))
	{
		enum NonTerminalType funcTerm = Function;
		struct Node* functionCallTemp = NewNodeTerminal(funcTerm);
	
		struct Node* functionCallChild = AddChild(tokens[tempCurrentToken - 1], functionCallTemp);
		enum NonTerminalType params = Params;

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
	if (Is(Variable))
	{
		struct Node* argFuncTemp = NewNode(tokens[tempCurrentToken-1]);
		if (Is(Comma))
		{
			struct Node* commaNode = AddNext(tokens[tempCurrentToken - 1], argFuncTemp);
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
	if (Is(Variable))
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
	if (Value(argumentsNode))
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
	if (Value(argumentNode))
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

bool AssignmentOperation()
{
	tempCurrentToken = currentToken;
	struct Token assignment;
	assignment.value = "=";
	assignment.type = Assignment;
	struct Node* assignmentNode = NewNode(assignment);
	if (Identificator(assignmentNode))
	{
		if (Is(Assignment))
		{
			AddChildNode(assignmentNode, current);
			currentToken = tempCurrentToken;
			if (ArithmeticExpressionMain(false, assignmentNode) && Is(Delimiter))
			{
				currentToken = tempCurrentToken;
				return true;
			}
			tempCurrentToken = currentToken;
			if (InputCommand(assignmentNode))
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
			if (ArrayDefinition(assignmentNode) && Is(Delimiter))
			{
				currentToken = tempCurrentToken;
				return true;
			}
		}
	}
	return false;
}

bool OutputCommand()
{
	tempCurrentToken = currentToken;
	if (Is(Output))
	{
		struct Node* outputNode = NewNode(tokens[currentToken]);
		if (Is(OpenBracket))
		{
			if (ArithmeticExpressionMain(true, outputNode))
			{
				if (Is(Delimiter))
				{
					AddChildNode(outputNode, current);
					currentToken = tempCurrentToken;
				}
				return true;
			}
		}
	}
	return false;
}

bool InputCommand(struct Node * inputNode)
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

bool LogicalOperationMain(struct Node* arifNode)
{
	int bracketCountDifference = 0;
	if (Is(OpenBracket))
	{
		bracketCountDifference++;
	}
	if (LogicalOperation(&bracketCountDifference, arifNode))
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

bool LogicalOperation(int * bracketCountDifference, struct Node* arifNode)
{
	if (Is(OpenBracket))
	{
		(*bracketCountDifference)++;
	}
	struct Node* valueNode = NewNode(tokens[currentToken]);
	if (LogicalExpression(bracketCountDifference, valueNode))
	{
		if (Is(Logical))
		{
			struct Node* childLog = AddChild(tokens[tempCurrentToken - 1], arifNode);
			AddChildNode(valueNode->childs, childLog);
			if (LogicalOperation(bracketCountDifference, childLog))
			{
				currentToken = tempCurrentToken;
			}
			else
			{
				return false;
			}
		}
		else
		{
			AddChildNode(valueNode->childs, arifNode);
		}
		if (Is(CloseBracket))
		{
			(* bracketCountDifference)--;
		}
		return true;
	}
	return false;
}

bool LogicalExpression(int * bracketCountDifference, struct Node* arifNode)
{
	if (Is(OpenBracket))
	{
		(*bracketCountDifference)++;
	}
	if (ArithmeticExpressionLO(bracketCountDifference, arifNode))
	{
		if(Is(Comparison))
		{
			struct Node* childComp = AddChild(tokens[tempCurrentToken - 1], arifNode);
			if(LogicalExpression(bracketCountDifference, childComp))
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

bool ArithmeticExpressionLO(int * bracketCountDifference, struct Node* arifNode)
{
	int temp = tempCurrentToken;
	if (ArithmeticExpression(bracketCountDifference, arifNode))
	{
		return true;
	}
	tempCurrentToken = temp;
	return false;
}

bool ArithmeticExpressionMain(bool open, struct Node* arifNode)
{
	int temp = tempCurrentToken;
	int bracketCountDifference = open;
	if (ArithmeticExpression(&bracketCountDifference, arifNode))
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

struct Node* bracketNode;

bool ArithmeticExpression(int * bracketCount, struct Node* arifNode)
{
	if (Is(OpenBracket))
	{
		(*bracketCount)++;
	}
	struct Node* valueNode=NewNode(tokens[currentToken]);
	if (Value(valueNode))
	{
		if (Is(MathSign))
		{
			struct Node* mathNode = AddChild(tokens[tempCurrentToken-1],arifNode);
			AddChildNode(valueNode->childs, mathNode);
			if(ArithmeticExpression(bracketCount, mathNode))
			{
				currentToken = tempCurrentToken;
			}
		}
		else
		{
			AddChildNode(valueNode->childs, arifNode);
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

bool Value(struct Node* valueNode)
{
	int temp = tempCurrentToken;
	if (Is(Variable) && Is(Dot) && Is(Variable))
	{
		struct Node* temp = AddChild(tokens[tempCurrentToken - 3], valueNode);
		struct Node* forNext = AddChild(tokens[tempCurrentToken - 2], temp);
		AddNext(tokens[tempCurrentToken - 1], forNext);
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Variable) && Is(OpenBraces) )
	{
		if (ArithmeticExpressionMain(false, valueNode) && Is(CloseBraces))
		{
			return true;
		}
	}
	tempCurrentToken = temp;
	if (Is(Variable) || Is(Number) || Is(Bool))
	{
		AddChild(tokens[tempCurrentToken - 1], valueNode);
		return true;
	}
	return false;
}

bool Identificator(struct Node* identificatorNode)
{
	int temp = tempCurrentToken;
	if (Is(Variable) && Is(Dot) && Is(Variable))
	{
		struct Node* temp = AddChild(tokens[tempCurrentToken - 3], identificatorNode);
		struct Node* forNext = AddChild(tokens[tempCurrentToken - 2], temp);
		AddNext(tokens[tempCurrentToken - 1], forNext);
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Variable) && Is(OpenBraces) && ArithmeticExpressionMain(false, identificatorNode) && Is(CloseBraces))
	{
		return true;
	}
	tempCurrentToken = temp;
	if (Is(Variable))
	{
		AddChild(tokens[tempCurrentToken - 1], identificatorNode);
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
		enum NonTerminalType lo = LogicalOperationTerm;
		struct Node* loNode = AddChildTerminal(lo, ifNode);
		if (LogicalOperationMain(loNode) && Is(DoubleDot) && Is(Delimiter))
		{
			tabCount += 1;
			needTabCount = tabCount;
			
			enum NonTerminalType body = BlockTerm;

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
						
						enum NonTerminalType body = BlockTerm;

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

bool WhileLoop()
{
	if(Is(While))
	{
		struct Node* whileNode = NewNode(tokens[currentToken]);
		enum NonTerminalType lo = LogicalOperationTerm;
		struct Node* loNode = AddChildTerminal(lo, whileNode);
		if(LogicalOperationMain(loNode))
		{
			if(Is(DoubleDot))
			{
				if(Is(Delimiter))
				{
					tabCount += 1;
					needTabCount = tabCount;

					enum NonTerminalType body = BlockTerm;

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

bool ForLoop()
{
	tempCurrentToken = currentToken;
	if(Is(For))
	{
		struct Node* forNode = NewNode(tokens[currentToken]);
		if(Identificator(forNode))
		{
			if(Is(In))
			{
				if(Identificator(forNode))
				{
					if(Is(DoubleDot))
					{
						if(Is(Delimiter))
						{
							tabCount += 1;
							needTabCount = tabCount;
							
							enum NonTerminalType body = BlockTerm;

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