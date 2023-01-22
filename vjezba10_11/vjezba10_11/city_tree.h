#pragma once
#define MAX_CITY_NAME (60)

struct _cityTree;
typedef struct _cityTree* CityTreeP;
typedef struct _cityTree 
{
	char cityName[MAX_CITY_NAME];
	int population;
	CityTreeP left;
	CityTreeP right;

}CityTree;

CityTreeP InitializeCityTree(CityTreeP root);
CityTreeP AddCityToTree(CityTreeP root, char* cityName, int population);
int PrintTreeCities(CityTreeP root);
CityTreeP ReadCitiesFromFile(CityTreeP root, char* citiesFileName);
int FindCity(CityTreeP root, int minValue);
CityTreeP DeleteCityTree(CityTreeP root);