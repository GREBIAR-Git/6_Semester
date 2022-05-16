#include <string.h>
#include <stdlib.h>
#include "parser.h"

int tempCurrentToken;

int currentToken;

int bracketCountDifference;

int tokenLength;

struct Token * tokens;

char*** parsing_table;

void init()
{
	const int notTermCount = 9;
	const int termCount = 14;
	const int stringSize = 200;

	parsing_table = malloc(notTermCount*sizeof(char**));
	for(int i = 0; i < notTermCount; i++)
	{
		parsing_table[i] = malloc(termCount*sizeof(char*));
		for (int j = 0; j < termCount; j++)
		{
			parsing_table[i][j] = malloc(stringSize*sizeof(char));
		}
	}

	char* empty = "empty";

	strcpy(parsing_table[0][0], "create table name (column PK FK)");
	strcpy(parsing_table[0][1], empty);
	strcpy(parsing_table[0][2], empty);
	strcpy(parsing_table[0][3], empty);
	strcpy(parsing_table[0][4], empty);
	strcpy(parsing_table[0][5], empty);
	strcpy(parsing_table[0][6], empty);
	strcpy(parsing_table[0][7], empty);
	strcpy(parsing_table[0][8], empty);
	strcpy(parsing_table[0][9], empty);
	strcpy(parsing_table[0][10], empty);
	strcpy(parsing_table[0][11], empty);
	strcpy(parsing_table[0][12], empty);
	strcpy(parsing_table[0][13], empty);

	strcpy(parsing_table[1][0], empty);
	strcpy(parsing_table[1][1], empty);
	strcpy(parsing_table[1][2], empty);
	strcpy(parsing_table[1][3], empty);
	strcpy(parsing_table[1][4], empty);
	strcpy(parsing_table[1][5], empty);
	strcpy(parsing_table[1][6], empty);
	strcpy(parsing_table[1][7], empty);
	strcpy(parsing_table[1][8], empty);
	strcpy(parsing_table[1][9], empty);
	strcpy(parsing_table[1][10], "name type attributes, column’");
	strcpy(parsing_table[1][11], empty);
	strcpy(parsing_table[1][12], empty);
	strcpy(parsing_table[1][13], empty);

	strcpy(parsing_table[2][0], empty);
	strcpy(parsing_table[2][1], empty);
	strcpy(parsing_table[2][2], "e");
	strcpy(parsing_table[2][3], empty);
	strcpy(parsing_table[2][4], empty);
	strcpy(parsing_table[2][5], empty);
	strcpy(parsing_table[2][6], empty);
	strcpy(parsing_table[2][7], empty);
	strcpy(parsing_table[2][8], empty);
	strcpy(parsing_table[2][9], empty);
	strcpy(parsing_table[2][10], "name type attributes, column’");
	strcpy(parsing_table[2][11], empty);
	strcpy(parsing_table[2][12], empty);
	strcpy(parsing_table[2][13], empty);

	strcpy(parsing_table[3][0], empty);
	strcpy(parsing_table[3][1], empty);
	strcpy(parsing_table[3][2], empty);
	strcpy(parsing_table[3][3], empty);
	strcpy(parsing_table[3][4], empty);
	strcpy(parsing_table[3][5], empty);
	strcpy(parsing_table[3][6], empty);
	strcpy(parsing_table[3][7], empty);
	strcpy(parsing_table[3][8], "int");
	strcpy(parsing_table[3][9], "char");
	strcpy(parsing_table[3][10], empty);
	strcpy(parsing_table[3][11], empty);
	strcpy(parsing_table[3][12], empty);
	strcpy(parsing_table[3][13], empty);

	strcpy(parsing_table[4][0], empty);
	strcpy(parsing_table[4][1], empty);
	strcpy(parsing_table[4][2], empty);
	strcpy(parsing_table[4][3], empty);
	strcpy(parsing_table[4][4], empty);
	strcpy(parsing_table[4][5], empty);
	strcpy(parsing_table[4][6], "null");
	strcpy(parsing_table[4][7], "not null");
	strcpy(parsing_table[4][8], empty);
	strcpy(parsing_table[4][9], empty);
	strcpy(parsing_table[4][10], empty);
	strcpy(parsing_table[4][11], empty);
	strcpy(parsing_table[4][12], empty);
	strcpy(parsing_table[4][13], empty);

	strcpy(parsing_table[5][0], empty);
	strcpy(parsing_table[5][1], empty);
	strcpy(parsing_table[5][2], "primary key (names)");
	strcpy(parsing_table[5][3], empty);
	strcpy(parsing_table[5][4], empty);
	strcpy(parsing_table[5][5], empty);
	strcpy(parsing_table[5][6], empty);
	strcpy(parsing_table[5][7], empty);
	strcpy(parsing_table[5][8], empty);
	strcpy(parsing_table[5][9], empty);
	strcpy(parsing_table[5][10], empty);
	strcpy(parsing_table[5][11], empty);
	strcpy(parsing_table[5][12], empty);
	strcpy(parsing_table[5][13], empty);

	strcpy(parsing_table[6][0], empty);
	strcpy(parsing_table[6][1], empty);
	strcpy(parsing_table[6][2], empty);
	strcpy(parsing_table[6][3], empty);
	strcpy(parsing_table[6][4], empty);
	strcpy(parsing_table[6][5], empty);
	strcpy(parsing_table[6][6], empty);
	strcpy(parsing_table[6][7], empty);
	strcpy(parsing_table[6][8], empty);
	strcpy(parsing_table[6][9], empty);
	strcpy(parsing_table[6][10], empty);
	strcpy(parsing_table[6][11], empty);
	strcpy(parsing_table[6][12], "e");
	strcpy(parsing_table[6][13], ", foreign key (names) references name (names) FK");

	strcpy(parsing_table[7][0], empty);
	strcpy(parsing_table[7][1], empty);
	strcpy(parsing_table[7][2], empty);
	strcpy(parsing_table[7][3], empty);
	strcpy(parsing_table[7][4], empty);
	strcpy(parsing_table[7][5], empty);
	strcpy(parsing_table[7][6], empty);
	strcpy(parsing_table[7][7], empty);
	strcpy(parsing_table[7][8], empty);
	strcpy(parsing_table[7][9], empty);
	strcpy(parsing_table[7][10], "name names’");
	strcpy(parsing_table[7][11], empty);
	strcpy(parsing_table[7][12], empty);
	strcpy(parsing_table[7][13], empty);

	strcpy(parsing_table[8][0], empty);
	strcpy(parsing_table[8][1], empty);
	strcpy(parsing_table[8][2], empty);
	strcpy(parsing_table[8][3], empty);
	strcpy(parsing_table[8][4], empty);
	strcpy(parsing_table[8][5], empty);
	strcpy(parsing_table[8][6], empty);
	strcpy(parsing_table[8][7], empty);
	strcpy(parsing_table[8][8], empty);
	strcpy(parsing_table[8][9], empty);
	strcpy(parsing_table[8][10], empty);
	strcpy(parsing_table[8][11], empty);
	strcpy(parsing_table[8][12], "e");
	strcpy(parsing_table[8][13], ",name names’");
}
      
void Parser(struct Token * token, int tokenQuantity)
{
	
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	
	init();

	printf("\nEND_PARSER\n");
}