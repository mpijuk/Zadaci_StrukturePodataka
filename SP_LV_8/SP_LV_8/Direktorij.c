#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define Max_chr (256)

typedef enum _enum {
	ALLOCATION_FAILED,
	SUCCESS,
	DUPLICATED_DIRECTORY
}Result;

struct _directory;
typedef struct _directory* Node;
typedef struct _directory {
	char Name[Max_chr];
	Node Child;
	Node Sibling;
}directory;

struct _stack;
typedef struct _stack* Position;
typedef struct _stack {
	Node Dir;
	Position Next;
}stack;

Result makeDirectory(Node, char*);
Node CreateDir(char*);
Node FindDir(Node, char*);
void Remove(Node);
Result PrintDir(Node);
void PushDir(Position, Node);
Node PopDir(Position);
Node EnterDir(Node, char*, Position);
Node ExitDirectory(Node, Position);
void DeleteStack(Position S);

int main()
{
	char command[10];
	char name[Max_chr];
	directory Root;
	Node currentDirectory = NULL;

	currentDirectory = &Root;
	printf("Type a name of the root directory: ");
	scanf(" %s", Root.Name);
	Root.Child = NULL;
	Root.Sibling = NULL;

	Position st = (Position)malloc(sizeof(stack));
	st->Next = NULL;
	st->Dir = NULL;

	printf("Type a command:\n");
	printf("\tPrint directory - dir\n");
	printf("\tMake directory - mk\n");
	printf("\tEnter directory - cd\n");
	printf("\tExit directory - cd..\n");
	printf("\tExit - E\n");

	while (1)
	{
		scanf("%s", command);

		if (strcmp(command, "dir") == 0)
		{
			PrintDir(currentDirectory);
		}
		else if (strcmp(command, "mk") == 0)
		{
			printf("Type a name of new directory: \n");
			scanf(" %s", name);
			makeDirectory(currentDirectory, name);
		}
		else if (strcmp(command, "cd") == 0)
		{
			printf("In which directory you want enter:\n");
			scanf(" %s", name);
			printf("%s:\\...", Root.Name); // tri tockie -> nisam napravio path!
			currentDirectory = EnterDir(currentDirectory, name, st);
		}
		else if (strcmp(command, "cd..") == 0)
		{
			printf("%s:\\...", Root.Name);
			currentDirectory = ExitDirectory(currentDirectory, st);
		}
		else if (strcmp(command, "E") == 0)
		{
			break;
		}
		else
			printf("Incorrect command!!!\n");
	}
	Remove(currentDirectory);
	DeleteStack(st);
	free(st);

	return 0;
}

Node CreateDir(char* name)
{
	Node newDirectory = NULL;
	newDirectory = (Node)malloc(sizeof(directory));

	if (newDirectory == NULL)
	{
		printf("Memory allocation failed!\n");
	}

	strcpy(newDirectory->Name, name);

	newDirectory->Child = NULL;
	newDirectory->Sibling = NULL;

	return newDirectory;
}

Node FindDir(Node current, char* name)
{
	Node child = current->Child;

	if (child == NULL)
	{
		return NULL;
	}

	while (child != NULL && strcmp(child->Name, name) != 0)
		child = child->Sibling;

	return child;
}

void Remove(Node p)
{
	if (p == NULL)
	{
		return;
	}
	else
	{
		Remove(p->Sibling);
		Remove(p->Child);
		free(p);
	}
}



Result makeDirectory(Node current, char* name)
{
	Node newEl = NULL; // ovaj sluzi za novi element
	Node child = NULL; // ovaj sluzi za manje teksta

	if (FindDir(current, name) != NULL)
	{
		return DUPLICATED_DIRECTORY;
	}

	newEl = CreateDir(name);

	if (newEl == NULL)
	{
		printf("Memory allocation failed! md command failed\n");
		return ALLOCATION_FAILED;
	}

	child = current->Child;

	if (child == NULL)
	{

		current->Child = newEl;
		return SUCCESS;
	}

	if (strcmp(child->Name, newEl->Name) > 0)
	{
		current->Child = newEl;
		newEl->Sibling = child;
		return SUCCESS;
	}

	while (child->Sibling != NULL && strcmp(child->Sibling->Name, newEl->Name) < 0)
	{
		child = child->Sibling;
	}

	newEl->Sibling = child->Sibling;
	child->Sibling = newEl;

	return SUCCESS;
}

Result PrintDir(Node current)
{
	Node child = current->Child;
	int br = 0;

	if (child == NULL)
	{
		printf("Directory is empty\n");
		return SUCCESS;
	}

	printf("Directory of %s:\n", current->Name);
	while (child != NULL)
	{
		br++;
		printf("\t\t%s\n", child->Name);
		child = child->Sibling;
	}
	printf("\t\tDIR(%d)\n", br);

	return SUCCESS;
}

void PushDir(Position S, Node current)
{
	Position q;

	q = (Position)malloc(sizeof(stack));

	if (q == NULL)
	{
		printf("Memory allocation failed!\n");
	}
	else
	{
		q->Dir = current;
		q->Next = S->Next;
		S->Next = q;
	}

}

Node PopDir(Position S)
{
	Node temp;
	Position st;

	if (NULL == S->Next)
		return NULL;

	else
	{
		temp = S->Next->Dir;
		st = S->Next;
		S->Next = st->Next;

		free(st);
		return temp;
	}


}

Node EnterDir(Node current, char* name, Position S)
{
	Node temp = current->Child;

	while (temp != NULL && strcmp(temp->Name, name) != 0)
		temp = temp->Sibling;

	if (temp == NULL)
	{
		printf("Don't exist sub-directory under that name!\n");
		return NULL;
	}
	else
	{
		PushDir(S, current); // na stog stavljam cvor trenutnog direktorija

		printf("\\%s> \n", temp->Name);

		return temp;
	}
}

Node ExitDirectory(Node current, Position S)
{
	Node temp;

	temp = PopDir(S); // sa stoga se skida prosli direktorij

	if (temp == NULL)
	{
		printf("We are in the root directory! We can't exit from it!\n");
		return current;
	}
	else
	{
		printf("\\%s>\n", temp->Name);

		return temp;
	}
}

void DeleteStack(Position S)
{
	Position st;

	if (S->Next == NULL)
	{
		printf("Stack with Nodes is already empty!\n");
	}

	while (S->Next != NULL)
	{
		st = S->Next;
		S->Next = st->Next;
		free(st);
	}

}







