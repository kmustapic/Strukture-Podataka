#define _CRT_SECURE_NO_WARNINGS

#include "state_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)

int execute_task10a() 
{
    StateListP head = NULL;
    char fileName[MAX_SIZE] = { 0 };
    char countryName[MAX_SIZE] = { 0 };
    StateListP foundCountry = NULL;
    int minValue=0, status = 0;

    head = InitializeStateList(head);

    printf("\nEnter the name of the file where states are stored: ");
    scanf(" %s", fileName);

    status=ReadStatesListFile(head, fileName);

    while (status == EXIT_FAILURE) 
    {
        system("cls");
        printf("\nEnter the name of the file where states are stored: ");
        scanf("%s", fileName);
        status = ReadStatesListFile(head, fileName);
    }
    system("cls");
    PrintListStates(head);
    printf(
            "=========================================================================\n"
            "Enter country name that you want to search: ");
    scanf("%s", countryName);
    foundCountry = FindCountry(head, countryName);

    while(NULL == foundCountry)
    {
        printf(
                "That country doesn't exist in the list yet!\n"
                "=========================================================================\n"
                "Enter country name that you want to search: ");
        scanf("%s", countryName);
        foundCountry = FindCountry(head, countryName);
    }

    printf(
            "=========================================================================\n"
            "Enter minimum population value in %s you want to check out:  ", countryName);
    scanf("%d", &minValue);
    printf(
            "=========================================================================\n"
            "Cities in %s that have population more than %d habitants: \n\n", countryName, minValue);
    FindCity(foundCountry->cityRoot, minValue);
    printf("\n\n=========================================================================\n");

    status = DeleteStateList(head);
    if ( status == EXIT_SUCCESS)
        printf(
                "List with countries (containing trees with cities)\n"
                "is successfully deleted!\n"
                "=========================================================================\n");

    return EXIT_SUCCESS;
}