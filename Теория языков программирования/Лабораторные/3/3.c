#include "Lexer.h"

int main(int argc, char* argv[])
{
    char* fileName;
    if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        printf("Input name file: ");
        char buf[100];
        gets(buf);
        fileName = buf;
    }
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", fileName);
        return 1;
    }

    
    char * fileContent = "\0";

    int test = 0;
    printf("File content:\n\n");
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (test > 10) break;
        charConcat1(&fileContent, ch);
        //putchar(ch);
        test++;
    }
    printf("\n\nEOF\n");
    fclose(fp);

    system("PAUSE");
    return 0;
}