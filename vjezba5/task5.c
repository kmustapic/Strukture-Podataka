/*
5. Napisati program koji iz datoteke cita postfiks izraz
i zatim koristenjem stoga racuna rezultat.
Stog je potrebno realizirati preko vezane liste.
*/

#define _CRT_SECURE_NO_WARNINGS

#define MAX_SIZE (1024)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _stackNode;
typedef struct _stackNode* StackNodeP;
typedef struct _stackNode
{
    double number;
    StackNodeP next;
} StackNode;

int PrintMenu();
int EnterValidString(char* string, char* variableName);
char* EnterFileName();
int CountPostfix(char* fileName, double* result);
char* ReadFile(char* fileName);
int StringToPostfix(char* buffer, double* result);
int Result(StackNodeP head, double* result, int* listExist);
StackNodeP CreateElement(double number);
int InsertAfter(StackNodeP head, StackNodeP newElement);
int PrintPostfix(StackNodeP head);
int Pop(StackNodeP head, double* result);
int PopAndOperation(StackNodeP head, char operation, double* result);
int DeleteList(StackNodeP head, int* listExist);

int main()
{
    char* fileName = NULL;
    double result = 0;
    int choice = -1;
    int listExist = 0;

    while (choice != 0)
    {
        system("cls");
        PrintMenu();
        result = 0;
        listExist = 0;
        printf("Choose an option from menu: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            printf(
                "====================================================================\n"
                "\nYou chose to calculate postfix from certain file.\n");
            fileName = EnterFileName();
            CountPostfix(fileName, &result);
            listExist = 1;
            printf(
                "\n\n\tRESULT: %.2g"
                "\n\nPress enter to continue app execution.\n"
                "====================================================================\n", result);
            system("pause");
            break;

        case 0:
            system("cls");
            printf(
                "====================================================================\n"
                "\nYou have exited the application!\n\n"
                "====================================================================\n");
            if (listExist == 0)
                printf(
                    "List for stack elements is empty!\n"
                    "====================================================================\n\n");
            system("pause");
            break;

        default:
            printf(
                "====================================================================\n"
                "\nYour choice is invalid.\n"
                "Please enter valid number for certain choice.\n"
                "\nPress enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
            break;
        }
    }

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "====================================================================\n"
        "\n\tAPP FOR CALCULATING POSTFIX FROM A .txt FILE\n\n"
        "====================================================================\n"
        "\t\t\t       MENU\n"
        "====================================================================\n"
        "\n\t1  -  Calculate postfix from certain file\n"
        "\t0  -  Exit application\n\n"
        "====================================================================\n");

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
{
    scanf(" %s", string);
    while ((strcmp(string, "") == 0) || fopen(string, "r") == NULL)
    {
        printf(
            "\nYou entered an empty string or file with that name does not exist yet!\n"
            "Please enter new %s: ", variableName);
        scanf(" %s", string);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

char* EnterFileName(void)
{
    char* str = NULL;
    str = malloc(sizeof(char) * MAX_SIZE);
    printf("Please enter name of the file you want to open: ");
    EnterValidString(str, "file name");
    printf("====================================================================\n");

    return str;
}

int CountPostfix(char* fileName, double* result)
{
    char* buffer = NULL;
    int status = 0;

    printf("\n\n");
    buffer = ReadFile(fileName);
    if (buffer == NULL)
        return EXIT_FAILURE;

    status = StringToPostfix(buffer, result);
    if (status != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

char* ReadFile(char* fileName)
{
    FILE* fp = NULL;
    int length = 0;
    char* buffer = NULL;

    fp = fopen(fileName, "rb");
    if (!fp)
    {
        perror("File can't be opened!\n");
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    buffer = (char*)calloc(length + 1, sizeof(char));
    if (!buffer)
    {
        perror("\nMemory cannot be allocated!\n");
        return NULL;
    }

    rewind(fp);
    fread(buffer, sizeof(char), length, fp);
    printf("\t|  %s  |\n", buffer);
    fclose(fp);

    return buffer;
}

int StringToPostfix(char* buffer, double* result)
{
    StackNode head = { .number = 0, .next = NULL };
    char* currentBuffer = buffer;
    char operation = 0;
    double number = 0.0;
    int status = 0, numBytes = 0;
    int listExist = 0;
    StackNodeP newElement = NULL;

    while (strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if (status != 1)
        {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = PopAndOperation(&head, operation, result);

            if (status != EXIT_SUCCESS)
                return EXIT_FAILURE;

            number = *result;
        }
        listExist = 1;
        newElement = CreateElement(number);
        if (!newElement)
            return EXIT_FAILURE;

        currentBuffer += numBytes;
        printf("\t| %s |     =>     ", currentBuffer);

        InsertAfter(&head, newElement); // push to beginning of a stack
    }

    return Result(&head, result, listExist);
}

StackNodeP CreateElement(double number)
{
    StackNodeP newElement = NULL;

    newElement = (StackNodeP)malloc(sizeof(StackNode));
    if (!newElement)
    {
        perror("\nMemory cannot be alocated!\n");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int Result(StackNodeP head, double* result, int* listExist)
{
    int status = 0;
    status = Pop(head, result);

    if (status != 0)
        return status;

    if (head->next)
    {
        printf("\nThe format of postfix is not correct!\n");
        return EXIT_FAILURE;
    }
    //
    DeleteList(head, listExist);

    return EXIT_SUCCESS;
}

int InsertAfter(StackNodeP head, StackNodeP newElement)
{
    newElement->next = head->next;
    head->next = newElement;

    PrintPostfix(head->next);

    return EXIT_SUCCESS;
}

int PrintPostfix(StackNodeP head)
{
    StackNodeP temp = head;

    while (temp)
    {
        printf(" %.2g", temp->number);
        temp = temp->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int Pop(StackNodeP head, double* result)
{
    StackNodeP temp = NULL;

    temp = head->next;
    if (!temp)
    {
        perror("\nStack is currently empty!\n");
        return EXIT_FAILURE;
    }

    head->next = temp->next;
    *result = temp->number;
    free(temp);

    return EXIT_SUCCESS;
}

int PopAndOperation(StackNodeP head, char operation, double* result)
{
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = Pop(head, &operand1);
    if (status1 != 0)
        return EXIT_FAILURE;

    status2 = Pop(head, &operand2);
    if (status2 != 0)
        return EXIT_FAILURE;

    switch (operation)
    {
    case '+':
        *result = operand2 + operand1;
        break;

    case '-':
        *result = operand2 - operand1;
        break;

    case '*':
        *result = operand2 * operand1;
        break;

    case '/':
        *result = operand2 / operand1;
        break;

    default:
        printf("\nThis operation doesn't exist yet!\n", operation);
        break;

    }

    return EXIT_SUCCESS;
}

int DeleteList(StackNodeP head, int* listExist)
{
    StackNodeP temp = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }


    return EXIT_SUCCESS;
}

/*
    FURTHER IMPROVEMENT:
    _____________________________________________________________________________
    * .txt files with different data to check correctness of app execution.

      postfix1.txt -> Result of postfix: 24
      postfix2.txt -> Result of postfix: -4
      postfix3.txt -> Result of postfix: empty stack! Not proper postfix format!
    _____________________________________________________________________________
*/