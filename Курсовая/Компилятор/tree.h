#include<stdio.h>
#include<malloc.h>
#include "token.h"

#define COUNT 5

struct Node
{
	struct Token data;
	struct Node* left, *right;
};

struct Node* newNode(struct Token data);

void print2DUtil(struct Node *root, int space);

void print2D(struct Node *root);