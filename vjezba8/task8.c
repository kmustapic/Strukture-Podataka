#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#define max_size (50)

struct _node;
typedef struct _node *NodeP;
typedef struct _node
{
    int number;
    NodeP left;
    NodeP right;

} Node;

int PrintMeni();
NodeP CreateEmptyNode(NodeP root);
NodeP InsertNode(NodeP root, int number);
NodeP DeleteNode(NodeP root, int number);
NodeP FindMin(NodeP root);
NodeP FindNode(NodeP root, int number);
int PrintInorder(NodeP root);
int PrintPreorder(NodeP root);
int PrintPostorder(NodeP root);
int FindHeight(NodeP root);
int PrintLevel(NodeP root, int level_no);
int LevelOrder(NodeP root);

int main()
{
    int choice = 0;
    int x = 1, number = 0;
    NodeP root = NULL, current = NULL;

    root = CreateEmptyNode(root);
    while (x)
    {
        PrintMeni();
        printf("Your input:");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tYou have chosen to insert a number in the tree!\t\n\n"
                "====================================================================\n");
            printf("Enter the number you want to insert in the tree:\n");
            scanf("%d", &number);
            root = InsertNode(root, number);
            if (root == NULL)
                printf("That number already exists in the tree!\n");
            system("pause");
            break;
        case 2:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tYou have chosen to delete a number in the tree!\t\n\n"
                "====================================================================\n");
            printf("Insert the number you want to delete:\n");
            scanf("%d", &number);
            current = DeleteNode(root, number);
            if (current == NULL)
                printf("Number %d doesn't exists in the tree!\n", number);
            else
                printf("You deleted the number %d\n", number);
            system("pause");
            break;
        case 3:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tYou have chosen to search a number in the tree!\t\n\n"
                "====================================================================\n");
            printf("Insert the number you want to find:\n");
            scanf("%d", &number);
            current = FindNode(root, number);
            if (current == NULL)
                printf("Number %d doesn't exists in the tree\n", number);
            else
                printf("Number %d successfully found\n", number);
            system("pause");
            break;
        case 4:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tPrinting the tree INORDER!\t\n\n"
                "====================================================================\n");
            PrintInorder(root);
            printf("\n");
            system("pause");
            break;
        case 5:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tPrinting the tree PREORDER!\t\n\n"
                "====================================================================\n");
            PrintPreorder(root);
            printf("\n");
            system("pause");
            break;
        case 6:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tPrinting the tree POSTORDER!\t\n\n"
                "====================================================================\n");
            PrintPostorder(root);
            printf("\n");
            system("pause");
            break;
        case 7:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tPrinting the tree LEVELORDER!\t\n\n"
                "====================================================================\n");
            LevelOrder(root);
            system("pause");
            break;
        default:
            printf("Wrong choice! Insert new choice:\n");
            break;
        }
         system("cls");
    }
    return EXIT_SUCCESS;
}

NodeP CreateEmptyNode(NodeP root)
{
    if (root != NULL)
    {
        root->left = CreateEmptyNode(root->left);
        root->right = CreateEmptyNode(root->right);
        free(root);
    }
    return EXIT_SUCCESS;
}

NodeP InsertNode(NodeP root, int number)
{
    if (root == NULL)
    {
        root = (NodeP)malloc(sizeof(Node));
        root->number = number;
        root->left = NULL;
        root->right = NULL;
    }
    else if (number < root->number)
    {
        root->left = InsertNode(root->left, number);
    }
    else if (number > root->number)
    {
        root->right = InsertNode(root->right, number);
    }
    else if (root->number == number)
    {
        printf("That number already exists!");
        return root;
    }

    return root;
}

int PrintInorder(NodeP root)
{
    if (root == NULL)
        return EXIT_FAILURE;

    PrintInorder(root->left);
    printf("%d\t", root->number);
    PrintInorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPreorder(NodeP root)
{
    if (root == NULL)
        return EXIT_FAILURE;
    printf("%d\t", root->number);
    PrintPreorder(root->left);
    PrintPreorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPostorder(NodeP root)
{
    if (root == NULL)
        return EXIT_FAILURE;

    PrintPostorder(root->left);
    PrintPostorder(root->right);
    printf("%d\t", root->number);

    return EXIT_SUCCESS;
}

NodeP DeleteNode(NodeP root, int number)
{
    NodeP temp = NULL;

    if (root == NULL)
    {
        printf("That element doesn't exists.");
        return NULL;
    }
    else if (number < root->number)
    {
        root->left = DeleteNode(root->left, number);
    }
    else if (number > root->number)
    {
        root->right = DeleteNode(root->right, number);
    }
    else if (root->left != NULL && root->right != NULL)
    {
        temp = FindMin(root->right);
        root->number = temp->number;
        root->right = DeleteNode(root->right, root->number);
    }
    else
    {
        temp = root;

        if (root->left == NULL)
            root = root->right;
        else
            root = root->left;

        free(temp);
    }
    return root;
}

NodeP FindMin(NodeP root)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;

    return FindMin(root->left);
}

NodeP FindNode(NodeP root, int number)
{
    if (root == NULL)
        return NULL;
    else if (number > root->number)
        return FindNode(root->right, number);
    else if (number < root->number)
        return FindNode(root->left, number);

    return root;
}

int PrintMeni()
{
    printf("=================================================================");
    printf("\nChoose one of the operations:\n");
    printf("\n\t\t1-Insert new node");
    printf("\n\t\t2-Delete node");
    printf("\n\t\t3-Find certain node in the tree\n");
    printf("\n\t\tISPISI:");
    printf("\n\t\t\t4-Inorder ispis");
    printf("\n\t\t\t5-Preorder ispis");
    printf("\n\t\t\t6-Postorder ispis");
    printf("\n\t\t\t7-Level-order ispis");
    printf("\n=================================================================\n\n");
}

int FindHeight(NodeP root) {

    if (!root)
        return EXIT_FAILURE;
    else {
        int leftHeight = FindHeight(root->left);
        int rightHeight = FindHeight(root->right);
        if (leftHeight >= rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

int PrintLevel(NodeP root, int level_no) {
   
    if (!root)
        return EXIT_FAILURE;
    if (level_no == 0) {
        printf("%d ", root->number);
    }
    else {
        PrintLevel(root->left, level_no - 1);
        PrintLevel(root->right, level_no - 1);
    }
    return EXIT_SUCCESS;
}

int LevelOrder(NodeP root) {
    if (!root)
        return EXIT_FAILURE;
    int height = FindHeight(root);
    for (int i=0; i<height; i++) {
        printf("Level %d: ", i);
        PrintLevel(root, i);
        printf("\n");
    }
    printf("\n\n-----Complete Level Order :-----\n");
    for (int i=0; i<height; i++) {
        PrintLevel(root, i);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}