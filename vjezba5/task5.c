#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_SIZE (1024)

struct _stacknode;
typedef struct _stacknode *StackNodeP;
typedef struct _stacknode
{
    double number;
    StackNodeP next;
} StackNode;

char *EnterFileName();
int CountPostfix(char *fileName, double *result);
char *ReadFile(char *fileName);
int StringToPostfix(char *buffer, double *result);
int Result(StackNodeP head, double *result);
StackNodeP CreateElement(double number);
int InsertAfter(StackNodeP head, StackNodeP newElement);
int PrintPostfix(StackNodeP head);
int Pop(StackNodeP head, double *result);
int PopAndOperation(StackNodeP head, char operation, double *result);

int main()
{
    char *fileName = NULL;
    double result = 0;

    printf("\t\tPROGRAM ZA RACUNANJE POSTFIKSA IZ DATOTEKE:\n\n");

    fileName = EnterFileName();
    CountPostfix(fileName, &result);
    printf("Rezultat: %lf\n", result);

    return EXIT_SUCCESS;
}

char *EnterFileName(void)
{

    char *str = NULL;
    str = malloc(sizeof(char) * MAX_SIZE);
    printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
    scanf(" %s", str);
    return str;
}

int CountPostfix(char *fileName, double *result)
{

    char *buffer = NULL;
    int status = 0;

    buffer = ReadFile(fileName);
    if (buffer == NULL)
    {
        return EXIT_FAILURE;
    }
    status = StringToPostfix(buffer, result);
    if (status != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

char *ReadFile(char *fileName)
{

    FILE *fp = NULL;
    int length = 0;
    char *buffer = NULL;

    fp = fopen(fileName, "rb");
    if (!fp)
    {
        perror("Can't open file!\n");
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    buffer = (char *)calloc(length + 1, sizeof(char));
    if (!buffer)
    {
        perror("\nMemory cannot be allocated.");
        return NULL;
    }

    rewind(fp);
    fread(buffer, sizeof(char), length, fp);
    printf("|%s|\n", buffer);
    fclose(fp);

    return buffer;
}

int StringToPostfix(char *buffer, double *result)
{
    StackNode head = {.number = 0, .next = NULL};
    char *currentBuffer = buffer;
    char operation = 0;
    double number = 0.0;
    int status = 0, numBytes = 0;
    StackNodeP newElement = NULL;

    while (strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if (status != 1)
        {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = PopAndOperation(&head, operation, result);

            if (status != EXIT_SUCCESS)
            {
                return EXIT_FAILURE;
            }

            number = *result;
        }

        newElement = CreateElement(number);
        if (!newElement)
        {
            return EXIT_FAILURE;
        }

        currentBuffer += numBytes;
        printf("|%s| =>", currentBuffer);

        InsertAfter(&head, newElement); // push na pocetak stack-a
    }

    return Result(&head, result);
}

StackNodeP CreateElement(double number)
{
    StackNodeP newElement = NULL;

    newElement = (StackNodeP)malloc(sizeof(StackNode));
    if (!newElement)
    {
        perror("\nMemory cannot be alocated.");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int Result(StackNodeP head, double *result)
{
    int status = 0;

    status = Pop(head, result);

    if (status != 0)
    {
        return status;
    }
    if (head->next)
    {
        printf("\nThe format of postfix is not correct.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int InsertAfter(StackNodeP head, StackNodeP newElement)
{

    newElement->next = head->next;
    head->next = newElement;

    PrintPostfix(head->next);

    return 0;
}

int PrintPostfix(StackNodeP head)
{
    StackNodeP temp = head;

    while (temp)
    {
        printf(" %lf", temp->number);
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
        perror("\nStack is empty.");
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
    {
        return EXIT_FAILURE;
    }

    status2 = Pop(head, &operand2);
    if (status2 != 0)
    {
        return EXIT_FAILURE;
    }

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
        printf("\nThis operation doesn't exists.", operation);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}