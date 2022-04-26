#include <stdio.h>

int main(int argc, char* argv[])
{
    char * fileName;
    if(argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        printf("Input name file: ");
        char buf[30];
        gets(buf);
        fileName = buf;
    }

    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", fileName);
        return 1;
    }
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    fclose(fp);
    return 0;
}