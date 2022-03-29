#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token
{
    char *name;
    char *value;
};

enum State
{
    Default,
    Identificator,
    Number,
    Comparison,
    Sign,
    KeyWord
};

char *str = "21323 54.43 54. 54 fdsfsd + == hghghg  fsd";
int currentToken = 0; int currentTokenLength = 0;
int identificatorFirst = 1;
struct Token tokens[100];
enum State state = Default;
int idx = 0;

#include "Lexer.c"

void finishToken(char* stateName)
{
    char buffer[currentTokenLength + 1];
    memcpy(buffer, &str[idx - currentTokenLength], currentTokenLength); // <- krasava
    buffer[currentTokenLength] = '\0';
    //strcpy(tokens[currentToken].name, stateName);
    //strcpy(tokens[currentToken].value, buffer);
    printf("\n\n%s - %s\n", stateName, buffer);
    //printf("%s - %s\n\n", tokens[currentToken].name, tokens[currentToken].value);
    currentToken++;
    currentTokenLength=0;
}

int main()
{
    // Подготавливаем буфер для вывода результата
    char buffer[strlen(str)+1];
    strcpy(buffer, str);
    strcat(buffer, " ");
    str = buffer;


    //
    //  Начало программы
    //


    while(idx < strlen(str))
    {
        switch(state)
        {
            case Default:
            {
                state = KeyWord;
                break;
            }
            case Identificator:
            {
                if(isalpha(str[idx]) || (!identificatorFirst && isdigit(str[idx])))
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
                || str[idx] == '=' && str[idx+1] == '='))
                {
                    idx+=2;
                    currentTokenLength+=2;
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
                && str[idx] == 'i' && str[idx+1] == 'f')
                {
                    idx+=2;
                    currentTokenLength += 2;
                    finishToken("keyword");
                    state = Default;
                }
                else if (idx + 5 < strlen(str)
                && str[idx] == 's' && str[idx+1] == 'w' && str[idx+2] == 'i'
                && str[idx+3] == 't' && str[idx+4] == 'c' && str[idx+5] == 'h')
                {
                    idx+=6;
                    currentTokenLength+=2;
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
    for (int i=0;i<currentToken;i++)
    {
        //printf("%s:%s\n",tokens[i].name,tokens[i].value);
    }
    return 0;
}



