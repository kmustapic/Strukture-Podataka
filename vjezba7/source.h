#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_LENGTH 1024

struct _treeNode;
typedef struct _treeNode* TreeNodeP;
typedef struct _treeNode
{
    char* directoryName;
    TreeNodeP child;
    TreeNodeP nextSibling;
} TreeNode;

struct _stackNode;
typedef struct _stackNode* StackNodeP;
typedef struct _stackNode
{
    TreeNodeP treeNode;
    StackNodeP next;
} StackNode;

int PrintMenu();
int CommandLine();
TreeNodeP CreateNewTreeNode();
StackNodeP CreateNewStackNode();
int Push(StackNodeP stackHead, TreeNodeP treeNode);
int Pop(StackNodeP stackHead, TreeNodeP* result);
int AllocateBuffers(char** path, char** inputBuffer, char** command, char** commandArgument);
int SetDirectoryName(TreeNodeP directory, char* directoryName);
int MakeNewDirectory(TreeNodeP currentDirectory, char* newDirectoryName);
TreeNodeP FindDirectory(TreeNodeP currentDirectory, char* directoryName);
int ReturnToPreviousDirectory(TreeNodeP* currentDirectory, TreeNodeP rootDirectory, char* path, StackNodeP stackHead);
int ChangeDirectory(TreeNodeP* currentDirectory, char* directoryName, char* path, StackNodeP stackHead);
int PrintDirectory(TreeNodeP currentDirectory);
int FreeBuffers(char* path, char* inputBuffer, char* command, char* commandArgument);
int FreeTree(TreeNodeP T);
int FreeStack(StackNodeP S);
int FreeAllMemory(char* path, char* inputBuffer, char* command, char* commandArgument, TreeNodeP root, StackNodeP stackHead);
