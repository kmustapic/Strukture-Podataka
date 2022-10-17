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

int pronadiBrojStudenata(char nazivDat[]);
Student* AlokacijaMemorije(int brojStudenata,char nazivDat[]);
//int Ispis(int brojStudenata,Student* student);
//int MaxBodovi(int BrojStudenata,Student* student);

int main() {

	char nazivDat[MAX_LINE]="studenti.txt";
	Student* student=NULL;
	int BrStudenata=0;

	BrStudenata=pronadiBrojStudenata(nazivDat);
	student=AlokacijaMemorije(BrStudenata,nazivDat);

	/*for(int i=0;i<BrStudenata;i++) {
		printf("\t%s\t\t%1s\t\t%d\n",student[i].ime,student[i].prezime,student[i].bodovi);
	} */

	//Ispis(BrStudenata,student);

	free(student);

    return 0;
}

int pronadiBrojStudenata(char nazivDat[]) {

	FILE* file=NULL;
	int brojac=0;
	char buffer[MAX_LINE]={0};

	file=fopen(nazivDat,"r");
	if(file==NULL) {
		printf("Greska pri otavarnju datoteke!");
		return -1;
	}

	while(!feof(file)) {
		fgets(buffer,sizeof(buffer),file);
		brojac++;
	}

	fclose(file);

	return brojac;
}

Student* AlokacijaMemorije(int BrStudenata,char nazivDat[]) {

	FILE* file=NULL;
	Student* student=NULL;

	file=fopen(nazivDat,"r");

	if(file==NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	student=(Student*)malloc(BrStudenata*sizeof(Student));

	for(int i=0;i<BrStudenata;i++) {
		fscanf(file," %s %s %d",student[i].ime,student[i].prezime,&student[i].bodovi);
	}

	fclose(file);

	return student;
}