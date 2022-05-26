%{
#include <stdio.h>
#include <string.h>

int yyparse(void);
int yylex(void);
int yywrap();
void yyerror(const char *str);

%}

%token DelimiterY TabY CommaY DotY DoubleDotY BoolY OpenBracesY CloseBracesY OpenBracketY CloseBracketY ComparisonY LogicalY AssignmentY MathSignY IfY ElseY ForY InY WhileY InputY OutputY DefY ClassY VariableY NumberY ReturnY ENDY ErrorY

%%
    Program: // ПРОГРАММА → [ УТВЕРЖДЕНИЕ ] ;
        Statements
        {
            printf("No errors\n");
        };

    Statement: // УТВЕРЖДЕНИЕ -> УСЛОВНЫЙ_ОПЕРАТОР | ОПЕРАТОР_ЦИКЛА | ПРИСВОЕНИЕ | ОПЕРАТОР_ВВОДА | ОПЕРАТОР_ВЫВОДА |  ОБЪЯВЛЕНИЕ_КЛАССА | ОБЪЯВЛЕНИЕ_ФУНКЦИИ | ВЫЗОВ_ФУНКЦИИ | ВОЗВРАТ | разделитель
        IfStatement | WhileStatement | ForStatement | AssignmentStatement | InputStatement | OutputStatement | ClassDeclaration | Function | FunctionCall | ReturnStatement | DelimiterY;

    Statements: // [УТВЕРЖДЕНИЕ]
        /* empty */ | Statements Statement;

    Value: // ЗНАЧЕНИЕ -> переменная '.' переменная | переменная '[' АРИФМЕТИЧЕСКОЕ_ВЫРАЖЕНИЕ ']' | переменная | число | булево_значение
        Identificator | NumberY | BoolY;

    CommaValues:
        /* empty */ | CommaValues CommaY Identificator | CommaValues CommaY NumberY | CommaValues CommaY BoolY;

    Identificator: // ИДЕНТИФИКАТОР -> переменная '.' переменная | переменная '[' АРИФМЕТИЧЕСКОЕ_ВЫРАЖЕНИЕ ']' | переменная
        VariableY DotY VariableY | VariableY OpenBracesY Arithmetic CloseBracesY | VariableY;

    ReturnStatement: // ВОЗВРАТ -> return разделитель | return ЗНАЧЕНИЕ разделитель
        ReturnY DelimiterY | ReturnY Value DelimiterY;

    AssignmentStatement: // ПРИСВОЕНИЕ -> ИДЕНТИФИКАТОР присвоение АРИФМЕТИЧЕСКОЕ_ВЫРАЖЕНИЕ разделитель | ИДЕНТИФИКАТОР присвоение ОПЕРАТОР_ВВОДА разделитель | ИДЕНТИФИКАТОР присвоение ВЫЗОВ_ФУНКЦИИ разделитель | ИДЕНТИФИКАТОР присвоение ОБЪЯВЛЕНИЕ_МАССИВА
        Identificator AssignmentY Arithmetic DelimiterY | Identificator AssignmentY InputStatement DelimiterY | Identificator AssignmentY FunctionCall DelimiterY | Identificator AssignmentY ArrayDeclaration DelimiterY;

    ArrayDeclaration: // "[" Arguments "]""
        OpenBracesY Values CloseBracesY;

    ClassDeclaration:
        ClassY VariableY OpenBracketY CloseBracketY DoubleDotY DelimiterY Block;

    Function:
        DefY VariableY OpenBracketY Value CommaValues CloseBracketY DoubleDotY DelimiterY Block;

    FuncArgsZeroOrMore: // [CommaY FunctionArgument]
        /* empty */ | FuncArgsZeroOrMore CommaY FunctionArgument;

    FunctionArgument: // VariableY [CommaY FunctionArgument]
        VariableY FuncArgsZeroOrMore;

    FunctionCall:
        VariableY OpenBracketY Identificators CloseBracketY DelimiterY;

    Identificators: // ["," Argument]
        /* empty */ | Identificators CommaY Identificator;

    IfStatement:
        IfY Logic DoubleDotY DelimiterY Block IfZeroOrMore;

    IfZeroOrMore: // [ElseY DoubleDotY DelimiterY Block]
        /* empty */ | IfZeroOrMore ElseY DoubleDotY DelimiterY Block;

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
        OutputY OpenBracketY Value CloseBracketY DelimiterY;

    Block:
        TabOneOrMore Statement Block | /* empty */;

    TabZeroOrMore:
        /* empty */ | TabZeroOrMore TabY;

    TabOneOrMore:
        TabY | TabZeroOrMore TabY;

%%

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
    yyparse();
}
