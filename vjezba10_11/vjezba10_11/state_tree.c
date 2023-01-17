#define _CRT_SECURE_NO_WARNINGS
#include "state_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 101

StateTreeP InitializeStateTree(StateTreeP root) {

	root = (StateTreeP)malloc(sizeof(StateTree));
	if (root == NULL) {
		printf("Error in alocating tree structure.\n");
		return NULL;
	}
	strcpy(root->stateName, "");
	root->cityHead = NULL;
	root->left = NULL;
	root->right = NULL;

	return root;
}

int ReadStatesTreeFile(StateTreeP root, char* fileName) {

	FILE* fp = NULL;
	char stateName[MAX_SIZE];
	char citiesFileName[MAX_SIZE];

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		perror("File can't be opened!\n");
		return EXIT_FAILURE;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s\n", stateName, citiesFileName);
		AddStateToTree(root, stateName, citiesFileName);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

StateTreeP AddStateToTree(StateTreeP root, char* stateName, char* citiesFileName)
{
	if (root == NULL)
	{
		root = InitializeStateTree(root);
		strcpy(root->stateName, stateName);
		//root->cityHead = NULL;
		root->cityHead = ReadCitiesListFile(root->cityHead, citiesFileName);
	}
	else if (strcmp(root->stateName, stateName) > 0)
		root->left = AddStateToTree(root->left, stateName, citiesFileName);
	else if (strcmp(root->stateName, stateName) < 0)
		root->right = AddStateToTree(root->right, stateName, citiesFileName);

	return root;
}

int PrintStatesTree(StateTreeP root) {

	if (root == NULL)
		return EXIT_SUCCESS;
	else
	{
		PrintStatesTree(root->left);
		printf("\t> %s\n", root->stateName);
		PrintCitiesList(root->cityHead);
		PrintStatesTree(root->right);
	}
	return EXIT_SUCCESS;
}

StateTreeP FindState(StateTreeP root, char* stateName) {

	if (root == NULL)
		return NULL;
	else if (strcmp(stateName, root->stateName) == 0)
		return root;
	else if (strcmp(stateName, root->stateName) > 0)
		return FindState(root->right, stateName);

	return FindState(root->left, stateName);
}