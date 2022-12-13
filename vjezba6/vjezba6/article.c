#define _CRT_SECURE_NO_WARNINGS
#include "article.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTICLE_AS_STRING (1024)

int InitializeArticle(ArticleP article) {
    article->count = 0;
    article->price = 0.0f;
    memset(article->name, 0, MAX_ARTICLE_NAME);
    article->next = NULL;

    return EXIT_SUCCESS;
}

ArticleP CreateArticleFromString(char* str) {
    ArticleP article = NULL;
    int status = 0;

    if (!str) {
        printf("String passed as null to create article!\n");
        return NULL;
    }

    article = (ArticleP)malloc(sizeof(Article));
    if (!article) {
        perror("Article allocation failed!\n");
        return NULL;
    }
    InitializeArticle(article);
    status = sscanf(str, "%s %d %f",
        &article->name,
        &article->count,
        &article->price
    );

    if (status != 3) {
        printf("Invalid article \"%s\", should be in format - <name> <count> <price>!\n", str);
        free(article);
        return NULL;
    }

    return article;
}

int ArticleToString(char* destination, ArticleP article) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return STRING_DESTINATION_NULL;
    }
    if (!article) {
        sprintf(destination, "##INVALID ARTICLE");
        return STRING_NOT_VALID;
    }
    sprintf(destination, "%s %d %.02f", article->name, article->count, article->price);

    return EXIT_SUCCESS;
}

int PrintArticle(ArticleP article) {
    char articleAsString[MAX_ARTICLE_AS_STRING] = { 0 };

    ArticleToString(articleAsString, article);
    printf(articleAsString);

    return EXIT_SUCCESS;
}

ArticleP FindArticleByName(ArticleP head, char* name) {
    ArticleP article = NULL;

    for (article = head; article != NULL; article = article->next)
        if (strcmp(article->name, name) == 0)
            return article;

    return NULL;
}

int DeleteArticleAfter(ArticleP position) {
    ArticleP toDelete = position->next;

    if (!toDelete)
        return EXIT_SUCCESS;

    position->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllArticles(ArticleP head) {
    while (head->next)
        DeleteArticleAfter(head);

    return EXIT_SUCCESS;
}

int InsertArticleAfter(ArticleP position, ArticleP article) {
    article->next = position->next;
    position->next = article;

    return EXIT_SUCCESS;
}

int InsertArticleSorted(ArticleP head, ArticleP article) {
    ArticleP position = head;

    while (position->next != NULL && strcmp(position->next->name, article->name) < 0)
        position = position->next;

    InsertArticleAfter(position, article);

    return EXIT_SUCCESS;
}