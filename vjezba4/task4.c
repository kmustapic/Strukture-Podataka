/*
4. Napisati program za zbrajanje i mnozenje polinoma.
Koeficijenti i eksponenti se citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani.
*/

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE

#define MAX_SIZE (60)
#define CANT_OPEN_FILE_ERROR (-1)
#define EMPTY_LIST (-2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int InsertAfter(PolynomialP head, PolynomialP newPolynomial);
int DeallocateList(PolynomialP head);
int PrintList(PolynomialP head);
int AddPolynomials(PolynomialP head1, PolynomialP head2, PolynomialP headSum);
int MultiplyPolynomials(PolynomialP head1, PolynomialP head2, PolynomialP headProduct);

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
    fileName = EnterFileName();
    flag = ReadFile(p1, p2, fileName);
    while (choice != 0)
    {
        system("cls");
        printf(
            "====================================================================\n"
            " Polynomials from the file: %s\n"
            "====================================================================\n"
            " 1st polynomial:", fileName);
        PrintList(p1);
        printf(" 2nd polynomial:");
        PrintList(p2);
        PrintMenu();
        printf("Choose an option from menu: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 0:
            system("cls");
            printf(
                "====================================================================\n"
                "\nYou have exited the application!\n\n"
                "====================================================================\n");
            DeallocateList(p1);
            DeallocateList(p2);
            DeallocateList(pSum);
            DeallocateList(pProduct);

            if (p1->next == NULL)
                printf("\nList for 1st polynomial is successfully deleted!\n");
            if (p2->next == NULL)
                printf("List for 2nd polynomial is successfully deleted!\n");
            if (pSum->next == NULL)
                printf("List for SUM polynomial is successfully deleted!\n");
            if (pProduct->next == NULL)
                printf(
                    "List for PRODUCT polynomial is successfully deleted!\n\n"
                    "====================================================================\n");
            system("pause");
            break;

        case 1:
            printf(
                "====================================================================\n"
                "\n You chose to ADD polynomials.\n"
                " SUM: ");
            AddPolynomials(p1, p2, pSum);
            PrintList(pSum);
            printf(
                "\n\nPress enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
            break;

        case 2:
            printf(
                "====================================================================\n"
                "\n You chose to MULTIPLY polynomials.\n"
                " PRODUCT: ");
            MultiplyPolynomials(p1, p2, pProduct);
            PrintList(pProduct);
            printf(
                "\n\nPress enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
            break;

        default:
            printf(
                "====================================================================\n"
                "\n Your choice is invalid.\n"
                " Please enter valid number for certain choice.\n"
                "\n Press enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
        }
    }

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "====================================================================\n"
        "\t\tOperations with polynomials\n"
        "====================================================================\n"
        "\t\t1  -  Sum polynomials\n"
        "\t\t2  -  Multiply polynomials\n"
        "\t\t0  -  Exit application\n"
        "====================================================================\n");

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
{
    scanf(" %s", string);
    while ((strcmp(string, "") == 0) || fopen(string, "r") == NULL)
    {
        printf(
            "\n You entered an empty string or file with that name does npt exist yet!\n"
            " Please enter new %s: ", variableName);
        scanf(" %s", string);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

char* EnterFileName()
{
    char* fileName = NULL;
    fileName = malloc(sizeof(char) * 20);
    printf("====================================================================\n");
    printf(" Enter the name of the file with polynomials: ");
    EnterValidString(fileName, "file name");
    printf("====================================================================\n");

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
        perror(" Error! The file cannot open!\n");
        return CANT_OPEN_FILE_ERROR;
    }

    else
    {
        fgets(buffer, MAX_SIZE, fp);
        ReadLine(head1, buffer);
        DeleteResultZero(head1);

        fgets(buffer, MAX_SIZE, fp);
        ReadLine(head2, buffer);
        DeleteResultZero(head2);

        printf(" Polynomials are successfully added from the file: %s!\n"
               "====================================================================\n", fileName);

        fclose(fp);
    }
	
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
        perror(" Error! The memory cannot be allocated!\n");
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

int InsertAfter(PolynomialP head, PolynomialP newPolynomial)
{
    newPolynomial->next = head->next;
    head->next = newPolynomial;

    return EXIT_SUCCESS;
}

int DeallocateList(PolynomialP head)
{
    PolynomialP temp = NULL;

    if (NULL != head->next)
    {
        while (NULL != head->next)
        {
            temp = head->next;
            head->next = temp->next;
            free(temp);
        }

        return EXIT_SUCCESS;
    }

    else
        return EMPTY_LIST;
}

int PrintList(PolynomialP head)
{
    PolynomialP temp = head->next;
    while (temp)
    {
        if (temp->coeff < 0)
            if (temp->exp < 0)
                printf(" (%d)x^(%d)", temp->coeff, temp->exp);
            else
                printf(" (%d)x^%d", temp->coeff, temp->exp);

        else
            if (temp->exp < 0)
                printf(" %dx^(%d)", temp->coeff, temp->exp);
            else
                printf(" %dx^%d", temp->coeff, temp->exp);

        if (NULL != temp->next)
            printf(" +");

        temp = temp->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int AddPolynomials(PolynomialP head1, PolynomialP head2, PolynomialP headSum)
{
    PolynomialP p1 = head1->next;
    PolynomialP p2 = head2->next;
    PolynomialP pSum = headSum;
    PolynomialP temp = NULL;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->exp > p2->exp)
        {
            InsertSorted(pSum, CreatePolynomial(p2->coeff, p2->exp));
            p2 = p2->next;
        }

        else if (p1->exp == p2->exp)
        {
            InsertSorted(pSum, CreatePolynomial(p1->coeff + p2->coeff, p1->exp));
            p1 = p1->next;
            p2 = p2->next;
        }

        else // p1 < p2
        {
            InsertSorted(pSum, CreatePolynomial(p1->coeff, p1->exp));
            p1 = p1->next;
        }
    }

    if (p1 != NULL)
        temp = p1;
    else
        temp = p2;

    while (temp != NULL)
    {
        InsertSorted(pSum, CreatePolynomial(temp->coeff, temp->exp));
        temp = temp->next;
    }
    DeleteResultZero(pSum);

    return EXIT_SUCCESS;
}

int MultiplyPolynomials(PolynomialP head1, PolynomialP head2, PolynomialP headProduct)
{
    PolynomialP p1 = head1->next;
    PolynomialP p2 = head2->next;
    PolynomialP pProduct = headProduct;
    PolynomialP start = head2;

    while (p1 != NULL)
    {
        p2 = start;
        while (p2 != NULL)
        {
            InsertSorted(pProduct, CreatePolynomial(p1->coeff * p2->coeff, p1->exp + p2->exp));
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    DeleteResultZero(pProduct);

    return EXIT_SUCCESS;
}
