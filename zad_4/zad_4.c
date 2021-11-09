#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

struct _Polinom;
typedef struct _Polinom* Pozicija;
typedef struct _Polinom {
	int koeficijent;
	int eksponent;
	Pozicija next;
}Polinom;

int ProcitajIzDatoteke(Pozicija head1, Pozicija head2);
Pozicija NoviElement(int koeficijent, int eksponent);
int DodajNaListu(Pozicija head, char* buffer);
int SortiraniUnos(Pozicija head, Pozicija novi_element);
int Spoji(Pozicija p, Pozicija novi_element);
int UbaciIza(Pozicija p, Pozicija novi_element);
int IzbrisiIza(Pozicija p);
int IspisiPolinom(char* ime, Pozicija first);
int IzradiiDodajIza(int koef, int eksp, Pozicija p);
int Zbroji(Pozicija rez_zbrajanja, Pozicija head1, Pozicija head2);
int Pomnozi(Pozicija rez_mnozenja, Pozicija head1, Pozicija head2);
int OslobodiMemoriju(Pozicija head);

int main()
{
	Polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom rez_zbrajanja = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom rez_mnozenja = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Pozicija p1 = &head1;
	Pozicija p2 = &head2;
	Pozicija z = &rez_zbrajanja;
	Pozicija m = &rez_mnozenja;

	if (ProcitajIzDatoteke(p1, p2) == 0)
	{
		IspisiPolinom("Polinom 1", p1->next);
		IspisiPolinom("Polinom 2", p2->next);
		Zbroji(z, p1, p2);
		Pomnozi(m, p1, p2);
		IspisiPolinom("Rezultat zbrajanja: ", z->next);
		IspisiPolinom("Rezultat mnozenja: ", m->next);
		OslobodiMemoriju(p1);
		OslobodiMemoriju(p2);
		OslobodiMemoriju(z);
		OslobodiMemoriju(m);
	}
	else
	{
		printf("Problem u funkciji ProcitajIzDatoteke!");
	}

	return 0;
}
int ProcitajIzDatoteke(Pozicija head1, Pozicija head2)
{
	FILE* f = NULL;
	char ime_datoteke[MAX_SIZE] = { 0 };
	char buffer[MAX_LINE] = { 0 };
	int status = 0;
	
	printf("Unesite ime datoteke: ");
	scanf(" %s", ime_datoteke);

	f = fopen(ime_datoteke, "r");
	if (!f)
	{
		printf("\nGreska u otvaranju datoteke!");
		return -1;
	}

	fgets(buffer, MAX_LINE, f);
	status = DodajNaListu(head1, buffer);
	if (status != 0)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, f);
	status = DodajNaListu(head2, buffer);
	if (status != 0)
	{
		return EXIT_FAILURE;
	}

	return 0;

}
Pozicija NoviElement(int koeficijent, int eksponent)
{
	Pozicija novi_element = NULL;

	novi_element = (Pozicija)malloc(sizeof(Polinom));
	if (!novi_element) {
		printf("\nGreska u alociranju memorije!");
		return NULL;
	}
	novi_element->koeficijent = koeficijent;
	novi_element->eksponent = eksponent;
	novi_element->next = NULL;
	return novi_element;
}
int DodajNaListu(Pozicija head, char* buffer)
{
	int temp_koef = 0, temp_eksp = 0, num = 0, s = 0;
	char *temp_buffer = buffer;
	Pozicija temp_element = NULL;
	while (strlen(temp_buffer) > 0) {
		s = sscanf(temp_buffer, "%d %d %n", &temp_koef, &temp_eksp, &num);
		if (s != 2) {
			printf("\nGreška u sadrzaju datoteke!");
			return -3;
		}
		temp_element = NoviElement(temp_koef, temp_eksp);
		SortiraniUnos(head, temp_element);
		temp_buffer = temp_buffer + num;
	}
	return 0;
}

int SortiraniUnos(Pozicija head, Pozicija novi_element)
{
	Pozicija temp_element = novi_element, temp_pos = head;
	while (temp_pos->next != NULL && temp_pos->next->eksponent < novi_element->eksponent) {
			temp_pos = temp_pos->next;
	}
	Spoji(temp_pos, temp_element);
	return 0;
}
int Spoji(Pozicija p, Pozicija novi_element)
{
	Pozicija temp_pos = p;
	if (temp_pos->next == NULL || temp_pos->next->eksponent != novi_element->eksponent)
	{
		UbaciIza(temp_pos, novi_element);
	}
	else
	{
		int a = temp_pos->next->koeficijent + novi_element->koeficijent;
		if (a == 0)
		{
			IzbrisiIza(temp_pos);
		}
		else
		{
			temp_pos->next->koeficijent = a;
		}
		free(novi_element);
	}

	return 0;
}
int UbaciIza(Pozicija p, Pozicija novi_element)
{
	novi_element->next = p->next;
	p->next = novi_element;

	return 0;
}
int IzbrisiIza(Pozicija p)
{
	Pozicija tr = p->next;

	p->next = tr->next;
	free(tr);

	return 0;
}
int IspisiPolinom(char* ime, Pozicija first)
{
	printf(" %s = ", ime);
	if (first) {
		if (first->eksponent < 0) {
			if (first->koeficijent == 1) {
				printf("x^(%d) ", first->eksponent);
			}
			else {
				printf("%dx^(%d) ", first->koeficijent, first->eksponent);
			}
		}
		else {
			if (first->koeficijent == 1) {
				printf("x^(%d) ", first->eksponent);
			}
			else {
				printf("%dx^(%d) ", first->koeficijent, first->eksponent);
			}
		}
	}
	first = first->next;
	for (first; first != NULL; first = first->next)
	{
		if (first->koeficijent < 0)
		{
			if (first->eksponent < 0)
			{
				printf(" - %dx^(%d) ", abs(first->koeficijent), first->eksponent);
			}
			else
			{
				printf(" - %dx^%d ", abs(first->koeficijent), first->eksponent); //krivo postavljena zagrada
			}
		}
		else
		{
			if (first->eksponent < 0)
			{
				if (first->koeficijent == 1)
				{
					printf(" + x^(%d) ", first->eksponent);
				}
				else
				{
					printf(" + %dx^(%d) ", first->koeficijent, first->eksponent);
				}

			}
			else
			{
				if (first->koeficijent == 1)
				{
					printf(" + x^(%d) ", first->eksponent);
				}
				else
				{
					printf(" + %dx^(%d) ", first->koeficijent, first->eksponent);
				}
			}
		}
	}
	printf("\n");
	return 0;
}
int IzradiiDodajIza(int koef, int eksp, Pozicija p)
{
	Pozicija novi_element = NoviElement(koef, eksp);
	if (novi_element == NULL)
	{
		return EXIT_FAILURE;
	}
	UbaciIza(p, novi_element);
	p = p->next;
	return 0;
}
int Zbroji(Pozicija rez_zbrajanja, Pozicija head1, Pozicija head2)
{
	Pozicija p = head1->next;
	Pozicija r = head2->next;
	Pozicija k = rez_zbrajanja;
	Pozicija temp = NULL;

	while (p->next != NULL && r->next != NULL)
	{
		if (p->eksponent == r->eksponent)
		{
			IzradiiDodajIza(p->koeficijent + r->koeficijent, p->eksponent, k);
			p = p->next;
			r = r->next;
		}
		else if (p->eksponent < r->eksponent)
		{
			IzradiiDodajIza(p->koeficijent, p->eksponent, k);
			p = p->next;
		}
		else
		{
			IzradiiDodajIza(r->koeficijent, r->eksponent, k);
			r = r->next;
		}
	}
	if (p == NULL)
	{
		temp = r;
	}
	else
	{
		temp = p;
	}
	while (temp != NULL)
	{
		IzradiiDodajIza(temp->koeficijent, temp->eksponent, k);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}
int Pomnozi(Pozicija rez_mnozenja, Pozicija head1, Pozicija head2)
{
	Pozicija i = NULL;
	Pozicija j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			Pozicija novi_element = NoviElement(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);
			if (!novi_element)
			{
				return EXIT_FAILURE;
			}
			SortiraniUnos(rez_mnozenja, novi_element);
		}
	}
	return EXIT_SUCCESS;
}

int OslobodiMemoriju(Pozicija head)
{
	Pozicija temp_pos = head;

	while (temp_pos->next)
	{
		IzbrisiIza(temp_pos);
	}
	return 0;
}