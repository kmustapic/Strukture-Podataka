#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int userPicksTask();

int main() {

	int x = 1;
	while (x) {
		switch (userPicksTask()) {
		case 1:
			execute_task10a();
			break;
		case 2:
			execute_task10b();
			break;
			//case 3:
				//task11();
			printf("You chose to execute task 11");
			//	break;
		case 3:
			x = 0;
			break;
		default:
			printf("Wrong choice! Try again!\r\n");
			break;
		}
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
		"\n\t\t|     1 to execute task 10 a)    |"
		"\n\t\t|     2 to execute task 10 b)    |"
		//"\n\t\t|     3 to execute task 11       |"
		"\n\t\t|________________________________|"
		"\n\n=================================================================\n");

	printf("\n\nYour choice -> ");
	scanf("%d", &choice);

	return choice;
}

