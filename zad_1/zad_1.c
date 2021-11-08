#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_L (1024)
#define MAX_S (128)

typedef struct _student {
	char ime[MAX_S];
	char prezime[MAX_S];
	double bodovi;
} student;

int proc_br_red(char* ime_dat);
student* aloc_mem_ucit_dat(int br, char* ime_dat);
double max_br_bod(student* s, int br);
int ispis(int br_red, int max_br, student* s);

int main()
{
	int br_red = 0, i = 0;
	double max_br = 0;
	student* s = NULL;
	char* ime_dat = "studenti.txt";

	br_red = proc_br_redaka(ime_dat);
	s = aloc_mem_ucit_dat(br_red, ime_dat);
	max_br = max_br_bod(s, br_red);
	ispis(br_red, max_br, s);

	return 0;
}

int proc_br_redaka(char* ime_dat)
{
	int i = 0;
	FILE* dat = NULL;
	char buff[MAX_L] = { 0 };

	dat = fopen(ime_dat, "r");
	if (!dat) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	while (!feof(dat)) {
		fgets(buff, MAX_L, dat);
		i++;
	}
	fclose(dat);
	return i;
}

student* aloc_mem_ucit_dat(int br, char* ime_dat)
{
	FILE* dat = NULL;
	student* s = NULL;
	int i = 0;

	s = (student*)malloc(br * sizeof(student));
	dat = fopen(ime_dat, "r");
	if (!dat) {
		printf("Greska u alociranju!\n");
		free(s);
		return NULL;
	}
	while (!feof(dat))
	{
		fscanf(dat, " %s %s %lf", s[i].ime, s[i].prezime, &s[i].bodovi);
		i++;
	}

	fclose(dat);
	return s;
}

double max_br_bod(student* s, int br)
{
	int i = 0;
	double max_br = 0;
	for (i = 0; i < br; i++) {
		if (s[i].bodovi > max_br)
			max_br = s[i].bodovi;
	}
	return max_br;
}

int ispis(int br_red, int max_br, student* s)
{
	int i = 0;
	for (i = 0; i < br_red; i++)
		printf("%s%15s\t%lf\t%lf\n", s[i].ime, s[i].prezime, s[i].bodovi, (s[i].bodovi / max_br) * 100);
	return 0;
}