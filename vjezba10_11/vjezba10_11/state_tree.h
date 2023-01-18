#pragma once
#define MAX_STATE_NAME (60)
#include "city_list.h"
struct _stateTree;
typedef struct _stateTree* StateTreeP;
typedef struct _stateTree {
	char stateName[MAX_STATE_NAME];
	CityListP cityHead;
	StateTreeP left;
	StateTreeP right;
}StateTree;

StateTreeP InitializeStateTree(StateTreeP root);
int ReadStatesTreeFile(StateTreeP root, char* fileName);
int PrintStatesTree(StateTreeP root);
StateTreeP AddStateToTree(StateTreeP root, char* stateName, char* citiesFileName);
StateTreeP FindState(StateTreeP root, char* stateName);
int DeleteStateTree(StateTreeP root);