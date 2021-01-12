#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct _List;
typedef struct _List* position;

typedef struct _List
{
	float Element;
	position Next;
}List;

position Allocation(position);
int Print(position p);
float Pop(position);
int PushStack(float, position);
float Racun_Postfix(position);

int main()
{
	position Head = NULL;
	float y = 0.0;

	Head = Allocation(Head);

	y = Racun_Postfix(Head);

	printf("Konacno rjesenje danog postfix izraza je %f.\n", y);

	return 0;
}

position Allocation(position Head)
{
	Head = (position)malloc(sizeof(List));
	Head->Next = NULL;

	if (Head == NULL)
	{
		printf("Greska u alociranju memorije!!!\n");
	}

	return Head;
}

int Print(position p)
{
	if (p == NULL)
	{
		printf("Stog je prazan!!!\n");
	}

	while (p != NULL)
	{
		printf("%f ", p->Element);
		p = p->Next;
	}
	printf("\n");

	return 0;
}

float Pop(position p)
{
	float x = -1;
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

int PushStack(float x, position p)
{
	position q;

	q = (position)malloc(sizeof(List));
	if (q == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
	}
	q->Element = x;

	q->Next = p->Next;
	p->Next = q;

	return 0;
}

float Racun_Postfix(position p)
{
	FILE* read = NULL;
	char postfix[256];
	int res = 0, n = 0;
	float num = 0.0;
	float x = 0.0, y = 0.0, z = 0.0;
	char op;

	read = fopen("Post_Izraz.txt", "r");
	if (read == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(read))
	{
		fgets(postfix, 256, read);

		while (sscanf(postfix + res, "%s %n", &num, &n) == 1)
		{
			if (sscanf(postfix + res, "%f %n", &num, &n) == 1)
			{
				PushStack(num, p);
				res += n;
			}
			else
			{
				sscanf(postfix + res, "%c %n", &op, &n);
				switch (op)
				{
				case '+':
					y = Pop(p);
					x = Pop(p);
					z = x + y;
					PushStack(z, p);
					break;
				case '-':
					y = Pop(p);
					x = Pop(p);
					z = x - y;
					PushStack(z, p);
					break;
				case '*':
					y = Pop(p);
					x = Pop(p);
					z = x * y;
					PushStack(z, p);
					break;
				case '/':
					y = Pop(p);
					x = Pop(p);
					if (y != 0.0)
					{
						z = x / y;
						PushStack(z, p);
					}
					break;
				default:
					printf("Nedozvoljena operacija!\n");
				}

				res += n;
			}
		}
	}

	z = Pop(p);

	return z;
}


