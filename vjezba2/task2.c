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
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include <unistd.h>
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
    int choice = -1;

    while (choice != 0)
    {
        system("cls");
        PrintMenu();
        printf("Choose an option from menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf (
                "=================================================================\n"
                "You chose to add new student to the beginning of list\n\n"
                "Please enter student's first name: "
            );
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter student's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter student's birth year: ");
            scanf("%d", &birthYear);
            AddFirst(p, firstName, lastName, birthYear);
            printf(
                "\nStudent is succesfully added to the beginning of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n"
            );
            system("pause");
            break;

        case 2:
            printf(
                "=================================================================\n"
                "You chose to add new student to the end of list\n\n"
                "Please enter student's first name: "
            );
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter student's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please eneter student's birth year: ");
            scanf("%d", &birthYear);
            AddLast(p, firstName, lastName, birthYear);
            printf(
                "\nStudent is succesfully added to the end of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n"
            );
            system("pause");
            break;

        case 3:
            printf(
                "=================================================================\n"
                "You chose to search for a student by their last name\n\n"
                "Please enter student's last name: "
            );
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            FindByLastName(p, lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n"
                  );
                system("pause");
            break;

        case 4:
            printf(
                "=================================================================\n"
                "You chose to delete existing student\n\n"
                "Please enter student's last name: "
            );
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            DeleteAfter(p,lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n"
            );
            system("pause");
            break;
        
        case 5:
            printf(
                "=================================================================\n"
                "You chose to print current student list:\n\n"
            );
            PrintList(p);
            printf(
                "\n\nPress enter to continue app execution.\n"
                "=================================================================\n"
            );
            system("pause");
            break;
        }
    }
    system("cls");
    printf(
        "=================================================================\n"
        "\nYou have exited the application!\n\n"
        "=================================================================\n"
    );
    system("pause");

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
           "=================================================================\n"
           "\t\t\tMENU\n"
           "=================================================================\n"
           "    1 - Add new element to the beginning of list\n"
           "    2 - Add new element to the end of list\n"
           "    3 - Find list element (search by last name)\n"
           "    4 - Delete certain list element\n"
           "    5 - Print current list\n"
           "    0 - Exit application\n"
           "=================================================================\n"
          );

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
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
                    "Please enter new %s: ", variableName
        );
        scanf("%s", string);
    }

    return EXIT_SUCCESS;
    }
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
        }
    }
    if (flag == 0)
        printf("\nStudent with searched last name currently doesn't exist in the list!\n");

    return EXIT_SUCCESS;
}

int DeleteAfter(PersonP head, char* lastName)
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
        printf("\nStudent with searched last name doesn't exist in current student list!\n");
    else
        printf("\nStudent is succesfully deleted from student list!\n");

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

/*
    FURTHER IMPROVEMENT:

    * In case when we want to delete certain student (list element), 
      it is not precisely defined how to distinguish which element to delete
      if we have students with same first and last name,
      currently it deletes 1st person found with searched last name
   
   -> possible solutions:
      1) add new int variable 'id' in struct, and earch student we want delete
         by it's unique id.
      
      2) (Probably wasn't intended to work this way)
         To delete all existing students in current list 
         with searched last name.
    _____________________________________________________________________________
    * compiler version issue, warnings for not assigning printf's return value
    
    -> possible solutions:
       1) define these commands:
    
            #define _CRT_SECURE_NO_DEPRECATE  
            #define _CRT_NONSTDC_NO_DEPRECATE
    _____________________________________________________________________________
    * increasing code readability
    
    -> possible solutions:
       1) inside switch case, put each case in it's own function code block 
*/
