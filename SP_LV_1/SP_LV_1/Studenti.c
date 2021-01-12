#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct _student {
	char ime[50];
	char prezime[50];
	int bodovi;

}student;

int ispis(student *);
double rel_bod(int);

int main()
{
	student *stud;
	FILE *s;

	int brojac = 0, i;
	char redak[100];

	s = fopen("popis.txt", "r");

	if (s == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	printf("Popis studenata i bodova na ispitu.\n");
	printf("(Najveci moguci broj bodova je 100.)\n\n");


	while (!feof(s))
	{
		if (fgets(redak, 100, s) != NULL)
		{
			brojac++;
		}
	}


	stud = (student *)malloc(brojac * sizeof(student));
	rewind(s);

	for (i = 0; i < brojac; i++)
	{
		fscanf(s, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);

	}
	for (i = 0; i < brojac; i++)
	{
		ispis(stud + i);

	}


	fclose(s);

	return 0;
}

int ispis(student *pok)
{
	printf("%-10s %-10s      %3.d   %lf\n", pok->ime, pok->prezime, pok->bodovi, rel_bod(pok->bodovi));

	return 1;
}


double rel_bod(int x)
{
	return ((double)x / (100))* (100);
}