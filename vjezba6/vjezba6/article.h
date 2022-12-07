#ifndef ARTICLE_H
#define ARTICLE_H
#include "errors.h"

#define MAX_ARTICLE_NAME (128)

struct _article;
typedef struct _article* ArticleP;
typedef struct _article {
    char name[MAX_ARTICLE_NAME];
    int count;
    float price;
    ArticleP next;
} Article;

int InitializeArticle(ArticleP article);
ArticleP CreateArticleFromString(char* str);
int ArticleToString(char* destination, ArticleP article);
int PrintArticle(ArticleP article);
ArticleP FindArticleByName(ArticleP head, char* name);
int DeleteArticleAfter(ArticleP position);
int DeleteAllArticles(ArticleP head);
int InsertArticleAfter(ArticleP position, ArticleP article);
int InsertArticleSorted(ArticleP head, ArticleP article);
#endif