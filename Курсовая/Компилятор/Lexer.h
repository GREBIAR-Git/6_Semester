#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"

enum number {
    numbers,
    one_dot_numbers,
    finish_number,
    no_number
};

bool IsNumber(char* str);
void FinishToken(enum TokenType type, int* tokenQuantity);
struct Token* Lexer(char* content,int * tokenQuantity);
bool CompareStrings(char* str);
bool CompareStringCheck(char* str);

#endif