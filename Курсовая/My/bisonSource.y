%{
#include <stdio.h>
#include <string.h>

#define YYDEBUG 1

int yyparse(void);
int yylex(void);
int yywrap();
void yyerror(const char *str);

%}

%token DelimiterY
%token TabY
%token CommaY
%token DotY
%token DoubleDotY
%token BoolY
%token OpenBracesY
%token CloseBracesY
%token OpenBracketY
%token CloseBracketY
%token ComparisonY
%token LogicalY
%token AssignmentY
%token MathSignY
%token IfY
%token ElseY
%token ForY
%token InY
%token WhileY
%token InputY
%token OutputY
%token DefY
%token ClassY
%token VariableY
%token NumberY
%token ReturnY
%token ENDY
%token ErrorY

%start Program


%%
    Program:
        Statements ENDY
        {
            printf("\n{No errors}");
        };

    Statements:
        /* empty */ | Statements Statement;

    Statement:
        IfStatement | WhileStatement | ForStatement | AssignmentStatement | InputStatement | OutputStatement | ClassDeclaration | Function | FunctionCall | ReturnStatement | DelimiterY;

    Block:
        /* empty */ | Block TabOneOrMore Statement;

    IfStatement:
        IfY Logic DoubleDotY DelimiterY Block Else | IfY Value DoubleDotY DelimiterY Block Else;

    Else:
        /* empty */ | ElseY DoubleDotY DelimiterY Block;

    WhileStatement:
        WhileY Logic DoubleDotY DelimiterY Block | WhileY Value DoubleDotY DelimiterY Block;

    ForStatement:
        ForY Value InY Value DoubleDotY DelimiterY Block;

    Value:
        Identificator | NumberY | BoolY;

    Identificator:
        VariableY DotY VariableY | VariableY OpenBracesY Arithmetic CloseBracesY | VariableY;

    ReturnStatement:
        ReturnY DelimiterY | ReturnY Value DelimiterY;

    AssignmentStatement:
        Identificator AssignmentY Value DelimiterY | Identificator AssignmentY Logic DelimiterY | Identificator AssignmentY Arithmetic DelimiterY | Identificator AssignmentY InputStatement DelimiterY | Identificator AssignmentY FunctionCall DelimiterY | Identificator AssignmentY ArrayDeclaration DelimiterY;

    ArrayDeclaration:
        OpenBracesY Arguments CloseBracesY;

    ClassDeclaration:
        ClassY VariableY OpenBracketY CloseBracketY DoubleDotY DelimiterY Block;

    Function:
        DefY Identificator OpenBracketY Arguments CloseBracketY DoubleDotY DelimiterY Block;

    FunctionCall:
        Identificator OpenBracketY Arguments CloseBracketY DelimiterY;

    Arguments:
        /* empty */ | Value CommaValue;

    CommaValue:
        /* empty */ | CommaValue CommaY Value;

    Logic:
        OpenBracketZeroOrMore Value ComparisonY Value CloseBracketZeroOrMore | OpenBracketZeroOrMore Logic LogicalY Logic CloseBracketZeroOrMore;

    OpenBracketZeroOrMore:
        /* empty */ | OpenBracketZeroOrMore OpenBracketY;

    CloseBracketZeroOrMore:
        /* empty */ | CloseBracketZeroOrMore CloseBracketY;

    /*Arithmetic:
        OpenBracketZeroOrMore Value MathSignY Value CloseBracketZeroOrMore | OpenBracketZeroOrMore Arithmetic MathSignY Arithmetic CloseBracketZeroOrMore;*/

    Arithmetic:
        Value MathSignY Value | Arithmetic MathSignY Arithmetic;

    InputStatement:
        InputY OpenBracketY CloseBracketY DelimiterY;

    OutputStatement:
        OutputY OpenBracketY Value CloseBracketY DelimiterY;

    TabOneOrMore:
        TabY | TabOneOrMore TabY;

%%

int yywrap()
{
    return 1;
}

void yyerror(const char *str)
{
    fprintf(stderr,"\nERROR: %s",str);
}

main()
{
    yyparse();
}

int yydebug = 0;