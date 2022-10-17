#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX_NAME 64
#define MAX_LINE 1024

typedef struct
{ 
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bodovi;
	float relBodovi;

} Student;

int pronadiBrojStudenata(char nazivDatoteke[]);
Student* AlokacijaMemorije(int brojStudenata,char dat[]);
int Ispis(int brojStudenata,Student* student);
int MaxBodovi(int BrojStudenata,Student* student);

int main() {

	char NazivDatoteke[MAX_LINE]="studenti.txt";
	int BrojStudenata=0;
	Student* student=NULL;
	
	BrojStudenata=pronadiBrojStudenata(NazivDatoteke);
	student=AlokacijaMemorije(BrojStudenata,NazivDatoteke);
	Ispis(BrojStudenata,student);

	free(student);
    return 0;
}