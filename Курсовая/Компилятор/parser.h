#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "token.h"
#include "tree.h"

enum StateBlock
{
	CommonBlock,
	ClassBlock,
	DefBlock,
};

bool Block();
bool Statement();
bool StatementDef();
bool StatementClass();

bool Condition();
bool WhileLoop();
bool ForLoop();

bool OutputCommand();
bool InputCommand(struct Node* inputNode);

bool AssignmentOperation();

bool ArrayDefinition(struct Node* arrayFunctionDefinition);

bool FunctionDefinition();
bool FunctionCall(struct Node* functionCallNode);
bool Return1();

bool LogicalOperationMain(struct Node* arifNode);
bool LogicalOperation(int* bracketCountDifference, struct Node* arifNode);
bool LogicalExpression(int* bracketCountDifference, struct Node* arifNode);
bool ArithmeticExpressionLO(int* bracketCountDifference, struct Node* arifNode);

bool ArithmeticExpressionMain(bool open, struct Node* arifNode);
bool ArithmeticExpression(int* bracketCount, struct Node* arifNode);

bool ArgumentsFunctionDefinition(struct Node* argumentsFunctionNode);
bool ArgumentFunctionDefinition(struct Node* argumentFunctionNode);
bool Arguments(struct Node* argumentsNode);
bool Argument(struct Node* argumentNode);

bool ClassDefinition();

bool Value(struct Node* valueNode);
bool Identificator(struct Node* identificatorNode);

bool Is(enum TokenType type);
void Parser(struct Token* token,int tokenQuantity);

#endif