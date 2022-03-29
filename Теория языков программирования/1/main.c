#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lexer.c"

struct Token
{
    char *name;
    char *value;
};

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

int main()
{
    struct Token tokens[100];
    int currentToken;
    char *str = "21323 54.43 54. 54 fdsfsd + == hghghg         f";
    char *token, *str1, *tofree;
    tofree = str1 = strdup(str);
    while ((token = strsep(&str1, " ")))
    {
        if(strlen(token)>0)
        {
            if(IsComparison(token))
            {
                tokens[currentToken].name = "comparison";
            }
            else if (IsSign(token))
            {
                tokens[currentToken].name = "isSign";
            }
            else if (IsKeyWords(token))
            {
                tokens[currentToken].name = "keyword";
            }
            else if (IsNumber(token))
            {
                tokens[currentToken].name = "diget";
            }
            else if (IsIdentifier(token))
            {
                tokens[currentToken].name = "ident";
            }
            else
            {
                tokens[currentToken].name = "undefined";
            }
            tokens[currentToken].value = (char*) malloc(strlen(token)+1);
            strcpy(tokens[currentToken].value, token);
            currentToken++;
        }
    }
    free(tofree);
    for (int i=0;i<currentToken;i++)
    {
        printf("%s:%s\n",tokens[i].name,tokens[i].value);
    }
    return 0;
}



