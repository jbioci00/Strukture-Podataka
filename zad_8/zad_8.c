#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct _Tree* Position;
typedef struct _Tree {
	int element;
	Position left;
	Position right;
}Tree;

Position createElement(int element, Position root);
Position addElement(int element, Position root);
Position deleteElement(int element, Position root);
Position findElement(int element, Position root);
Position findMin(Position root);
int inOrder(Position root);
int postOrder(Position root);
int preOrder(Position root);

int main()
{
	Position root = NULL;
	int element = 0;
	int odabir;

	do {
		printf("1-Dodaj element\n2-Izbrisi element\n3-Pronadi element\n4-inOrder ispis\n5-postOrder ispis\n6-preOrder ispis\n7-Izlaz\nTvoj odabir: ");
		scanf("%d", &odabir);
		printf("\n");
		switch (odabir) {

		case 1:
			printf("\nUnesi element koji zelis dodati: ");
			scanf("%d", &element);
			root = addElement(element, root);
			break;
		case 2:
			printf("\nUnesi element koji zelis izbrisati: ");
			scanf("%d", &element);
			deleteElement(element, root);
			break;
		case 3:
			printf("\nUnesi element koji zelis pronaci: ");
			scanf("%d", &element);
			if (findElement(element, root))
				printf("\nElement %d postoji u stablu!\n", element);
			else
				printf("\nElement ne %d postoji u stablu!\n", element);
			break;

		case 4:
			printf("inOrder: \n");
			inOrder(root);
			printf("\n");
			break;
		case 5:
			printf("postOrder: \n");
			postOrder(root);
			printf("\n\n");
			break;
		case 6:
			printf("preOrder: \n");
			preOrder(root);
			printf("\n");
			break;
		case 7:
			printf("\nIzisli ste iz programa!");
			break;
		default:
			printf("Krivi odabir!\n");
			printf("\n");
			break;
		}
		printf("\n");
	} while (odabir != 7);

	return 0;
}
Position createElement(int element, Position root)
{
	root = (Position)malloc(sizeof(Tree));
	root->element = element;
	root->left = NULL;
	root->right = NULL;
	return root;
}

Position addElement(int element, Position root) {

	if (NULL == root)
	{
		return createElement(element, root);
	}

	if (element > root->element) {
		root->right = addElement(element, root->right);
		return root;
	}

	if (element < root->element) {
		root->left = addElement(element, root->left);
		return root;
	}

}

Position findElement(int element, Position root) {

	if (NULL == root)
		return NULL;
	else if (element > root->element)
		return findElement(element, root->right);
	else if (element < root->element)
		return findElement(element, root->left);
	else
		return root;
}

Position findMin(Position root) {
	if (NULL == root)
		return NULL;
	else if (NULL == root->left)
		return root;
	else
		return findMin(root->left);
}

int inOrder(Position root) {
	if (NULL == root)
		return -1;
	inOrder(root->left);
	printf("%d ", root->element);
	inOrder(root->right);
	return 0;
}

int preOrder(Position root)
{
	if (NULL == root)
		return -1;
	printf("%d ", root->element);
	preOrder(root->left);
	preOrder(root->right);
	return 0;
}

int postOrder(Position root)
{
	if (NULL == root)
		return -1;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->element);
	return 0;
}
Position deleteElement(int element, Position root) {

	Position temp = NULL;
	if (NULL == root)
		printf("\tElement ne postoji!\n");
	else if (element < root->element)
		root->left = deleteElement(element, root->left);
	else if (element > root->element)
		root->right = deleteElement(element, root->right);
	else if (root->left != NULL && root->right != NULL)
	{
		temp = findMin(root->right);
		root->element = temp->element;
		root->right = deleteElement(root->element, root->right);
	}
	else
	{
		temp = root;
		if (NULL == root->left)
			root = root->right;
		else
			root = root->left;
		free(temp);
	}

	return root;
}