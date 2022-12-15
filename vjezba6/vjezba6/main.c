#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME (1024)
#define MAX_LINE (50)

int UserSearchArticleInRange(BillP head);
int SearchArticleInRange(BillP head, FilterP filter);
int PrintMenu();

int main(int argc, char* argv[]) {
    Bill head;
    char fileName[MAX_FILE_NAME] = { 0 };
//*********************************************
    char enterString[MAX_LINE] = { 0 };
//*********************************************
    int status = EXIT_SUCCESS;
    int choice = -1;
    int ch;

    InitializeBill(&head);

    do {
        system("cls");
        printf(
                "====================================================================\n"
                "\t\tRECEIPT MANAGEMENT SYSTEM\n"
                "====================================================================\n"
                "\n    Please insert FILENAME of the file\n"
                "    that contains name of all existing receipts: ");

        scanf(" %s", fileName);
        printf("\n");

        status = ReadBillsFromFile(&head, fileName);
        if (status > EXIT_SUCCESS) {
            printf(
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");
        }
    } while (status > EXIT_SUCCESS);

    if (status != EXIT_SUCCESS) {
        printf("App execution failed!\n");
        return EXIT_FAILURE;
    }

    while (choice != 0) {

        system("cls");
        printf(
            "====================================================================\n"
            "\t\tRECEIPT MANAGEMENT SYSTEM\n"
            "====================================================================\n"
            " File that contains names of all existing receipts: %s\n", fileName);
        PrintMenu();
        printf("Choose an option from menu: ");
        scanf(" %d", &choice);
        do {
            ch = getchar();
        } while ((ch != EOF) && (ch != '\n'));

        switch (choice) {

        case 0:
            printf("====================================================================\n");
            printf("0");
            system("pause");
            break;

        case 1:
            // Kike
            printf(
                "====================================================================\n"
                " You chose to add new receipt.\n\n"
                " Please enter date of receipt creation"
                " in valid format: <year>-<month>-<day>: ");
            scanf(" %s", enterString);
            printf(
                "====================================================================\n");
//*********************************************

//*********************************************
            printf(
                "\n New receipt is successfully added to the list!\n\n"
                " Press enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 2:
            // Kike
            printf("====================================================================\n");
            printf("2");
            system("pause");
            break;

        case 3:
            // Kike
            printf("====================================================================\n");
            printf("3");
            system("pause");
            break;

        case 4:
            // Kike
            printf("====================================================================\n");
            printf("4");
            system("pause");
            break;

        case 5:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print name list of existing receipts\n\n");
            PrintNameOfAllBills(&head);
            system("pause");
            break;

        case 6:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print all receipts info that contain certain product\n\n");
            system("pause");
            break;

        case 7:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print receipt info with lowest total profit\n\n");
            BillP lowest = NULL;
            lowest=FindLowestProfitOfAll(&head);
            //printf("............%s\n", lowest->name); TESTING
            PrintBill(lowest);
            system("pause");
            break;

        case 8:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print receipt info with highest total profit\n\n");
            BillP highest = NULL;
            highest=FindHighestProfitOfAll(&head);
            //printf("............%s\n", highest->name);    TESTING
            PrintBill(highest);
            system("pause");
            break;

        default:
            printf(
                "====================================================================\n"
                "\n Your choice is invalid.\n"
                " Please enter valid number for certain choice.\n"
                "\n Press enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
        }
    }
//*********************************************

//    PrintAllBills(&head);
//    UserSearchArticleInRange(&head);
//    DeleteAllBills(&head);

    return EXIT_SUCCESS;
}
//*********************************************

int UserSearchArticleInRange(BillP head) {
    char article[MAX_ARTICLE_NAME] = { 0 };
    char dateFromString[MAX_DATE_AS_STRING] = { 0 };
    char dateToString[MAX_DATE_AS_STRING] = { 0 };
    FilterP filter = NULL;

    printf(
        "\n\n======================== SEARCH ================================\n"
        "\n\t<article> <from date> <to date> (inclusive)\n"
        "\tEXAMPLE: kruh 1992-01-03 1992-02-08\n\n"
        "====================================================================\n\n");

    do {
        printf("\t Your input: ");
        scanf(" %s %s %s", article, dateFromString, dateToString);

        filter = CreateFilter(dateFromString, dateToString, article);
    } while (!filter);

    SearchArticleInRange(head, filter);
    DeleteFilter(filter);

    return EXIT_SUCCESS;
}

int SearchArticleInRange(BillP head, FilterP filter) {
    BillP bill = NULL;
    int totalCount = 0;
    float totalPrice = 0.0f;

    printf("\t     Result:\r\n");

    for (bill = head->next; bill != NULL; bill = bill->next) {
        if (IsDateInsideOfRange(bill->date, filter->from, filter->to)) {
            ArticleP article = FindArticleByName(&bill->articleHead, filter->name);

            if (article) {
                printf("\t\t- ");
                PrintArticle(article);
                printf("\r\n");
                totalCount += article->count;
                totalPrice += article->count * article->price;
            }
        }
    }

    printf(
        "\t\tSearch result for \"%s\"\r\n"
        "\t\t\tCount:\t\t%d\r\n"
        "\t\t\tTotal profit\t%.02f\r\n",
        filter->name,
        totalCount,
        totalPrice
    );
}

int PrintMenu()
{
    printf(
        "====================================================================\n"
        "\t\t\t   MENU\n"
        "====================================================================\n\n"
        "\t1  -  Add new receipt\n"
        "\t2  -  Delete certain existing receipt\n"
        "\t3  -  Print existing receipts info\n"
        "\t4  -  Modify data for certain existing receipt\n"
        "\t5  -  Print name list of existing receipts\n"
        "\t6  -  Print all receipts info that contain certain product\n"
        "\t7  -  Print receipt info with lowest total profit\n"
        "\t8  -  Print receipt info with highest total profit\n"
        "\t0  -  Exit application\n"
        "\n====================================================================\n");

    return EXIT_SUCCESS;
}
/*
    FURTHER IMPROVEMENT:
    _____________________________________________________________________________
    * while scanning choice if input is 'non-number', e.g.: "*"
      we enter an infinte loop -> needs to be resolved!

    -> possible solutions:
       1) https://stackoverflow.com/questions/66723859/why-does-scanf-enter-a-loop-when-i-input-a-character
    _____________________________________________________________________________
    * increase code readability

    -> possible solutions:
       1) divide code inside switch cases (in main.c),
          each case should have it's own function
    _____________________________________________________________________________
    * extending app capabilities 

    -> possible solutions:
       1) realize "login form" and separating different options while login
          a) admin
          b) customer
         
         also separate authorized actions for each case, develop code logic
         new struct needs to be implemented such as:
         
         struct _user;
         typedef struct _user* UserP;
         typedf _user {
            char username[MAX_LINE];
            char password[MAX_LINE];
            int authority;
            BillP billHead;
         }

        for distinguishing authority e.g. : customer -> 1 and admin -> 2 
    _____________________________________________________________________________
*/
