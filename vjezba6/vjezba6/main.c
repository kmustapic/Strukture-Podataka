#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME (1024)

int UserSearchArticleInRange(BillP head);
int SearchArticleInRange(BillP head, FilterP filter);

int main(int argc, char* argv[]) {
    Bill head;
    char fileName[MAX_FILE_NAME] = { 0 };
    int status = EXIT_SUCCESS;

    InitializeBill(&head);

    do {
        printf("============================================================\n"
               " Please insert filename: ");
        scanf(" %s", fileName);
        printf("============================================================\n");

        status = ReadBillsFromFile(&head, fileName);
    } while (status > EXIT_SUCCESS);
    if (status != EXIT_SUCCESS)
        return EXIT_FAILURE;

    printf(
        "\r\n"
        "\t ** Successfully read %s:\r\n\r\n", fileName);
    PrintAllBills(&head);
    UserSearchArticleInRange(&head);
    DeleteAllBills(&head);

    return EXIT_SUCCESS;
}

int UserSearchArticleInRange(BillP head) {
    char article[MAX_ARTICLE_NAME] = { 0 };
    char dateFromString[MAX_DATE_AS_STRING] = { 0 };
    char dateToString[MAX_DATE_AS_STRING] = { 0 };
    FilterP filter = NULL;

    printf(
        "\n\n====================== SEARCH ==============================\n"
        "\n\t<article> <from date> <to date> (inclusive)\n"
        "\tEXAMPLE: kruh 1992-01-03 1992-02-08\n\n"
        "============================================================\n\n");

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