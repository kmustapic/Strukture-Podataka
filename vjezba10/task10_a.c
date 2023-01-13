#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max (60)

struct _cityTree;
typedef struct _Citytree *CityTreeP;
typedef struct _Citytree
{
    char cityName[max];
    int population;
    CityTreeP left;
    CityTreeP right;
} CityTree;

struct _stateList;
typedef struct _stateList *StateListP;
typedef struct _stateList
{
    char stateName[max];
    CityTreeP cityRoot;
    StateListP next;
} StateList;

StateListP InitializeList(StateListP head);
CityTreeP InitializeTree(CityTreeP root);
int ReadStatesFromFile(StateListP head, char *fileName);
int InsertStatesSorted(StateListP head, char *state_name, char *state_file);
int ReadCitiesFromFile(CityTreeP root, char *fileName);
CityTreeP InsertCitiesInTree(CityTreeP root, char *cityName,int cityPopulation);
int PrintList(StateListP head);
int PrintInorder(CityTreeP root);

int main()
{
    StateListP head = NULL;
    char fileName[max] = {0};

    head = InitializeList(head);

    printf("Insert the name of the file with states:");
    scanf(" %s", fileName);

    ReadStatesFromFile(head, fileName);
    PrintList(head);

    return EXIT_SUCCESS;
}

StateListP InitializeList(StateListP head)
{
    head = (StateListP)malloc(sizeof(StateList));
    if (head == NULL)
    {
        printf("Error in alocating memory.\n");
        return NULL;
    }
    strcpy(head->stateName, "");
    head->cityRoot = NULL;
    head->next = NULL;

    return head;
}

CityTreeP InitializeTree(CityTreeP root)
{
    root = (CityTreeP)malloc(sizeof(CityTree));
    if (root == NULL)
    {
        printf("Error in alocating memory.\n");
        return NULL;
    }
    strcpy(root->cityName, "");
    root->population = 0;
    root->left = NULL;
    root->right = NULL;

    return root;
}

int ReadStatesFromFile(StateListP head, char *fileName)
{
    FILE *fp = NULL;
    char state_name[max] = {0};
    char state_file[max] = {0};

    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error in opening the file.\n");
        return EXIT_FAILURE;
    }
    while (!feof(fp))
    {
        fprintf(fp, " %s %s", state_name, state_file);
        InsertStatesSorted(head, state_name, state_file);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int InsertStatesSorted(StateListP head, char *state_name, char *state_file)
{
    StateListP q = NULL;

    q = InitializeList(q);

    strcpy(q->stateName, state_name);
    ReadCitiesFromFile(q->cityRoot, state_file);

    while (head != NULL)
    {
        if (head->next == NULL)
        {
            head->next = q;
            q->next = NULL;
            break;
        }
        else if (strcmp(state_name, head->next->stateName) < 0)
        {
            q->next = head->next;
            head->next = q;
            break;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int ReadCitiesFromFile(CityTreeP root, char *fileName)
{
    FILE *fp = NULL;
    char cityName[max] = {0};
    int cityPopulation = 0;

    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error in opening file.\n");
        return EXIT_FAILURE;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%s %d\n", cityName, &cityPopulation);
        root = InsertCitiesInTree(root, cityName, cityPopulation);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

CityTreeP InsertCitiesInTree(CityTreeP root, char *cityName,int cityPopulation)
{
    if (root == NULL)
    {
        root = InitializeTree(root);
        strcpy(root->cityName, cityName);
        root->population = cityPopulation;
        root->left = NULL;
        root->right = NULL;
    }
    // ovo stavit u posebnu funkciju cityCompare slicno ka DateCmp ili strcmp
    else if (cityPopulation == root->population)
    {
        if (strcmp(cityName, root->cityName) < 0)
            root->left = InsertCitiesInTree(root->left, cityName, cityPopulation);
        else if (strcmp(cityName, root->cityName) > 0)
            root->right = InsertCitiesInTree(root->right, cityName, cityPopulation);
    }
    else
    {
        if (cityPopulation < root->population)
            root->left = InsertCitiesInTree(root->left, cityName, cityPopulation);
        else if (cityPopulation > root->population)
            root->right = InsertCitiesInTree(root->right, cityName, cityPopulation);
    }
    return root;
}

int PrintList(StateListP head)
{
    head=head->next;
    while (head != NULL)
    {
        printf("\n%s:\n", head->stateName);
        PrintInorder(head->cityRoot);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int PrintInorder(CityTreeP root)
{
    if (root == NULL)
        return 0;

    PrintInorder(root->left);
    printf(" %s-%d ", root->cityName, root->population);
    PrintInorder(root->right);

    return EXIT_SUCCESS;
}