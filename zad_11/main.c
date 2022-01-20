#include"functions.h"

int main()
{
	int i = 0;
	Hash h = NULL;
	h = malloc(sizeof(table) * HASH_SIZE);
	for (i = 0; i < HASH_SIZE; i++) {
		h->root[i] = (PosL)malloc(sizeof(drzava));
		EmptyListElement(h->root[i]);
	}
	ReadFromFile(h, "Drzave.txt");
	for (i = 0; i < HASH_SIZE; i++) {
		Print(h->root[i]);
	}
	return 0;
}