#include <ctype.h>

enum number{
    numbers,
    one_dot_numbers,
    finish_number,
    no_number
};

int IsNumber(char *str)
{
    int count_str = strlen(str);
    enum number stage = numbers;
    while(1)
    {
        switch (stage)
        {
        case numbers:
        {
            if(idx < strlen(str) && str[idx] != ' ')
            {
                if(isdigit(str[idx]))
                {
                    currentTokenLength++;
                    idx++;
                }
                else if (str[idx] == '.')
                {
                    currentTokenLength++;
                    idx++;
                    stage = one_dot_numbers;
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
            if(idx < strlen(str) && str[idx] != ' ')
            {
                if(isdigit(str[idx]))
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