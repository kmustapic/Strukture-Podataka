#define _CRT_SECURE_NO_WARNINGS

#include "state_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (1024)

StateTreeP InitializeStateTree(StateTreeP root) 
{
	root = (StateTreeP)malloc(sizeof(StateTree));
	if (NULL == root) {
		printf("\nError in allocating tree structure for state!\n");
		return NULL;
	}
	strcpy(root->stateName, "");
	root->cityHead = NULL;
	root->left = NULL;
	root->right = NULL;

	return root;
}

int ReadStatesTreeFile(StateTreeP root, char* fileName)
{
	FILE* fp = NULL;
	char stateName[MAX_SIZE];
	char citiesFileName[MAX_SIZE];

	fp = fopen(fileName, "r");
	if (!fp)
	{
		perror(
				"\n========================================================================="
				"\nFile can't be opened or currently doesn't exist!\n"
				"Please press enter and enter existing file name.\n"
				"=========================================================================\n");
		system("pause");

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
	if (NULL == root)
	{
		root = InitializeStateTree(root);
		strcpy(root->stateName, stateName);
		root->cityHead = ReadCitiesListFile(root->cityHead, citiesFileName);
	}

	else if (strcmp(root->stateName, stateName) > 0)
		root->left = AddStateToTree(root->left, stateName, citiesFileName);
	
	else if (strcmp(root->stateName, stateName) < 0)
		root->right = AddStateToTree(root->right, stateName, citiesFileName);

	return root;
}

int PrintStatesTree(StateTreeP root, int counter) 
{
	if (NULL == root)
	{
		counter++;
		return EXIT_FAILURE;
	}
		
	else 
	{
//			if (counter > 1)
//			{
				PrintStatesTree(root->left, counter);
				printf("\t> %s\n", root->stateName);
				PrintCitiesList(root->cityHead);
				printf("\n\n");
				PrintStatesTree(root->right, counter);
//			}
	}

	return counter;
}

StateTreeP FindState(StateTreeP root, char* stateName) 
{
	if (NULL == root)
		return NULL;

	else if (strcmp(stateName, root->stateName) == 0)
		return root;

	else if (strcmp(stateName, root->stateName) > 0)
		return FindState(root->right, stateName);

	return FindState(root->left, stateName);
}

StateTreeP DeleteStateTree(StateTreeP root) 
{
	if (!root)
		return EXIT_SUCCESS;

	root->left = DeleteStateTree(root->left);
	root->right = DeleteStateTree(root->right);
	free(root);

	return NULL;
}