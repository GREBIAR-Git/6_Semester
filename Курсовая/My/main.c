#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "bisonReady.h"
// token.h
enum TokenType
{
    Delimiter,// \n
    Tab,// \t
    Comma,// ,
    Dot,// .
    DoubleDot,// :
    Bool, // true false
    OpenBraces,//[
    CloseBraces,//]
    OpenBracket,//(
    CloseBracket,//)
    Comparison,//< > == != >= <=
    Logical,// and or not
    Assignment,// = += -= *= /= %=
    MathSign,// + - * / %
    If, // if
    Else, // else 
    For, // for
    In, // in
    While, // while
    Input, // input
    Output, // print
    Def, // def
    Class, // class
    Variable,
    Number,
    Return,
    END,
    Error,
};

enum NonTerminalType
{
    Terminal,
    BlockTerm,
    Function,
    Params,
    LogicalOperationTerm,
};

struct Token
{
    enum TokenType type;
    char* value;
    int pos;
    int line;
};

char* NameNonTerminalType(enum NonTerminalType type);

char* NameType(enum TokenType type);
// lexer.h
enum number {
    numbers,
    one_dot_numbers,
    finish_number,
    no_number
};

bool IsNumber(char* str);
void FinishToken(enum TokenType type, int* tokenQuantity);
struct Token* Lexer(char* content,int * tokenQuantity);
bool CompareStrings(char* str);
bool CompareStringCheck(char* str);
// token.c
char* NameType(enum TokenType type)
{
    switch (type)
    {
    case Delimiter:
        return "Delimiter";
    case Tab:
        return "Tab";
    case Comma:
        return "Comma";
    case Dot:
        return "Dot";
    case DoubleDot:
        return "Double Dot";
    case Bool:
        return "Bool";
    case OpenBraces:
        return "Open Braces";
    case CloseBraces:
        return "Close Braces";
    case OpenBracket:
        return "Open Bracket";
    case CloseBracket:
        return "Close Bracket";
    case Comparison:
        return "Comparison";
    case Logical:
        return "Logical";
    case Assignment:
        return "Assignment";
    case MathSign:
        return "MathSign";
    case If:
        return "If";
    case Else:
        return "Else:";
    case For:
        return "For";
    case In:
        return "In";
    case While:
        return "While";
    case Def:
        return "Def";
    case Class:
        return "Class";
    case Input:
        return "Input";
    case Output:
        return "Output";
    case Variable:
        return "Variable";
    case Number:
        return "Number";
    case Return:
        return "Return";
    case END:
        return "END";
    case Error:
        return "Error";
    default:
        break;
    }
}

char* NameNonTerminalType(enum NonTerminalType type)
{
    switch (type)
    {
    case Terminal:
        return "nonterminal";
    case BlockTerm:
        return "Block";
        break;
    case Function:
        return "Function";
        break;
    case Params:
        return "Params";
        break;
    case LogicalOperationTerm:
        return "LogicalOperation";
    default:
        break;
    }
   
}
// lexer.c
char* fileContent;

int currentTokenLength = 0;
int idx = 0;

int lines = 0;

struct Token * tokenS;

void FinishToken(enum TokenType type, int * tokenQuantity)
{
    struct Token* temp = malloc((*tokenQuantity + 1)*sizeof(struct Token));
    for (int i = 0; i < *tokenQuantity; i++)
    {
        temp[i] = tokenS[i];
    }
    temp[*tokenQuantity].type = type;
    char buffer[currentTokenLength + 1];
    memcpy(buffer, &fileContent[idx - currentTokenLength], currentTokenLength);
    buffer[currentTokenLength] = '\0';
    temp[*tokenQuantity].value = malloc(strlen(buffer) + 1);
    strcpy(temp[*tokenQuantity].value, buffer);
    temp[*tokenQuantity].pos = idx - currentTokenLength;
    temp[*tokenQuantity].line = lines;
    if (tokenS)
    {
        free(tokenS);
    }
    tokenS = temp;
    (*tokenQuantity)++;
    currentTokenLength = 0;
}

struct Token * Lexer(char* content, int * tokenQuantity)
{
    enum TokenType state = Delimiter;
    tokenS = malloc(0);
    fileContent = content;
    bool io_Rooted = false;
    bool identificatorFirst = true;

    while (idx < strlen(fileContent))
    {  
        switch (state)
        {
        case Delimiter:
            if ((idx + 1 < strlen(fileContent) && fileContent[idx] == '\r'&& fileContent[idx+1] =='\n'))
            {
                lines++;
                idx+=2;
                currentTokenLength+=1;
                FinishToken(Delimiter, tokenQuantity);
                state = Delimiter;
            }
            else if ( fileContent[idx] == '\n' || fileContent[idx] == '\0')
            {
                lines++;
                idx++;
                currentTokenLength++;
                FinishToken(Delimiter, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Tab;
            }
            break;
        case Tab:
            if(CompareStrings("\t"))
            {
                FinishToken(Tab, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Comma;
            }
            break;
        case Comma:
            if (CompareStrings(","))
            {
                FinishToken(Comma, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Dot;
            }
            break;
        case Dot:
            if (CompareStrings("."))
            {
                FinishToken(Dot, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = DoubleDot;
            }
            break;
        case DoubleDot:
            if (CompareStrings(":"))
            {
                FinishToken(DoubleDot, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Bool;
            }
            break;
        case Bool:
            if (CompareStringCheck("true")||CompareStringCheck("false"))
            {
                FinishToken(Bool, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Logical;
            }
            break;
        case Logical:
            if (CompareStringCheck("and")||CompareStringCheck("or")||CompareStringCheck("not"))
            {
                FinishToken(Logical, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = OpenBraces;
            }
            break;
        case OpenBraces:
            if (CompareStrings("["))
            {
                FinishToken(OpenBraces, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = CloseBraces;
            }
            break;
        case CloseBraces:
            if (CompareStrings("]"))
            {
                FinishToken(CloseBraces, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = OpenBracket;
            }
            break;
        case OpenBracket:
            if (CompareStrings("("))
            {
                FinishToken(OpenBracket, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = CloseBracket;
            }
            break;
        case CloseBracket:
            if (CompareStrings(")"))
            {
                FinishToken(CloseBracket, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Comparison;
            }
            break;
        case Comparison:
            if (CompareStrings("!=")||CompareStrings("==")||CompareStrings("<=")||CompareStrings(">=")||CompareStrings(">")||CompareStrings("<"))
            {
                FinishToken(Comparison, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Assignment;
            }
            break;
        case Assignment:
            if (CompareStrings("=")||CompareStrings("+=")||CompareStrings("-=")||CompareStrings("*=")||CompareStrings("/=")||CompareStrings("\%="))
            {
                FinishToken(Assignment, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = MathSign;
            }
            break;
        case MathSign:
            if (CompareStrings("+") || CompareStrings("-") || CompareStrings("*") || CompareStrings("/") || CompareStrings("\%"))
            {
                FinishToken(MathSign, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = If;
            }
            break;
        case If:
            if (CompareStringCheck("if"))
            {
                FinishToken(If, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Else;
            }
            break;
        case Else:
            if (CompareStringCheck("else"))
            {
                FinishToken(Else, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = For;
            }
            break;
        case For:
            if (CompareStringCheck("for"))
            {
                FinishToken(For, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = While;
            }
            break;
        case While:
            if (CompareStringCheck("while"))
            {
                FinishToken(While, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Input;
            }
            break;
        case Input:
            if (CompareStringCheck("input"))
            {
                FinishToken(Input, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Output;
            }
            break;
        case Output:
            if (CompareStringCheck("print"))
            {
                FinishToken(Output, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Class;
            }
            break;
        case Class:
            if (CompareStringCheck("class"))
            {
                FinishToken(Class, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Def;
            }
            break;
        case Def:
            if (CompareStringCheck("def"))
            {
                FinishToken(Def, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = In;
            }
            break;
        case In:
            if (CompareStringCheck("in"))
            {
                FinishToken(In, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Return;
            }
            break;
        case Return:
            if (CompareStringCheck("return"))
            {
                FinishToken(Return, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Variable;
            }
            break;
        case Variable:
            if (isalpha(fileContent[idx]) || CompareStrings("_") || (!identificatorFirst && isdigit(fileContent[idx])))
            {
                identificatorFirst = false;
                currentTokenLength++;
                idx++;
            }
            else if (!identificatorFirst)
            {
                identificatorFirst = true;
                FinishToken(Variable, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Number;
            }
            break;
        case Number:
            if (IsNumber(fileContent))
            {
                FinishToken(Number, tokenQuantity);
                state = Delimiter;
            }
            else
            {
                state = Error;
            }
            break;
        case Error:
            if(fileContent[idx]!=' ')
            {
                printf("\nLexical error on the line %d - unreserved character: %c  ",lines+1 , fileContent[idx]);
            }
            idx++;
            state = Delimiter;
        default:
            break;
        }
    }
    FinishToken(Delimiter, tokenQuantity);
    FinishToken(END, tokenQuantity);
    return tokenS;
}

bool CompareStrings(char* str)
{
    if (idx + strlen(str)-1 < strlen(fileContent))
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (fileContent[idx + i] != str[i])
            {
                return false;
            }
        }
        idx += strlen(str);
        currentTokenLength += strlen(str);
        return true;
    }
    return false;
}

bool CompareStringCheck(char* str)
{
    if (idx + strlen(str)-1 < strlen(fileContent))
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (fileContent[idx + i] != str[i])
            {
                return false;
            }
        }
        if(idx + strlen(str) < strlen(fileContent))
        {
            if(isalpha(fileContent[idx + strlen(str)]) || isdigit(fileContent[idx + strlen(str)]))
            {
                return false;
            }
        }
        idx += strlen(str);
        currentTokenLength += strlen(str);
        return true;
    }
    return false;
}

bool IsNumber(char* str)
{
    enum number stage = numbers;
    bool RootNumber = false;
    while (true)
    {
        switch (stage)
        {
        case numbers:
        {
            if (idx < strlen(str))
            {
                if (isdigit(str[idx]))
                {
                    RootNumber = true;
                    currentTokenLength++;
                    idx++;
                }
                else if (str[idx] == '.' && RootNumber)
                {

                    currentTokenLength++;
                    idx++;
                    stage = one_dot_numbers;
                }
                else if ((str[idx] != ' ' || str[idx] != '\n' || str[idx] != '\r') && RootNumber)
                {
                    stage = finish_number;
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
            if (idx < strlen(str) && str[idx] != ' ' && str[idx] != '\n' && str[idx] != '\r')
            {
                if (isdigit(str[idx]))
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
            return false;
        }
        case finish_number:
        {
            return true;
        }
        }
    }
}
// 3.c
struct Token * tokens;
int tokenize()
{
    char* fileName = "pythonCode.txt";
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
    tokens = Lexer(fileContent, &tokenQuantity);

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

    //Parser(tokens, tokenQuantity);

    system("PAUSE");
    return 0;
}

int ind = -1;
int yylex()
{
    if (ind == -1)
    {
        tokenize();
    }
    ind++;
    return tokens[ind].type;
}