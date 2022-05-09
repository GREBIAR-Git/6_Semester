#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charcopy.h"

/*
struct Token
{
    char* name;
    char* value;
};


enum TokenType
{
    Type,
    Identificator,
    Number,
    IO,
    Comparison,
    MathSign,
    String,
    KeyWord,
    Delimiter
};


int currentToken = 0; int currentTokenLength = 0;
int identificatorFirst = 1;
struct Token tokens[300];
enum TokenType state = Default;
int idx = 0;

void finishToken(char* stateName)
{
    char * buffer;
    charcopy(&buffer, &str[idx - currentTokenLength], currentTokenLength);

    char buffer[currentTokenLength + 1];
    memcpy(buffer, &str[idx - currentTokenLength], currentTokenLength); // <- krasava
    buffer[currentTokenLength] = '\0';
    //strcpy(tokens[currentToken].name, stateName);
    //strcpy(tokens[currentToken].value, buffer);
    printf("\n\n%s - %s\n", stateName, buffer);
    //printf("%s - %s\n\n", tokens[currentToken].name, tokens[currentToken].value);
    currentToken++;
    currentTokenLength = 0;
}

int main()
{
    char buffer[strlen(str) + 1];
    strcpy(buffer, str);
    strcat(buffer, " ");
    str = buffer;

    while (idx < strlen(str))
    {
        switch (state)
        {
        case Default:
        {
            state = KeyWord;
            break;
        }
        case Identificator:
        {
            if (isalpha(str[idx]) || (!identificatorFirst && isdigit(str[idx])))
            {
                currentTokenLength++;
                idx++;
            }
            else if (str[idx] == ' ' || str[idx] == '\n')
            {
                if (currentTokenLength)
                {
                    finishToken("identificator");
                }
                idx++;
                state = Default;
            }
            else
            {
                state = Number;
            }
            break;
        }
        case Number:
        {
            if (IsNumber(str))
            {
                finishToken("number");
                state = Default;
            }
            else
            {
                idx++;
                state = Default;
            }
            break;
        }
        case Comparison:
        {
            if (idx + 1 < strlen(str)
                && (str[idx] == '!' && str[idx] == '='
                    || str[idx] == '=' && str[idx + 1] == '='))
            {
                idx += 2;
                currentTokenLength += 2;
                finishToken("comparison");
                state = Default;
            }
            else
            {
                state = Sign;
            }
            break;
        }
        case Sign:
        {
            if (str[idx] == '+' || str[idx] == '-')
            {
                idx++;
                currentTokenLength++;
                finishToken("sign");
                state = Default;
            }
            else
            {
                state = Identificator;
            }
            break;
        }
        case KeyWord:
        {
            if (idx + 1 < strlen(str)
                && str[idx] == 'i' && str[idx + 1] == 'f')
            {
                idx += 2;
                currentTokenLength += 2;
                finishToken("keyword");
                state = Default;
            }
            else if (idx + 5 < strlen(str)
                && str[idx] == 's' && str[idx + 1] == 'w' && str[idx + 2] == 'i'
                && str[idx + 3] == 't' && str[idx + 4] == 'c' && str[idx + 5] == 'h')
            {
                idx += 6;
                currentTokenLength += 2;
                finishToken("keyword");
                state = Default;
            }
            else
            {
                state = Comparison;
            }
            break;
        }
        }
    }
    for (int i = 0; i < currentToken; i++)
    {
        //printf("%s:%s\n",tokens[i].name,tokens[i].value);
    }
    return 0;
}


#include <ctype.h>

enum number {
    numbers,
    one_dot_numbers,
    finish_number,
    no_number
};

int IsNumber(char* str)
{
    int count_str = strlen(str);
    enum number stage = numbers;
    while (1)
    {
        switch (stage)
        {
        case numbers:
        {
            if (idx < strlen(str) && str[idx] != ' ')
            {
                if (isdigit(str[idx]))
                {
                    currentTokenLength++;
                    idx++;
                }
                else if (str[idx] == '.')
                {
                    currentTokenLength++;
                    idx++;
                    stage = one_dot_numbers;
                }
                else
                {
                    stage = no_number;
                }
            }
            else
            {
                stage = finish_number;
            }
            break;
        }
        case one_dot_numbers:
        {
            if (idx < strlen(str) && str[idx] != ' ')
            {
                if (isdigit(str[idx]))
                {
                    currentTokenLength++;
                    idx++;
                }
                else
                {
                    stage = no_number;
                }
            }
            else
            {
                stage = finish_number;
            }
            break;
        }
        case no_number:
        {
            return 0;
        }
        case finish_number:
        {
            return 1;
        }
        }
    }
}

*/