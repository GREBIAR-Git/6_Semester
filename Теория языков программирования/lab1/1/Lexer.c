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
    for (int i =0; i < strlen(str); i++)
    {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int IsComparison(char *str)
{
    return (str == "==" || str == "!=");
}

int IsSign(char *str)
{
    return (str == "+" || str == "-");
}

int IsKeyWords(char *str)
{
    return (str == "if" || str == "switch");
}
