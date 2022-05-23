#include "tree.h"

struct Node* NewNode(struct Token data)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->data = data;
	node->next = node->childs = NULL;
	return node;
}

struct Node * AddChild(struct Token data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->data = data;
		node->next = node->childs = NULL;
		return node;
	}
	else
	{
		if (node->childs == NULL)
		{
			node->childs = malloc(sizeof(struct Node));
			node->childs->data = data;
			node->childs->next = node->childs->childs = NULL;
			node->childs->parent = node;
			return node->childs;
		}
		struct Node** temp = &node->childs;
		
		while ((*temp)->next != NULL)
		{
			temp = (&((*temp)->next));
		}
		if ((*temp)->next == NULL)
		{
			(*temp)->next = malloc(sizeof(struct Node));
			(*temp)->next->parent = node;
			(*temp)->next->data = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
			return (*temp)->next;
		}
	}
}

void AddParent(struct Token data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->data = data;
		node->next = node->childs = NULL;
	}
	else
	{
		if (node->parent == NULL)
		{
			node->parent = malloc(sizeof(struct Node));
			node->parent->data = data;
			node->parent->next = NULL;
			node->parent->childs = node;
			return;
		}
		struct Node** temp = &node->childs;

		while ((*temp)->next != NULL)
		{
			temp = (&((*temp)->next));
		}
		if ((*temp)->next == NULL)
		{
			(*temp)->next->parent = node;
			(*temp)->next = malloc(sizeof(struct Node));
			(*temp)->next->data = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
		}
	}
}

void AddNext(struct Token data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->data = data;
		node->next = node->childs = NULL;
	}
	else
	{
		if (node->next== NULL)
		{
			node->next = malloc(sizeof(struct Node));
			node->next->data = data;
			node->next->next = node->next->childs = NULL;
			return;
		}
		struct Node** temp = &node->next;

		while ((*temp)->next != NULL)
		{
			temp = (&((*temp)->next));
		}
		if ((*temp)->next == NULL)
		{
			(*temp)->next = malloc(sizeof(struct Node));
			(*temp)->next->parent = (*temp)->parent;
			(*temp)->next->data = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
		}
	}
}

void PrintTree(struct Node *root, int space)
{
	if (root == NULL)
		return;
	for (int i = 0; i < space; i++)
		printf(" ");
	if (root->childs == NULL)
	{
		printf("%s - %s\n", NameType(root->data.type), ((*root).data.value));
	}
	else
	{
		printf("%s\n", NameType(root->data.type));
	}
	PrintTree(root->childs, space+ COUNT);
	PrintTree(root->next, space);
}

void Print2D(struct Node *root)
{
	printf("\nTree: \n\n");
    PrintTree(root, 0);
	printf("\nTree end; \n");
}
