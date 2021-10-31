#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (50)
struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position first, char* surname);
int DeleteAfter(Position head, char* surname);
int InsertBeforeSpecificPerson(Position head, char* surname_specific, char* name, char* surname, int birthYear);
int InsertBeforeSpecificPerson(Position head, char* surname_specific, char* name, char* surname, int birthYear);
int InsertBetween(Position first, Position second);
int SortedInputBySurname(Position head, char* name, char* surname, int birthYear);
int PrintListToFile(Position first, char* filename);
int InputFromFile(Position first, char* filename);

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;
	/*InputFromFile(p, "Primjer.txt");*/
	
	SortedInputBySurname(p, "Iva", "Ivic", 2001);
	SortedInputBySurname(p, "Jakov", "Jakovic", 1961);
	SortedInputBySurname(p, "Marko", "Markic", 2002);
	SortedInputBySurname(p, "Ante", "Antic", 2003);
	SortedInputBySurname(p, "Marin", "Marinkovic", 1999);
	SortedInputBySurname(p, "Karlo", "Karlic", 2004);		//primjer sortiranog unosa
	
	PrintList(p->next);
	
	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}
int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("Name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;

}
int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}
Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;

}
int FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}
Position FindBefore(Position first, char* surname)
{
	Position temp1 = first;
	char* temp_surname = surname;
	Position temp2 = FindBySurname(temp1, temp_surname);
	while (temp1) 
	{
		if (temp1->next == temp2)
			return temp1;
		temp1 = temp1->next;
	}
	
	return NULL;
}
int DeleteElement(Position head, char* surname)
{
	char* temp_surname = surname;
	Position temp1 = head;
	Position temp2 = FindBySurname(temp1, temp_surname);
	Position temp3 = FindBefore(temp1->next, surname);
	temp3->next = temp2->next;
	free(temp2);

	return 0;
}
int InsertAfterSpecificPerson(Position head, char* surname_specific, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position temp1 = head, temp2 = NULL;
	char* temp_s = surname_specific;
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	temp2 = FindBySurname(temp1->next, temp_s);

	InsertAfter(temp2, newPerson);

	return EXIT_SUCCESS;

}
int InsertBeforeSpecificPerson(Position head, char* surname_specific, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position temp1 = head, temp2 = NULL;
	char* temp_s = surname_specific;
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	temp2 = FindBefore(temp1->next, temp_s);
	InsertAfter(temp2, newPerson);
	return EXIT_SUCCESS;

}
int SortedInputBySurname(Position head, char* name, char* surname, int birthYear)
{
	Position p = head;
	Position q = p->next;
	char* temp_name = name;
	char* temp_surname = surname;
	int temp_birthYear = birthYear;
	Position temp_person = CreatePerson(temp_name, temp_surname, temp_birthYear);
	if (q != 0) {
		while (q != 0) {
			if (strcmp(q->surname, temp_surname) >= 0) {
				InsertAfter(p, temp_person);
				return 0;
			}
			else if (q->next == NULL)
			{
				AppendList(p, temp_name, temp_surname, temp_birthYear);
				return 0;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
	}
	else 
		InsertAfter(p, temp_person);

	return 0;

}
int PrintListToFile(Position first, char* filename)
{
	Position temp = first;
	char* temp_filename = filename;
	FILE* f = fopen(temp_filename, "w");
	while (temp)
	{
		fprintf(f, "Name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	fclose(f);
	return EXIT_SUCCESS;
}
int InputFromFile(Position head, char* filename)
{
	Position temp = head;
	char name[50] = { 0 };
	char surname[50] = { 0 };
	int birthYear = 0;

	FILE* f = fopen(filename, "r");
	if (!f) {
		perror("\nDatoteka nije uspjesno otvorena!\n");
		return -1;
	}
	while (!feof(f)) {
		if(fscanf(f, " %s %s %d", name, surname, &birthYear) == 3)
			SortedInputBySurname(temp, name, surname, birthYear);
	}
	fclose(f);
	return 0;
}
