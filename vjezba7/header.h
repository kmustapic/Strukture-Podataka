#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

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

#endif
