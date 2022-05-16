#include "lexer.h"

char* fileContent;

int currentTokenLength = 0;
int idx = 0;

struct Token * tokenS;

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
    enum TokenType state = Create;
    tokenS = malloc(0);
    fileContent = content;
    bool io_started = false;
    bool identificatorFirst = true;

    while (idx < strlen(fileContent))
    {
        switch (state)
        {
        case Create:
            if (CompareStrings("CREATE"))
            {
                FinishToken(Create, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Table;
            }
            break;
        case Table:
            if (CompareStrings("TABLE"))
            {
                FinishToken(Table, tokenQuantity);
                state = Create;
            }
            else
            {
                state = OpenBrackets;
            }
            break;
        case OpenBrackets:
            if (CompareStrings("("))
            {
                FinishToken(OpenBrackets, tokenQuantity);
                state = Create;
            }
            else
            {
                state = CloseBrackets;
            }
            break;
        case CloseBrackets:
            if (CompareStrings(")"))
            {
                FinishToken(CloseBrackets, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Type;
            }
            break;
        case Type:
            if (CompareStrings("INT") || CompareStrings("CHAR"))
            {
                FinishToken(Type, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Attributes;
            }
            break;
        case Attributes:
            if (CompareStrings("NOT NULL") || CompareStrings("NULL"))
            {
                FinishToken(Attributes, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Comma;
            }
            break;
        case Comma:
            if (CompareStrings(","))
            {
                FinishToken(Comma, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Primary;
            }
            break;
        case Primary:
            if (CompareStrings("PRIMARY"))
            {
                FinishToken(Primary, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Foreign;
            }
            break;
        case Foreign:
            if (CompareStrings("FOREIGN"))
            {
                FinishToken(Foreign, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Key;
            }
            break;
        case Key:
            if (CompareStrings("KEY"))
            {
                FinishToken(Key, tokenQuantity);
                state = Create;
            }
            else
            {
                state = References;
            }
            break;
        case References:
            if (CompareStrings("REFERENCES"))
            {
                FinishToken(References, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Name;
            }
            break;
        case Name:
            if (isalpha(fileContent[idx])||(fileContent[idx] == '_') || (!identificatorFirst && isdigit(fileContent[idx])))
            {
                identificatorFirst = false;
                currentTokenLength++;
                idx++;
            }
            else if (!identificatorFirst)
            {
                identificatorFirst = true;
                FinishToken(Name, tokenQuantity);
                state = Create;
            }
            else
            {
                state = Error;
            }
            break;
        case Error:
            if (fileContent[idx] != ' ')
            {
                printf("\n skip - ( %c )", fileContent[idx]);
            }
            idx++;
            state = Create;
            break;
        default:
            break;
        }
    }
    return tokenS;
}

bool CompareStrings(char* str)
{
    if (idx + strlen(str)-1 < strlen(fileContent))
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (fileContent[idx + i] != str[i])
            {
                return false;
            }
        }
        idx += strlen(str);
        currentTokenLength += strlen(str);
        return true;
    }
    return false;
}