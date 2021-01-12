#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define Max_char (256)

struct _lista;
typedef struct _lista* position;

typedef struct _lista {
	int Element;
	position Next;

}lista;

int ReadAndSort(position, position);
int Print(position);
int Sort(position, position);
position AllocationPositioningCheck(position);
int Insert(position, int);
int EraseAll(position);

position Union(position, position, position);
position Section(position, position, position);

int main()
{
	position Head1 = NULL, Head2 = NULL, Head3 = NULL, Head4 = NULL;


	Head1 = AllocationPositioningCheck(Head1);
	Head2 = AllocationPositioningCheck(Head2);
	Head3 = AllocationPositioningCheck(Head3);
	Head4 = AllocationPositioningCheck(Head4);

	ReadAndSort(Head1, Head2);
	Print(Head1->Next);
	Print(Head2->Next);

	Union(Head1->Next, Head2->Next, Head3);
	Print(Head3->Next);

	Section(Head1->Next, Head2->Next, Head4);
	Print(Head4->Next);

	EraseAll(Head1);
	EraseAll(Head2);
	EraseAll(Head3);
	EraseAll(Head4);

	free(Head1);
	free(Head2);
	free(Head3);
	free(Head4);

	return 0;
}

position AllocationPositioningCheck(position Head)
{
	Head = (position)malloc(sizeof(lista));
	Head->Next = NULL;

	if (Head == NULL)
	{
		printf("Greska u alociranju memorije!!\n");
		return -1;
	}
	return Head;
}


int ReadAndSort(position p, position q)
{
	FILE* read;
	position t = NULL;
	char Line[Max_char];
	int res = 0, n = 0, br = 1, number;

	read = fopen("Numbers.txt", "r");
	if (read == NULL)
	{
		printf("Greska u alociranju memorije!!!\n");
		perror("Error");
		return -1;
	}

	while (!feof(read))
	{
		br++;

		fgets(Line, Max_char, read);
		while (sscanf(Line + res, "%d %n", &number, &n) == 1)
		{
			t = (position)malloc(sizeof(lista));
			t->Element = number;

			if (br % 2 == 0) //parni redovi ulaze u jednu listu, a neparni u drugu
			{
				Sort(p, t);
			}
			else
			{
				Sort(q, t);
			}
			res += n;
		}
		res = 0;
	}
	rewind(read);
	fclose(read);

	return 0;
}

int Print(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!!!\n");
		return -1;
	}

	while (p != NULL)
	{
		printf("%d ", p->Element);
		p = p->Next;
	}
	printf("\n");

	return 0;
}

int Sort(position p, position q)
{
	while (p->Next != NULL && (p->Next->Element < q->Element))
	{
		p = p->Next;
	}

	q->Next = p->Next;
	p->Next = q;

	return 0;
}

position Union(position p, position q, position z) // p i q adrese 1. clanova listi
{

	while ((p != NULL) || (q != NULL))
	{
		if ((p->Element) == (q->Element))
		{
			Insert(z, p->Element);
			p = p->Next;
			q = q->Next;
		}

		else if ((p->Element) > (q->Element))
		{
			Insert(z, q->Element);
			q = q->Next;
		}
		else
		{
			Insert(z, p->Element);
			p = p->Next;
		}

		if (p == NULL || q == NULL) //dodatni uvjet da se ispisu svi elementi unije
		{
			while (p != NULL)
			{
				Insert(z, p->Element);
				p = p->Next;
			}
			while (q != NULL)
			{
				Insert(z, q->Element);
				q = q->Next;
			}
		}

	}

	return z;
}

int Insert(position z, int x)
{
	position t = NULL;

	t = (position)malloc(sizeof(lista));
	if (t == NULL)
	{
		printf("Greska u alociranju memorije!!\n");
		return -1;
	}

	t->Element = x;

	while ((z->Next != NULL) && (z->Next->Element < t->Element))
	{
		z = z->Next;
	}

	t->Next = z->Next;
	z->Next = t;

	return 0;
}

position Section(position p, position q, position z)
{
	while ((p != NULL) && (q != NULL))
	{
		if ((p->Element) == (q->Element))
		{
			Insert(z, p->Element);
			p = p->Next;
			q = q->Next;
		}

		else if ((p->Element) > (q->Element))
		{
			q = q->Next;
		}
		else
		{
			p = p->Next;
		}

	}

	return z;
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
