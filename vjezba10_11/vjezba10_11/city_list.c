#define _CRT_SECURE_NO_WARNINGS
#include "city_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 101

CityListP InitializeCityList(CityListP head) {

	head = (CityListP)malloc(sizeof(CityList));
	if (head == NULL) {
		printf("Error in alocating list structure.\n");
		return NULL;
	}
	strcpy(head->cityName, "");
	head->population = 0;
	head->next = NULL;

	return head;
}

int PrintCitiesList(CityListP head) {

	//head = head->next;
	if (head == NULL)
	{
		perror("List of cities is empty!\n");
		return EXIT_FAILURE;
	}
	while (head != NULL)
	{
		printf("\t\t|__ %s\n", head->cityName);
		head = head->next;
		printf("\n");
	}
	return EXIT_SUCCESS;
}

CityListP ReadCitiesListFile(CityListP head, char* citiesFileName) {

	FILE* fp = NULL;
	char cityName[MAX_SIZE] = { 0 };
	int population = 0;

	head = InitializeCityList(head);

	fp = fopen(citiesFileName, "r");
	if (fp == NULL)
	{
		printf("Error in opening the file.\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d\n", cityName, &population);
		AddCitiesToList(head, cityName, population);
	}

	fclose(fp);
	return head;
}

int AddCitiesToList(CityListP head, char* cityName, int population) {

	CityListP newCityEl = NULL;
	newCityEl = InitializeCityList(newCityEl);

	strcpy(newCityEl->cityName, cityName);
	newCityEl->population = population;

	while (head->next != NULL)
	{
		if (newCityEl->population < head->next->population)
			break;
		else if (newCityEl->population == head->next->population)
		{
			if (strcmp(newCityEl->cityName, head->next->cityName) < 0)
				break;
			else if (strcmp(newCityEl->cityName, head->next->cityName) > 0)
			{
				head = head->next;
				continue;
			}
		}
		head = head->next;
	}
	newCityEl->next = head->next;
	head->next = newCityEl;

	return EXIT_SUCCESS;
}

int FindCityInTree(CityListP head, int minValue) {

	while (head != NULL)
	{
		if (minValue < head->population)
			printf("\t\t|__ %s\t%d\n", head->cityName, head->population);
		head = head->next;
	}
	return EXIT_SUCCESS;
}