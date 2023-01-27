#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

#define MAX_SIZE 101
#define SIZE 11

struct _city;
typedef struct _city* CityP;
struct _city
{
    char name[MAX_SIZE];
    int population;
    CityP left;
    CityP right;
} City;

struct _country;
typedef struct _country* CountryP;
struct _country
{
    char name[MAX_SIZE];
    CityP citiesP;
    CountryP next;
} Country;

void AddCountryToList(CountryP currentListEl, char* countryName, char* citiesFileName);
void AddCitiesToTree(CityP currentTreeNode, char* citiesFileName);
CityP AddCityToTree(CityP newCity, char* cityName, int population);
void PrintCountries(CountryP currentCountry);
void PrintCities(CityP currentCity);
CountryP FindCountry(CountryP currentCountry, char* countryName);
int FindCity(CityP currentCity, int minValue);
int CreateKey(char* countryName);
void ExecuteTask11();

#endif
