#include "tree.h"

struct Node* newNode(struct Token data)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

void print2DUtil(struct Node *root, int space)
{
	if (root == NULL)
		return;

	space += COUNT;

	print2DUtil(root->right, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n",  NameType(root->data.type));

	print2DUtil(root->left, space);
}

void print2D(struct Node *root)
{
    print2DUtil(root, 0);
}
