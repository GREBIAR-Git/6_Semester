#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lexer.c"

struct Token
{
    char *name;
    char *value;
};

int main()
{
    struct Token tokens[100];
    int currentToken;
    char *str;
    gets(str);
    char *token, *str1, *tofree;
    tofree = str1 = strdup(str);
    while ((token = strsep(&str1, " ")))
    {
        if(strlen(token)>0)
        {
            if(IsOperatorComparison(token))
            {
                tokens[currentToken].name = "�������� ���������";
            }
            else if (IsComparisonMark(token))
            {
                tokens[currentToken].name = "���� ��������";
            }
            else if (IsKeywords(token))
            {
                tokens[currentToken].name = "�������� �����";
            }
            else if (IsNumber(token))
            {
                tokens[currentToken].name = "�����";
            }
            else if (IsIdentifier(token))
            {
                tokens[currentToken].name = "�������������";
            }
            tokens[currentToken].value = token;
        }
    }
    free(tofree);

    for (int i=0;i<sizeof(tokens)/sizeof(tokens[0]);i++)
    {
        printf("%s:%s",tokens->name,tokens->value);
    }
    return 0;
}
