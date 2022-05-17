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
    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", fileName);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char* fileContent = (char*)malloc(sizeof(char) * size+1);
    fread(fileContent, 1, size, fp);
    fileContent[size]=0;
    fclose(fp);

    printf("\n\nfileContent:\n%s\n\nEOF\n", fileContent);
    
    int tokenQuantity = 0;
    struct Token * tokens = Lexer(fileContent, &tokenQuantity);

    printf("\n\ntokens:\n");
    for (int i = 0; i < tokenQuantity; i++)
    {
        if (tokens[i].type==Delimiter)
        {
            printf("#%d : %s - \[ \\n ]\n", i, NameType(tokens[i].type));
        }
        else
        {
            printf("#%d : %s - \[ %s ]\n",i, NameType(tokens[i].type),tokens[i].value);
        }
    }
    printf("end tokens\n");
    
    free(fileContent);

    Parser(tokens, tokenQuantity);

    system("PAUSE");
    return 0;
}