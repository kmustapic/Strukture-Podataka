#define _CRT_SECURE_NO_WARNINGS

#include "city_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 101

CityListP InitializeCityList(CityListP head) 
{
	head = (CityListP)malloc(sizeof(CityList));
	if (NULL == head) {
		printf("\nError in allocating list structure!\n");
		return NULL;
	}
	strcpy(head->cityName, "");
	head->population = 0;
	head->next = NULL;

	return head;
}

int PrintCitiesList(CityListP head) 
{
	if (NULL == head)
	{
		perror("\nList of cities is currently empty!\n");
		return EXIT_FAILURE;
	}

	CityListP p = NULL;
	p = head->next;

	while (NULL != p)
	{
		printf("\t\t|__ %s\t\t%d\n", p->cityName, p->population);
		p = p->next;
	}

	return EXIT_SUCCESS;
}

CityListP ReadCitiesListFile(CityListP head, char* citiesFileName) 
{
	FILE* fp = NULL;
	char cityName[MAX_SIZE] = { 0 };
	int population = 0;

	head = InitializeCityList(head);
	fp = fopen(citiesFileName, "r");
	if (NULL == fp)
	{
		printf("\nError in opening the file!\n");
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

int AddCitiesToList(CityListP head, char* cityName, int population) 
{
	CityListP newCityEl = NULL;
	newCityEl = InitializeCityList(newCityEl);
	strcpy(newCityEl->cityName, cityName);
	newCityEl->population = population;

	while (NULL != head->next)
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

int FindCityInTree(CityListP head, int minValue) 
{
	while (NULL != head)
	{
		if (minValue < head->population)
			printf("\t\t|__ %s\t%d\n", head->cityName, head->population);
		
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int DeleteCityList(CityListP head) 
{
	CityListP temp = NULL;
	while (head->next) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	head->next = NULL;

	return EXIT_SUCCESS;
}