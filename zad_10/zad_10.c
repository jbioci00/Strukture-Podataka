#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 50

struct _tree;
typedef struct _tree* PosT;
typedef struct _tree {
    char ime_grada[MAX_NAME];
    int broj_stanovnika;
    PosT left;
    PosT right;
}tree;

struct _drzava;
typedef struct _drzava* PosL;
typedef struct _drzava {
    char ime_drzave[MAX_NAME];
    PosT grad;
    PosL next;
}drzava;

int InsToListFromFile(PosL head, char* fileName);
int InsToTreeFromFile(PosL ime_drzave, char* fileName);
int SortedInputList(PosL head, PosL newPerson);
int InsertAfter(PosL head, PosL NewEl);
PosL MakeListEL(char* ime_drzave);
int PrintList(PosL first);
int PrintT(PosT curr);
PosT SortedInputTree(PosT curr, PosT NewEl);
PosT MakeTreeEl(char* ime_grada, int broj_stanovnika);

int main() {

    drzava lstDrzava = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PosL listaDrzava = &lstDrzava;

    char filename[] = "drzave.txt";
    InsToListFromFile(listaDrzava, filename);
    PrintList(listaDrzava);

    return 1;

}


int InsToListFromFile(PosL head, char* fileName) {

    FILE* f = NULL;
    f = fopen(fileName, "r");
    char ime_drzave[MAX_NAME] = { 0 };
    char grad[MAX_NAME] = { 0 };

    drzava t = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PosL temp = &t;

    if (!f) {
        printf("File is invalid.\n");
        return -1;
    }

    while (!feof(f)) {

        fscanf(f, "%s %s\n", ime_drzave, grad);
        temp = MakeListEL(ime_drzave);

        InsToTreeFromFile(temp, grad);

        SortedInputList(head, temp);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int InsToTreeFromFile(PosL ime_drzave, char* fileName) {
    FILE* f = NULL;
    f = fopen(fileName, "r");

    char ime_grada[MAX_NAME] = { 0 };
    int broj_stanovnika = 0;

    if (!f) {
        perror("File is invalid\n");
        return -1;
    }

    while (!feof(f)) {
        fscanf(f, "%s %d", ime_grada, &broj_stanovnika);
        PosT temp = MakeTreeEl(ime_grada, broj_stanovnika);
        ime_drzave->grad = SortedInputTree(ime_drzave->grad, temp);
    }

    fclose(f);

    return EXIT_SUCCESS;

}

int SortedInputList(PosL head, PosL NewEl) {

    PosL temp = NULL;
    temp = head->next;

    while (temp != NULL && strcmp(temp->ime_drzave, NewEl->ime_drzave) > 0) 
    {
        temp = temp->next;
    }

    InsertAfter(NewEl, head);
    return EXIT_SUCCESS;
}

int InsertAfter(PosL head, PosL NewEl) {

    head->next = NewEl->next;
    NewEl->next = head;

    return EXIT_SUCCESS;
}

PosL MakeListEL(char* ime_drzave) {
    PosL NewEl = NULL;
    NewEl = (PosL)malloc(sizeof(drzava));

    if (!NewEl) {
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(NewEl->ime_drzave, ime_drzave);
    NewEl->grad = NULL;
    NewEl->next = NULL;

    return NewEl;
}

int PrintList(PosL first) {
    PosL temp = first->next;

    while (temp) {
        printf("%s\n ", temp->ime_drzave);
        PrintT(temp->grad);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int PrintT(PosT curr) {
    if (curr == NULL)
        return 0;

    PrintT(curr->left);
    printf("\t%s - %d stanovnika\n", curr->ime_grada, curr->broj_stanovnika);
    PrintT(curr->right);

    return 0;
}

PosT SortedInputTree(PosT curr, PosT NewEl) {

    if (!curr)
        return NewEl;

    if (curr->broj_stanovnika < NewEl->broj_stanovnika) {
        curr->right = SortedInputTree(curr->right, NewEl);
    }

    else if (curr->broj_stanovnika > NewEl->broj_stanovnika) {
        curr->left = SortedInputTree(curr->left, NewEl);
    }
    else free(NewEl);

    return curr;
}

PosT MakeTreeEl(char* ime_grada, int broj_stanovnika) {
    PosT NewEl = (PosT)malloc(sizeof(tree));

    if (!NewEl) {
        printf("\nCan't allocate memory.");
        return NULL;
    }

    strcpy(NewEl->ime_grada, ime_grada);
    NewEl->broj_stanovnika = broj_stanovnika;
    NewEl->right = NULL;
    NewEl->left = NULL;

    return NewEl;
}