/*
2. Definirati strukturu osoba(ime, prezime, godina rodenja) i napisati program koji :
    A.  dinamicki dodaje novi element na pocetak liste,
    B.  ispisuje listu,
    C.  dinamicki dodaje novi element na kraj liste,
    D.  pronalazi element u listi(po prezimenu),
    E.  brise odredeni element iz liste,

   U zadatku se ne smiju koristiti globalne varijable.
*/

#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (50)

struct _person;
typedef struct _person* PersonP;
typedef struct _person
{
    char firstName[MAX_SIZE];
    char lastName[MAX_SIZE];
    int birthYear;
    PersonP next;
} Person;

int PrintMenu();
int EnterValidString(char* string, char* variableName);
int AddFirst(PersonP head, char* firstName, char* lastName, int birthYear);
PersonP CreatePerson(char* firstName, char* lastName, int birthYear);
int InsertAfter(PersonP position, PersonP newPerson);
int AddLast(PersonP head, char* firstName, char* lastName, int birthYear);
PersonP FindLast(PersonP head);
int FindByLastName(PersonP first, char* lastName);
int DeleteAfter(PersonP head, char* lastName);
int PrintList(PersonP head);

int main()
{
    Person Head = { .next = NULL, .firstName = {0}, .lastName = {0}, .birthYear = 0 };
    PersonP p = &Head;
    char firstName[MAX_SIZE] = { 0 };
    char lastName[MAX_SIZE] = { 0 };
    int birthYear = 0;
    int choice = 0;

    while (choice != 7)
    {
        printf("\nChoose an option from menu:\n");
        PrintMenu();
 
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf (
                "=================================================================\n"
                "You chose to add new student to the beginning of list\n"
                "Please enter student's first name: "
            );
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("\nPlease enter student's last name: \n");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("\nPlease eneter student's birth year: \n");
            scanf("%d", &birthYear);
            AddFirst(p, firstName, lastName, birthYear);
            printf(
                "\nStudent is succesfully added to the beginning of list!\n"
                "=================================================================\n"
                  );
            break;

        case 2:
            printf(
                "=================================================================\n"
                "You chose to add new student to the end of list\n"
                "Please enter student's first name: "
            );
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("\nPlease enter student's last name: \n");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("\nPlease eneter student's birth year: \n");
            scanf("%d", &birthYear);
            AddLast(p, firstName, lastName, birthYear);
            printf(
                "\nStudent is succesfully added to the end of list!\n"
                "=================================================================\n"
            );
            break;

        case 3:
            printf(
                "=================================================================\n"
                "You chose to search for a student by their last name\n"
                "Please enter student's last name: "
            );
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            FindByLastName(p, lastName);
            printf("=================================================================\n");
            break;

        case 4:
            printf(
                "=================================================================\n"
                "You chose to delete existing student\n"
                "Please enter student's last name: "
            );
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            DeleteAfter(p,lastName);
            break;
        
        case 5:
            printf(
                "=================================================================\n"
                "You chose to print current student list:\n\n"
            );
            PrintList(p);
            break;

        case 0:
            printf(
                "=================================================================\n"
                "\n\nYou have exited the application!\n\n"
                "=================================================================\n"
            );
            return EXIT_SUCCESS;
        }

    }

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
           "=================================================================\n"
           "\nMENU:\n"
           "=================================================================\n"
           "    1 - Add new element to the beginning of list\n"
           "    2 - Add new element to the end of list\n"
           "    3 - Find list element (search by last name)\n"
           "    4 - Delete certain list element\n"
           "    5 - Print current list\n"
           "    0 - Exit application\n\n"
           "=================================================================\n"
          );

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
{
    scanf("%s", string);
    while (strcmp(string, "") == 0)
    {
        printf(
            "You entered an empty string!\n"
            "Please enter new %s: ", variableName
        );
        scanf("%s", string);
    }

    return EXIT_SUCCESS;
}

int AddFirst(PersonP head, char* firstName, char* lastName, int birthYear)
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

PersonP CreatePerson(char* firstName, char* lastName, int birthYear)
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

int AddLast(PersonP head, char* firstName, char* lastName, int birthYear)
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

int FindByLastName(PersonP first, char* lastName)
{
    int flag = 0;
    PersonP temp = NULL;
    for (temp = first->next; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->lastName, lastName) == 0)
        {
            flag++;
            if(flag == 1)
            printf("\nStudent/s with searched last name is/are:\n");

            printf("FIRST NAME: %s, LAST NAME: %s, BIRTH YEAR: %d\n", temp->firstName, temp->lastName, temp->birthYear);
  //**********system("pause > nul");
  //break;
        }
        if (flag == 0)
            printf("Student with searched last name currently doesn't exist in the list!\n");
    }

    return EXIT_SUCCESS;
}

int DeleteAfter(PersonP head, char* lastName)
{
    PersonP prev = NULL;
    PersonP current = NULL;

    for (prev = head; prev->next != NULL; prev = prev->next)
    {
        if (strcmp(prev->next->lastName, lastName) == 0)
        {
            current = prev->next;
            prev->next = prev->next->next;
            free(current);
            break;
        }
    }

    return EXIT_SUCCESS;
}

int PrintList(PersonP head) 
{
    PersonP q = head->next;
    printf("| First name             || Last name             || Birth year \n");
    printf("-----------------------------------------------------------\n");
    for (q = head->next; q != NULL; q = q->next) 
        printf("| %-15s || %-19s || %d\n", q->firstName, q->lastName, q->birthYear);

    return EXIT_SUCCESS;
}
