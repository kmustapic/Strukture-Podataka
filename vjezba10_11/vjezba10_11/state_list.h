#pragma once
#define MAX_STATE_NAME (60)
#include "city_tree.h"

struct _stateList;
typedef struct _stateList* StateListP;
typedef struct _stateList {

	char stateName[MAX_STATE_NAME];
	CityTreeP cityRoot;
	StateListP next;

}StateList;

StateListP InitializeStateList(StateListP head);
int AddStateToList(StateListP head, char* stateName, char* citiesFileName);
int PrintListStates(StateListP head);
int ReadStatesListFile(StateListP head, char* fileName);
StateListP FindCountry(StateListP head, char* countryName);
int DeleteStateList(StateListP head);