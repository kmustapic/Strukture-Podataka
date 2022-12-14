#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

int InitializeBill(BillP bill) {
    bill->date = NULL;
    bill->next = NULL;
    bill->total = 0;
    memset(bill->name, 0, MAX_BILL_NAME);
    InitializeArticle(&bill->articleHead);

    return EXIT_SUCCESS;
}

BillP CreateBill(char* billFileName) {
    FILE* fp = NULL;
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(billFileName, "r");
    if (!fp) {
        perror("\tBill not opened!\n");
        return NULL;
    }

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        perror("Bill not allocated!\n");
        fclose(fp);
        return NULL;
    }

    InitializeBill(bill);

    strcpy(bill->name, billFileName);

    fgets(fileLine, MAX_LINE, fp);
    bill->date = CreateDateFromString(fileLine);
    if (!bill->date) {
        fclose(fp);
        DeleteBill(bill);
        return NULL;
    }

    while (!feof(fp)) {
        ArticleP article = NULL;
        fgets(fileLine, MAX_LINE, fp);

        if (strlen(fileLine) == 0)
            continue;

        article = CreateArticleFromString(fileLine);
        if (!article) {
            fclose(fp);
            DeleteBill(bill);

            return NULL;
        }
        InsertArticleSorted(&bill->articleHead, article);
    }
    fclose(fp);

    return bill;
}

int InsertBillAfter(BillP position, BillP bill) {
    bill->next = position->next;
    position->next = bill;

    return EXIT_SUCCESS;
}

int InsertBillSorted(BillP head, BillP bill) {
    BillP position = head;
    while (position->next != NULL && Datecmp(position->next->date, bill->date) < 0)
        position = position->next;

    InsertBillAfter(position, bill);

    return EXIT_SUCCESS;
}

int ReadBillsFromFile(BillP head, char* fileName) {
    FILE* fp = NULL;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) {
        perror("File with bills not opened!\n");
        return FILE_WITH_BILLS_NOT_OPENED;
    }

    while (!feof(fp)) {
        BillP bill = NULL;
        fscanf(fp, "%s", fileLine);

        if (strlen(fileLine) == 0)
            continue;

        bill = CreateBill(fileLine);
        if (!bill) {
            fclose(fp);
            DeleteAllBills(head);
            return CREATE_BILL_FAILED;
        }
        InsertBillSorted(head, bill);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int PrintBill(BillP bill) {
    ArticleP article = NULL;

    printf("\t============================\r\n");
    printf("\t\t** Date => ");
    PrintDate(bill->date);
    printf("\r\n");
    printf("\t\t** Articles (name, count, price) \r\n");

    for (article = bill->articleHead.next; article != NULL; article = article->next) {
        printf("\t\t\t * ");
        PrintArticle(article);
        printf("\r\n");
    }

    return EXIT_SUCCESS;
}

int PrintAllBills(BillP head) {
    BillP bill = NULL;
    for (bill = head->next; bill != NULL; bill = bill->next)
        PrintBill(bill);

    return EXIT_SUCCESS;
}

int DeleteBill(BillP bill) {
    if (!bill)
        return EXIT_SUCCESS;

    if (bill->date)
        free(bill->date);

    DeleteAllArticles(&bill->articleHead);
    free(bill);
}

int DeleteBillAfter(BillP position) {
    BillP toDelete = position->next;
    if (!toDelete)
        return EXIT_SUCCESS;

    position->next = toDelete->next;
    DeleteBill(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllBills(BillP head) {
    while (head->next)
        DeleteBillAfter(head);

    return EXIT_SUCCESS;
}

int CalculateTotalBill(BillP bill)
{
    ArticleP article = NULL;
    bill->total = 0;

        article = &bill->articleHead;
        for (article = article->next; article != NULL; article = article->next)
        {
            bill->total += (float)article->price * article->count;
        }
       // print("%f", sumPrice);
    return bill->total;
}

BillP FindLowestProfitOfAll(BillP head) {
    
    head = head->next;
    BillP lowest = head;
    int min = INT_MAX;
    int total = 0;

    for (; head->next != NULL; head = head->next) {
        total=CalculateTotalBill(head);
        if (total < min) {
            min = total;
            lowest = head;
        }
    }
    printf("%d", lowest->total);

    return lowest;
}

BillP FindHighestProfitOfAll(BillP head) {

    head = head->next;
    BillP highest = NULL;
    int max = INT_MIN;
    int total = 0;

    for (; head->next != NULL; head = head->next) {
        total = CalculateTotalBill(head);
        if (total > max) {
            max = total;
            highest = head;
        }
    }
    printf("%d", highest->total);

    return highest;
}