#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "charcopy.h"
#include <assert.h>
int tempCurrentToken;

int currentToken;

int bracketCountDifference;

int tokenLength;

struct Token * tokens;

char*** parsing_table;

int stackSize = 0;

char** stack;

void init()
{
	const int notTermCount = 9;
	const int termCount = 12;
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

	char* empty = "Empty";

	strcpy(parsing_table[0][0], "Create Table Name OpenBrackets Column PK FK CloseBrackets");
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

	strcpy(parsing_table[1][0], empty);
	strcpy(parsing_table[1][1], empty);
	strcpy(parsing_table[1][2], empty);
	strcpy(parsing_table[1][3], empty);
	strcpy(parsing_table[1][4], empty);
	strcpy(parsing_table[1][5], empty);
	strcpy(parsing_table[1][6], empty);
	strcpy(parsing_table[1][7], empty);
	strcpy(parsing_table[1][8], "Name Type Attributes Comma Column'");
	strcpy(parsing_table[1][9], empty);
	strcpy(parsing_table[1][10], empty);
	strcpy(parsing_table[1][11], empty);

	strcpy(parsing_table[2][0], empty);
	strcpy(parsing_table[2][1], empty);
	strcpy(parsing_table[2][2], "Epsilon");
	strcpy(parsing_table[2][3], empty);
	strcpy(parsing_table[2][4], empty);
	strcpy(parsing_table[2][5], empty);
	strcpy(parsing_table[2][6], empty);
	strcpy(parsing_table[2][7], empty);
	strcpy(parsing_table[2][8], "Name Type Attributes Comma Column'");
	strcpy(parsing_table[2][9], empty);
	strcpy(parsing_table[2][10], empty);
	strcpy(parsing_table[2][11], empty);

	strcpy(parsing_table[3][0], empty);
	strcpy(parsing_table[3][1], empty);
	strcpy(parsing_table[3][2], empty);
	strcpy(parsing_table[3][3], empty);
	strcpy(parsing_table[3][4], empty);
	strcpy(parsing_table[3][5], empty);
	strcpy(parsing_table[3][6], empty);
	strcpy(parsing_table[3][7], "Type");
	strcpy(parsing_table[3][8], empty);
	strcpy(parsing_table[3][9], empty);
	strcpy(parsing_table[3][10], empty);
	strcpy(parsing_table[3][11], empty);

	strcpy(parsing_table[4][0], empty);
	strcpy(parsing_table[4][1], empty);
	strcpy(parsing_table[4][2], empty);
	strcpy(parsing_table[4][3], empty);
	strcpy(parsing_table[4][4], empty);
	strcpy(parsing_table[4][5], empty);
	strcpy(parsing_table[4][6], "Attributes");
	strcpy(parsing_table[4][7], empty);
	strcpy(parsing_table[4][8], empty);
	strcpy(parsing_table[4][9], empty);
	strcpy(parsing_table[4][10], empty);
	strcpy(parsing_table[4][11], empty);

	strcpy(parsing_table[5][0], empty);
	strcpy(parsing_table[5][1], empty);
	strcpy(parsing_table[5][2], "Primary Key OpenBrackets Names CloseBrackets");
	strcpy(parsing_table[5][3], empty);
	strcpy(parsing_table[5][4], empty);
	strcpy(parsing_table[5][5], empty);
	strcpy(parsing_table[5][6], empty);
	strcpy(parsing_table[5][7], empty);
	strcpy(parsing_table[5][8], empty);
	strcpy(parsing_table[5][9], empty);
	strcpy(parsing_table[5][10], empty);
	strcpy(parsing_table[5][11], empty);

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
	strcpy(parsing_table[6][10], "Epsilon");
	strcpy(parsing_table[6][11], "Comma Foreign Key OpenBrackets Names CloseBrackets References Name OpenBrackets Names CloseBrackets FK");

	strcpy(parsing_table[7][0], empty);
	strcpy(parsing_table[7][1], empty);
	strcpy(parsing_table[7][2], empty);
	strcpy(parsing_table[7][3], empty);
	strcpy(parsing_table[7][4], empty);
	strcpy(parsing_table[7][5], empty);
	strcpy(parsing_table[7][6], empty);
	strcpy(parsing_table[7][7], empty);
	strcpy(parsing_table[7][8], "Name Names'");
	strcpy(parsing_table[7][9], empty);
	strcpy(parsing_table[7][10], empty);
	strcpy(parsing_table[7][11], empty);

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
	strcpy(parsing_table[8][10], "Epsilon");
	strcpy(parsing_table[8][11], "Comma Name Names'");
}

int RowNonTerminal()
{
	if (CompareStrings2(stack[stackSize - 1], "Create_table"))
	{
		return 0;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Column"))
	{
		return 1;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Column'"))
	{
		return 2;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Type"))
	{
		return 3;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Attributes"))
	{
		return 4;
	}
	else if (CompareStrings2(stack[stackSize - 1], "PK"))
	{
		return 5;
	}
	else if (CompareStrings2(stack[stackSize - 1], "FK"))
	{
		return 6;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Names"))
	{
		return 7;
	}
	else if (CompareStrings2(stack[stackSize - 1], "Names'"))
	{
		return 8;
	}
}

bool Terminal(char* str)
{
	if (CompareStrings2(str, "Create")||
		CompareStrings2(str, "Table") ||
		CompareStrings2(str, "Primary")||
		CompareStrings2(str, "Foreign")||
		CompareStrings2(str, "Key")||
		CompareStrings2(str, "References")||
		CompareStrings2(str, "Attributes")||
		CompareStrings2(str, "Type")||
		CompareStrings2(str, "Name")||
		CompareStrings2(str, "OpenBrackets")||
		CompareStrings2(str, "CloseBrackets")||
		CompareStrings2(str, "Comma"))
	{
		return true;
	}
	return false;
}

bool CompareStrings2(char* str1,char * str2)
{
	if (strlen(str1) <= strlen(str2))
	{
		for (int i = 0; i < strlen(str1); i++)
		{
			if (str2[i] != str1[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

char** str_split(char* a_str, const char a_delim, int* count)
{
	char** result = 0;
	*count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			(*count)++;
			last_comma = tmp;
		}
		tmp++;
	}

	(*count) += last_comma < (a_str + strlen(a_str) - 1);

	(*count)++;

	result = malloc(sizeof(char*) * (*count));

	if (result)
	{
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < (*count));
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == (*count) - 1);
		*(result + idx) = 0;
	}

	return result;
}


void PushStack(char * newElement)
{
	char** temp = malloc(stackSize * sizeof(char*));
	stackSize++;
	if (stackSize > 1)
	{
		for (int i = 0; i < stackSize - 1; i++)
		{
			charCopy(&(temp[i]) , &(stack[i]));
		}
	}
	stack = realloc(stack, stackSize*sizeof(char*));
	for (int i = 0; i < stackSize - 1; i++)
	{
		charCopy(&(stack[i]), &(temp[i]));
	}
	charCopy(&(stack[stackSize - 1]), &newElement);
}

void PopStack()
{
	if (stackSize > 0)
	{
		stackSize--;
	}
}

void Parser(struct Token * token, int tokenQuantity)
{
	tokens = token;
	tokenLength = tokenQuantity;
	currentToken = 0;
	printf("\nSTART_PARSER\n");
	stack = malloc(0);
	init();

	PushStack("Create_table");

	int i = 0;
	do
	{
		if (Terminal(stack[stackSize - 1]))
		{
			PopStack();
			i++;
		}
		else
		{
			int r = RowNonTerminal();
			int c = tokens[i].type;
			if (!CompareStrings2(parsing_table[r][c], "Epsilon"))
			{
				if (!CompareStrings2(parsing_table[r][c], "Empty"))
				{
					PopStack();

					char* copy;
					charCopy(&copy, &(parsing_table[r][c]));

					int count;
					char** elems = str_split(copy, ' ', &count);
					for (int f = count-2; f>=0; f--)
					{
						PushStack(elems[f]);
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				PopStack();
			}
		}
	} while (stackSize != 0);

	if (tokens[i-1].type == CloseBrackets)
	{
		printf("\nNo one error\n");
	}
	else
	{
		printf("%s", tokens[i].value);
		printf("\nError\n");
	}
	printf("\nEND_PARSER\n");
}