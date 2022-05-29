#include "tree.h"

struct Node* NewNode(struct Token data)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->data = data;
	node->type = Terminal;
	node->next = node->childs = NULL;
	return node;
}

struct Node* NewNodeTerminal(enum NonTerminalType data)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->type = data;
	node->next = node->childs = NULL;
	return node;
}

struct Node * AddChild(struct Token data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->data = data;
		node->type = Terminal;
		node->next = node->childs = NULL;
		return node;
	}
	else
	{
		if (node->childs == NULL)
		{
			node->childs = malloc(sizeof(struct Node));
			node->childs->data = data;
			node->childs->type = Terminal;
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
			(*temp)->next->type = Terminal;
			(*temp)->next->data = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
			return (*temp)->next;
		}
	}
}

struct Node* AddChildTerminal(enum NonTerminalType data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->type = data;
		node->next = node->childs = NULL;
		return node;
	}
	else
	{
		if (node->childs == NULL)
		{
			node->childs = malloc(sizeof(struct Node));
			node->childs->type = data;
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
			(*temp)->next->type = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
			return (*temp)->next;
		}
	}
}

struct Node* AddChildNode(struct Node* child, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->childs = child;
		child->parent = node;
		return child;
	}
	else
	{
		if (node->childs == NULL)
		{
			struct Node** temp = &child;
			while ((*temp)->next != NULL)
			{
				(*temp)->next->parent = node;
				temp = (&((*temp)->next));
			}
			node->childs = malloc(sizeof(struct Node));
			node->childs = child;
			node->childs->parent = node;

			return child;
		}
		struct Node** temp2 = &node->childs;
		while ((*temp2)->next != NULL)
		{
			temp2 = (&((*temp2)->next));
		}
		if ((*temp2)->next == NULL)
		{
			struct Node** temp1 = &child;
			while ((*temp1)->next != NULL)
			{
				(*temp1)->next->parent = node;
				temp1 = (&((*temp1)->next));
			}

			(*temp2)->next = malloc(sizeof(struct Node));
			(*temp2)->next = child;
			(*temp2)->next->parent = node;

			return child;
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

struct Node * AddNext(struct Token data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->data = data;
		node->type = Terminal;
		node->next = node->childs = NULL;
		return node;
	}
	else
	{
		if (node->next == NULL)
		{
			node->next = malloc(sizeof(struct Node));
			node->next->data = data;
			node->next->type = Terminal;
			node->next->parent = node->parent;
			node->next->next = node->next->childs = NULL;
			return node->next;
		}
		struct Node** temp = &node->next;
		while ((*temp)->next != NULL)
		{
			temp = (&((*temp)->next));
		}
		if ((*temp)->next == NULL)
		{
			(*temp)->next = malloc(sizeof(struct Node));
			(*temp)->next->parent = node->parent;
			(*temp)->next->data = data;
			(*temp)->next->type = Terminal;
			(*temp)->next->next = (*temp)->next->childs = NULL;
			return (*temp)->next;
		}
	}
}

struct Node* AddNextTerminal(enum NonTerminalType data, struct Node* node)
{
	if (node == NULL)
	{
		node = malloc(sizeof(struct Node));
		node->type = data;
		node->next = node->childs = NULL;
		return node;
	}
	else
	{
		if (node->next == NULL)
		{
			node->next = malloc(sizeof(struct Node));
			node->next->type = data;
			node->next->parent = node->parent;
			node->next->next = node->next->childs = NULL;
			return node->next;
		}
		struct Node** temp = &node->next;
		while ((*temp)->next != NULL)
		{
			temp = (&((*temp)->next));
		}
		if ((*temp)->next == NULL)
		{
			(*temp)->next = malloc(sizeof(struct Node));
			(*temp)->next->parent = node->parent;
			(*temp)->next->type = data;
			(*temp)->next->next = (*temp)->next->childs = NULL;
			return (*temp)->next;
		}
	}
}

void PrintTree(struct Node *root, int space)
{
	if (root == NULL)
		return;
	for (int i = 0; i < space; i++)
		if(i==space-4)
		{
			printf("|");
		}
		else if (i>space-4)
		{
			printf("-");
		}
		else
		{
			printf(" ");
		}
	if (root->type == Terminal)
	{
		if (root->childs == NULL || root->data.type == Variable || root->data.type == MathSign || root->data.type == Comparison || root->data.type == Logical)
		{
			printf("%s - %s\n", NameType(root->data.type), ((*root).data.value));
		}
		else
		{
			printf("%s\n", NameType(root->data.type));
		}
	}
	else
	{
		printf("%s\n", NameNonTerminalType(root->type));
	}
	PrintTree(root->childs, space + COUNT);
	PrintTree(root->next, space);
}

void Print2D(struct Node *root)
{
	printf("\nTree: \n\n");
    PrintTree(root, 0);
	printf("\nTree end; \n");
}
