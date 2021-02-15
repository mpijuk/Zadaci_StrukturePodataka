#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxChar (256)
#define hSize (11)

struct _list;
typedef struct _list* position;
struct _hash;
typedef struct _hash* hashTab;

typedef struct _list
{
	char name[MaxChar];
	char surname[MaxChar];
	int key;
	int id_num;
	position next;
}list;

typedef struct _hash
{
	int size;
	position hashLists[hSize];
}hash;

hashTab Initialization(int hash_size);
position Find(hashTab Hhead, char* lastName, char* firstName);
int FindIndex(char* lastName, int hash_size);
int FindKey(char* lastName);
int Insert(char* lastName, char* firstName, int id, hashTab Hhaed);
int ReadFile(hashTab Hhead);
position Allocation(position ptr);
void PrintHash(hashTab Hhead);
int EraseAll(hashTab Hhead);
int EraseHash(hashTab Hhead);

int main()
{
	int hash_size = 11, loop = 1;
	char name[MaxChar] = { 0 };
	char surname[MaxChar] = { 0 };
	hashTab Hash = NULL;
	position find = NULL;
	char c;

	Hash = Initialization(hash_size);
	ReadFile(Hash);
	PrintHash(Hash);

	printf("\nUnesi F za trazenje studenta\nUnesi S za prestanak trazenja\n");

	while (loop)
	{
		scanf("%c", &c);
		switch (c) {
		case 'F':
		case 'f':
			printf("Type name and surname of the student you want find in a HASH?\n");
			scanf(" %s", name);
			scanf(" %s", surname);
			find = Find(Hash, surname, name);
			if (find != NULL)
			{
				printf("Student's identification number is:%d\n", find->id_num);
			}
			break;
		case 'S':
		case 's':
			loop = 0;
			break;
		default:
			printf("Incorrect command!\n");
			break;

		}

	}

	EraseAll(Hash);
	EraseHash(Hash);
	free(Hash);
	return 0;
}

int FindKey(char* lastName)
{
	int key = 0;
	if (strlen(lastName) < 5)
	{
		printf("Lastname is to short for key!\n");
		return -1;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			key += lastName[i];
		}
		return key;
	}
}


int FindIndex(char* lastName, int hash_size)
{
	int hashV = 0;
	if (strlen(lastName) < 5)
	{
		printf("Lastname is to short for hash key!\n");
		return -1;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			hashV += lastName[i];
		}
		return hashV % hash_size;
	}

}

hashTab Initialization(int hash_size)
{
	hashTab H;

	H = (hashTab)malloc(sizeof(hash));
	if (H == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	H->size = hash_size;


	for (int i = 0; i < H->size; i++)
	{
		H->hashLists[i] = Allocation(H->hashLists[i]);
	}

	return H;
}

position Allocation(position ptr)
{
	ptr = (position)malloc(sizeof(list));
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	ptr->next = NULL;

	return ptr;
}

int ReadFile(hashTab Hhead)
{
	FILE* readptr = NULL;
	char Line[MaxChar] = { 0 };
	char name[MaxChar] = { 0 };
	char surname[MaxChar] = { 0 };
	int id = 0, res = 0, n = 0;

	readptr = fopen("Ucenici.txt", "r");
	if (readptr == NULL)
	{
		printf("File si not open for reading!\n");
		return -1;
	}

	while (!feof(readptr))
	{
		fgets(Line, MaxChar, readptr);
		while (sscanf(Line + res, "%s %s %d %n", name, surname, &id, &n) == 3)
		{
			Insert(surname, name, id, Hhead);
			res += n;
		}
		res = 0;
	}
	fclose(readptr);

	return 0;
}

int Insert(char* lastName, char* firstName, int id, hashTab Hhead)
{
	position newNode = NULL, currL = NULL;
	int index = 0;


	newNode = Allocation(newNode);

	if (newNode == NULL)
	{
		return -1;
	}

	strcpy(newNode->surname, lastName);
	strcpy(newNode->name, firstName);
	newNode->id_num = id;
	newNode->key = FindKey(newNode->surname);

	index = FindIndex(newNode->surname, Hhead->size);

	while (Hhead->hashLists[index]->next != NULL && strcmp(Hhead->hashLists[index]->next->surname, newNode->surname) < 0)
	{
		Hhead->hashLists[index] = Hhead->hashLists[index]->next;
	}

	newNode->next = Hhead->hashLists[index]->next;
	Hhead->hashLists[index]->next = newNode;

	return 0;
}

position Find(hashTab Hhead, char* lastName, char* firstName)
{
	position L = NULL;

	L = Hhead->hashLists[FindIndex(lastName, Hhead->size)];

	while (L != NULL && (strcmp(L->surname, lastName) != 0 || strcmp(L->name, firstName) != 0))
	{
		L = L->next;
	}
	if (L == NULL)
	{
		printf("Person %s %s do not exist in Hash!\n", firstName, lastName);
	}
	return L;
}

void PrintHash(hashTab Hhead)
{
	position currL = NULL;
	if (Hhead == NULL)
	{
		printf("Hash is empty!\n");
	}
	else
	{
		for (int i = 0; i < Hhead->size; i++)
		{
			currL = Hhead->hashLists[i]->next;
			printf("Students under index %d\n", i);
			while (currL != NULL)
			{
				printf("%s %s %d Key(%d):::", currL->name, currL->surname, currL->id_num, currL->key);
				currL = currL->next;
			}
			printf("\n");
		}
	}
}

int EraseAll(hashTab Hhead)
{
	position currL = NULL;
	position temp = NULL;

	for (int i = 0; i < Hhead->size; i++)
	{
		currL = Hhead->hashLists[i];
		while (currL->next != NULL)
		{
			temp = currL->next;
			currL->next = temp->next;
			free(temp);
		}
	}
	return 0;
}

int EraseHash(hashTab Hhead)
{
	for (int i = 0; i < Hhead->size; i++)
	{
		free(Hhead->hashLists[i]);
	}

	return 0;
}
