#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX_NAME (50)
#define HASH_SIZE (11)
#define MAX_LINE (1024)

struct _drzava;
typedef struct _drzava* PosL;

struct _grad;
typedef struct _grad* PosT;

typedef struct _drzava {
	char ime_drzave[MAX_NAME];
	PosT root;
	PosL next;
}drzava;

typedef struct _grad {
	char ime_grada[MAX_NAME];
	int broj_stanovnika;
	PosT left;
	PosT right;
}grad;

struct _table;
typedef struct _table* Hash;
typedef struct _table {
	PosL root[HASH_SIZE];
}table;

int EmptyListElement(PosL q);
PosL CreateListElement(char* ime_drzave);
PosL CreateTreeElement(char* ime_grada, int broj_stanovnika);
PosL InsertToHashT(Hash, char*);
PosL InsertAfter(PosL current, PosL next);
PosL SortedListInput(PosL root, char* ime_drzave);
PosT SortedTreeInput(PosT root, PosT NewEl);
int ReadFromFile(Hash h, char* txtfile);
PosT InsToTree(PosL root, char* txtfile);
int Print(PosL head);
int PrintTree(PosT root);
/*int Delete(PosL head);
int DelTree(PosT root);
int Pop(PosL head);*/