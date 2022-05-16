#include "parser.h"
int tempCurrentToken;

int currentToken;

int bracketCountDifference;

int tokenLength;

struct Token * tokens;

char** parsing_table;
      
void Parser(struct Token * token, int tokenQuantity)
{
	
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	
	printf("\nEND_PARSER\n");
}