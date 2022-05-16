#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"

void FinishToken(enum TokenType type, int* tokenQuantity);
struct Token* Lexer(char* content,int * tokenQuantity);
bool CompareStrings(char* str);

#endif