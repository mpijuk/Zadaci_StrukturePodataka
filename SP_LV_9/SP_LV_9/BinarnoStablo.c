#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


struct _BinarySearchTree;
typedef struct _BinarySearchTree* Node;

typedef struct _BinarySearchTree {
	int Element;
	Node Left;
	Node Right;
}BinarySearchTree;

Node MakeEmpty(Node);
Node Insert(Node, Node);
Node CreateNode(int);
Node FindElement(Node, int);
Node FindMin(Node);
Node FindMax(Node);
Node DeleteElement(Node, int);
void PrintInOrder(Node);

int main()
{
	Node Root = NULL;
	Node New = NULL;
	Node tmp;
	int y, x, j = 1;

	printf("Choose function:\n");
	printf("\tMake empty tree - 1\n");
	printf("\tInsert new element in tree - 2\n");
	printf("\tFind element - 3\n");
	printf("\tFind  MAX element - 4\n");
	printf("\tFind  MIN element - 5\n");
	printf("\tDelete element - 6\n");
	printf("\tPrint tree - 7\n");
	printf("\tExit - 0\n");

	while (j)
	{
		scanf("%d", &y);

		switch (y)
		{
		case 1:
			Root = MakeEmpty(Root);
			break;
		case 2:
			printf("Which element you want insert:\n");
			scanf("%d", &x);
			New = CreateNode(x);
			Root = Insert(Root, New);

			break;
		case 3:
			printf("Which element you want find:\n");
			scanf("%d", &x);
			tmp = FindElement(Root, x);
			if (tmp != NULL)
			{
				printf("Successfully found!\n");
			}
			break;
		case 4:
			tmp = FindMax(Root);
			if (tmp != NULL)
			{
				printf("Max. elemnt is: %d\n", tmp->Element);
			}
			break;
		case 5:
			tmp = FindMin(Root);
			if (tmp != NULL)
			{
				printf("Min element is: %d\n", tmp->Element);
			}
			break;
		case 6:
			printf("Which element you want delete:\n");
			scanf("%d", &x);
			Root = DeleteElement(Root, x);
			break;
		case 7:
			PrintInOrder(Root);
			printf("\n");
			break;
		case 0:
			j = 0;
			break;
		default:
			printf("Wrong choice!\n");
			break;
		}
	}

	return 0;
}

Node MakeEmpty(Node R) // Brise sve ili inicijlizira R na NULL
{
	if (R != NULL)
	{
		R->Left = MakeEmpty(R->Left);
		R->Right = MakeEmpty(R->Right);

		free(R);
	}
	return NULL;
}
Node CreateNode(int x)
{
	Node newEl = (Node)malloc(sizeof(BinarySearchTree));

	if (newEl == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	newEl->Element = x;
	newEl->Left = NULL;
	newEl->Right = NULL;

	return newEl;
}

Node Insert(Node R, Node newEl)
{
	if (R == NULL)
	{
		return newEl;
	}
	else if (newEl->Element > R->Element)
	{
		R->Right = Insert(R->Right, newEl);
	}
	else if (newEl->Element < R->Element)
	{
		R->Left = Insert(R->Left, newEl);
	}
	else
	{
		free(newEl);
	}

	return R;
}

Node FindElement(Node R, int x)
{
	if (R == NULL)
	{
		printf("Element %d don't exist!\n", x);
		return NULL;
	}
	else if (x < R->Element)
		return FindElement(R->Left, x);
	else if (x > R->Element)
		return FindElement(R->Right, x);

	return R; // Nije ni manji ni veci dakle to je taj!
}

Node FindMin(Node R)
{
	if (R == NULL)
	{
		printf("Tree is empty!\n");
		return NULL;
	}

	while (R->Left != NULL)
	{
		R = R->Left;
	}

	return R;
}

Node FindMax(Node R)
{
	if (R == NULL)
	{
		printf("Tree is empty!\n");
		return NULL;
	}

	while (R->Right != NULL)
	{
		R = R->Right;
	}

	return R;
}

Node DeleteElement(Node R, int x)
{
	if (R == NULL)
		return NULL;

	if (R->Element == x)
	{
		if (R->Left != NULL)
		{
			Node temp = FindMax(R->Left);
			R->Element = temp->Element;
			R->Left = DeleteElement(R->Left, temp->Element);
		}
		else if (R->Right != NULL)
		{
			Node temp = FindMin(R->Right);
			R->Element = temp->Element;
			R->Right = DeleteElement(R->Right, temp->Element);
		}
		else
		{
			free(R);
			return NULL;
		}
	}
	else if (R->Element > x)
	{
		R->Left = DeleteElement(R->Left, x);
	}
	else
	{
		R->Right = DeleteElement(R->Right, x);
	}

	return R;
}

void PrintInOrder(Node R)
{
	if (R == NULL)
	{
		return;
	}

	PrintInOrder(R->Left);

	printf("%d ", R->Element);

	PrintInOrder(R->Right);
}

