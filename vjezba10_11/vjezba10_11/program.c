/*
10. Napisati program koji cita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih drzava. 
Uz ime drzave u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze 
gradovi pojedine drzave. Svaka datoteka koja predstavlja drzavu sadrzi 
popis gradova u formatu naziv_grada, broj_stanovnika.

a) Potrebno je formirati sortiranu vezanu listu drzava po nazivu. 
Svaki cvor vezane liste sadrzi stablo gradova 
sortirano po broju stanovnika, zatim po nazivu grada.

b) Potrebno je formirati stablo drzava sortirano po nazivu.
Svaki cvor stabla sadrzi vezanu listu gradova 
sortiranu po broju stanovnika, zatim po nazivu grada.

Nakon formiranja podataka potrebno je ispisati drzave i gradove 
te omoguciti korisniku putem tastature 
pretragu gradova odredene drzave 
koji imaju broj stanovnika veci od unosa natastaturi.


11. Prepraviti zadatak 10 na nacin da se formira hash tablica drzava.
Tablica ima 11 mjesta, a funkcija za preslikavanje kljuc racuna 
da se zbraja ASCII vrijednost prvih pet slova drzave zatim
racuna ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice.
Drzave s istim kljucem se pohranjuju u vezanu listu sortiranu po nazivu države.
Svaki cvor vezane liste sadrzi stablo gradova 
sortirano po broju stanovnika, zatim po nazivu grada.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int userChoosesTask();

int main() {

	while (true) 
	{
		system("cls");
		switch (userChoosesTask()) 
		{
			case 1:
				system("cls");
				execute_task10a();
				system("pause");
				break;

			case 2:
				system("cls");
				execute_task10b();
				system("pause");
				break;

			case 3:
				//task11();
				printf("\nTask 11 in progress...\n\n");
				system("pause");
				break;

			case 4:
				system("cls");
				printf(
					"====================================================================\n"
					"\n\t\tYou have exited the application!\t\n\n"
					"====================================================================\n");
			return EXIT_SUCCESS;

			default:
				printf(
					"====================================================================\n"
					"\nYour choice is invalid.\n"
					"Please enter valid number for certain choice.\n"
					"\nPress enter to continue app execution.\n"
					"====================================================================\n");
				system("pause");
		}
		system("cls");
	}
	return EXIT_SUCCESS;
}

int userChoosesTask() 
{
	int choice = 0;
	printf(
		"=========================================================================\n"
		"\t\t\t\tMENU\n"
		"=========================================================================\n"
		"\n\t\t ________________________________"
		"\n\t\t|                                |"
		"\n\t\t|        Enter a number :        |"
		"\n\t\t|                                |"
		"\n\t\t|    1 - Execute task 10 a)      |"
		"\n\t\t|    2 - Execute task 10 b)      |"
		"\n\t\t|    3 - Execute task 11         |"
		"\n\t\t|    4 - Exit the application    |"
		"\n\t\t|                                |"
		"\n\t\t|________________________________|"
		"\n\n=========================================================================\n");

	printf("Your choice: ");
	scanf("%d", &choice);

	return choice;
}

/*
	FURTHER IMPROVEMENT:
	_________________________________________________________________________________________
	* basically works, in some cases occurs error: read access violation
	  -> need to check memory addresses and fix the issue
	_________________________________________________________________________________________
    * bug in 10 b), file: state_tree.c, function: 'PrintStatesTree'
	
	when printing existing countries (tree structure) 
	value of root node is also printed, value equals an empty string ("")
	and one symbol "> " extra before thatempty string,
	need to implement logic that would be correct for a recursive function
	_________________________________________________________________________________________
*/