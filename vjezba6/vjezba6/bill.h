#ifndef BILL_H
#define BILL_H
#include "date.h"
#include "article.h"
#include "errors.h"

#define MAX_BILL_NAME (128)

struct _bill;
typedef struct _bill* BillP;
typedef struct _bill {
    char name[MAX_BILL_NAME];
    DateP date;
    Article articleHead;
    BillP next;
    float total;
} Bill;

int InitializeBill(BillP bill);
BillP CreateBillFromFile(char* billFileName);
int InsertBillAfter(BillP position, BillP bill);
int InsertBillSorted(BillP head, BillP bill);
int ReadBillsFromFile(BillP head, char* fileName);
int PrintBill(BillP bill);
int PrintAllBills(BillP head);
int DeleteBill(BillP bill);
int DeleteBillAfter(BillP position);
int DeleteAllBills(BillP head);
float CalculateTotalBill(BillP bill);
BillP FindLowestProfitOfAll(BillP head);
BillP FindHighestProfitOfAll(BillP head);
int PrintNamesOfAllBills(BillP head);
int FindBillsContainingCertainArticle(BillP head, char* articleName);
int CheckIfBillExist(BillP head, char* enterString);

BillP CreateBillFromInput(char* billFileName, DateP date);

#endif
