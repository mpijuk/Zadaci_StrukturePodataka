#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Data_Size (11)
#define Max_Char (256)
#define File_Name_Size (324)

struct Tree;
typedef struct Tree* Node;
typedef struct Tree {
	char Element[Data_Size];
	Node Right;
	Node Left;
}BinaryTree;

struct _Stack;
typedef struct _Stack* Position;
typedef struct _Stack {
	Node TreeNode;
	Position Next;
}Stack;

Node ReadPostfix(char *);
Node CreateNode(char*);
int PushStack(Position, Node);
Node PopStack(Position);
int isNumber(char *);
char* PrintInOrder(Node, char*);
int WriteInfix(char*, char*);

int main()
{
	char filename1[File_Name_Size] = { 0 };
	char filename2[File_Name_Size] = { 0 };

	Node root = NULL;
	char infix[Max_Char] = { 0 };
	char* p;
	
	printf("Type file name: \n");
	scanf(" %s", filename1);

	root = ReadPostfix(filename1);
	p =PrintInOrder(root, infix);
	
	printf("Type file name: \n");
	scanf(" %s", filename2);

	WriteInfix(filename2, p);

	return 0;
}

Node ReadPostfix(char* filename)
{
	FILE* read = NULL;
	Node newEl = NULL;
	Node result = NULL, check = NULL;
	char Line[Max_Char] = { 0 };
	char data[Data_Size] = { 0 };
	int res = 0, n = 0;

	Stack Head;
	Head.Next = NULL;

	read = fopen(filename, "r");

	if (read == NULL)
	{
		printf("File is inaccessible for reading!!!\n");
		return NULL;
	}

	while (!feof(read))
	{
		
		fgets(Line, sizeof(Line), read);

		while (sscanf(Line + res, "%s %n", data, &n) == 1)
		{
			newEl = CreateNode(data);

			if (!newEl)
			{
				fclose(read);
				return NULL;
			}

			if (isNumber(data))
			{
				PushStack(&Head, newEl);	
			}
			else
			{
				

				newEl->Right = PopStack(&Head);
				if (!newEl->Right)
				{
					printf("Postfix is not well written\n");
					fclose(read);
					return NULL;
				}

				newEl->Left = PopStack(&Head);
				if (!newEl->Left)
				{
					printf("Postfix is not well writen\n");
					fclose(read);
					return NULL;
				}

				PushStack(&Head, newEl);
				
			}
			res += n;
		}

	}

	fclose(read);
	result = PopStack(&Head);

	if (!result)
	{
		printf("Postfix is not well writen\n");
		return NULL;
	}

	if ((check = PopStack(&Head)) != NULL)
	{
		printf("Postfix is not well writen\n");
		return NULL;
	}

	return result;
}

int isNumber(char* data)
{
	int number = 0;

	if (sscanf(data, " %d", &number) == 1)
		return 1;

	else
		return 0;
}

Node CreateNode(char* data)
{
	Node newEl = NULL;
	newEl = (Node)malloc(sizeof(BinaryTree));

	if (newEl == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	newEl->Left = NULL;
	newEl->Right = NULL;
	strcpy(newEl->Element, data);

	return newEl;
}

int PushStack(Position Stck, Node Tree)
{
	Position newSt = NULL;

	newSt = (Position)malloc(sizeof(Stack));

	if (!newSt)
	{
		printf("Memory allocation failed!\n");
		return -1;
	}

	newSt->TreeNode = Tree;
	newSt->Next = Stck->Next;
	Stck->Next = newSt;

	return 0;
}

Node PopStack(Position Stck)
{
	Position temp = Stck->Next;
	Node result = NULL;

	if (!temp)
	{
		return NULL;
	}

	result = temp->TreeNode;
	Stck->Next = temp->Next;

	free(temp);
	return result;

}

char* PrintInOrder(Node root, char* inf)
{

	if (root == NULL)
		return inf;

	
	strcat(inf, "(");
	PrintInOrder(root->Left, inf);
	strcat(inf, root->Element);
	PrintInOrder(root->Right, inf);
	strcat(inf, ")");


	return inf;
}

int WriteInfix(char* filename2, char* p)
{
	FILE* write= NULL;

	write = fopen(filename2, "w");

	if (write == NULL)
	{
		printf("File is inaccessible for writing!!!\n");
		return -1;
	}
	fprintf(write, "%s", p);

	fclose(write);
	return 0;
}

