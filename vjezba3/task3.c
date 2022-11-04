#define CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_SIZE (50)

struct _person;
typedef struct _person *PersonP;
typedef struct _person
{
    char firstName[MAX_SIZE];
    char lastName[MAX_SIZE];
    int birthYear;
    PersonP next;
} Person;

int PrintMenu();
int EnterValidString(char *string, char *variableName);
int AddFirst(PersonP head, char *firstName, char *lastName, int birthYear);
PersonP CreatePerson(char *firstName, char *lastName, int birthYear);
int InsertAfter(PersonP position, PersonP newPerson);
int AddLast(PersonP head, char *firstName, char *lastName, int birthYear);
PersonP FindLast(PersonP head);
int FindByLastName(PersonP first, char *lastName);
int DeleteAfter(PersonP head, char *lastName);
int PrintList(PersonP head);

int InsertAfterCertainEl(PersonP head, PersonP newPerson, char *findLastName);
int InsertBeforeCertainEl(PersonP head, PersonP newPerson, char *findLastName);
int SortList(PersonP head);
int WriteInFile(PersonP head, char *fileName);
char *EnterFileName();

int main()
{
    Person Head = {.next = NULL, .firstName = {0}, .lastName = {0}, .birthYear = 0};
    PersonP p = &Head;
    char firstName[MAX_SIZE] = {0};
    char lastName[MAX_SIZE] = {0};
    char searchLastName[MAX_SIZE] = {0};
    int birthYear = 0;
    int choice = -1;
    PersonP newPerson = NULL;
    char *fileName = NULL;

    while (choice != 0)
    {
        system("cls");
        PrintMenu();
        printf("Choose an option from menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf(
                "=================================================================\n"
                "You chose to add new person to the beginning of list\n\n");

            printf("Please enter person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter person's birth year: ");
            scanf("%d", &birthYear);

            AddFirst(p, firstName, lastName, birthYear);
            printf(
                "\nperson is succesfully added to the beginning of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 2:
            printf(
                "=================================================================\n"
                "You chose to add new person to the end of list\n\n");

            printf("Please enter person's first name:");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please eneter person's birth year: ");
            scanf("%d", &birthYear);

            AddLast(p, firstName, lastName, birthYear);
            printf(
                "\nPerson is succesfully added to the end of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 3:
            printf(
                "=================================================================\n"
                "You chose to search for a person by their last name\n\n"
                "Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            FindByLastName(p, lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 4:
            printf(
                "=================================================================\n"
                "You chose to delete existing person\n\n"
                "Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            DeleteAfter(p, lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 5:
            printf(
                "=================================================================\n"
                "You chose to print current person list:\n\n");
            PrintList(p);
            printf(
                "\n\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 6:
            printf(
                "=================================================================\n"
                "You chose to insert new person after certain person (by surname):\n\n");

            printf("Enter last name of person in the list, after who you want to add new person:");
            scanf(" %s", searchLastName);
            EnterValidString(searchLastName, "searched last name");

            printf("Please enter new person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter new person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter new person's birth year: ");
            scanf("%d", &birthYear);
            newPerson = CreatePerson(firstName, lastName, birthYear);
            InsertAfterCertainEl(p, newPerson, searchLastName);

            printf(
                "\nPerson is succesfully added after certain person in the list!\n\n"
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 7:
            printf(
                "=================================================================\n"
                "You chose to insert new person before certain person (by surname):\n\n"
                "Enter last name of person in the list, before who you want to add new person:\n");
            scanf(" %s", searchLastName);
            EnterValidString(searchLastName, "searched last name");

            printf("Please enter new person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter new person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter new person's birth year: ");
            scanf("%d", &birthYear);
            newPerson = CreatePerson(firstName, lastName, birthYear);

            system("pause");
            break;
        case 8:
            printf(
                "=================================================================\n"
                "You chose to sort the list of people(by surname):\n\n");
            SortList(p);
            printf(
                "\nList has been sucesfully sorted!\n\n"
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 9:
            printf(
                "=================================================================\n"
                "You chose to insert the list of people in the file:\n\n");
            fileName = EnterFileName();
            WriteInFile(p, fileName);
            printf(
                "\nList has been sucesfully added to the file : %s\n\n", fileName);
            printf("\nPress enter to continue app execution.\n"
                   "=================================================================\n");
            system("pause");
            break;
        }
    }
    system("cls");
    printf(
        "=================================================================\n"
        "\nYou have exited the application!\n\n"
        "=================================================================\n");
    system("pause");

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "=================================================================\n"
        "\t\t\tMENU\n"
        "=================================================================\n"
        "    1 - Add new person to the beginning of list\n"
        "    2 - Add new person to the end of list\n"
        "    3 - Find list person (search by last name)\n"
        "    4 - Delete certain person\n"
        "    5 - Print current person list\n"
        "    6 - Inset new person after certain person (by surname)\n"
        "    7 - Insert new person before certain person(by surname)\n"
        "    8 - Sort the list of people (by surname)\n"
        "    9 - Insert the list in the file\n"
        "    10 -Read the list from the file\n "
        "    0 - Exit application\n"
        "=================================================================\n");

    return EXIT_SUCCESS;
}

int EnterValidString(char *string, char *variableName)
{
    if (strcmp(string, "") != 0)
        return EXIT_SUCCESS;
    else
    {
        scanf("%s", string);
        while (strcmp(string, "") == 0)
        {
            printf(
                "You entered an empty string!\n"
                "Please enter new %s: ",
                variableName);
            scanf("%s", string);
        }

        return EXIT_SUCCESS;
    }
}

int AddFirst(PersonP head, char *firstName, char *lastName, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = CreatePerson(firstName, lastName, birthYear);
    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return EXIT_FAILURE;
    }
    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

PersonP CreatePerson(char *firstName, char *lastName, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));

    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return NULL;
    }
    strcpy(newPerson->firstName, firstName);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(PersonP position, PersonP newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

int AddLast(PersonP head, char *firstName, char *lastName, int birthYear)
{
    PersonP newPerson = NULL;
    PersonP last = NULL;
    newPerson = CreatePerson(firstName, lastName, birthYear);
    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return EXIT_FAILURE;
    }
    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

PersonP FindLast(PersonP head)
{
    PersonP temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    return temp;
}

int FindByLastName(PersonP first, char *lastName)
{
    int flag = 0;
    PersonP temp = NULL;
    for (temp = first->next; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->lastName, lastName) == 0)
        {
            flag++;
            if (flag == 1)
                printf("\nperson/s with searched last name is/are:\n");

            printf("FIRST NAME: %s, LAST NAME: %s, BIRTH YEAR: %d\n", temp->firstName, temp->lastName, temp->birthYear);
        }
    }
    if (flag == 0)
        printf("\nperson with searched last name currently doesn't exist in the list!\n");

    return EXIT_SUCCESS;
}

int DeleteAfter(PersonP head, char *lastName)
{
    int flag = 0;
    PersonP prev = NULL;
    PersonP current = NULL;

    for (prev = head; prev->next != NULL; prev = prev->next)
    {
        if (strcmp(prev->next->lastName, lastName) == 0)
        {
            flag++;
            current = prev->next;
            prev->next = prev->next->next;
            free(current);
            break;
        }
    }

    if (flag == 0)
        printf("\nperson with searched last name doesn't exist in current person list!\n");
    else
        printf("\nperson is succesfully deleted from person list!\n");

    return EXIT_SUCCESS;
}

int PrintList(PersonP head)
{
    PersonP q = head->next;
    printf("| First name          || Last name          || Birth year \n");
    printf("-----------------------------------------------------------\n");
    for (q = head->next; q != NULL; q = q->next)
        printf("| %-20s || %-20s || %d\n", q->firstName, q->lastName, q->birthYear);

    return EXIT_SUCCESS;
}

int InsertAfterCertainEl(PersonP head, PersonP newPerson, char *findLastName)
{
    PersonP temp = NULL;
    temp = head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->lastName, findLastName) == 0)
        {
            InsertAfter(temp, newPerson);
        }
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int InsertBeforeCertainEl(PersonP head, PersonP newPerson, char *findLastName)
{
    PersonP prev = NULL;
    PersonP temp = NULL;
    temp = head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->lastName, findLastName) == 0)
        {
            InsertAfter(temp, newPerson);
        }
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int SortList(PersonP p)
{
    PersonP a = NULL, b = NULL, prev = NULL, end = NULL;
    for (a = p; a->next != end;)
    {
        prev = a;
        for (b = a->next; b->next != end; b = b->next)
        {
            if (strcmp(b->lastName, b->next->lastName) > 0)
            {
                PersonP pom = b->next;
                prev->next = pom;
                b->next = pom->next;
                pom->next = b;
                b = pom;
            }
            prev = b;
        }
        end = b;
    }
}

char *EnterFileName()
{
    char *fileName = NULL;
    fileName = malloc(sizeof(char) * 20);
    printf("\nInsert the name of the file you want to add the list to:\n");
    scanf(" %s", fileName);
    return fileName;
}

int WriteInFile(PersonP head, char *fileName)
{

    FILE *file = NULL;
    file = fopen(fileName, "w");

    PersonP temp = head->next;

    if (NULL == file)
    {
        printf("Unable to open file.");
        return -1;
    }

    while (temp)
    {
        fprintf(file, "NAME: %s, SURNAME: %s, BIRTHYEAR: %d\n", temp->firstName, temp->lastName, temp->birthYear);
        temp = temp->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}
