#include <ctype.h>

int IsIdentifier(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isalnum(str[i])) return 0;
    }
    return (isalpha(str[0]) == 2);
}

int IsNumber(char *str)
{
    int dotCount = 0;
    for (int i =0; i < strlen(str); i++)
    {
        if (str[i] == '.') dotCount++;
        if (!isdigit(str[i]) && str[i] != '.') return 0;
    }
    return (dotCount < 2);
}

int IsComparison(char *str)
{
    return (strcmp (str, "==")==0 || strcmp (str, "!=")==0);
}

int IsSign(char *str)
{
    return (strcmp (str, "+")==0 || strcmp (str, "-")==0);
}

int IsKeyWords(char *str)
{
    return (strcmp (str, "if")==0 || strcmp (str, "switch")==0);
}
