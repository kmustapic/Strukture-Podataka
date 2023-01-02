#include <stdio.h>
#include <stdlib.h>

struct _tree;
typedef struct _tree *TreeP;
struct _list;
typedef struct _list *ListP;

typedef struct _tree
{
    int number;
    TreeP left;
    TreeP right;
} Tree;

typedef struct _list
{
    int element;
    ListP next;
} List;

TreeP InitializeTree(TreeP root);
ListP InitializeList(ListP head);
TreeP InsertNumberInTree(TreeP root, int number);
int PrintElements(TreeP root, ListP head);
int PushElementToList(ListP head, int element);

int main()
{
    TreeP root = NULL;
    ListP head1 = NULL,head2=NULL,head3=NULL;

    head1 = InitializeList(head1);
    head2=InitializeList(head2);
    head3=InitializeList(head3);

    //a)
    root = InsertNumberInTree(root, 2);
    root = InsertNumberInTree(root, 5);
    root = InsertNumberInTree(root, 7);
    root = InsertNumberInTree(root, 8);
    root = InsertNumberInTree(root, 11);
    root = InsertNumberInTree(root, 1);
    root = InsertNumberInTree(root, 4);
    root = InsertNumberInTree(root, 2);
    root = InsertNumberInTree(root, 3);
    root = InsertNumberInTree(root, 7);
    PrintElements(root,head1);

    //b)
    

    return EXIT_SUCCESS;
}


TreeP InitializeTree(TreeP root)
{
    root = (TreeP)malloc(sizeof(Tree));
    if (root == NULL)
    {
        printf("Error in initializing tree\n");
        return NULL;
    }
    root->number = 0;
    root->left = NULL;
    root->right = NULL;

    return root;
}

ListP InitializeList(ListP head)
{
    head = (ListP)malloc(sizeof(List));
    if (head == NULL)
    {
        printf("Error in initializing the list.\n");
        return NULL;
    }
    head->element = 0;
    head->next = NULL;

    return head;
}

TreeP InsertNumberInTree(TreeP root, int number)
{
    if (root == NULL)
    {
        root = InitializeTree(root);
        root->number = number;
        root->left = NULL;
        root->right = NULL;
    }
    else if (number >= root->number)
    {
        root->left = InsertNumberInTree(root->left, number);
    }
    else if (number <= root->number)
    {
        root->right = InsertNumberInTree(root->right, number);
    }
    return root;
}

int PrintElements(TreeP root,ListP head) {
//inorder
    if(root == NULL)
        return 0;
    PrintElements(root->left, head);
    printf("%d ", root->number);
    PrintElements(root->right, head);
    
    PushElementToList(head ,root->number);
    return EXIT_SUCCESS;
}

int PushElementToList(ListP head, int element)
{
    ListP temp;
    head=head->next;
    while(head != NULL)
    {
        if(head->next == NULL)
        {
            temp = (ListP)malloc(sizeof(List));
            temp->element = element;
            head->next = temp;
            temp->next = NULL;

            return 0;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

