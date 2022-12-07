#ifndef DATE_H
#define DATE_H
#include "errors.h"
#include <stdbool.h>

#define YEAR_STRING_LENGTH (4)           // 1999
#define DAY_STRING_LENGTH (2)            // 08
#define MONTH_STRING_LENGTH (2)          // 12
#define DASH_LENGTH (1)                  // -
#define NULL_TERMINATING_CHAR_LENGTH (1) // \0
#define MAX_DATE_AS_STRING (YEAR_STRING_LENGTH + DASH_LENGTH + MONTH_STRING_LENGTH + DASH_LENGTH + DAY_STRING_LENGTH + NULL_TERMINATING_CHAR_LENGTH)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int year;
    int month;
    int day;
} Date;

DateP CreateDateFromString(char* str);
int DateToString(char* destination, DateP date);
int PrintDate(DateP date);
int Datecmp(DateP date1, DateP date2);
bool IsDateInsideOfRange(DateP date, DateP from, DateP to);

#endif