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

bool Identificator2(struct Node* identificatorNode);

bool Value1(struct Node* valueNode);

bool Block();
bool Statement();
bool StatementDef();
bool StatementClass();

bool Condition();
bool While1();
bool For1();

bool Output1();
bool Input1();

bool VariableDeclarationOrAssignment();

bool ArrayFunctionDefinition();

bool FunctionDefinition();
bool FunctionCall();

bool LogicalOperationMain();
bool LogicalOperation(int* bracketCountDifference, struct Node* arifNode);
bool LogicalExpression(int* bracketCountDifference, struct Node* arifNode);
bool ArithmeticExpressionLO(int* bracketCountDifference, struct Node* arifNode);

bool ArithmeticExpressionMain(bool open1, struct Node* arifNode);
bool ArithmeticExpression(int* bracketCount, struct Node* arifNode);

bool ArgumentsFunctionDefinition();
bool ArgumentFunctionDefinition();
bool Arguments();
bool Argument();
bool Return1();

bool ClassDefinition();

bool Value();
bool Identificator1();

bool Is(enum TokenType type);
void Parser(struct Token* token,int tokenQuantity);

#endif