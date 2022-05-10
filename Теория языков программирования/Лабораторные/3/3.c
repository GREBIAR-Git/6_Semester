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
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        charConcat1(&fileContent, ch);
    }
    fclose(fp);
    printf("\n\nfileContent:\n%s\n\nEOF\n", fileContent);
    
    lexer();

    printf("\n\ntokens:\n");
    for (int i = 0; i < currentToken; i++)
    {
        printf("%s:%s\n",tokens[i].name,tokens[i].value);
    }
    printf("\n\nend tokens\n");

    system("PAUSE");
    return 0;
}