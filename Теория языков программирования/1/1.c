#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int main(int argc, char *argv[])
{
    char *str1 = "variable1";
    char *str2 = "36365";
    char *str3 = "==";


    printf("%s = %d\n", str1, IsIdentifier(str1));
    printf("%s = %d\n", str2, IsNumber(str2));
    printf("%s = %d\n", str3, IsComparison(str3));
    
    system("pause");
}