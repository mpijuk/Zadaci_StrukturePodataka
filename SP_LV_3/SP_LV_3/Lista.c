#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ch (256)

struct _preson;

typedef struct _person* position;

typedef struct _person {
	char Name[MAX_ch];
	char LastName[MAX_ch];
	int Year;

	position next;

}person;

position UnosPodataka(char *, char *, int);
int UnosPocetak(position, position);
int UnosKraj(position, position);
position Trazi(position, char*);
int Ispis(position);
position TraziPrethodni(position, char*);
int Brisi(position, char*);
int UpisDatoteka(position);
int Sortiraj(position, position);
int Brojac();
int IspisDatoteka(position);

int main()
{
	position Head = NULL;
	position q = NULL, t = NULL, prije = NULL, nakon = NULL;
	char ime[MAX_ch];
	char prezime[MAX_ch];
	char prez[MAX_ch];
	char znak;
	int god, j = 1;

	Head = (position)malloc(sizeof(person));

	if (Head == NULL)
	{
		printf("Graska u alociranju memorije!\n");
		return -1;
	}
	Head->next = NULL;


	while (j)
	{
		printf("Koju funkciju zelite obaviti sa listom: \n\n");
		printf("Novi element na pocetak liste - P\nNovi element na kraj liste - K\nPronalazak elmenta po prezimenu - T\nIzbrisati odredeni element - B\nIspis elemenata liste- I\nUnos elemnta nakon odredenog - N\nUnos elemnta prije odredenog - R\nSortirani unos - S\nUpisi listu  u datoteku - D\nCitaj listu iz datoteke - C\n Izlazak iz liste za odabir - E\n");
		scanf(" %c", &znak);
		printf("\n");

		switch (znak) {

		case 'p':
		case 'P':

			printf("Unesi ime studenta:");
			scanf(" %s", ime);
			printf("Unesi prezime studenta:");
			scanf(" %s", prezime);
			printf("Unesi godinu rodenja studenta:");
			scanf("%d", &god);

			q = UnosPodataka(ime, prezime, god);
			UnosPocetak(Head, q);

			printf("\n");

			break;

		case 'k':
		case 'K':

			printf("Unesi ime studenta:");
			scanf(" %s", ime);
			printf("Unesi prezime studenta:");
			scanf(" %s", prezime);
			printf("Unesi godinu rodenja studenta:");
			scanf("%d", &god);

			q = UnosPodataka(ime, prezime, god);
			UnosKraj(Head, q);

			printf("\n");

			break;
		case 's':
		case 'S':

			printf("Unesi ime studenta:");
			scanf(" %s", ime);
			printf("Unesi prezime studenta:");
			scanf(" %s", prezime);
			printf("Unesi godinu rodenja studenta:");
			scanf("%d", &god);

			q = UnosPodataka(ime, prezime, god);
			Sortiraj(Head, q);

			printf("\n");

			break;
		case 't':
		case 'T':

			printf("Unesite prezime studenta koje zelite pronaci:");
			scanf(" %s", prez);

			t = Trazi(Head, prez);
			printf("\n%s %s %d\n", t->Name, t->LastName, t->Year);

			printf("\n");

			break;
		case 'n':
		case 'N':



			printf("Unesite prezime studenta nakon kojeg zelite unijeti novi element:");
			scanf(" %s", prez);

			nakon = Trazi(Head, prez);

			printf("Unesi ime studenta:");
			scanf(" %s", ime);
			printf("Unesi prezime studenta:");
			scanf(" %s", prezime);
			printf("Unesi godinu rodenja studenta:");
			scanf("%d", &god);

			q = UnosPodataka(ime, prezime, god);

			UnosPocetak(nakon, q);

			printf("\n");

			break;

		case 'r':
		case 'R':

			printf("Unesite prezime studenta prije kojeg zelite unijeti novi element:");
			scanf(" %s", prez);

			prije = TraziPrethodni(Head, prez);

			printf("Unesi ime studenta:");
			scanf(" %s", ime);
			printf("Unesi prezime studenta:");
			scanf(" %s", prezime);
			printf("Unesi godinu rodenja studenta:");
			scanf("%d", &god);

			q = UnosPodataka(ime, prezime, god);

			UnosPocetak(prije, q);

			printf("\n");

			break;
		case 'd':
		case 'D':

			UpisDatoteka(Head->next);
			printf("%d", Brojac());
			printf("\n");

			break;
		case 'c':
		case 'C':

			IspisDatoteka(Head);

			printf("\n");

			break;
		case 'i':
		case 'I':

			Ispis(Head->next);
			printf("\n");

			break;
		case 'b':
		case 'B':

			printf("Unesite prezime studenta koje zelite izbrisati:");
			scanf(" %s", prez);

			Brisi(Head, prez);

			printf("\n");

			break;

		case 'e':
		case 'E':

			j = 0;
			break;

		default:

			printf("Greska u odabiru funkcije!!!\n");
			break;
		}
	}



	free(Head);

	return 0;
}

position UnosPodataka(char* ime, char* prezime, int god)
{
	position p;

	p = (position)malloc(sizeof(person));

	p->Year = god;
	strcpy(p->Name, ime);
	strcpy(p->LastName, prezime);
	p->next = NULL;

	return p;
}

int UnosPocetak(position p, position q)
{

	q->next = p->next;
	p->next = q;

	return 0;
}

int UnosKraj(position p, position q)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

	return 0;
}

position Trazi(position p, char* prez)
{
	while (p->next != NULL && strcmp(p->LastName, prez))
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Student nije pronaden u listi!\n");
		return NULL;
	}
	return p;

}

position TraziPrethodni(position p, char* prez)
{
	position prev;
	prev = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->LastName, prez))
	{
		prev = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Student nije pronaden u listi!\n");
		return NULL;
	}

	return prev;
}

int Brisi(position p, char* prez)
{
	position prev;

	prev = TraziPrethodni(p, prez);

	if (prev != NULL)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
	}

	return 0;
}
int Ispis(position p)
{
	while (p != NULL)
	{
		printf("%s %s %d ::: ", p->Name, p->LastName, p->Year);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int Sortiraj(position p, position q)
{
	while (p->next != NULL && strcmp(p->next->LastName, q->LastName) < 0)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

	return 0;
}
int UpisDatoteka(position p)
{
	FILE* write;

	write = fopen("studenti.txt", "w");

	if (write == NULL)
	{
		printf("Greska u otvaranju datoteke!");
		return -1;
	}

	while (p != NULL)
	{
		fprintf(write, "%s %s %d\n", p->Name, p->LastName, p->Year);
		p = p->next;
	}

	fclose(write);
	return 0;
}

int Brojac()
{
	FILE* read;
	char redak[MAX_ch];
	int brojac = 0;

	read = fopen("studenti.txt", "r");
	if (read == NULL)
	{
		printf("Greska u otvaranju datoteke!");
		return -1;
	}

	while (fgets(redak, MAX_ch, read) != NULL)
	{
		brojac++;
	}

	fclose(read);

	return brojac;
}
int IspisDatoteka(position p)
{
	FILE* read;
	char redak[MAX_ch];
	int brojac = 0, i = 0;
	position q;

	brojac = Brojac();
	read = fopen("studenti.txt", "r");

	if (read == NULL)
	{
		printf("Greska u otvaranju datoteke!");
		return -1;
	}

	for (i = 0; i < brojac; i++)
	{
		q = (position)malloc(sizeof(person));
		fgets(redak, MAX_ch, read);
		sscanf(redak, "%s %s %d", q->Name, q->LastName, &q->Year);
		UnosPocetak(p, q);

	}

	fclose(read);
	return 0;
}