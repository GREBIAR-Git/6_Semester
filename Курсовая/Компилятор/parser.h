#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "token.h"

enum StateSequence
{
	CommonSequence,
	ClassSequence,
	DefSequence,
};

bool Sequence();
bool Statement();
bool StatementDef();
bool StatementClass();

bool Condition();
bool While1();
bool For1();

bool Output1();
bool Input1();

bool VariableDeclarationOrAssignment();

bool FunctionDefinition();
bool FunctionCall();

bool LogicalOperation();
bool LogicalExpression();

bool ArithmeticExpressionMain(bool open1);
bool ArithmeticExpression(int* bracketCount);

bool ArgumentsFunctionDefinition();
bool Arguments();
bool Return1();

bool ClassDefinition();

bool Value();
bool Identificator1();

bool Is(enum TokenType type);
void Parser(struct Token* token,int tokenQuantity);

#endif