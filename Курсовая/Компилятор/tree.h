#include<stdio.h>
#include<malloc.h>
#include "token.h"

#define COUNT 5

struct Node
{
	enum TerminalType type;
	struct Token data;
	struct Node* parent;
	struct Node* next;
	struct Node* childs;
};

struct Node* NewNode(struct Token data);
struct Node* NewNodeTerminal(enum TerminalType data);


struct Node* AddChild(struct Token data, struct Node* node);
struct Node* AddChildNode(struct Node* child, struct Node* node);
struct Node* AddChildTerminal(enum TerminalType data, struct Node* node);

void AddParent(struct Token data, struct Node* node);

struct Node* AddNext(struct Token data, struct Node* node);
struct Node* AddNextTerminal(enum TerminalType data, struct Node* node);

void PrintTree(struct Node *root, int space);
void Print2D(struct Node *root);