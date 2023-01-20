/*
9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7
   koji su spremljeni u cvorove binarnog stabla.

a) Napisati funkciju insert koja dodaje element u stablo
   tako da se pozivima te funkcije za sve element zadanog niza brojeva
   stvori stablo kao na slici Slika 1.
   Funkcija vraca pokazivac na korijen stabla.

b) Napisati funkciju replace koja ce svaki element stabla
   zamijeniti sumom elemenata u njegovom lijevom i desnom podstablu
   (tj. sumom svih potomaka prije zamjene vrijednosti u tim potomcima).
   Npr. stablo sa slike Slika 1 transformirat ce se
   u stablo na slici Slika 2.

c) Prepraviti program na nacin da umjesto
   predefiniranog cjelobrojnog polja
   koristenjem funkcije rand() generira slucajne brojeve
   u rasponu <10, 90>.
   Takoder, potrebno je upisati u datoteku.
*/

#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _tree;
typedef struct _tree* TreeP;
typedef struct _tree
{
	int number;
	TreeP left;
	TreeP right;
} Tree;

struct _list;
typedef struct _list* ListP;
typedef struct _list
{
	int element;
	ListP next;

} List;

int Inorder(TreeP root, ListP head);
TreeP CreateEmptyTree(TreeP root);
TreeP InsertNumberInTree(TreeP root, int element);
TreeP Replace(TreeP root);
int Sum(TreeP root);
TreeP InsertRandom(TreeP root);
int InsertLast(ListP head, int number);
ListP FindLast(ListP head);
int InsertInList(ListP head, int number);
int InsertListInFile(ListP list1, ListP list2, ListP list3, char* fileName);
int DeleteTree(TreeP root);
int DeleteList(ListP head);

int main()
{
	TreeP root = NULL;
	ListP head1 = NULL, head2 = NULL, head3 = NULL;
	char fileName[50] = { 0 };

	root = CreateEmptyTree(root);
	head1 = (ListP)malloc(sizeof(List));
	head1->next = NULL;
	head2 = (ListP)malloc(sizeof(List));
	head2->next = NULL;
	head3 = (ListP)malloc(sizeof(List));
	head3->next = NULL;

	// a)
	root = InsertNumberInTree(root, 2);
	root = InsertNumberInTree(root, 5);
	root = InsertNumberInTree(root, 7);
	root = InsertNumberInTree(root, 8);
	root = InsertNumberInTree(root, 11);
	root = InsertNumberInTree(root, 1);
	root = InsertNumberInTree(root, 4);
	root = InsertNumberInTree(root, 2);
	root = InsertNumberInTree(root, 3);
	root = InsertNumberInTree(root, 7);
	Inorder(root, head1);

	// b)
	root = Replace(root);
	Inorder(root, head2);

	// c)
	root = CreateEmptyTree(root);
	root = InsertRandom(root);
	Inorder(root, head3);

	printf("\nEnter the name of the file you want to save the lists: ");
	scanf(" %s", fileName);
	InsertListInFile(head1->next, head2->next, head3->next, fileName);

	DeleteTree(root);
	DeleteList(head1);
	DeleteList(head2);
	DeleteList(head3);

	if (DeleteTree(root) == EXIT_SUCCESS)
		printf("\nMemory allocated for tree is successfully deleted!\n");

	if (DeleteList(head1) == EXIT_SUCCESS)
		printf("\nMemory allocated for 1st list is successfully deleted!\n");

	if (DeleteList(head2) == EXIT_SUCCESS)
		printf("\nMemory allocated for 2nd list is successfully deleted!\n");

	if (DeleteList(head3) == EXIT_SUCCESS)
		printf("\nMemory allocated for 3rd list is successfully deleted!\n");

	return EXIT_SUCCESS;
}

TreeP CreateEmptyTree(TreeP root)
{
	if (NULL != root)
	{
		root->left = CreateEmptyTree(root->left);
		root->right = CreateEmptyTree(root->right);
		free(root);
	}

	return NULL;
}

int Inorder(TreeP root, ListP head)
{
	if (NULL == root)
		return EXIT_FAILURE;

	Inorder(root->left, head);
	InsertLast(head, root->number);
	Inorder(root->right, head);

	return EXIT_SUCCESS;
}

TreeP InsertNumberInTree(TreeP root, int element)
{
	if (NULL == root)
	{
		root = (TreeP)malloc(sizeof(Tree));
		root->number = element;
		root->left = NULL;
		root->right = NULL;
	}

	else if (element >= root->number)
		root->left = InsertNumberInTree(root->left, element);

	else if (element <= root->number)
		root->right = InsertNumberInTree(root->right, element);

	return root;
}

int Sum(TreeP root)
{
	int sum = 0;
	if (NULL == root)
		return sum;

	if (NULL != root->left)
		sum += root->left->number + Sum(root->left);

	if (NULL != root->right)
		sum += root->right->number + Sum(root->right);

	return sum;
}

TreeP Replace(TreeP root)
{
	if (NULL != root)
	{
		root->number = Sum(root);
		root->left = Replace(root->left);
		root->right = Replace(root->right);
	}

	return root;
}

TreeP InsertRandom(TreeP root)
{
	int i = 0, number = 0;

	printf("\n");
	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		number = (rand() % (90 - 10 + 1)) + 10;
		printf("%d) New generated number: %d\n", i + 1, number);
		root = InsertNumberInTree(root, number);
	}
	printf("\n");

	return root;
}

int InsertLast(ListP head, int number)
{
	ListP last = NULL;
	last = FindLast(head);
	InsertInList(last, number);

	return EXIT_SUCCESS;
}

ListP FindLast(ListP head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int InsertInList(ListP head, int number)
{
	ListP temp = NULL;
	temp = (ListP)malloc(sizeof(List));
	if (NULL == temp)
	{
		printf("\nMemory can't be allocated!\n");
		return EXIT_FAILURE;
	}
	temp->element = number;
	temp->next = head->next;
	head->next = temp;

	return EXIT_SUCCESS;
}

int InsertListInFile(ListP list1, ListP list2, ListP list3, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "w");
	if (NULL == fp)
	{
		printf("\nFile can't be opened!\n");
		return EXIT_FAILURE;
	}

	fprintf(fp, "a)\n");
	while (NULL != list1)
	{
		fprintf(fp, "%d\t", list1->element);
		list1 = list1->next;
	}

	fprintf(fp, "\n\nb)\n");
	while (NULL != list2)
	{
		fprintf(fp, "%d\t", list2->element);
		list2 = list2->next;
	}

	fprintf(fp, "\n\nc)\n");
	while (NULL != list3)
	{
		fprintf(fp, "%d\t", list3->element);
		list3 = list3->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int DeleteTree(TreeP root)
{

	while (NULL != root)
	{
		DeleteTree(root->left);
		DeleteTree(root->left);
		free(root);
	}

	return EXIT_SUCCESS;
}

int DeleteList(ListP head)
{
	ListP temp = NULL;
	while (NULL != head->next)
	{
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

/*
	FURTHER IMPROVEMENT:
	_________________________________________________________________________________________
	* basically works, in some cases occurs error: read access violation
	  -> need to check memory addresses and fix the issue
	_________________________________________________________________________________________
*/