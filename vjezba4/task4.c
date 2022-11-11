/*
4. Napisati program za zbrajanje i mnozenje polinoma. 
Koeficijenti i eksponenti se citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani.
*/

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_SIZE (60)
#define CANT_OPEN_FILE_ERROR (-1)
#define EMPTY_LIST (-2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct _polynomial;
typedef struct _polynomial* PolynomialP;
typedef struct _polynomial
{
    int coeff;
    int exp;
    PolynomialP next;
} Polynomial;

int EnterValidString(char* string, char* variableName);
int PrintMenu();
char* EnterFileName();
int ReadFile(PolynomialP head1, PolynomialP head2, char* fileName);
int ReadLine(PolynomialP head, char* buffer);
PolynomialP CreatePolynomial(int coeff, int exp);
int InsertSorted(PolynomialP head, PolynomialP newPolynomial);
int DeleteResultZero(PolynomialP head);
int InsertAfter(PolynomialP position, PolynomialP newPolynomial);
int PrintList(PolynomialP head);

//****************************








int main()
{
    Polynomial head1 = { .exp = 0, .coeff = 0, .next = NULL };
    Polynomial head2 = { .exp = 0, .coeff = 0, .next = NULL };
    Polynomial headSum = { .exp = 0, .coeff = 0, .next = NULL };
    Polynomial headProduct = { .exp = 0, .coeff = 0, .next = NULL };
    PolynomialP p1 = &head1;
    PolynomialP p2 = &head2;
    PolynomialP pSum = &headSum;
    PolynomialP pProduct = &headProduct;

    char* fileName = NULL;
    int choice = -1;
    int flag = 0;
    while (choice != 0)
    {
        system("cls");
        PrintMenu();
        fileName = EnterFileName();
        //while(fileName == NULL)
        flag = ReadFile(p1, p2, fileName);



        if (flag == EXIT_SUCCESS)
            printf("\nList has been sucesfully read from the file : %s\n\n", fileName);


        printf("\nPress enter to continue app execution.\n"
            "=================================================================\n");

        /*
        printf("Please eneter file name: ");
        fileName = EnterFileName();

        ReadFile(p1, p2, fileName);


        printf("Choose an option from menu: ");
        scanf(" %d", &choice);
        */

//system("color F");

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
        flag++;
    }

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "=================================================================\n"
        "\tOperations with polynomials\n"
        "=================================================================\n"
        "    1  -  Sum polynomials\n"
        "    2  -  Multiply polynomials\n"
        "    0  -  Exit application\n"
        "=================================================================\n");

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
{
    if (strcmp(string, "") != 0)
        return EXIT_SUCCESS;
    else
    {
        scanf(" %s", string);
        while (strcmp(string, "") == 0)
        {
            printf(
                "You entered an empty string!\n"
                "Please enter new %s: ",
                variableName);
            scanf(" %s", string);
        }

        return EXIT_SUCCESS;
    }
}

char* EnterFileName()
{
    char* fileName = NULL;
    fileName = malloc(sizeof(char) * 20);
    printf("\nEnter the name of the file with polynomials: \n\t");
    scanf(" %s", fileName);
    EnterValidString(fileName, "file name");

    return fileName;
}

int ReadFile(PolynomialP head1, PolynomialP head2, char* fileName)
{
    int coeff = 0;
    int exp = 0;
    char buffer[MAX_SIZE] = { 0 };
    FILE* fp = NULL;
    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        perror("Error! The file cannot open!\n");
        return CANT_OPEN_FILE_ERROR;
    }

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(head1, buffer);
    DeleteNull(head1);

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(head2, buffer);
    DeleteNull(head2);

    printf("Polynomials are successfully added from the file: %s!\n\n", fileName);

    fclose(fp);

    return EXIT_SUCCESS;
}

int ReadLine(PolynomialP head, char* buffer)
{
    int coeff = 0;
    int exp = 0;
    char* p = NULL;   
    int status = 0; 
    int n = 0;        
    PolynomialP newPoly = NULL;

    p = buffer;
    while (strlen(p) > 0) 
    {
        status = sscanf(p, " %d %d %n", &coeff, &exp, &n);
        if (status == 2 && coeff != 0)
        { 
            newPoly = CreatePolynomial(coeff, exp);
            InsertSorted(head, newPoly);
        }
        p += n;
    }
    return EXIT_SUCCESS;
}

PolynomialP CreatePolynomial(int coeff, int exp)
{
    PolynomialP newPoly = NULL;
    newPoly = (PolynomialP)malloc(sizeof(Polynomial));
    if (!newPoly)
    {
        perror("Error! The memory cannot be allocated!\n");
        return NULL;
    }

    newPoly->coeff = coeff;
    newPoly->exp = exp;
    newPoly->next = NULL;

    return newPoly;
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
        current->next->coeff += added->coeff;
        result = current->coeff;

        if (result == 0)
            DeleteResultZero(current); 
    }
    else
    {
        CreatePolynomial(added->coeff, added->exp);
        InsertAfter(current, added);
    }
    return EXIT_SUCCESS;
}

int DeleteResultZero(PolynomialP head)
{
    PolynomialP prev = head;
    PolynomialP temp = NULL;

    while (prev->next != NULL)
    {
        if (prev->next->coeff == 0)
        {
            temp = prev->next;
            prev->next = temp->next;
            free(temp);
        }
        else
            prev = prev->next;
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
        return EMPTY_LIST; // neuspjesno ako je lista npr. prazna
}

int PrintList(PolynomialP head)
{
    PolynomialP temp = NULL;
    while (temp)
    {
        printf("\t%dx^(%d)\n", temp->coeff, temp->exp);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}
//*******************
