/*
8. Napisati program koji omogucava rad s binarnim stablom pretrazivanja.
Treba omoguciti unosenje novog elementa u stablo, ispis elemenata
(inorder, preorder, postorder i level order),
brisanje i pronalazenje nekog elementa.
 */

#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)

#define MAX_SIZE (50)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct _node;
typedef struct _node* NodeP;
typedef struct _node
{
    int number;
    NodeP left;
    NodeP right;

} Node;

int PrintMenu();
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
    int choice = -1;
    int number = 0;
    NodeP root = NULL, current = NULL;

    root = CreateEmptyNode(root);
    while (true)
    {
        system("cls");
        PrintMenu();
        printf("Your choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            printf(
                "=================================================================\n"
                "You chose to insert a number in the tree.\n\n"
                "Please enter the number you want to insert in the tree: ");
            scanf("%d", &number);
            root = InsertNode(root, number);
            if (NULL != root)
                printf("\nYou have successfully added number %d in the tree!\n", number);
            number = 0;
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;


        case 2:
            printf(
                "=================================================================\n"
                "You chose to delete a number in the tree.\n\n"
                "Please enter the number you want to delete: ");
            scanf("%d", &number);
            current = DeleteNode(root, number);
            if (NULL == current)
                printf("Number %d doesn't exist in the tree yet!\n", number);
            else
                printf("You successfully deleted the number %d from the tree!\n", number);
            number = 0;
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 3:
            printf(
                "=================================================================\n"
                "You chose to search a certain number in the tree.\n\n"
                "Please enter the number you want to find: ");
            scanf("%d", &number);
            current = FindNode(root, number);
            if (NULL == current)
                printf("Number %d doesn't exist in the tree yet!\n", number);
            else
                printf("Number %d is successfully found!\n", number);
            number = 0;
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 4:
            printf(
                "=================================================================\n"
                "You chose to print INORDER traversal.\n\n");
            PrintInorder(root);
            printf("\n");
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 5:
            printf(
                "=================================================================\n"
                "You chose to print PREORDER traversal.\n\n");
            PrintPreorder(root);
            printf("\n");
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 6:
            printf(
                "=================================================================\n"
                "You chose to print POSTORDER traversal.\n\n");
            PrintPostorder(root);
            printf("\n");
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 7:
            printf(
                "=================================================================\n"
                "You chose to print LEVEL ORDER traversal.\n\n");
            LevelOrder(root);
            printf("\n");
            printf("\nPress enter to continue app execution.\n");
            system("pause");
            break;

        case 8:
            system("cls");
            printf(
                "=================================================================\n"
                "\nYou have exited the application!\n\n"
                "=================================================================\n"
                "\nAllocated memory is emptied!\n"
                "\n=================================================================\n\n");
            system("pause");
            break;

        default:
            printf(
                "=================================================================\n"
                "\nYour choice is invalid.\n"
                "Please enter valid number for certain choice.\n"
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;
        }
    }

    return EXIT_SUCCESS;
}

int PrintMenu()
{
    printf(
        "=================================================================\n"
        "\t\t   Binary Search Tree (BST)\n"
        "================================================================="
        "\n\n\t\t            OPERATIONS"
        "\n\t      _______________________________________"
        "\n\t      |\t                                    |"
        "\n\t      |\t       1 - Insert new node\t    |"
        "\n\t      |\t       2 - Delete node\t            |"
        "\n\t      |  3 - Find certain node in the tree  |\n"
        "\t      |_____________________________________|\n"

        "\n\n\t\t      PRINT TRAVERSAL OPTIONS"
        "\n\t      _______________________________________"
        "\n\t      |\t                                    |"
        "\n\t      |     4 - Print INORDER traversal\t    |"
        "\n\t      |     5 - Print PREORDER traversal    |"
        "\n\t      |     6 - Print POSTORDER traversal   |"
        "\n\t      |     7 - Print LEVEL ORDER traversal |"
        "\n\t      |_____________________________________|\n"

        "\n\t\t       8 - Exit application"
        "\n\n=================================================================\n");

    return EXIT_SUCCESS;
}

NodeP CreateEmptyNode(NodeP root)
{
    if (NULL != root)
    {
        root->left = CreateEmptyNode(root->left);
        root->right = CreateEmptyNode(root->right);
        free(root);
    }

    return EXIT_SUCCESS;
}

NodeP InsertNode(NodeP root, int number)
{
    if (NULL == root)
    {
        root = (NodeP)malloc(sizeof(Node));
        root->number = number;
        root->left = NULL;
        root->right = NULL;
    }

    else if (number < root->number)
        root->left = InsertNode(root->left, number);

    else if (number > root->number)
        root->right = InsertNode(root->right, number);

    else if (root->number == number)
    {
        printf("\nThat number already exists!\n");
        return NULL;
    }

    return root;
}

int PrintInorder(NodeP root)
{
    if (NULL == root)
        return EXIT_FAILURE;

    PrintInorder(root->left);
    printf("%d\t", root->number);
    PrintInorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPreorder(NodeP root)
{
    if (NULL == root)
        return EXIT_FAILURE;

    printf("%d\t", root->number);
    PrintPreorder(root->left);
    PrintPreorder(root->right);

    return EXIT_SUCCESS;
}

int PrintPostorder(NodeP root)
{
    if (NULL == root)
        return EXIT_FAILURE;

    PrintPostorder(root->left);
    PrintPostorder(root->right);
    printf("%d\t", root->number);

    return EXIT_SUCCESS;
}

NodeP DeleteNode(NodeP root, int number)
{
    NodeP temp = NULL;
    if (NULL == root)
    {
        printf("That element doesn't exist yet!\n");
        return NULL;
    }

    else if (number < root->number)
        root->left = DeleteNode(root->left, number);

    else if (number > root->number)
        root->right = DeleteNode(root->right, number);

    else if (NULL != root->left && NULL != root->right)
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
    if (NULL == root)
        return NULL;

    else if (NULL == root->left)
        return root;

    return FindMin(root->left);
}

NodeP FindNode(NodeP root, int number)
{
    if (NULL == root)
        return NULL;

    else if (number > root->number)
        return FindNode(root->right, number);

    else if (number < root->number)
        return FindNode(root->left, number);

    return root;
}



int FindHeight(NodeP root) {

    if (!root)
        return EXIT_FAILURE;

    else
    {
        int leftHeight = FindHeight(root->left);
        int rightHeight = FindHeight(root->right);

        if (leftHeight >= rightHeight)
            return leftHeight + 1;

        else
            return rightHeight + 1;
    }

    return EXIT_SUCCESS;
}

int PrintLevel(NodeP root, int level_no) {

    if (!root)
        return EXIT_FAILURE;

    if (level_no == 0)
        printf("%d ", root->number);

    else
    {
        PrintLevel(root->left, level_no - 1);
        PrintLevel(root->right, level_no - 1);
    }

    return EXIT_SUCCESS;
}

int LevelOrder(NodeP root) {

    if (!root)
        return EXIT_FAILURE;

    int height = FindHeight(root);
    int i;
    for (i = 0; i < height; i++)
    {
        printf("Level %d: ", i);
        PrintLevel(root, i);
        printf("\n");
    }
    printf("\n\n-----Complete Level Order :-----\n");
    for (int i = 0; i < height; i++) {
        PrintLevel(root, i);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

/*
    FURTHER IMPROVEMENT:
    _____________________________________________________________________________
    * needs to limit and check user's input data type
      e.g. if user enters a string instead of int value
           app execution breaks, not working properly!
      e.g. when entering value for int variable choice
    _____________________________________________________________________________
*/