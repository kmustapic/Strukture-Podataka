#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

int InitializeFilter(FilterP filter) {
    filter->from = NULL;
    filter->to = NULL;
    memset(filter->name, MAX_ARTICLE_NAME, 0);

    return EXIT_SUCCESS;
}

FilterP CreateFilter(char* dateFromStr, char* dateToStr, char* articleName) {
    FilterP filter = NULL;

    filter = (FilterP)malloc(sizeof(Filter));
    if (!filter) {
        perror("Filter not allocated!\ n");
        return NULL;
    }
    InitializeFilter(filter);

    filter->from = CreateDateFromString(dateFromStr);
    if (!filter->from) {
        DeleteFilter(filter);
        return NULL;
    }

    filter->to = CreateDateFromString(dateToStr);
    if (!filter->to) {
        DeleteFilter(filter);
        return NULL;
    }
    strcpy(filter->name, articleName);

    return filter;
}

int DeleteFilter(FilterP filter) {
    if (filter->from)
        free(filter->from);

    if (filter->to)
        free(filter->to);

    free(filter);

    return EXIT_SUCCESS;
}
