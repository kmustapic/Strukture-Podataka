#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (50)

struct _person;
typedef struct _person *Position;
typedef struct _person
{
    char FName[MAX_SIZE];
    char LName[MAX_SIZE];
    int birthYear;

    Position next;
} Person;

int Meni();
Position CreatePerson(char *FName, char *LName, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int addFirst(Position head, char *FName, char *LName, int birthYear);
int addLast(Position head, char *FName, char *LName, int birthYear);
int PrintList(Position head);
int main()
{

    Person Head = {.next = NULL, .FName = {0}, .LName = {0}, .birthYear = 0};
    Position p = &Head;
    char FName[MAX_SIZE];
    char LName[MAX_SIZE];
    int BirthYear;
    int izbor;


    while (izbor != '6')
    {
        Meni();
        printf("\nUnesite broj koji zelite:\n");
        scanf("%d", &izbor);

        switch (izbor)
        {
        case 1:
            printf("Vrsi se unos osobe na pocetak liste.");
            printf("\nUnesite ime osobe.\n");
            scanf(" %s", FName);
            printf("\nUnesite prezime osobe.\n");
            scanf(" %s", LName);
            printf("\nUnesite godinu rodenja studenta.\n");
            scanf("%d", &BirthYear);

            addFirst(p, FName, LName, BirthYear);
            printf("\nOsoba uspjesno dodan na pocetak liste.\n");
            break;

        case 2:
            printf("Vrsi se unos osobe na kraj liste.");
            printf("\nUnesite ime osobe.\n");
            scanf(" %s", FName);
            printf("\nUnesite prezime osobe.\n");
            scanf(" %s", LName);
            printf("\nUnesite godinu rodenja studenta.\n");
            scanf("%d", &BirthYear);

            addLast(p, FName, LName, BirthYear);
            printf("\nOsoba uspjesno dodana na kraj liste.\n");
            break;
            
        case 3:
                PrintList(p);
                break;
        }

    }

    return EXIT_SUCCESS;
}

int Meni()
{

    printf("\nIZBORNIK:\n1)Dodaj novi element na pocetak liste\n2)Dodaj novi element na kraj liste\n");
    printf("3)Ispisi listu\n4)Pronadi element u listi(po prezimenu)\n");
    printf("5)Obrisi odredeni lement iz liste\n6)Prekini program\n\n");

    return EXIT_SUCCESS;
}

Position CreatePerson(char *FName, char *LName, int birthYear)
{

    Position newPerson = NULL;
    newPerson = (Position)malloc(sizeof(Person));

    if (!newPerson)
    {
        printf("Greska pri alociranju memorije!");
        return -1;
    }
    strcpy(newPerson->FName, FName);
    strcpy(newPerson->LName, LName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{

    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head)
{

    Position temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    return temp;
}
int addFirst(Position head, char *FName, char *LName, int birthYear)
{

    Position newPerson = NULL;

    newPerson = CreatePerson(FName, LName, birthYear);
    if (!newPerson)
    {
        printf("Greska kod alociranja memorije!");
        return -1;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int addLast(Position head, char *FName, char *LName, int birthYear)
{

    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(FName, LName, birthYear);
    if (!newPerson)
    {
        printf("Greska pri alociranju memorije!");
        return -1;
    }
    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

int PrintList(Position head) {

	Position q = head->next;

	printf("| Ime             || Prezime             || Godina rodenja \n");
	printf("-----------------------------------------------------------\n");
	for (q = head->next; q != NULL; q = q->next) {

		printf("| %-15s || %-19s || %d\n", q->FName, q->LName, q->birthYear);
		
	}

	return EXIT_SUCCESS;
}