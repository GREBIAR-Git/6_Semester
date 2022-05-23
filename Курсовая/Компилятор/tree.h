#include<stdio.h>
#include<malloc.h>
#include "token.h"

#define COUNT 5

struct Node
{
	struct Token data;
	struct Node* parent;
	struct Node* next;
	struct Node* childs;
};

struct Node* AddChild(struct Token data, struct Node* node);

void AddParent(struct Token data, struct Node* node);

struct Node* NewNode(struct Token data);

void AddNext(struct Token data, struct Node* node);

void PrintTree(struct Node *root, int space);

void Print2D(struct Node *root);