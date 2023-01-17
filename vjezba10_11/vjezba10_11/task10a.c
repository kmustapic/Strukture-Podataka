#define _CRT_SECURE_NO_WARNINGS
#include "state_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 101

#define LINE_MAX (1024)

int execute_task10a() {

    StateListP head = NULL;
    char fileName[LINE_MAX] = { 0 };
    char countryName[MAX_SIZE] = { 0 };
    StateListP foundCountry = NULL;
    int minValue;

    head = InitializeStateList(head);

    printf("\nEnter the name of the file where states are stored -> ");
    scanf(" %s", fileName);

    ReadStatesListFile(head, fileName);

    PrintListStates(head);

    printf("___________________________________________________________________\n");
    printf("Enter country name that you want to search: ");
    scanf("%s", countryName);
    foundCountry = FindCountry(head, countryName);
    while (foundCountry == NULL)
    {
        printf("That country doesn't exist in the list yet!\nTry again :)\n");
        system("cls");
        PrintListStates(head);
        printf("___________________________________________________________________\n");
        printf("Enter country name that you want to search: ");
        scanf("%s", countryName);
        foundCountry = FindCountry(head, countryName);
    }
    printf("___________________________________________________________________\n");
    printf("Enter minimum population value in %s you want to check out:  ", countryName);
    scanf("%d", &minValue);
    printf("___________________________________________________________________\n");
    printf("Cities in %s that havev population more than %d habitants: \n\n", countryName, minValue);
    FindCity(foundCountry->cityRoot, minValue);
    printf("\n___________________________________________________________________\n");

    return EXIT_SUCCESS;
}