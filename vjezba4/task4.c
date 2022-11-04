#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (60)

struct _polynomial;
typedef struct _polynomial *PolynomialP;
typedef struct _polynomial
{

    int exp;
    int coef;
    PolynomialP next;
} Polynomial;

char *EnterFileName();
int ReadFile(PolynomialP head1, PolynomialP head2, char *fileName);
int ReadLine(PolynomialP head, char *buffer);
PolynomialP CreatePolynomial(int coef, int exp);
int InsertSorted(PolynomialP head, PolynomialP newPolynomial);
int DeleteNull(PolynomialP head);
int InsertAfter(PolynomialP position, PolynomialP newPolynomial);
int PrintList(PolynomialP head);

int main()
{

    Polynomial Head1 = {.exp = 0, .coef = 0, .next = NULL};
    Polynomial Head2 = {.exp = 0, .coef = 0, .next = NULL};
    Polynomial HeadS = {.exp = 0, .coef = 0, .next = NULL};
    Polynomial HeadP = {.exp = 0, .coef = 0, .next = NULL};

    PolynomialP p1 = &Head1;
    PolynomialP p2 = &Head2;
    PolynomialP pS = &HeadS;
    PolynomialP pP = &HeadP;

    char *fileName = NULL;
    int choice = 1;

    while (choice != 0)
    {

        system("cls");
        printf("Choose the operation for polynomials:\n\n");
        system("color F");
        printf("\t[1] - Add polynomials\n");
        printf("\t[2] - Multiply polynomials\n");
        printf("\t[0] - Exit the program\n");
        printf("\nYour choice:\n\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            system("color C");
            break;
        case 1:
            fileName = EnterFileName();
            ReadFile(p1, p2, fileName);
            printf("\nPolynomial 1:\n");
            PrintList(p1);
            printf("\nPolynomial 2:\n");
            PrintList(p2);
        }
    }

    return EXIT_SUCCESS;
}

char *EnterFileName()
{

    char *fileName = NULL;
    fileName = malloc(sizeof(char) * MAX_SIZE);
    printf("\nEnter the name of the file with polynomials:\n\t");
    scanf(" %s", fileName);
    return fileName;
}

int ReadFile(PolynomialP head1, PolynomialP head2, char *fileName)
{
    int coef = 0;
    int exp = 0;
    char buffer[MAX_SIZE] = {0};

    FILE *file = NULL;
    file = fopen(fileName, "r");

    if (file == NULL)
    {
        perror("Error!The file cannot open\n");
        return -1;
    }

    fgets(buffer, MAX_SIZE, file);
    ReadLine(head1, buffer);
    DeleteNull(head1);

    fgets(buffer, MAX_SIZE, file);
    ReadLine(head2, buffer);
    DeleteNull(head2);

    printf("Polynomials succesfully added from the file: %s\n\n", fileName);

    fclose(file);

    return EXIT_SUCCESS;
}

int ReadLine(PolynomialP head, char *buffer)
{
    int coef = 0;
    int exp = 0;
    char *p = NULL;   // pokazivac na liniju
    int readLine = 0; // vrijednost sscanf
    int n = 0;        // broj znakova
    PolynomialP newPol = NULL;

    p = buffer;
    while (strlen(p) > 0) // dok pokazivac ne stigne do kraja
    {
        readLine = sscanf(p, " %d %d %n", &coef, &exp, &n);
        if (readLine == 2 && coef != 0)
        { // ako su ucitana dva integera s koef razlicitim od 0
            newPol = CreatePolynomial(coef, exp);
            InsertSorted(head, newPol);
        }
        p += n;
    }
    return EXIT_SUCCESS;
}

PolynomialP CreatePolynomial(int coef, int exp)
{
    PolynomialP newPol = NULL;

    newPol = (PolynomialP)malloc(sizeof(Polynomial));

    if (!newPol)
    {
        perror("ERROR!The memory cannot be allocated!");
        return -1;
    }

    newPol->coef = coef;
    newPol->exp = exp;
    newPol->next = NULL;

    return EXIT_SUCCESS;
}

int InsertSorted(PolynomialP head, PolynomialP newPolynomial)
{

    PolynomialP current = head;
    PolynomialP added = newPolynomial;
    int result = 0;

    while (current->next != NULL && current->next->exp > added->exp)
        current = current->next;
    if (current->next != NULL && current->next->exp == added->exp)
    {
        current->next->coef += added->coef;
        result = current->coef;

        if (result == 0)
            DeleteNull(current); // ako je zbroj istih koef 0,izbrisi clan
    }
    else
    {
        CreatePolynomial(added->coef, added->exp);
        InsertAfter(current, added);
    }
    return EXIT_SUCCESS;
}

int DeleteNull(PolynomialP head)
{
    PolynomialP previous = head;
    PolynomialP temp = NULL;

    while (previous->next != NULL)
    {
        if (previous->next->coef == 0)
        {
            temp = previous->next;
            previous->next = temp->next;
            free(temp);
        }
        else
            previous = previous->next;
    }

    return EXIT_SUCCESS;
}

int InsertAfter(PolynomialP position, PolynomialP newPolynomial)
{
    newPolynomial->next = position->next;
    position->next = newPolynomial;

    return EXIT_SUCCESS;
}

int DeallocateList(PolynomialP head)
{
    PolynomialP current = head;
    PolynomialP temp = NULL;

    if (NULL != current->next)
    {
        while (NULL != current->next)
        {
            temp = current->next;
            current->next = temp->next;
            free(temp);
        }

        return EXIT_SUCCESS; // uspjesno ukoliko lista postoji i prode petlju
    }
    else
        return EXIT_FAILURE; // neuspjesno ako je lista npr. prazna
}

int PrintList(PolynomialP head)
{
    PolynomialP temp = NULL;

    while (temp)
    {
        printf("\t%dx^(%d)\n", temp->coef, temp->exp);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}