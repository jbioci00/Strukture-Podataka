#include "functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int EmptyListElement(PosL q)
{
	strcpy(q->ime_drzave, " ");
	q->next = NULL;
	q->root = NULL;
	return 0;
}
PosL CreateListElement(char* ime_drzave)
{
	PosL q = (PosL)malloc(sizeof(drzava));
	if (!q) {
		perror("Cannot allocate");
		return NULL;
	}
	strcpy(q->ime_drzave, ime_drzave);
	q->next = NULL;
	q->root = NULL;
	return q;
}
PosL CreateTreeElement(char* ime_grada, int broj_stanovnika)
{
	PosT x = NULL;
	x = (PosT)malloc(sizeof(grad));
	if (!x) {
		perror("Can't allocate!");
		return -2;
	}
	strcpy(x->ime_grada, ime_grada);
	x->broj_stanovnika = broj_stanovnika;
	x->left = NULL;
	x->right = NULL;
	return x;
}
PosL InsertToHashT(Hash h, char* ime_drzave)
{
	PosL remb = NULL;
	int sum = 0, i = 0, mod = 0;
	for (i = 0; i < 5; i++) {
		sum += (int)(ime_drzave[i]);
	}
	mod = sum % 11;
	remb = h->root[mod];

	return SortedListInput(remb, ime_drzave);
}
PosL InsertAfter(PosL current, PosL next)
{
	next->next = current->next;
	current->next = next;
	return next;
}

PosL SortedListInput(PosL root, char* ime_drzave)
{

	PosL q = CreateListElement(ime_drzave);
	while (root->next != NULL && strcmp(root->next->ime_drzave, ime_drzave) > 0) {
		root = root->next;
	}
	return InsertAfter(root, q);
}

PosT SortedTreeInput(PosT root, PosT NewEl)
{

	if (!root)
	{
		root = NewEl;
		return root;
	}
	if (root->broj_stanovnika < NewEl->broj_stanovnika) {
		root->right = SortedTreeInput(root->right, NewEl);
	}

	else if (root->broj_stanovnika > NewEl->broj_stanovnika) {
		root->left = SortedTreeInput(root->left, NewEl);
	}
	else free(NewEl);

	return root;
}

int ReadFromFile(Hash h, char* txtfile)
{
	PosT x = NULL;
	int s = 0;
	char buffer[MAX_LINE] = { 0 };
	char ime_dat[MAX_NAME] = { 0 };
	char ime_drzave[MAX_NAME] = { 0 };
	FILE* f = fopen(txtfile, "r");
	if (!f) {
		perror("Problem u datoteci!");
		return -1;
	}
	while (fgets(buffer, MAX_LINE, f))
	{
		PosL q = NULL;
		s = sscanf(buffer, " %s %s", ime_drzave, ime_dat);
		if (s == 2) {
			q = InsertToHashT(h, ime_drzave);
		}
		if (q != NULL) {
			x = InsToTree(q, ime_dat);
		}
	}
	fclose(f);
	return 0;
}

PosT InsToTree(PosL root, char* txtfile)
{
	PosT temp = root->root;
	int s = 0;
	char buffer[MAX_LINE] = { 0 };
	char ime_grada[MAX_NAME] = { 0 };
	int broj_stanovnika = 0;
	FILE* k = fopen(txtfile, "r");
	if (!k) {
		perror("Problem u datoteci!");
		return -1;
	}
	while (fgets(buffer, MAX_LINE, k)) {
		s = sscanf(buffer, " %s %d", ime_grada, &broj_stanovnika);
		if (s == 2) {
			PosT q = CreateTreeElement(ime_grada, broj_stanovnika);
			root->root = SortedTreeInput(root->root, q);
		}
	}
	fclose(k);
	return root;
}

int Print(PosL head)
{
	PosL temp = head->next;
	while (temp) {
		printf("%s\n", temp->ime_drzave);
		PrintTree(temp->root);
		temp = temp->next;
	}
	return 0;
}
int PrintTree(PosT root)
{
	if (root->right) {
		PrintTree(root->right);
	}
	printf("\t\t%s, %d stanovnika\n", root->ime_grada, root->broj_stanovnika);
	if (root->left) {
		PrintTree(root->left);
	}
	return 0;
}
int Delete(PosL head)
{
	PosL temp2 = head;
	PosL temp = NULL;
	while (head->next) {
		temp = head->next;
		DelTree(head->next->root);
		head->next = head->next->next;
		free(temp);

	}
	free(temp2);
	return 0;
}
int DelTree(PosT root)
{
	if (!root)
		return 0;
	if (root->left)
		DelTree(root->left);
	if (root->right)
		DelTree(root->right);
	free(root);
	return 0;
}

/*int Pop(PosL head)
{
PosL temp = head->next;

head->next = temp->next;
free(temp);
return 0;
}*/