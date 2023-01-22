#pragma once
#define MAX_CITY_NAME (60)

struct _cityList;
typedef struct _cityList* CityListP;
typedef struct _cityList 
{
	char cityName[MAX_CITY_NAME];
	int population;
	CityListP next;

}CityList;

CityListP InitializeCityList(CityListP head);
int PrintCitiesList(CityListP head);
CityListP ReadCitiesListFile(CityListP head, char* citiesFileName);
int AddCitiesToList(CityListP head, char* cityName, int population);
int FindCityInTree(CityListP head, int minValue);
int DeleteCityList(CityListP head);