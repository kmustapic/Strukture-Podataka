#define _CRT_SECURE_NO_WARNINGS

#include "state_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)

int execute_task10b() 
{
    StateTreeP root = NULL;
    char fileName[MAX_SIZE] = { 0 };
    char stateName[MAX_SIZE] = { 0 };
    StateTreeP foundState = NULL;
    int minValue, status = 0, counter = 0;

    root = InitializeStateTree(root);

    printf("\nEnter the name of the file where states are stored: ");
    scanf(" %s", fileName);

    status=ReadStatesTreeFile(root, fileName);

    while (status == EXIT_FAILURE) {
        system("cls");
        printf("\nEnter the name of the file where states are stored: ", fileName);
        scanf("%s", fileName);
        status = ReadStatesTreeFile(root, fileName);
    }
    system("cls");
    printf(
        "=========================================================================\n"
        "\t\tList of countries\n"
        "=========================================================================\n\n");
    counter = PrintStatesTree(root,counter);
    if(counter > 1)
        perror("\nTree of countries is currenttly empty!\n");
    printf(
            "=========================================================================\n"
            "Enter country name that you want to search: ");
    scanf("%s", stateName);
    foundState = FindState(root, stateName);

    while (NULL == foundState)
    {
        printf(
            "That country doesn't exist in the list yet!\n"
            "=========================================================================\n"
            "Enter country name that you want to search: ");
        scanf("%s", stateName);
        foundState = FindState(root, stateName);
    }

    printf(
            "=========================================================================\n"
            "Enter minimum population value in %s you want to check out:  ", stateName);
    scanf("%d", &minValue);
    printf(
            "=========================================================================\n"
            "Cities in %s that have population more than %d habitants: \n\n", stateName, minValue);
    FindCityInTree(foundState->cityHead, minValue);
    printf("\n\n=========================================================================\n");

    root = DeleteStateTree(root);
    if(NULL == root)
        printf(
                "Tree with countries (containing lists with cities)\n"
                "is successfully deleted!\n"
                "=========================================================================\n");

    return EXIT_SUCCESS;
}