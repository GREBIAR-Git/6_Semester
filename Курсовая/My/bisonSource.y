%{
#include <stdio.h>
#include <string.h>

int yyparse(void);
int yylex(void);

int yywrap()
{
    return 1;
}

void yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n",str);
}

main()
{
    #ifdef YYDEBUG
        yydebug = 1;
    #endif
    yyparse();
}

%}

%token DelimiterY TabY CommaY DotY DoubleDotY BoolY OpenBracesY CloseBracesY OpenBracketY CloseBracketY ComparisonY LogicalY AssignmentY MathSignY IfY ElseY ForY InY WhileY InputY OutputY DefY ClassY VariableY NumberY ReturnY ENDY ErrorY

%%
    Program:
        Statement Block | ClassStatement Block | FunctionStatement Block | /* empty */;

    Value:
        VariableY DotY VariableY | VariableY OpenBracesY Arithmetic CloseBracesY | VariableY | NumberY | BoolY;

    Identificator:
        VariableY DotY VariableY | VariableY OpenBracesY Arithmetic CloseBracesY | VariableY;

    ReturnStatement:
        ReturnY DelimiterY | ReturnY Value DelimiterY;

    AssignmentStatement:
        Identificator AssignmentY Arithmetic DelimiterY | Identificator AssignmentY InputStatement DelimiterY | Identificator AssignmentY FunctionCall DelimiterY | Identificator AssignmentY ArrayDeclaration DelimiterY;

    ArrayDeclaration: // "[" Arguments "]""
        OpenBracesY Arguments CloseBracesY;

    ClassDeclaration:
        ClassY VariableY OpenBracketY CloseBracketY DoubleDotY DelimiterY Block;

    Function:
        DefY VariableY OpenBracketY FunctionArguments CloseBracketY DoubleDotY DelimiterY Block;

    FunctionArguments: // VariableY [CommaY FunctionArgument] | empty
        VariableY FuncArgsZeroOrMore | /* empty */;

    FuncArgsZeroOrMore: // [CommaY FunctionArgument]
        /* empty */ | FuncArgsZeroOrMore CommaY FunctionArgument;

    FunctionArgument: // VariableY [CommaY FunctionArgument]
        VariableY FuncArgsZeroOrMore;

    FunctionCall:
        VariableY OpenBracketY Arguments CloseBracketY DelimiterY;

    Arguments: // Identificator ["," Argument] | empty
        Identificator ArgsZeroOrMore | /* empty */;

    ArgsZeroOrMore: // ["," Argument]
        /* empty */ | ArgsZeroOrMore CommaY Argument;

    Argument: // Identificator ["," Argument]
        Identificator ArgsZeroOrMore;

    IfStatement:
        IfY Logic DoubleDotY DelimiterY Block IfZeroOrMore;

    IfZeroOrMore: // [ElseY DoubleDotY DelimiterY Block]
        /* empty */ | ElseY DoubleDotY DelimiterY Block;

    WhileStatement:
        WhileY Logic DoubleDotY DelimiterY Block;

    ForStatement:
        ForY Value InY Value DoubleDotY DelimiterY Block;

    Logic:
        OpenBracketZeroOrMore LogicExpression LogicZeroOrMore CloseBracketZeroOrMore;

    LogicZeroOrMore: // [LogicalY Logic]
        /* empty */ | LogicZeroOrMore LogicalY Logic;

    LogicExpression:
        OpenBracketZeroOrMore Arithmetic LogicExprZeroOrMore CloseBracketZeroOrMore;

    LogicExprZeroOrMore: // [LogicalY LogicExpression]
        /* empty */ | LogicExprZeroOrMore ComparisonY LogicExpression;

    OpenBracketZeroOrMore:
        /* empty */ | OpenBracketZeroOrMore OpenBracketY;

    CloseBracketZeroOrMore:
        /* empty */ | CloseBracketZeroOrMore CloseBracketY;

    Arithmetic: // ["("] Value [MathSignY Arithmetic] [")"]
        OpenBracketZeroOrMore Value ArithmeticZeroOrMore CloseBracketZeroOrMore;

    ArithmeticZeroOrMore: // [MathSignY Arithmetic]
        /* empty */ | ArithmeticZeroOrMore MathSignY Arithmetic;

    InputStatement:
        InputY OpenBracketY CloseBracketY DelimiterY;

    OutputStatement:
        OutputY OpenBracketY Arithmetic CloseBracketY DelimiterY;

    Statement:
        IfStatement | WhileStatement | ForStatement | AssignmentStatement | InputStatement | OutputStatement | ClassDeclaration | Function | FunctionCall | DelimiterY;

    ClassStatement:
        AssignmentStatement | Function | DelimiterY;

    FunctionStatement:
        Statement | ReturnStatement;

    Block:
        TabOneOrMore Statement Block | TabOneOrMore ClassStatement Block | TabOneOrMore FunctionStatement Block | /* empty */;

    TabZeroOrMore:
        /* empty */ | TabZeroOrMore TabY;

    TabOneOrMore:
        TabY | TabZeroOrMore TabY;

%%
