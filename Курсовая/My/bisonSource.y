%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define YYDEBUG 1

int yyparse(void);
int yylex(void);
int yywrap();
void yyerror(const char *str);

bool errors = false;

void charCopy(char ** destination, char ** str)
{
	if (!(*destination))
	{
		free(*destination); // in case the function has already been called before
	}
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
	memcpy(*destination, *str, strlen(*str) * sizeof(char));
	return;
}

struct TreeNode
{
    char * text;
    struct TreeNode * next;
    struct TreeNode * child;
};

struct TreeNode * treeRoot;

void setChild(struct TreeNode * branch, struct TreeNode * child1)
{
    struct TreeNode * current = branch->child;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = child1;
}

void newNode(struct TreeNode * branch, char * text1)
{
    branch = malloc(sizeof(struct TreeNode));
    charCopy(&(branch->text), &text1);
    branch->next = NULL;
    branch->child = NULL;
}

void setLeave(struct TreeNode * branch, char * child1)
{
    struct TreeNode * current = branch->child;
    while(current->next != NULL)
    {
        current = current->next;
    }
    newNode(current->next, child1);
}

void displayBranch(struct TreeNode * branch, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printf("%s", branch->text);
    struct TreeNode * current = branch->child;
    while (current->next != NULL)
    {
        displayBranch(current, depth + 1);
        current = current->next;
    }
}

%}

%union {
    char* str;
    struct TreeNode* treeNode;
}

%token<str> DelimiterY
%token<str> TabY
%token<str> CommaY
%token<str> DotY
%token<str> DoubleDotY
%token<str> BoolY
%token<str> OpenBracesY
%token<str> CloseBracesY
%token<str> OpenBracketY
%token<str> CloseBracketY
%token<str> ComparisonY
%token<str> LogicalY
%token<str> AssignmentY
%token<str> MathSignY
%token<str> IfY
%token<str> ElseY
%token<str> ForY
%token<str> InY
%token<str> WhileY
%token<str> InputY
%token<str> OutputY
%token<str> DefY
%token<str> ClassY
%token<str> VariableY
%token<str> NumberY
%token<str> ReturnY
%token<str> ENDY
%token<str> ErrorY

%type<treeNode> Program
%type<treeNode> Statements
%type<treeNode> Statement
%type<treeNode> Block
%type<treeNode> IfStatement
%type<treeNode> Else
%type<treeNode> WhileStatement
%type<treeNode> ForStatement
%type<treeNode> Value
%type<treeNode> Identificator
%type<treeNode> ReturnStatement
%type<treeNode> AssignmentStatement
%type<treeNode> ArrayDeclaration
%type<treeNode> ClassDeclaration
%type<treeNode> Function
%type<treeNode> FunctionCall
%type<treeNode> Arguments
%type<treeNode> CommaValue
%type<treeNode> Logic
%type<treeNode> Arithmetic
%type<treeNode> Input
%type<treeNode> Output
%type<treeNode> TabOneOrMore

%start Program


%%
    Program:
        Statements ENDY
        {
            newNode(treeRoot, "Program");
            setChild(treeRoot, $1);
            setLeave(treeRoot, $2);
            printf("\n{No errors}");
        };

    Statements: /* empty */
        | Statements Statement
        {
            newNode($$, "Statements");
            setChild($$, $1);
            setChild($$, $2);
        };

    Statement:
        IfStatement
        {
            newNode($$, "Statement");
            setChild($$, $1);
        };
        | WhileStatement
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | ForStatement
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | AssignmentStatement
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | Input
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | Output
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | ClassDeclaration
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | Function
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | FunctionCall
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | ReturnStatement
        {
            newNode($$, "Statement");
            setChild($$, $1);
        }
        | DelimiterY
        {
            newNode($$, "Statement");
            setLeave($$, $1);
        };

    Block: /* empty */
        | Block TabOneOrMore Statement
        {
            newNode($$, "Block");
            setChild($$, $1);
            setChild($$, $2);
            setChild($$, $3);
        };

    IfStatement:
        IfY Logic DoubleDotY DelimiterY Block Else
        {
            newNode($$, "IfStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setLeave($$, $4);
            setChild($$, $5);
            setChild($$, $6);
        }
        | IfY Value DoubleDotY DelimiterY Block Else
        {
            newNode($$, "IfStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setLeave($$, $4);
            setChild($$, $5);
            setChild($$, $6);
        };

    Else: /* empty */
        | ElseY DoubleDotY DelimiterY Block
        {
            newNode($$, "Else");
            setLeave($$, $1);
            setLeave($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
        };

    WhileStatement:
        WhileY Logic DoubleDotY DelimiterY Block
        {
            newNode($$, "WhileStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setLeave($$, $4);
            setChild($$, $5);
        }
        | WhileY Value DoubleDotY DelimiterY Block
        {
            newNode($$, "WhileStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setLeave($$, $4);
            setChild($$, $5);
        };

    ForStatement:
        ForY Value InY Value DoubleDotY DelimiterY Block
        {
            newNode($$, "ForStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
            setLeave($$, $6);
            setChild($$, $7);
        };

    Value:
        Identificator
        {
            newNode($$, "Value");
            setChild($$, $1);
        }
        | NumberY
        {
            newNode($$, "Value");
            setLeave($$, $1);
        }
        | BoolY
        {
            newNode($$, "Value");
            setLeave($$, $1);
        };

    Identificator:
        VariableY DotY VariableY
        {
            newNode($$, "Identificator");
            setLeave($$, $1);
            setLeave($$, $2);
            setLeave($$, $3);
        }
        | VariableY OpenBracesY Arithmetic CloseBracesY
        {
            newNode($$, "Identificator");
            setLeave($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | VariableY OpenBracesY Value CloseBracesY
        {
            newNode($$, "Identificator");
            setLeave($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | VariableY
        {
            newNode($$, "Identificator");
            setLeave($$, $1);
        };

    ReturnStatement:
        ReturnY DelimiterY
        {
            newNode($$, "ReturnStatement");
            setLeave($$, $1);
            setLeave($$, $2);
        }
        | ReturnY Value DelimiterY
        {
            newNode($$, "ReturnStatement");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
        };

    AssignmentStatement:
        Identificator AssignmentY Value DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | Identificator AssignmentY Logic DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | Identificator AssignmentY Arithmetic DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | Identificator AssignmentY Input DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | Identificator AssignmentY FunctionCall DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        }
        | Identificator AssignmentY ArrayDeclaration DelimiterY
        {
            newNode($$, "AssignmentStatement");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        };

    ArrayDeclaration:
        OpenBracesY Arguments CloseBracesY
        {
            newNode($$, "ArrayDeclaration");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
        };

    ClassDeclaration:
        ClassY VariableY OpenBracketY CloseBracketY DoubleDotY DelimiterY Block
        {
            newNode($$, "ClassDeclaration");
            setLeave($$, $1);
            setLeave($$, $2);
            setLeave($$, $3);
            setLeave($$, $4);
            setLeave($$, $5);
            setLeave($$, $6);
            setChild($$, $7);
        };

    Function:
        DefY Identificator OpenBracketY Arguments CloseBracketY DoubleDotY DelimiterY Block
        {
            newNode($$, "Function");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
            setLeave($$, $6);
            setLeave($$, $7);
            setChild($$, $8);
        };

    FunctionCall:
        Identificator OpenBracketY Arguments CloseBracketY DelimiterY
        {
            newNode($$, "FunctionCall");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
            setLeave($$, $5);
        };

    Arguments: /* empty */
        | Value CommaValue
        {
            newNode($$, "Arguments");
            setChild($$, $1);
            setChild($$, $2);
        };

    CommaValue:  /* empty */
        | CommaValue CommaY Value
        {
            newNode($$, "CommaValue");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        };

    Logic:
        Value ComparisonY Value
        {
            newNode($$, "Logic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | Logic LogicalY Logic
        {
            newNode($$, "Logic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | OpenBracketY Value ComparisonY Value CloseBracketY
        {
            newNode($$, "Logic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        }
        | OpenBracketY Logic LogicalY Logic CloseBracketY
        {
            newNode($$, "Logic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        };

    Arithmetic:
        Value MathSignY Value
        {
            newNode($$, "Arithmetic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | Arithmetic MathSignY Arithmetic
        {
            newNode($$, "Arithmetic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | Arithmetic MathSignY Value
        {
            newNode($$, "Arithmetic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | Value MathSignY Arithmetic
        {
            newNode($$, "Arithmetic");
            setChild($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
        }
        | OpenBracketY Value MathSignY Value CloseBracketY
        {
            newNode($$, "Arithmetic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        }
        | OpenBracketY Arithmetic MathSignY Arithmetic CloseBracketY
        {
            newNode($$, "Arithmetic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        }
        | OpenBracketY Arithmetic MathSignY Value CloseBracketY
        {
            newNode($$, "Arithmetic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        }
        | OpenBracketY Value MathSignY Arithmetic CloseBracketY
        {
            newNode($$, "Arithmetic");
            setLeave($$, $1);
            setChild($$, $2);
            setLeave($$, $3);
            setChild($$, $4);
            setLeave($$, $5);
        };

    Input:
        InputY OpenBracketY CloseBracketY
        {
            newNode($$, "Input");
            setLeave($$, $1);
            setLeave($$, $2);
            setLeave($$, $3);
        };

    Output:
        OutputY OpenBracketY Value CloseBracketY
        {
            newNode($$, "Output");
            setLeave($$, $1);
            setLeave($$, $2);
            setChild($$, $3);
            setLeave($$, $4);
        };

    TabOneOrMore:
        TabY
        {
            newNode($$, "TabOneOrMore");
            setLeave($$, $1);
        }
        | TabOneOrMore TabY
        {
            newNode($$, "OuTabOneOrMoreput");
            setChild($$, $1);
            setLeave($$, $2);
        };

%%

int yywrap()
{
    return 1;
}

void yyerror(const char *str)
{
    errors = true;
    fprintf(stderr,"\nERROR: %s",str);
}

main()
{
    yyparse();
    if (!errors)
    {
        displayBranch(treeRoot, 0);
    }
}

int yydebug = 0;