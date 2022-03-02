#include <stdio.h>
int main()
{
    int range[] = { 11, 112, 1233, 12344, 21321, 43534, 6546, 432, 110000 };
    int sum = 0;
    for (int i = 0; i < sizeof(range)/sizeof(int); i++)
    {
        for (int f = i; f < sizeof(range)/sizeof(int); f++)
        {
            if (range[i] < range[f])
            {
                int save = range[i];
                range[i] = range[f];
                range[f] = save;
            }
        }
        sum += range[i];
        if (sum >= 130000)
        {
            printf("Sum: %d", sum);
            printf("\nlast summand: %d", range[i]);
            printf("\nnumber summand: %d", i + 1);
            break;
        }
    }
}
