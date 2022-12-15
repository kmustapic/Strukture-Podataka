#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 21

struct _directory;
typedef struct _directory *DirectoryP;
typedef struct _directory
{
    char name[MAX_SIZE];
    DirectoryP sibling;
    DirectoryP child;
} Directory;

struct _stack;
typedef struct _stack *StackP;
typedef struct _stack
{
    DirectoryP data;
    StackP next;
} Stack;

void printMenu();
void CreateNewDir(char* dirName, DirectoryP p, DirectoryP currentDirP);
DirectoryP AddNewDir(DirectoryP currentDir, DirectoryP newDir);
DirectoryP FindChildDir(DirectoryP p, char* dirName, char* currentDir, int n, StackP stack);
DirectoryP PopDir(StackP stack);
StackP PushDirToStack(StackP stack, DirectoryP p);
StackP PopDirFromStack(StackP stack);
void PrintDirList(DirectoryP pos);
void DeleteDirList(DirectoryP p);
void ExitApp(DirectoryP p);
void PerformAction();

int main()
{
    PerformAction();
    return EXIT_SUCCESS;
}

void PrintMenu()
{
    printf("=================================================================\n");
    printf("\t\tDirectory Management System\n");
    printf("=================================================================\n");
    printf("Options available:\n");
    printf("\n\t\tmd DIRECTORY_NAME");
    printf("\n\t\tcd DIRECTORY_NAME");
    printf("\n\t\tcd.. DIRECTORY_NAME");
    printf("\n\t\tdir");
    printf("\n\t\texit\n");
    printf("\n=================================================================\n\n");
}

void CreateNewDir(char* dirName, DirectoryP p, DirectoryP currentDirP)
{
    scanf("%s", dirName);
    p = (DirectoryP)malloc(sizeof(Directory));
    strcpy(p->name, dirName);
    p->sibling = NULL;
    p->child = NULL;
    currentDirP->child = AddNewDir(currentDirP->child, p);
}

DirectoryP AddNewDir(DirectoryP currentDir, DirectoryP newDir)
{
    if(currentDir == NULL)
    {
        return newDir;
    }

    if(strcmp(currentDir->name, newDir->name) > 0)
    {
        newDir->sibling = currentDir;
        return newDir;
    }

    else if(strcmp(currentDir->name, newDir->name) < 0)
    {
        currentDir->sibling = AddNewDir(currentDir->sibling, newDir);
    }

    else
    {
        printf("That directory already exists!\n");
        free(newDir);
    }

    return currentDir;
}

DirectoryP FindChildDir(DirectoryP p, char* dirName, char* currentDir, int n, StackP stack)
{
    int i;
    DirectoryP dir = p;
    p = p->child;

    while(p != NULL)
    {
        if(strcmp(p->name, dirName) == 0)
        {
            for(i = 0; i < strlen(dirName); i++)
            {
               currentDir[n + i] = dirName[i];
            }
            currentDir[n + i] = ':';
            currentDir[n + 1 + i] = '\0';
            stack = PushDirToStack(stack, p);

            return p;
        }
        p = p->sibling;
    }

    if(p == NULL)
    {
        printf("Directory doesn't exist!\n");
        return NULL;
    }

    return dir;
}

DirectoryP PopDir(StackP stack)
{
    DirectoryP q = stack->data;
    return q;
}

StackP PushDirToStack(StackP stack, DirectoryP p)
{
    StackP q = (StackP)malloc(sizeof(Stack));
    q->data = p;
    q->next = stack;

    return q;
}

StackP PopDirFromStack(StackP stack)
{
    StackP q = stack->next;
    return q;
}

void PrintDirList(DirectoryP pos)
{
    if(pos == NULL)
    {
        printf("Directory list is empty!\n");
    }

    while(pos != NULL)
    {
        printf("\t%s\n", pos->name);
        pos = pos->sibling;
    }
    sleep(4);
}

void DeleteDirList(DirectoryP p)
{
    if(!p)
        return;
    DeleteDirList(p->sibling);
    DeleteDirList(p->child);
    free(p);
}

void ExitApp(DirectoryP p)
{
    printf("\nYou exited application!\n");
    DeleteDirList(p);
}

void PerformAction()
{
    Directory dir;
    Stack head = {.data = &dir, .next = NULL};
    char command[21], dirName[MAX_SIZE], currentDir[51];
    DirectoryP p, currentDirP = &dir;
    StackP currentStackP = &head;
    int n,i;

    strcpy(currentDir, "");
    strcpy(dir.name, "C:");
    dir.sibling = NULL;
    dir.child = NULL;

    while(EXIT_FAILURE)
    {
        system("cls");
        PrintMenu();

        printf("%s%s>", dir.name, currentDir);
        scanf("%s", command);

        if(strcmp(command, "md") == 0)
        {
            CreateNewDir(dirName,p,currentDirP);
        }
        else if(strcmp(command, "cd") == 0)
        {
            /*
                need to create appropriate declaration for function 'GoToChildDir'
                that contains code lines below, inside this "if" case to perform action for
                placing inside child directory ( "cd" )
            */
            scanf("%s", dirName);
            n = strlen(currentDir);
            currentDirP = FindChildDir(currentDirP, dirName, currentDir, n, currentStackP);
            currentStackP = PushDirToStack(currentStackP, currentDirP);
        }
        else if(strcmp(command, "cd..") == 0)
        {
            /*
                need to create appropriate declaration for function 'GoToParentDir'
                that contains code lines below, inside this "if" case to perform action for
                placing inside parent directory ( "cd.." )
            */
            if(currentDirP != &dir)
            {
                currentStackP = PopDirFromStack(currentStackP);
                currentDirP = PopDir(currentStackP);
            }

            for(i = strlen(currentDir) - 2; i >= 0; i--)
            {
                if(currentDir[i] == ':')
                    break;
                currentDir[i] = '\0';
            }
        }
        else if(strcmp(command, "dir") == 0)
        {
            PrintDirList(currentDirP->child);
        }
        else if(strcmp(command, "exit") == 0)
        {
            ExitApp(&dir);
            return EXIT_SUCCESS;
        }
        else
        {
            printf("Command not found!\n");
        }
    }
}
