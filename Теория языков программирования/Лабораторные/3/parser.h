#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "token.h"

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
void Parser(struct Token* token,int tokenQuantity);

#endif