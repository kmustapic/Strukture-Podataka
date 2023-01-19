#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int userPicksTask();

int main() {

	while (true) {
		switch (userPicksTask()) {
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
			printf("\nTask 11 in progress... :)\n");
			break;
		case 4:
			//system("cls");
			printf(
				"====================================================================\n"
				"\n\t\tYou have exited the application!\t\n\n"
				"====================================================================\n");
			//system("pause");
			exit(0);
			break;
		default:
			printf(
				"====================================================================\n"
				"\n Your choice is invalid.\n"
				" Please enter valid number for certain choice.\n"
				"\n Press enter to continue app execution.\n"
				"====================================================================\n");
			system("pause");
		}
		system("cls");
	}
	return EXIT_SUCCESS;
}

int userPicksTask() {

	int choice = 0;
	printf(
		"=================================================================\n"
		"\t\t\t\tMENI\n"
		"=================================================================\n"
		"\n\t\t|Enter a number :                |"
		"\n\t\t|                                |"
		"\n\t\t|    1 to execute task 10 a)     |"
		"\n\t\t|    2 to execute task 10 b)     |"
		"\n\t\t|    3 to execute task 11        |"
		"\n\t\t|    4 to exit the application   |"
		"\n\t\t|________________________________|"
		"\n\n=================================================================\n");

	printf("\n\nYour choice -> ");
	scanf("%d", &choice);

	return choice;
}

