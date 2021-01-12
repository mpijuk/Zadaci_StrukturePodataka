#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_chr (256)

struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
	int koef;
	int pot;
	position next;

}polinom;

position ZbrojPolinoma(position, position, position);
position UmnozakPolinoma(position, position, position);
int Citaj(position, position);
int Ispis(position);
int SortiraniUnos(position, position);

int UnosZbroja(position, position);
int UnosZbrojaIstih(position, position, position);
int UnosMnozenja(position, position, position);



int main()
{
	position Head1 = NULL, Head2 = NULL, Head3 = NULL, Head4 = NULL;

	Head1 = (position)malloc(sizeof(polinom));
	Head2 = (position)malloc(sizeof(polinom));
	Head3 = (position)malloc(sizeof(polinom));
	Head4 = (position)malloc(sizeof(polinom));

	Head1->next = NULL;
	Head2->next = NULL;
	Head3->next = NULL;
	Head4->next = NULL;


	if ((Head1 == NULL) || (Head3 == NULL) || (Head3 == NULL) || (Head4 == NULL))
	{
		printf("Greska u alociranju memorije!!!\n");
		return -1;
	}

	Citaj(Head1, Head2);
	Ispis(Head1->next);
	Ispis(Head2->next);

	ZbrojPolinoma(Head1->next, Head2->next, Head3);
	Ispis(Head3->next);

	UmnozakPolinoma(Head1->next, Head2->next, Head4);
	Ispis(Head4->next);



	free(Head1);
	free(Head2);
	free(Head3);
	free(Head4);

	return 0;
}

int Citaj(position p, position q)
{
	FILE* read;
	position t = NULL;
	char redak[MAX_chr];

	int n1 = 0, res1 = 0, n2 = 0, res2 = 0;  // varijable vezane za sscanf
	int k = 0, exp = 0; // pomocne varijable

	read = fopen("izrazi.txt", "r");
	if (read == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}


	while (!feof(read))
	{


		fgets(redak, MAX_chr, read);
		while (sscanf(redak + res1, "%d %d %n", &k, &exp, &n1) == 2)
		{

			t = (position)malloc(sizeof(polinom));
			t->koef = k;
			t->pot = exp;

			SortiraniUnos(p, t);

			res1 += n1;

		}

		fgets(redak, MAX_chr, read);
		while (sscanf(redak + res2, "%d %d %n", &k, &exp, &n2) == 2)
		{
			t = (position)malloc(sizeof(polinom));
			t->koef = k;
			t->pot = exp;

			SortiraniUnos(q, t);
			res2 += n2;

		}

	}
	rewind(read);

	fclose(read);
	return 0;
}

int Ispis(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return -1;
	}

	while (p != NULL)
	{
		printf("%d %d ", p->koef, p->pot);
		p = p->next;
	}
	printf("\n");

	return 0;
}


position ZbrojPolinoma(position p, position q, position z)
{
	while ((p != NULL) || (q != NULL))
	{
		for (p; p != NULL; p = p->next)
		{
			if ((p->pot) > (q->pot))
			{
				for (q; q != NULL; q = q->next)
				{
					if ((p->pot) == (q->pot))
						break;
					UnosZbroja(z, q);
				}
			}

			else if ((p->pot) == (q->pot))
			{
				UnosZbrojaIstih(z, p, q);
				q = q->next;
			}

			else if ((p->pot) < (q->pot))
			{
				UnosZbroja(z, p);
			}

			if (q == NULL)
			{
				while (p != NULL)
				{
					UnosZbroja(z, p);
					p = p->next;
				}
				break;
			}

		}

		while (q != NULL)
		{
			UnosZbroja(z, q);
			q = q->next;
		}
	}

	return z;

}

int UnosZbroja(position z, position r)
{
	position t;
	t = (position)malloc(sizeof(polinom));

	t->koef = r->koef;
	t->pot = r->pot;

	SortiraniUnos(z, t);


	return 0;
}
int UnosZbrojaIstih(position z, position p, position q)
{
	position t;
	t = (position)malloc(sizeof(polinom));

	t->koef = p->koef + q->koef;
	t->pot = p->pot;

	SortiraniUnos(z, t);

	return 0;

}

int SortiraniUnos(position p, position q)
{
	while (p->next != NULL && (p->next->pot < q->pot))
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

	return 0;

}

position UmnozakPolinoma(position p, position q, position z)
{
	position t = q;


	while (p != NULL)
	{
		for (p; p != NULL; p = p->next)
		{

			for (t; t != NULL; t = t->next)
			{

				UnosMnozenja(p, t, z);

			}

			t = q;

		}
	}

	return z;
}

int UnosMnozenja(position p, position q, position z)
{
	position t;
	t = (position)malloc(sizeof(polinom));

	t->koef = (p->koef)*(q->koef);
	t->pot = (p->pot) + (q->pot);

	SortiraniUnos(z, t);

	return 0;

}

