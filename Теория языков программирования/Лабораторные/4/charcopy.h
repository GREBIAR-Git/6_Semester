#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example call: charcopy(&str1, &str2);  where str1 and str2 are both of char * type

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

void charCopyL(char ** destination, char ** str, int length)
{
	if (!(*destination))
	{
		free(*destination); // in case the function has already been called before
	}
	*destination = (char *)calloc(1, (strlen(*str) + 1) * sizeof(char));
    int min_length = strlen(*str) < length ? strlen(*str) : length;
	memcpy(*destination, *str, min_length * sizeof(char));
	return;
}

void charConcat(char ** destination, char ** str)
{
	char* tmp;
	charCopy(&tmp, destination);
	if (!(*destination))
	{
		free(*destination); // in case the function has already been called before
	}
	*destination = (char *)calloc(1, (strlen(*destination) + strlen(*str)) * sizeof(char));
	memcpy(*destination, tmp, strlen(tmp) * sizeof(char));
	memcpy(*destination + strlen(tmp) * sizeof(char), *str, (strlen(*str)) * sizeof(char));
	return;
}

void charConcatL(char ** destination, char ** str, int length)
{
	char* tmp;
	charCopy(&tmp, destination);
	if (!(*destination))
	{
		free(*destination); // in case the function has already been called before
	}
    int min_length = strlen(*str) < length ? strlen(*str) : length;
	*destination = (char *)calloc(1, (min_length + 1) * sizeof(char));
	memcpy(*destination, tmp, strlen(tmp) * sizeof(char));
	memcpy(*destination + strlen(tmp) * sizeof(char), *str, min_length * sizeof(char));
	return;
}

void charConcat1(char ** destination, char ch)
{
	char* tmp;
	charCopy(&tmp, destination);
	if (!(*destination))
	{
		free(*destination); // in case the function has already been called before
	}
	*destination = (char *)calloc((strlen(tmp) + 2), sizeof(char));
	memcpy(*destination, tmp, strlen(tmp) * sizeof(char));
	memcpy(*destination + strlen(tmp), &ch, 1 * sizeof(char));
	char end = '\0';
	memcpy(*destination + strlen(tmp) + 1, &end, 1 * sizeof(char));
	free(tmp);
	return;
}