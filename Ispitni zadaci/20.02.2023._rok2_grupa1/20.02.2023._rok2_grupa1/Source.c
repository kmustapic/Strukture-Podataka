#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN (32)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
	int year;
	int month;
	int day;
} Date;

struct _hotel;
typedef struct _hotel* HotelP;
typedef struct _hotel {
	char name[MAX_NAME_LEN];
	DateP date;
	int income;
	HotelP next;
} Hotel;

// 2
DateP InitializeD();
HotelP InitializeH();
HotelP CreateH(char* name, int year, int month, int day, int income);
int AddFront(HotelP head, HotelP n);
int Read(HotelP head, char* file);
int Print(HotelP p);
int Delete(HotelP p);
int InsertSortedAfter1(HotelP p, HotelP new);
int InsertSorted1(HotelP head, HotelP new);
int InsertSorted2(HotelP head, HotelP new);
double Avg(HotelP head);
int ToEnd(HotelP head, HotelP new);



int main() {
	HotelP hotels = NULL;
	hotels = InitializeH();
	char* f1[MAX_NAME_LEN] = { 0 };

	strcpy(f1, "hoteli.txt");
	Read(hotels, f1);

/*
	printf("\nLIST SORTED BY DATE:\n");
	Print(hotels);
*/



	return EXIT_SUCCESS;
}

DateP InitializeD() {
	DateP new = NULL;
	new = (DateP)malloc(sizeof(Date));
	if (!new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	new->day = 0;
	new->month = 0;
	new->year = 0;

	return new;
}

HotelP InitializeH() {
	HotelP new = NULL;
	new = (HotelP)malloc(sizeof(Hotel));
	if (!new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	strcpy(new->name, "");
	new->income = 0;
	new->next = NULL;
	new->date = InitializeD();

	return new;
}

HotelP CreateH(char* name, int year, int month, int day, int income) {
	HotelP new = NULL;
	new = (HotelP)malloc(sizeof(Hotel));
	if (!new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	new = InitializeH();
	strcpy(new->name, name);
	new->date->year = year;
	new->date->month = month;
	new->date->day = day;
	new->income = income;
	new->next = NULL;

	return new;
}

int AddFront(HotelP head, HotelP n) {
	HotelP t = head;
	n->next = t->next;
	t->next = n;

	return EXIT_SUCCESS;
}

int Read(HotelP head, char* file) {
	FILE* fp = NULL;
	HotelP new, t = NULL;
	char* name[MAX_NAME_LEN] = { 0 };
	int y, m, d, inc;

	fp = fopen(file, "r");
	if (!fp) {
		printf("\nFile opening error!\n");
		return EXIT_FAILURE;
	}

	else {
		while (!feof(fp)) {
			fscanf(fp, "%s %d-%d-%d %d", name, &y, &m, &d, &inc);
			new = CreateH(name, y, m, d, inc);
			//AddFront(head, new);
			InsertSorted1(head, new);
		}
		printf("\nLIST SORTED BY DATE:\n");
		Print(head);

		InsertSorted2(head);
		printf("\nLIST SORTED BY INCOME:\n");
		Print(head);


	}

	return EXIT_SUCCESS;
}

int Print(HotelP p)
{
	printf("\n\n");
	HotelP t = p->next;
	while (NULL != t) {
		printf("%s %.4d_%.2d_%.2d  %d\n", t->name, t->date->year, t->date->month, t->date->day, t->income);
		t = t->next;
	}
}

int Delete(HotelP p) {
	HotelP t = NULL;
	while (p -> next != NULL) {
		t = p->next;
		p->next = t->next;
		free(t);
	}

	return EXIT_SUCCESS;
}

int Datecmp(DateP head, DateP new) {
	int r = head->year - new->year;

	if (r == 0) {
		r = head->month - new->month;

		if (r == 0)
			r = head->day - new->day;
	}
	
	return r;
}

int InsertSortedAfter1(HotelP p, HotelP new) {
	new->next = p->next;
	p->next = new;

	return EXIT_SUCCESS;
}

double Avg(HotelP head) {
	HotelP t = NULL;
	double avg = 0;
	int n = 0;

	for (t = head->next; t != NULL; t = t->next) {
		avg += t->income;
		n++;
	}
	avg = (1. * avg) / n;

	return avg;
}

//
int ToEnd(HotelP head, HotelP new) {
	HotelP p = NULL;
	HotelP temp = new;

	while (p = head->next, p != NULL, p = p->next)
		p = p->next;
	
	temp->next = p->next;
	p->next = temp;

	return EXIT_SUCCESS;
}

int InsertSorted1(HotelP head, HotelP new) {
	HotelP p = head;

	while (p->next != NULL && Datecmp(p->next->date, new->date) < 0)
		p = p->next;
	InsertSortedAfter1(p, new);

	return EXIT_SUCCESS;
}

int InsertSorted2(HotelP head, HotelP new) {
	HotelP p = head;
	HotelP t = NULL;
	double avg = 0.0;
	avg = Avg(head);

	while (p->next != NULL && p->next->income >= avg)
		p = p->next;
	ToEnd(p, new);
	printf("\nLIST SORTED BY INCOME:\n");
	Print(head);

	return EXIT_SUCCESS;
}



