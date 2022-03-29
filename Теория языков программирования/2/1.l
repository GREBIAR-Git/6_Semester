%{
    #include <string.h>
    struct Token
    {
        char *name;
        char *value;
    };
    int textbyf = 0;
    char *name;
    char *value;
    struct Token tokens[50];
    int idxToken=0;
%}


%%

:= {name = "assignment"; value = yytext;textbyf+=1;yymore();}
var|if|then|else|begin|end {name = "keyword"; value = yytext; textbyf+=1;yymore();}
or|and {name = "logic operation"; value = yytext;textbyf+=1;yymore();}
\<|\>|\= {name = "comparison sign"; value = yytext;textbyf+=1;yymore();}
; {name = "delimiter"; value = yytext;textbyf+=1;yymore();}
round {name = "round"; value = yytext;textbyf+=1;yymore();}
: {name = "colon"; value = yytext;textbyf+=1;yymore();}
\( {name = "open bracket"; value = yytext;textbyf+=1;yymore();}
\) {name = "close bracket"; value = yytext;textbyf+=1;yymore();}
\-|\+|\-|\*|\/ {name = "operation sign"; value = yytext;textbyf+=1;yymore();}
[0-9]+.|,[0-9]+ {name = "decimal"; value = yytext; textbyf+=1;yymore();}
[0-9]* {name = "digit"; value = yytext;textbyf+=1;yymore();}
[a-z|A-Z][a-z|A-Z|0-9]* {name = "identificator"; value = yytext;textbyf+=1;yymore();}
[ \t\n] {
        if(textbyf==1)
        {
            printf("%s-\t\t%s",name,value); 
            textbyf=0;
        }
        else
        {
            printf("Error - \t\t%s", value);
            textbyf=0;
        }
    }
. { textbyf+=1;yymore();}
%%

int yywrap()
{

}

int main()
{
    FILE *fp;
    char *filename = "1.txt";
    fp = fopen(filename,"r");
    yyin = fp;
    yylex();
    return 0;
}