#define _CRT_SECURE_NO_WARNINGS
#include "state_list.h"
#include "city_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 101

StateListP InitializeStateList(StateListP head)
{
    head = (StateListP)malloc(sizeof(StateList));
    if (head == NULL)
    {
        printf("Error in alocating states list.\n");
        return NULL;
    }
    strcpy(head->stateName, "");
    head->next = NULL;
    head->cityRoot = NULL;

    return head;
}

int AddStateToList(StateListP head, char* stateName, char* citiesFileName) {

    StateListP newListEl = NULL;
    newListEl = InitializeStateList(newListEl);
    strcpy(newListEl->stateName, stateName);
    newListEl->cityRoot = InitializeCityTree(newListEl->cityRoot);

    newListEl->cityRoot = ReadCitiesFromFile(newListEl->cityRoot, citiesFileName);

    while (head != NULL)
    {
        if (head->next == NULL)
        {
            head->next = newListEl;
            newListEl->next = NULL;
            break;
        }
        if (strcmp(newListEl->stateName, head->next->stateName) < 0)
        {
            newListEl->next = head->next;
            head->next = newListEl;
            break;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int PrintListStates(StateListP head)
{
    head = head->next;
    if (head == NULL)
    {
        perror("List of countries is empty!\n");
        return;
    }
    printf("___________________________________________________________________\n");
    printf("\t\tList of countries\n");
    printf("___________________________________________________________________\n\n");

    while (head != NULL)
    {
        printf("\t> %s\n", head->stateName);
        PrintTreeCities(head->cityRoot);
        head = head->next;
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int ReadStatesListFile(StateListP head, char* fileName) {

    FILE* fp = NULL;
    char stateName[MAX_SIZE];
    char citiesFileName[MAX_SIZE];

    fp = fopen(fileName, "r");
    if (!fp)
    {
        //perror("File can't be opened!\n");
        return EXIT_FAILURE;
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s\n", stateName, citiesFileName);
        AddStateToList(head, stateName, citiesFileName);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

StateListP FindCountry(StateListP head, char* countryName) {

    head = head->next;
    while (head != NULL)
    {
        if (strcmp(head->stateName, countryName) == 0)
        {
            return head;
        }
        head = head->next;
    }

    return head;
}

int DeleteStateList(StateListP head) {
    StateListP temp = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        temp->cityRoot=DeleteCityTree(temp->cityRoot);
        free(temp);
    }
    return EXIT_SUCCESS;
}