#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{
    int choice = 0;
    int x = 1, number = 0;
    NodeP root = NULL, current = NULL;

    root = CreateEmptyNode(root);
    PrintMeni();
    while (x)
    {
        printf("Your input:");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            printf("Insert the number you want to insert in the tree:\n");
            scanf("%d", &number);
            root = InsertNode(root, number);
            if (root == NULL)
                printf("That number already exists in the tree!\n");
            system("pause");
            break;
        case 2:
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
            PrintInorder(root);
            printf("\n");
            system("pause");
            break;
        case 5:
            PrintPreorder(root);
            printf("\n");
            system("pause");
            break;
        case 6:
            PrintPostorder(root);
            printf("\n");
            system("pause");
            break;
        case 7:
            root = CreateEmptyNode(root);
            x = 0;
            system("pause");
            break;
        default:
            printf("Wrong choice! Insert new choice:\n");
            break;
        }
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
        return NULL;

    PrintInorder(root->left);
    printf("%d\t", root->number);
    PrintInorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPreorder(NodeP root)
{
    if (root == NULL)
        return NULL;
    printf("%d\t", root->number);
    PrintPreorder(root->left);
    PrintPreorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPostorder(NodeP root)
{
    if (root == NULL)
        return NULL;

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
    printf("=================================================================\n");
    printf("\nChoose one of the operations:");
    printf("\n\t\t\t1-Insert new node");
    printf("\n\t\t\t2-Delete node");
    printf("\n\t\t\t3-Find certain node in the tree");
    printf("\n\t\tISPISI:");
    printf("\n\t\t\t4-Inorder ispis");
    printf("\n\t\t\t5-Preorder ispis");
    printf("\n\t\t\t6-Postorder ispis");
    printf("\n\t\t\t7-Level-order ispis");
    printf("\n=================================================================\n\n");
}