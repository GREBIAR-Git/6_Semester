#include "lexer.h"

char* fileContent;

int currentTokenLength = 0;
int idx = 0;

struct Token * tokenS;

enum TokenType state = Delimiter;

void FinishToken(enum TokenType type, int * tokenQuantity)
{
    struct Token* temp = malloc((*tokenQuantity + 1)*sizeof(struct Token));
    for (int i = 0; i < *tokenQuantity; i++)
    {
        temp[i] = tokenS[i];
    }
    temp[*tokenQuantity].type = type;
    char buffer[currentTokenLength + 1];
    memcpy(buffer, &fileContent[idx - currentTokenLength], currentTokenLength);
    buffer[currentTokenLength] = '\0';
    temp[*tokenQuantity].value = malloc(strlen(buffer) + 1);
    strcpy(temp[*tokenQuantity].value, buffer);
    temp[*tokenQuantity].pos = idx - currentTokenLength;
    if (tokenS)
    {
        free(tokenS);
    }
    tokenS = temp;
    (*tokenQuantity)++;
    currentTokenLength = 0;
}

struct Token * Lexer(char* content, int * tokenQuantity)
{
    tokenS = malloc(0);
    fileContent = content;
    bool io_started = false;
    bool identificatorFirst = true;

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
                FinishToken(Delimiter, tokenQuantity);
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
                FinishToken(Comma, tokenQuantity);
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
                FinishToken(Comparison, tokenQuantity);
                state = Delimiter;
            }
            else if (fileContent[idx] == '<' || fileContent[idx] == '>')
            {
                idx++;
                currentTokenLength++;
                FinishToken(Comparison, tokenQuantity);
                state = Delimiter;
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
                FinishToken(Assignment, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = OpenBracket;
            }
            break;
        }
        case OpenBracket:
        {
            if (fileContent[idx] == '(')
            {
                idx++;
                currentTokenLength++;
                FinishToken(OpenBracket, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = CloseBracket;
            }
            break;
        }
        case CloseBracket:
        {
            if (fileContent[idx] == ')')
            {
                idx++;
                currentTokenLength++;
                FinishToken(CloseBracket, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = OpenBraces;
            }
            break;
        }
        case OpenBraces:
        {
            if (fileContent[idx] == '{')
            {
                idx++;
                currentTokenLength++;
                FinishToken(OpenBraces, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = CloseBraces;
            }
            break;
        }
        case CloseBraces:
        {
            if (fileContent[idx] == '}')
            {
                idx++;
                currentTokenLength++;
                FinishToken(CloseBraces, tokenQuantity);
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
                FinishToken(MathSign, tokenQuantity);
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
                io_started = true;
                currentTokenLength++;
                idx++;
            }
            else if (fileContent[idx] == '"' && io_started)
            {
                io_started = false;
                idx++;
                currentTokenLength++;
                if (currentTokenLength)
                {
                    FinishToken(IOstring, tokenQuantity);
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
                state = IF;
            }
            break;
        }
        case IF:
        {
            if (idx + 1 < strlen(fileContent)
                && fileContent[idx] == 'i' && fileContent[idx + 1] == 'f')
            {
                idx += 2;
                currentTokenLength += 2;
                FinishToken(IF, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Else;
            }
            break;
        }
        case Else:
        {
            if (idx + 3 < strlen(fileContent)
                && fileContent[idx] == 'e' && fileContent[idx + 1] == 'l' && fileContent[idx + 2] == 's' && fileContent[idx + 3] == 'e')
            {
                idx += 4;
                currentTokenLength += 4;
                FinishToken(Else, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Input;
            }
            break;
        }
        case Input:
        {
            if (idx + 4 < strlen(fileContent)
                && fileContent[idx] == 's' && fileContent[idx + 1] == 'c' && fileContent[idx + 2] == 'a' && fileContent[idx + 3] == 'n' && fileContent[idx + 4] == 'f')
            {
                idx += 5;
                currentTokenLength += 5;
                FinishToken(Input, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Output;
            }
            break;
        }
        case Output:
        {
            if (idx + 5 < strlen(fileContent)
                && fileContent[idx] == 'p' && fileContent[idx + 1] == 'r' && fileContent[idx + 2] == 'i'
                && fileContent[idx + 3] == 'n' && fileContent[idx + 4] == 't' && fileContent[idx + 5] == 'f')
            {
                idx += 6;
                currentTokenLength += 6;
                FinishToken(Output, tokenQuantity);
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
                FinishToken(Type, tokenQuantity);
                state = Delimiter;
            }
            else if (idx + 2 < strlen(fileContent)
                && fileContent[idx] == 'i' && fileContent[idx + 1] == 'n' && fileContent[idx + 2] == 't')
            {
                idx += 3;
                currentTokenLength += 3;
                FinishToken(Type, tokenQuantity);
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
                FinishToken(Identificator, tokenQuantity);
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
                FinishToken(Number, tokenQuantity);
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
    return tokenS;
}

bool IsNumber(char* str)
{
    int count_str = strlen(str);
    enum number stage = numbers;
    bool startNumber = false;
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
            return false;
        }
        case finish_number:
        {
            return true;
        }
        }
    }
}