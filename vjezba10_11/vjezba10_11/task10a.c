#define _CRT_SECURE_NO_WARNINGS
#include "state_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (1024)

int execute_task10a() {

    StateListP head = NULL;
    char fileName[MAX_SIZE] = { 0 };
    char countryName[MAX_SIZE] = { 0 };
    StateListP foundCountry = NULL;
    int minValue=0;
    int status = 0;

    head = InitializeStateList(head);

    printf("\nEnter the name of the file where states are stored -> ");
    scanf(" %s", fileName);


    status=ReadStatesListFile(head, fileName);

    if (status == EXIT_FAILURE) {

        printf("The file with name %s doesn't exists!\nTry again :)\n",fileName);
        printf("___________________________________________________________________\n");
        printf("\nEnter the name of the file where states are stored -> ");
        scanf("%s", fileName);
        status = ReadStatesListFile(head, fileName);
    }
    
    system("cls");
    PrintListStates(head);

    printf("___________________________________________________________________\n");
    printf("Enter country name that you want to search: ");
    scanf("%s", countryName);
    foundCountry = FindCountry(head, countryName);
    if(foundCountry == NULL)
    {
        printf("That country doesn't exist in the list yet!\nTry again :)\n");
        printf("___________________________________________________________________\n");
        printf("Enter country name that you want to search: ");
        scanf("%s", countryName);
        foundCountry = FindCountry(head, countryName);
    }
    printf("___________________________________________________________________\n");
    printf("Enter minimum population value in %s you want to check out:  ", countryName);
    scanf("%d", &minValue);
    printf("___________________________________________________________________\n");
    printf("Cities in %s that have population more than %d habitants: \n\n", countryName, minValue);
    FindCity(foundCountry->cityRoot, minValue);
    printf("\n___________________________________________________________________\n");

    DeleteStateList(head);

    return EXIT_SUCCESS;
}