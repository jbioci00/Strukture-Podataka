#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 128

typedef struct _Dir* Position;
typedef struct _Stack* PosStack;

typedef struct _Dir {
	char* name;
	Position child;
	Position sibling;
}Dir;

typedef struct _Stack {
	Position directory;

	PosStack next;
	PosStack prev;
}Stack;

int createDirectory(Position);
int printDirectory(Position);
Position enterDirectory(Position, PosStack);
Position previous(Position, PosStack);
Position FindByName(char*, Position);
int push(PosStack, Position);
Position pop(PosStack);
int printPath(PosStack, Position, Position);
PosStack findLast(PosStack);

int main()
{
	Position root;
	root = (Position)malloc(sizeof(Dir));
	root->child = NULL;
	root->sibling = NULL;
	PosStack head;
	head = (PosStack*)malloc(sizeof(Stack));
	head->next = NULL;
	head->prev = NULL;
	root->name = (char*)malloc(MAX * sizeof(char));
	root->name = "C:";

	Position current = root;
	char command[MAX] = { 0 };


	printf("md <ime direktorija> - dodaj direktorij\n");
	printf("cd <ime direktorija> - otvori direktorij\n");
	printf("cd.. - vrati se na prosli direktorij\n");
	printf("dir - ispisi sadrzaj direktorija\n");
	printf("exit - izidi iz programa\n\n");


	while (1) {

		printPath(head, root, current);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			createDirectory(current);
		}

		else if (!strcmp(command, "cd")) {
			current = enterDirectory(current, head);
		}

		else if (!strcmp(command, "cd..")) {
			current = previous(current, head);
		}

		else if (!strcmp(command, "dir")) {
			printDirectory(current);
		}

		else if (!strcmp(command, "exit")) {
			return 0;
		}

		else
			printf("Krivi unos\n");
	}


	return 0;
}

int printPath(PosStack head, Position root, Position current)
{
	PosStack s;

	s = findLast(head);

	if (head->next == NULL) {
		printf("%s>", root->name);
		return EXIT_SUCCESS;
	}

	while (s->prev != NULL) {
		printf("%s>", s->directory->name);
		s = s->prev;
	}

	printf("%s>", current->name);

	return EXIT_SUCCESS;
}

PosStack findLast(PosStack head)
{
	PosStack s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int createDirectory(Position current) {
	Position directory;
	directory = (Position)malloc(sizeof(Dir));
	directory->name = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Greska u alociranju!\n");

	if (current->child != NULL) {
		current = current->child;
		while (current->sibling != NULL) {
			current = current->sibling;
		}
		current->sibling = directory;
	}

	else
		current->child = directory;

	scanf(" %s", directory->name);

	directory->sibling = NULL;
	directory->child = NULL;

	return EXIT_SUCCESS;
}

int printDirectory(Position current) {
	if (current->child == NULL) {
		printf("Prazan direktorij!\n");
		return EXIT_SUCCESS;
	}

	current = current->child;

	printf("Direktoriji: \n");
	printf("\t%s\n", current->name);

	while (current->sibling != NULL) {
		printf("\t%s\n", current->sibling->name);
		current = current->sibling;
	}

	return EXIT_SUCCESS;
}

Position FindByName(char* name, Position current) {
	if (current->child == NULL) {
		printf("Prazan direktorij!");
		return EXIT_SUCCESS;
	}

	current = current->child;

	while (strcmp(name, current->name) != 0 && current->sibling != NULL) {
		current = current->sibling;
	}

	if (current->sibling == NULL) {
		if (strcmp(name, current->name) != 0)
			return NULL;
		else
			return current;
	}

	else
		return current;
}

int push(PosStack head, Position directory) {

	PosStack q = (PosStack)malloc(sizeof(Stack));

	q->next = head->next;
	q->prev = head;

	if (head->next != NULL) {
		head->next->prev = q;
	}

	head->next = q;
	q->directory = directory;

	return EXIT_SUCCESS;
}

Position pop(PosStack head) {

	PosStack q = (PosStack)malloc(sizeof(Stack));
	Position p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;

	free(q);

	return p;
}

Position previous(Position current, PosStack head)
{
	Position s;

	s = pop(head);

	if (s == NULL) {
		printf("Vec se nalazite u rootu!\n");
		s = current;
	}

	return s;
}

Position enterDirectory(Position current, PosStack head)
{
	Position s;
	char* name;
	name = (char*)malloc(MAX * sizeof(char));

	scanf(" %s", name);

	if (current->child == NULL) {
		printf("Prazan direktorij!\n");
		return current;
	}

	s = FindByName(name, current);

	if (s == 0) {
		printf("Pogresan naziv direktorija!\n");
		return current;
	}

	push(head, current);

	return s;
}