#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _tree;
typedef struct _tree *TreeP;
typedef struct _tree
{
	int number;
	TreeP left;
	TreeP right;
} Tree;

struct _list;
typedef struct _list *ListP;
typedef struct _list
{
	int element;
	ListP next;

} List;

int Inorder(TreeP root, ListP head);
TreeP CreateEmpty(TreeP root);
TreeP InsertNumberInTree(TreeP root, int element);
TreeP Replace(TreeP root);
int Sum(TreeP root);
TreeP InsertRandom(TreeP root);
int InsertLast(ListP head, int number);
ListP FindLast(ListP head);
int InsertInList(ListP head, int number);
int InsertListInFile(ListP list1, ListP list2, ListP list3, char *fileName);
int DeleteTree(TreeP root);
int DeleteList(ListP head);

int main()
{
	TreeP root = NULL;
	ListP head1 = NULL, head2 = NULL, head3 = NULL;
	char fileName[50] = {0};

	root = CreateEmpty(root);
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
	root = CreateEmpty(root);
	root = InsertRandom(root);
	Inorder(root, head3);

	printf("\nEnter the name of the file you want to save the lists:");
	scanf(" %s",fileName);
	InsertListInFile(head1->next, head2->next, head3->next, fileName);

	DeleteTree(root);
	DeleteList(head1);
	DeleteList(head2);
	DeleteList(head3);

	return EXIT_SUCCESS;
}

TreeP CreateEmpty(TreeP root)
{
	if (root != NULL)
	{
		root->left = CreateEmpty(root->left);
		root->right = CreateEmpty(root->right);
		free(root);
	}
	return NULL;
}

int Inorder(TreeP root, ListP head)
{
	if (root == NULL)
		return 0;

	Inorder(root->left, head);
	InsertLast(head, root->number);
	Inorder(root->right, head);

	return EXIT_SUCCESS;
}

TreeP InsertNumberInTree(TreeP root, int element)
{
	if (root == NULL)
	{
		root = (TreeP)malloc(sizeof(Tree));
		root->number = element;
		root->left = NULL;
		root->right = NULL;
	}
	else if (element >= root->number)
	{
		root->left = InsertNumberInTree(root->left, element);
	}
	else if (element <= root->number)
	{
		root->right = InsertNumberInTree(root->right, element);
	}

	return root;
}

int Sum(TreeP root)
{
	int sum = 0;
	if (root == NULL)
		return sum;
	if (root->left != NULL)
		sum += root->left->number + Sum(root->left);
	if (root->right != NULL)
		sum += root->right->number + Sum(root->right);

	return sum;
}

TreeP Replace(TreeP root)
{
	if (root != NULL)
	{
		root->number = Sum(root);
		root->left = Replace(root->left);
		root->right = Replace(root->right);
	}
	return root;
}

TreeP InsertRandom(TreeP root)
{
	int i = 0;
	int number = 0;

	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		number = (rand() % (90 - 10 + 1)) + 10;
		root = InsertNumberInTree(root, number);
	}

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

	if (temp == NULL)
	{
		printf("Error in alocating memory. \n");
		return EXIT_FAILURE;
	}
	temp->element = number;
	temp->next = head->next;
	head->next = temp;

	return EXIT_SUCCESS;
}

int InsertListInFile(ListP list1, ListP list2, ListP list3, char *fileName)
{
	FILE *fp = NULL;
	fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		printf("Error in opening the file!");
		return EXIT_FAILURE;
	}
	fprintf(fp,"a)\n");
	while (list1 != NULL)
	{
		fprintf(fp, "%d\t", list1->element);
		list1 = list1->next;
	}
	fprintf(fp, "\n");
	fprintf(fp,"b)\n");
	while (list2 != NULL)
	{
		fprintf(fp, "%d\t", list2->element);
		list2 = list2->next;
	}
	fprintf(fp, "\n");
	fprintf(fp,"c)\n");
	while (list3 != NULL)
	{
		fprintf(fp, "%d\t", list3->element);
		list3 = list3->next;
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int DeleteTree(TreeP root)
{

	while (root != NULL)
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
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}