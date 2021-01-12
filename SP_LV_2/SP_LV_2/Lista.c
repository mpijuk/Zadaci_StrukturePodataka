#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define M (256)

struct _osoba;
typedef struct _osoba* pozicija;

struct _osoba {
	char ime[M];
	char prezime[M];
	int godina_rod;

	pozicija next;

}osoba;

int unosPodatka(pozicija);
int unosPocetak(pozicija);
int ispisi(pozicija);
int unosKraj(pozicija);
pozicija trazi(pozicija, char*);
int brisi(pozicija, char*);
pozicija traziPrethodni(pozicija, char*);

int main()
{
	pozicija Head = NULL;
	Head = (pozicija)malloc(sizeof(osoba));
	Head->next = NULL;
	if (Head == NULL)
	{
		printf("Greska u alociranju memorije!!!\n");
		return -1;
	}

	unosPocetak(Head);
	unosPocetak(Head);
	unosKraj(Head);

	ispisi(Head->next);

	printf("Adresa liste s prezimenom %s je %d.\n", "lukic", trazi(Head->next, "lukic"));

	printf("\nAdresa liste s prezimenom %s je %d.\n", "simic", trazi(Head->next, "simic"));

	brisi(Head, "simic");

	ispisi(Head->next);


	return 0;
}

int unosPodataka(pozicija q)
{

	printf("Unesi ime studenta: ");
	scanf(" %s", q->ime);
	printf("Unesite prezime studenta: ");
	scanf(" %s", q->prezime);
	printf("Unesite godinu rodenja studenta: ");
	scanf("%d", &q->godina_rod);
	printf("\n----\n");

	return 0;
}

int unosPocetak(pozicija p)
{
	pozicija q = NULL;

	q = (pozicija)malloc(sizeof(osoba));

	unosPodataka(q);

	q->next = p->next;
	p->next = q;

	return 0;
}

int unosKraj(pozicija p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	unosPocetak(p);

	return 0;
}

int ispisi(pozicija p)
{

	printf("\n");

	while (p != NULL)
	{
		printf("%s %s, %d (adresa: %d) ::: ", p->ime, p->prezime, p->godina_rod, p);
		p = p->next;
	}

	printf("\n------\n");

	return 0;
}
pozicija trazi(pozicija p, char* prez)
{
	while (p != NULL && strcmp(p->prezime, prez))
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Element ne postoji u listi!!!\n");
		return NULL;
	}

	return p;
}
pozicija traziPrethodni(pozicija p, char* prez)
{
	pozicija prev = NULL;
	prev = p;
	p = p->next;

	while (p != NULL && strcmp(p->prezime, prez))
	{
		prev = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf("\nElement ne postoji u listi!!!\n");
		return NULL;
	}

	return prev;

}
int brisi(pozicija p, char* prez)
{
	pozicija prev = NULL;

	prev = traziPrethodni(p, prez);

	if (prev != NULL)
	{
		printf("\nBrise se student: %s\n", prez);
		p = prev->next;
		prev->next = p->next;
		free(p);
	}

	return 0;
}
