/*
1. Napisati program koji prvo procita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova / max_br_bodova * 100
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NAME 64
#define MAX_LINE 1024

struct _student;
typedef struct _student* StudentP;
typedef struct _student
{
    char name[MAX_NAME];
    char surname[MAX_NAME];
    double score;
} Student;

int CountRows(char fileName[]);
StudentP ReadStudentsFile(char fileName[], int rowsNum);
double FindMaxScore(StudentP students, int rowsNum);
int CompareDoubleNum(double a, double b);
int PrintStudents(StudentP students, int rowsNum, double maxScore);

int main()
{
    int rowsNum = CountRows("./students.txt");
    if (rowsNum <= 0)
    {
        printf("Empty file\n");
        return EXIT_FAILURE;
    }
    StudentP students = NULL;
    students = ReadStudentsFile("./students.txt", rowsNum);
    double maxScore = FindMaxScore(students, rowsNum);
    PrintStudents(students, rowsNum, maxScore);
    free(students);

    return EXIT_SUCCESS;
}

int CountRows(char fileName[])
{
    int counter = 0;
    char buffer[MAX_LINE];
    FILE* fp = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Unable to open file.");
        return EXIT_FAILURE;
    }
    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp);
        counter++;
    }
    counter--;
    fclose(fp);

    return counter;
}

StudentP ReadStudentsFile(char fileName[], int rowsNum)
{
    int status = 0;
    FILE* fp = NULL;
    StudentP students = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Unable to open file.");
        return NULL;
    }
    students = (StudentP)malloc(rowsNum * sizeof(Student));

    for (int i = 0; i < rowsNum; i++)
    status = fscanf(fp, "%s %s %lf", students[i].name, students[i].surname, &students[i].score);
    if (status != 3)
    {
        printf("Not proper file data!\n");
        return NULL;
    }
    fclose(fp);

    return students;
}

double FindMaxScore(StudentP students, int rowsNum)
{
    double max = 0;
    for (int i = 0; i < rowsNum; i++)
        if (!CompareDoubleNum(students[i].score, max))
            if (students[i].score > max)
                max = students[i].score;

    return max;
}

int CompareDoubleNum(double a, double b)
{
    if (abs(a - b) < 1e-9)
        return 1;
    else
        return 0;
}

int PrintStudents(StudentP students, int rowsNum, double maxScore)
{
    printf("NAME\t SURNAME\t ABSOLUTE SCORE\t RELATIVE SCORE\n");
    printf("__________________________________________________________________\n");
    double relativeScore;

    for (int i = 0; i < rowsNum; i++)
    {
        relativeScore = students[i].score / maxScore * 100;
        printf("%s\t %s\t\t %.2lf\t\t %.2lf\n", students[i].name, students[i].surname, students[i].score, relativeScore);
    }

    return EXIT_SUCCESS;
}
