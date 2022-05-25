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
    yyparse();
}

%}

%token Delimiter Tab Comma Dot DoubleDot Bool OpenBraces CloseBraces OpenBracket CloseBracket Comparison Logical Assignment MathSign If Else For In While Input Output Def Class Variable Number Return END Error

%%
    Value:
        Variable Dot Variable | Variable OpenBraces Arithmetic CloseBraces | Variable | Number | Bool

    Identificator:
        Variable Dot Variable | Variable OpenBraces Arithmetic CloseBraces | Variable

    ReturnStatement:
        Return Delimiter | Return Value Delimiter

    AssignmentStatement:
        Identificator Assignment Arithmetic Delimiter | Identificator Assignment Read Delimiter | Identificator Assignment FunctionCall Delimiter | Identificator Assignment ArrayDeclaration Delimiter

    ArrayDeclaration: // "[" Arguments "]""
        OpenBraces Arguments CloseBraces

    ClassDeclaration:
        Class Variable OpenBracket CloseBracket DoubleDot Delimiter Block

    Function:
        Def Variable OpenBracket FunctionArguments CloseBracket DoubleDot Delimiter Block

    FunctionArguments: // Variable [Comma FunctionArgument] | empty
        Variable FuncArgsZeroOrMore | /* empty */

    FuncArgsZeroOrMore: // [Comma FunctionArgument]
        /* empty */ | FuncArgsZeroOrMore Comma FunctionArgument

    FunctionArgument: // Variable [Comma FunctionArgument]
        Variable FuncArgsZeroOrMore

    FunctionCall:
        Variable OpenBracket Arguments CloseBracket Delimiter

    Arguments: // Identificator ["," Argument] | empty
        Identificator ArgsZeroOrMore | /* empty */

    ArgsZeroOrMore: // ["," Argument]
        /* empty */ | ArgsZeroOrMore Comma Argument

    Argument: // Identificator ["," Argument]
        Identificator ArgsZeroOrMore

    IfStatement:
        If Logic DoubleDot Delimiter Block IfZeroOrMore

    IfZeroOrMore: // [Else DoubleDot Delimiter Block]
        /* empty */ | Else DoubleDot Delimiter Block

    WhileStatement:
        While Logic DoubleDot Delimiter Block

    ForStatement:
        For Value In Value DoubleDot Delimiter Block

    Logic:
        OpenBracketZeroOrMore LogicExpression LogicZeroOrMore CloseBracketZeroOrMore

    LogicZeroOrMore: // [Logical Logic]
        /* empty */ | LogicZeroOrMore Logical Logic

    LogicExpression:
        OpenBracketZeroOrMore Arithmetic LogicExprZeroOrMore CloseBracketZeroOrMore

    LogicExprZeroOrMore: // [Logical LogicExpression]
        /* empty */ | LogicExprZeroOrMore Logical LogicExpression

    OpenBracketZeroOrMore:
        /* empty */ | OpenBracketZeroOrMore OpenBracket

    CloseBracketZeroOrMore:
        /* empty */ | CloseBracketZeroOrMore CloseBracket

    Arithmetic: // ["("] Value [MathSign Arithmetic] [")"]
        OpenBracketZeroOrMore Value ArithmeticZeroOrMore CloseBracketZeroOrMore

    ArithmeticZeroOrMore: // [MathSign Arithmetic]
        /* empty */ | ArithmeticZeroOrMore MathSign Arithmetic

    InputStatement:
        Input OpenBracket CloseBracket Delimiter

    OutputStatement:
        Output OpenBracket Arithmetic CloseBracket Delimiter

    Statement:
        IfStatement | WhileStatement | ForStatement | AssignmentStatement | InputStatement | OutputStatement | ClassDeclaration | Function | FunctionCall | Delimiter

    ClassStatement:
        AssignmentStatement | Function | Delimiter

    FunctionStatement:
        Statement | ReturnStatement

    Block:
        TabZeroOrMore Statement Block | TabZeroOrMore ClassStatement Block | TabZeroOrMore FunctionStatement Block | /* empty */

    TabZeroOrMore:
        /* empty */ | TabZeroOrMore Tab

%%
