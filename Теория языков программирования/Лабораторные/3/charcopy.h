#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example call: charcopy(&str1, &str2);  where str1 and str2 are both of char * type

void charCopy(char ** destination, char ** str)
{
	free(*destination); // in case the function has already been called before
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
	memcpy(*destination, *str, strlen(*str) * sizeof(char));
	return;
}

void charCopyL(char ** destination, char ** str, int length)
{
	free(*destination); // in case the function has already been called before
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
    int min_length = strlen(*str) < length ? strlen(*str) : length;
	memcpy(*destination, *str, min_length * sizeof(char));
	return;
}

void charConcat(char ** destination, char ** str)
{
	free(*destination); // in case the function has already been called before
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
	memcpy(*destination, *str, (strlen(*destination) + strlen(*str)) * sizeof(char));
	return;
}

void charConcatL(char ** destination, char ** str, int length)
{
	free(*destination); // in case the function has already been called before
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
    int min_length = strlen(*destination) + strlen(*str) < strlen(*destination) + length ? strlen(*destination) + strlen(*str) : strlen(*destination) + length;
	memcpy(*destination, *str, min_length * sizeof(char));
	return;
}

void charConcat1(char ** destination, char ch)
{
	char* tmp;
	charCopy(&tmp, destination);
	free(*destination); // in case the function has already been called before
	*destination = (char *)calloc((strlen(tmp) + 2), sizeof(char));
	memcpy(*destination, tmp, strlen(tmp) * sizeof(char));
	memcpy(*destination + strlen(tmp), &ch, 1 * sizeof(char));
	char end = '\0';
	memcpy(*destination + strlen(tmp) + 1, &end, 1 * sizeof(char));
	free(tmp);
	return;
}