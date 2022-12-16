#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

DateP CreateDateFromString(char* str) {
    DateP date = NULL;
    int status = 0;

    if (!str) {
        printf("String passed as NULL to create date!\n");
        return NULL;
    }

    date = (DateP)malloc(sizeof(Date));
    if (!date) {
        perror("Date allocation failed!\n");
        return NULL;
    }
    status = sscanf(str, "%d-%d-%d",
        &date->year,
        &date->month,
        &date->day
    );

    if (status != 3) {
        printf("Invalid date \"%s\", should be in format YYYY-MM-DD!\n", str);
        free(date);
        return NULL;
    }

    return date;
}

int DateToString(char* destination, DateP date) {
    if (!destination) {
        printf("Destination string is null!\n");
        return STRING_DESTINATION_NULL;
    }

    if (!date) {
        sprintf(destination, "-");
        return EXIT_SUCCESS;
    }
    sprintf(destination, "%04d-%02d-%02d", date->year, date->month, date->day);

    return EXIT_SUCCESS;
}

int PrintDate(DateP date) {
    char dateAsString[MAX_DATE_AS_STRING] = { 0 };

    DateToString(dateAsString, date);
    printf(dateAsString);

    return EXIT_SUCCESS;
}

int Datecmp(DateP date1, DateP date2) {
    int result = date1->year - date2->year;

    if (result == 0) {
        result = date1->month - date2->month;

        if (result == 0)
            result = date1->day - date2->day;
    }

    return result;
}

bool IsDateInsideOfRange(DateP date, DateP from, DateP to) {
    return Datecmp(date, from) >= 0 && Datecmp(date, to) <= 0;
}

//***********************

DateP CreateDateFromNumbers(int year, int month, int day) {
    DateP date = NULL;

    date = (DateP)malloc(sizeof(Date));
    if (!date) {
        perror("Date allocation failed!\n");
        return NULL;
    }
    date->year = year;
    date->month = month;
    date->day = day;

    return date;
}

