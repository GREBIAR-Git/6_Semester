#include <ctype.h>

int IsIdentifier(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isalnum(str[i])) return 0;
    }
    return (isalpha(str[0]) == 2);
}

enum number{
numbers,
one_dot_numbers,
finish_number,
no_number
};

int IsNumber(char *str)
{
    int i=0;
    int count_str = strlen(str);
    enum number stage;
    while(1)
    {
        switch (stage)
        {
        case numbers:
        {
            if(count_str>i)
            {
                if(isdigit(str[i]))
                {
                    i++;
                }
                else if (str[i] == '.')
                {
                    i++;
                    stage=one_dot_numbers;
                }
                else
                {
                    stage =no_number;
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
            if(count_str>i)
            {
                if(isdigit(str[i]))
                {
                    i++;
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
        default:
            break;
        }
    }
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
