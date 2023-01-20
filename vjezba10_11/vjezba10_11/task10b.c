#define _CRT_SECURE_NO_WARNINGS
#include "state_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (1024)

int execute_task10b() {

    StateTreeP root = NULL;
    char fileName[MAX_SIZE] = { 0 };
    char stateName[MAX_SIZE] = { 0 };
    StateTreeP foundState = NULL;
    int minValue;
    int status = 0;

    root = InitializeStateTree(root);

    printf("\nEnter the name of the file where states are stored -> ");
    scanf(" %s", fileName);

    status=ReadStatesTreeFile(root, fileName);

    if (status == EXIT_FAILURE) {

        printf("The file with name %s doesn't exists!\nTry again :)\n", fileName);
        printf("___________________________________________________________________\n");
        printf("\nEnter the name of the file where states are stored -> ");
        scanf("%s", fileName);
        status = ReadStatesTreeFile(root, fileName);
    }

    printf("___________________________________________________________________\n");
    printf("\t\tList of states\n");
    printf("___________________________________________________________________\n");
    PrintStatesTree(root);
    
    printf("___________________________________________________________________\n");
    printf("Enter state name that you want to search: ");
    scanf("%s", stateName);
    foundState = FindState(root, stateName);
    while (foundState == NULL)
    {
        printf("That state doesn't exist in the list yet!\nTry again :)\n");
        system("cls");
        PrintStatesTree(root);
        printf("___________________________________________________________________\n");
        printf("Enter state name that you want to search: ");
        scanf("%s", stateName);
        foundState = FindState(root, stateName);
    }
    printf("___________________________________________________________________\n");
    printf("Enter minimum population value in %s you want to check out:  ", stateName);
    scanf("%d", &minValue);
    printf("___________________________________________________________________\n");
    printf("Cities in %s that have population more than %d habitants: \n\n", stateName, minValue);
    FindCityInTree(foundState->cityHead, minValue);
    printf("\n___________________________________________________________________\n");

    DeleteStateTree(root);

    return EXIT_SUCCESS;
}