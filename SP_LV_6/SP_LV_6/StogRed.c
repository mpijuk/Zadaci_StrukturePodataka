#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _List;
typedef struct _List* position;

typedef struct _List
{
	int Element;
	position Next;
}List;

position AllocationPositioningCheck(position);
int PushStack(int, position);
position PushRow(int, position, position);
int Pop(position);
int Print(position);
int EraseAll(position);

int main()
{
	position Head1 = NULL, Head2 = NULL, last = NULL;
	int n = 0, x = 0, i, j = 1;
	char sign;

	Head1 = AllocationPositioningCheck(Head1);
	Head2 = AllocationPositioningCheck(Head2);

	while (j)
	{
		printf("Koju funkciju zelite izvrsiti:\n");
		printf("Stavi element u stog - S\nStavi element u red - R\nSkini element iz stoga - W\nSkini element iz reda - Q\nKraj - K\n");
		scanf(" %c", &sign);
		printf("\n");

		switch (sign)
		{
		case 'S':
		case 's':
			printf("Koliko elemenata zelite unijeti u stog: ");
			scanf("%d", &n);

			srand(time(NULL));
			printf("Elementi koji se unose na stog: ");
			for (i = 0; i < n; i++)
			{
				x = 10 + rand() % 91;

				printf("%d ", x);
				PushStack(x, Head1);
			}
			printf("\n");
			printf("Stog:\n");
			Print(Head1->Next);
			printf("\n");

			break;

		case 'R':
		case 'r':
			printf("Koliko elemenata zelite unijeti u red: ");
			scanf("%d", &n);

			srand(time(NULL));

			printf("Elementi koji se unose u red: ");
			for (i = 0; i < n; i++)
			{
				x = 10 + rand() % 91;
				printf("%d ", x);
				last = PushRow(x, Head2, last);
			}
			printf("\n");
			printf("Red:\n");
			Print(Head2->Next);
			printf("\n");

			break;

		case 'W':
		case 'w':

			x = Pop(Head1);
			if (x == -1)
			{
				printf("Stog je prazan!\n");
			}
			else
				printf("Skinuli smo element %d sa stoga!\n", x);
			printf("\n");

			break;

		case 'Q':
		case 'q':

			x = Pop(Head2);
			if (x == -1)
			{
				printf("Red je prazan!\n");
			}
			else
				printf("Skinuli smo element %d sa reda!\n", x);
			printf("\n");

			break;

		case 'K':
		case 'k':
			j = 0;
			break;

		default:
			printf("Greska prilikom odabira!!!\n");
		}
	}

	EraseAll(Head1);
	EraseAll(Head2);

	free(Head1);
	free(Head2);
	return 0;
}
position AllocationPositioningCheck(position Head)
{
	Head = (position)malloc(sizeof(List));
	Head->Next = NULL;

	if (Head == NULL)
	{
		printf("Greska u alociranju memorije!!\n");
		return NULL;

	}
	return Head;
}

int PushStack(int x, position p)
{
	position q;

	q = (position)malloc(sizeof(List));
	if (q == NULL)
	{
		printf("Greska u alociranju memorije!\n");
	}
	q->Element = x;

	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int Pop(position p)
{
	int x = -1;
	position temp;

	if (p->Next != NULL)
	{
		x = p->Next->Element;

		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}

	return x;
}
position PushRow(int x, position p, position last)
{
	position q;

	q = (position)malloc(sizeof(List));
	if (q == NULL)
	{
		printf("Greska u alociranju memorije!\n");
	}
	q->Element = x;

	if (p->Next == NULL)
	{
		q->Next = p->Next;
		p->Next = q;
		last = q;
	}
	else
	{
		q->Next = last->Next;
		last->Next = q;
		last = q;
	}
	return last;
}


int Print(position p)
{
	if (p == NULL)
	{
		printf("Stog/Red je prazan!!!\n");
	}

	while (p != NULL)
	{
		printf("%d ", p->Element);
		p = p->Next;
	}
	printf("\n");

	return 0;
}

int EraseAll(position p)
{
	position temp;

	while (p->Next != NULL)
	{
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}
	return 0;
}
