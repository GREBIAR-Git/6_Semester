#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "charcopy.h"

enum TokenType
{
    Delimiter,
    Comma,
    Comparison,
    Assignment,
    MathSign,
    IOstring,
    KeyWord,
    IO,
    Type,
    Identificator,
    Number,
    Error,
};

struct Token
{
    char* name;
    char* value;
    int pos;
};

enum number {
    numbers,
    one_dot_numbers,
    finish_number,
    no_number
};

bool startNumber = false;


char* NameType(enum TokenType type)
{
    switch (type)
    {
    case Delimiter:
        return "Delimiter";
        break;
    case Comma:
        return "Comma";
    case Comparison:
        return "Comparison";
        break;
    case Assignment:
        return "Assignment";
    case MathSign:
        return "MathSign";
        break;
    case IOstring:
        return "IOstring";
        break;
    case KeyWord:
        return "KeyWord";
        break;
    case IO:
        return "IO";
        break;
    case Type:
        return "Type";
        break;
    case Identificator:
        return "Identificator";
        break;
    case Number:
        return "Number";
        break;
    default:
        break;
    }
}



char * fileContent;

int currentToken = 0; 
int currentTokenLength = 0;
bool identificatorFirst = true;
struct Token tokens[300];
enum TokenType state = KeyWord;
int idx = 0;

int IsNumber(char* str)
{
    int count_str = strlen(str);
    enum number stage = numbers;
    startNumber = false;
    while (1)
    {
        switch (stage)
        {
        case numbers:
        {
            if (idx < strlen(str))
            {
                if (isdigit(str[idx]))
                {
                    startNumber = true;
                    currentTokenLength++;
                    idx++;
                }
                else if (str[idx] == '.' && startNumber)
                {

                    currentTokenLength++;
                    idx++;
                    stage = one_dot_numbers;
                }
                else if ((str[idx] != ' ' || str[idx] != '\n' || str[idx] != ';') && startNumber)
                {
                    stage = finish_number;
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
            if (idx < strlen(str) && (str[idx] != ' ' || str[idx] != '\n' || str[idx] != ';'))
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

void finishToken(char * type)
{
    tokens[currentToken].name = type;
    char buffer[currentTokenLength + 1];
    memcpy(buffer, &fileContent[idx - currentTokenLength], currentTokenLength);
    buffer[currentTokenLength] = '\0';
    tokens[currentToken].value = malloc(strlen(buffer) + 1);
    strcpy(tokens[currentToken].value, buffer);
    currentToken++;
    currentTokenLength = 0;
}

int lexer()
{
    int io_started = 0;

    while (idx < strlen(fileContent))
    {
        switch (state)
        {
        case Delimiter:
        {
            if (fileContent[idx] == ';')
            {
                idx++;
                currentTokenLength++;
                finishToken("delimiter");
                state = Delimiter;
            }
            else
            {
                state = Comma;
            }
            break;
        }
        case Comma:
        {
            if (fileContent[idx] == ',')
            {
                idx++;
                currentTokenLength++;
                finishToken("comma");
                state = Delimiter;
            }
            else
            {
                state = Comparison;
            }
            break;
        }
        case Comparison:
        {
            if (idx + 1 < strlen(fileContent)
                && (fileContent[idx] == '!' && fileContent[idx + 1] == '='
                    || fileContent[idx] == '=' && fileContent[idx + 1] == '='
                    || fileContent[idx] == '<' && fileContent[idx + 1] == '='
                    || fileContent[idx] == '>' && fileContent[idx + 1] == '='))
            {
                idx += 2;
                currentTokenLength += 2;
                finishToken("comparison");
                state = Delimiter;
            }
            else if (fileContent[idx] == '<' || fileContent[idx] == '>')
            {
                idx++;
                currentTokenLength++;
                finishToken("comparison");
                state = KeyWord;
            }
            else
            {
                state = Assignment;
            }
            break;
        }
        case Assignment:
        {
            if (fileContent[idx] == '=')
            {
                idx++;
                currentTokenLength++;
                finishToken("assignment");
                state = Delimiter;
            }
            else
            {
                state = MathSign;
            }
            break;
        }
        case MathSign:
        {
            if (fileContent[idx] == '+' || fileContent[idx] == '-' || fileContent[idx] == '*' || fileContent[idx] == '/' || fileContent[idx] == '%' || fileContent[idx] == '(' || fileContent[idx] == ')')
            {
                idx++;
                currentTokenLength++;
                finishToken("sign");
                state = Delimiter;
            }
            else
            {
                state = IOstring;
            }
            break;
        }
        case IOstring:
        {
            if (fileContent[idx] == '"' && !io_started)
            {
                io_started = 1;
                currentTokenLength++;
                idx++;
            }
            else if (fileContent[idx] == '"' && io_started)
            {
                io_started = 0;
                idx++;
                currentTokenLength++;
                if (currentTokenLength)
                {
                    finishToken("identificator");
                }
                state = Delimiter;
            }
            else if (io_started)
            {
                currentTokenLength++;
                idx++;
            }
            else
            {
                state = KeyWord;
            }
            break;
        }
        case KeyWord:
        {
            if (idx + 1 < strlen(fileContent)
                && fileContent[idx] == 'i' && fileContent[idx + 1] == 'f')
            {
                idx += 2;
                currentTokenLength += 2;
                finishToken("keyword");
                state = Delimiter;
            }
            else if (idx + 5 < strlen(fileContent)
                && fileContent[idx] == 's' && fileContent[idx + 1] == 'w' && fileContent[idx + 2] == 'i'
                && fileContent[idx + 3] == 't' && fileContent[idx + 4] == 'c' && fileContent[idx + 5] == 'h')
            {
                idx += 6;
                currentTokenLength += 6;
                finishToken("keyword");
                state = Delimiter;
            }
            else
            {
                state = IO;
            }
            break;
        }
        case IO:
        {
            if (idx + 4 < strlen(fileContent)
                && fileContent[idx] == 's' && fileContent[idx + 1] == 'c' && fileContent[idx + 2] == 'a' && fileContent[idx + 3] == 'n' && fileContent[idx + 4] == 'f')
            {
                idx += 5;
                currentTokenLength += 5;
                finishToken("io");
                state = Delimiter;
            }
            else if (idx + 5 < strlen(fileContent)
                && fileContent[idx] == 'p' && fileContent[idx + 1] == 'r' && fileContent[idx + 2] == 'i'
                && fileContent[idx + 3] == 'n' && fileContent[idx + 4] == 't' && fileContent[idx + 5] == 'f')
            {
                idx += 6;
                currentTokenLength += 6;
                finishToken("io");
                state = Delimiter;
            }
            else
            {
                state = Type;
            }
            break;
        }
        case Type:
        {
            if (idx + 4 < strlen(fileContent)
                && fileContent[idx] == 'f' && fileContent[idx + 1] == 'l' && fileContent[idx + 2] == 'o' && fileContent[idx + 3] == 'a' && fileContent[idx + 4] == 't')
            {
                idx += 5;
                currentTokenLength += 5;
                finishToken("type");
                state = Delimiter;
            }
            else if (idx + 2 < strlen(fileContent)
                && fileContent[idx] == 'i' && fileContent[idx + 1] == 'n' && fileContent[idx + 2] == 't')
            {
                idx += 3;
                currentTokenLength += 3;
                finishToken("type");
                state = Delimiter;
            }
            else
            {
                state = Identificator;
            }
            break;
        }
        case Identificator:
        {
            if (isalpha(fileContent[idx]) || (!identificatorFirst && isdigit(fileContent[idx])))
            {
                identificatorFirst = false;
                currentTokenLength++;
                idx++;
            }
            else if (!identificatorFirst)
            {
                identificatorFirst = true;
                finishToken("identificator");
                state = Delimiter;
            }
            else
            {
                state = Number;
            }
            break;
        }
        case Number:
        {
            if (IsNumber(fileContent))
            {
                finishToken("number");;
                state = Delimiter;
            }
            else
            {
                state = Error;
            }
            break;
        }
        case Error:
        {
            printf("skip - ( \%c )\n", fileContent[idx]);
            idx++;
            state = Delimiter;
        }
        }
    }
}
