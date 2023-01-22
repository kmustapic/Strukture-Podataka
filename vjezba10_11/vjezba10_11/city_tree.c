#define _CRT_SECURE_NO_WARNINGS

#include "city_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 101

static int flag = EXIT_FAILURE;

CityTreeP InitializeCityTree(CityTreeP root) 
{
    root = (CityTreeP)malloc(sizeof(CityTree));
    if (NULL == root) {
        printf("\nError in allocating tree structure!\n");
        return NULL;
    }
    strcpy(root->cityName, "");
    root->population = 0;
    root->left = NULL;
    root->right = NULL;

    return root;
}

CityTreeP AddCityToTree(CityTreeP root, char* cityName, int population) 
{
    if (NULL == root)
    {
        root = InitializeCityTree(root);
        strcpy(root->cityName, cityName);
        root->population = population;
        root->left = NULL;
        root->right = NULL;
    }

    if (population < root->population)
        root->left = AddCityToTree(root->left, cityName, population);
    
    else if (population > root->population)
        root->right = AddCityToTree(root->right, cityName, population);
    
    else
    {
        if (strcmp(cityName, root->cityName) < 0)
            root->left = AddCityToTree(root->left, cityName, population);

        else if (strcmp(cityName, root->cityName) > 0)
            root->right = AddCityToTree(root->right, cityName, population);
    }

    return root;
}

CityTreeP ReadCitiesFromFile(CityTreeP root, char* citiesFileName)
{
    FILE* fp = NULL;
    char cityName[MAX_SIZE] = { 0 };
    int population = 0;
    int i;

    fp = fopen(citiesFileName, "r");
    if (NULL == fp)
    {
        perror("\nFile can't be opened or doesn't exist yet!\n");
        return;
    }

    int numOfLines = 0;
    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, fp))
        numOfLines++;
    
    rewind(fp);
    for (i = 0; i < numOfLines; i++)
    {
        fscanf(fp, "%s %d", cityName, &population);
        root = AddCityToTree(root, cityName, population);
    }
    fclose(fp);

    return root;
}

int PrintTreeCities(CityTreeP root)
{
    if (NULL == root)
        return EXIT_SUCCESS;

    PrintTreeCities(root->right);
    printf("\t\t|__ %s\t\t%d\n", root->cityName,root->population);
    PrintTreeCities(root->left);

    return EXIT_SUCCESS;
}

int FindCity(CityTreeP root, int minValue) 
{
    if (NULL == root)
        return EXIT_FAILURE;
    
    FindCity(root->left, minValue);
    if (root->population >= minValue)
    {
        flag = EXIT_SUCCESS;
        printf("\t\t|__ %s\t%d\n", root->cityName, root->population);
    }
    FindCity(root->right, minValue);

    return EXIT_SUCCESS;
}

CityTreeP DeleteCityTree(CityTreeP root) 
{
    if (!root)
        return NULL;

    root->left = DeleteCityTree(root->left);
    root->right = DeleteCityTree(root->right);
    free(root);

    return NULL;
}