#include "lexer.h"
#include "parser.h"
#include "token.h"

int main(int argc, char* argv[])
{
   char* fileName = "1.txt";
   /* if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        printf("Input1 name file: ");
        char buf[100];
        gets(buf);
        fileName = buf;
    }*/
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", fileName);
        return 1;
    }
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char* fileContent = (char*)malloc(sizeof(char) * size);
    fread(fileContent, 1, size, fp);
    fclose(fp);

    printf("\n\nfileContent:\n%s\n\nEOF\n", fileContent);
    
    int tokenQuantity = 0;
    struct Token * tokens = Lexer(fileContent, &tokenQuantity);
    printf("\n\ntokens:\n");
    for (int i = 0; i < tokenQuantity; i++)
    {
        printf("#%d : %s - \[ %s ]\n",i, NameType(tokens[i].type),tokens[i].value);
    }
    printf("end tokens\n");
    free(fileContent);

    Parser(tokens, tokenQuantity);

    system("PAUSE");
    return 0;
}