/*
7. Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij.Tocnije
program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "source.h"

int main()
{
    CommandLine();
    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "=================================================================\n"
        "\t\tDIRECTORY MANAGEMENT SYSTEM\n"
        "=================================================================\n"
        "\n\t\t________Options available_________\n\t\t|                                |"
        "\n\t\t|        md DIRECTORY_NAME       |"
        "\n\t\t|        cd DIRECTORY_NAME       |"
        "\n\t\t|       cd.. DIRECTORY_NAME      |"
        "\n\t\t|               dir              |"
        "\n\t\t|              exit              |"
        "\n\t\t|________________________________|"
        "\n\n=================================================================\n");

    return EXIT_SUCCESS;
}

int CommandLine()
{
    PrintMenu();
    TreeNode rootDirectory = { .directoryName = NULL, .child = NULL, .nextSibling = NULL };
    TreeNodeP currentDirectory = &rootDirectory;
    StackNode stack = { .treeNode = NULL, .next = NULL };
    int numberOfArguments = 0;
    int offset = 0;
    char* inputBuffer = NULL;
    char* command = NULL;
    char* commandArgument = NULL;
    char* path = NULL;

    if (AllocateBuffers(&path, &inputBuffer, &command, &commandArgument) != EXIT_SUCCESS)
        return EXIT_FAILURE;
    SetDirectoryName(&rootDirectory, "C");
    strcpy(path, "C:\\");

    while (true)
    {
        system("cls");
        PrintMenu();
        memset(inputBuffer, 0, BUFFER_LENGTH);
        memset(command, 0, BUFFER_LENGTH);
        memset(commandArgument, 0, BUFFER_LENGTH);
        numberOfArguments = 0;
        offset = 0;

        printf("%s> ", path);
        fgets(inputBuffer, BUFFER_LENGTH, stdin);

        numberOfArguments = sscanf(inputBuffer, " %s %s %n", command, commandArgument, &offset);
        if (strcmp(command, "md") == 0)
        {
            if (numberOfArguments == 1)
            {
                printf("The syntax of the command is incorrect!\n");
                system("pause");
                printf("\nPress enter to continue app execution.\n");
            }

            else
            {
                MakeNewDirectory(currentDirectory, commandArgument);
                while (true)
                {
                    int n = 0;
                    numberOfArguments = sscanf((inputBuffer + offset), "%s %n", commandArgument, &n);
                    if (numberOfArguments < 0)
                        break;
                    offset += n;
                    MakeNewDirectory(currentDirectory, commandArgument);
                }
            }
        }

        else if (strcmp(command, "cd..") == 0)
        {
            if (currentDirectory == &rootDirectory)
                continue;
            ReturnToPreviousDirectory(&currentDirectory, &rootDirectory, path, &stack);
        }

        else if (strcmp(command, "cd") == 0)
        {
            if (strcmp(commandArgument, "..") == 0)
            {
                if (currentDirectory == &rootDirectory)
                    continue;
                ReturnToPreviousDirectory(&currentDirectory, &rootDirectory, path, &stack);
            }

            else if (numberOfArguments == 1)
                printf("%s\n\n", path);

            else
                ChangeDirectory(&currentDirectory, commandArgument, path, &stack);
        }

        else if (strcmp(command, "dir") == 0)
        {
            PrintDirectory(currentDirectory);
            system("pause");
            printf("Press enter to continue app execution.\n");
        }

        else if (strcmp(command, "exit") == 0)
        {
            free(rootDirectory.directoryName);
            FreeAllMemory(path, inputBuffer, command, commandArgument, &rootDirectory, &stack);
            system("cls");
            printf(
                "====================================================================\n"
                "\nYou have exited the application!\n\n"
                "====================================================================\n"
                "\nAllocated memory is emptied!\n"
                "\n====================================================================\n\n");
            system("pause");

            return EXIT_SUCCESS;
        }

        else
        {
            printf("\n %s is not recognized as an internal or external command, operable program or batch file!\n", command);
            system("pause");
            printf("\nPress enter to continue app execution.\n");
        }
    }

    return EXIT_SUCCESS;
}

TreeNodeP CreateNewTreeNode()
{
    TreeNodeP newNode = NULL;
    newNode = (TreeNodeP)malloc(sizeof(TreeNode));
    if (NULL == newNode)
    {
        printf("Tree node memory allocation failed!\n");
        system("pause");
        printf("\nPress enter to continue app execution.\n");

        return NULL;
    }
    newNode->child = NULL;
    newNode->nextSibling = NULL;
    newNode->directoryName = NULL;

    return newNode;
}

StackNodeP CreateNewStackNode()
{
    StackNodeP newNode = NULL;
    newNode = (StackNodeP)malloc(sizeof(StackNode));
    if (NULL == newNode)
    {
        printf("Stack node memory allocation failed!\n");
        system("pause");
        printf("\nPress enter to continue app execution.\n");

        return NULL;
    }
    newNode->treeNode = NULL;
    newNode->next = NULL;

    return newNode;
}

int Push(StackNodeP stackHead, TreeNodeP treeNode)
{
    StackNodeP nodeToPush = NULL;
    nodeToPush = CreateNewStackNode();
    if (NULL == nodeToPush)
        return EXIT_FAILURE;

    nodeToPush->treeNode = treeNode;
    nodeToPush->next = stackHead->next;
    stackHead->next = nodeToPush;

    return EXIT_SUCCESS;
}

int Pop(StackNodeP stackHead, TreeNodeP* result)
{
    StackNodeP nodeToFree = NULL;
    if (NULL == stackHead->next)
        return EXIT_FAILURE;

    *result = stackHead->next->treeNode;
    nodeToFree = stackHead->next;
    stackHead->next = stackHead->next->next;
    free(nodeToFree);

    return EXIT_SUCCESS;
}

int AllocateBuffers(char** path, char** inputBuffer, char** command, char** commandArgument)
{
    *path = (char*)malloc(BUFFER_LENGTH * sizeof(char));
    *inputBuffer = (char*)malloc(BUFFER_LENGTH * sizeof(char));
    *command = (char*)malloc(BUFFER_LENGTH * sizeof(char));
    *commandArgument = (char*)malloc(BUFFER_LENGTH * sizeof(char));

    return EXIT_SUCCESS;
}

int SetDirectoryName(TreeNodeP directory, char* directoryName)
{
    directory->directoryName = (char*)malloc((strlen(directoryName) + 1) * sizeof(char));
    if (NULL == directory->directoryName)
    {
        printf("Error in setting directory name!\n");
        system("pause");
        printf("\nPress enter to continue app execution.\n");

        return EXIT_FAILURE;
    }
    strcpy(directory->directoryName, directoryName);

    return EXIT_SUCCESS;
}

int MakeNewDirectory(TreeNodeP currentDirectory, char* newDirectoryName)
{
    TreeNodeP newDirectory = NULL;
    TreeNodeP* temp = NULL;
    if (FindDirectory(currentDirectory, newDirectoryName) != NULL)
    {
        printf("\nA subdirectory %s already exists!\n\n", newDirectoryName);
        system("pause");
        printf("Press enter to continue app execution.\n");

        return EXIT_FAILURE;
    }

    newDirectory = CreateNewTreeNode();
    if (NULL == newDirectory)
        return EXIT_FAILURE;

    if (SetDirectoryName(newDirectory, newDirectoryName) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (NULL == currentDirectory->child)
    {
        currentDirectory->child = newDirectory;
        return EXIT_SUCCESS;
    }

    temp = &currentDirectory->child;
    while (*temp != NULL && strcmp((*temp)->directoryName, newDirectoryName) < 0)
        temp = &(*temp)->nextSibling;

    newDirectory->nextSibling = *temp;
    *temp = newDirectory;

    return EXIT_SUCCESS;
}

TreeNodeP FindDirectory(TreeNodeP currentDirectory, char* directoryName)
{
    TreeNodeP temp = NULL;
    temp = currentDirectory->child;
    while (temp)
    {
        if (strcmp(temp->directoryName, directoryName) == 0)
            return temp;

        temp = temp->nextSibling;
    }

    return temp;
}

int ReturnToPreviousDirectory(TreeNodeP* currentDirectory, TreeNodeP rootDirectory, char* path, StackNodeP stackHead)
{
    char* endOfPath = NULL;
    TreeNodeP dummy = NULL;
    TreeNodeP newCurrentDirectory = NULL;

    Pop(stackHead, &dummy);
    if (Pop(stackHead, &newCurrentDirectory) == EXIT_FAILURE)
    {
        *currentDirectory = rootDirectory;
        strcpy(path, rootDirectory->directoryName);
        strcat(path, "\\");

        return EXIT_SUCCESS;
    }
    *currentDirectory = newCurrentDirectory;
    endOfPath = strrchr(path, '\\');
    *endOfPath = '\0';

    return EXIT_SUCCESS;
}

int ChangeDirectory(TreeNodeP* currentDirectory, char* directoryName, char* path, StackNodeP stackHead)
{
    TreeNodeP temp = NULL;
    temp = FindDirectory(*currentDirectory, directoryName);
    if (NULL == temp)
    {
        printf("\nThe system cannot find the path specified!\n\n");
        system("pause");
        printf("\nPress enter to continue app execution.\n");

        return EXIT_FAILURE;
    }
    if (Push(stackHead, temp) == EXIT_FAILURE)
        return EXIT_FAILURE;

    *currentDirectory = temp;
    if (path[strlen(path) - 1] != '\\')
        strcat(path, "\\");

    strcat(path, directoryName);

    return EXIT_SUCCESS;
}

int PrintDirectory(TreeNodeP currentDirectory)
{
    char* directoryName = currentDirectory->directoryName;
    currentDirectory = currentDirectory->child;
    int numDir = 0;

    if (NULL == currentDirectory)
    {
        printf("\n\t0 Dir(s)\n\n");
        return EXIT_FAILURE;
    }

    printf("\n");
    while (NULL != currentDirectory)
    {
        printf("\t<DIR>\t\t%s\n", currentDirectory->directoryName);
        numDir++;
        currentDirectory = currentDirectory->nextSibling;
    }
    printf(
        "\n\t%d Dir(s)\n\n"
        "=================================================================\n"
        "List of all existing directories"
        "\nin directory '%s' is successfully printed!\n"
        "=================================================================\n", numDir, directoryName);
    system("pause");
    printf("\nPress enter to continue app execution.\n");

    return EXIT_SUCCESS;
}

int FreeBuffers(char* path, char* inputBuffer, char* command, char* commandArgument)
{
    free(path);
    free(inputBuffer);
    free(command);
    free(commandArgument);

    return EXIT_SUCCESS;
}

int FreeTree(TreeNodeP T)
{
    if (NULL == T)
        return EXIT_SUCCESS;

    FreeTree(T->child);
    FreeTree(T->nextSibling);
    free(T->directoryName);
    free(T);

    return EXIT_SUCCESS;
}

int FreeStack(StackNodeP S)
{
    if (NULL == S)
        return EXIT_SUCCESS;

    FreeStack(S->next);
    free(S);

    return EXIT_SUCCESS;
}

int FreeAllMemory(char* path, char* inputBuffer, char* command, char* commandArgument, TreeNodeP root, StackNodeP stackHead)
{
    FreeBuffers(path, inputBuffer, command, commandArgument);
    FreeStack(stackHead->next);
    FreeTree(root->child);

    return EXIT_SUCCESS;
}
