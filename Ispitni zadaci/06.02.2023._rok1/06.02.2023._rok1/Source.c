#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME_LEN (256)

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int subject1;
	int subject2;
	int subject3;
	double avg;
	StudentP next;
} Student;

// OCJENA 2
StudentP InitializeStud();
int ReadFile(StudentP head, char* file, int whichList);
StudentP CreateStud(char* firstName, char* lastName, int grade, int whichList);
int AddToFront(StudentP head, StudentP new);
int PrintList(StudentP head);
int DeleteList(StudentP head);
StudentP FindStud(StudentP head, char* firstName, char* lastName);
StudentP MergeLists(StudentP head, StudentP toMerge, int whichList);
// OCJENA 3
StudentP MergeLists2(StudentP head, StudentP toMerge, int whichList);
double Avg(StudentP stud);
int Cmp(StudentP head, StudentP new);
int InsertSorted(StudentP head, StudentP new);
int PrintList2(StudentP head);
// OCJENA 4
StudentP FindStud2(StudentP head, char* firstName);
int DeleteStud(StudentP head, StudentP stud);
int DeleteChosenStud(StudentP head);
// OCJENA 5
int GenerateRand(int lower, int upper);
int MoveStudToFront(StudentP head, StudentP toMove);
int MoveToFront(StudentP head);

int main() {
	StudentP head1 = NULL;
	StudentP head2 = NULL;
	StudentP head3 = NULL;
	StudentP headMerge = NULL;
	StudentP headMerge2 = NULL;

	head1 = InitializeStud();
	head2 = InitializeStud();
	head3 = InitializeStud();
	headMerge = InitializeStud();
	headMerge2 = InitializeStud();

	char f1[MAX_NAME_LEN] = "subject1.txt";
	char f2[MAX_NAME_LEN] = "subject2.txt";
	char f3[MAX_NAME_LEN] = "subject3.txt";

	ReadFile(head1, f1, 1);
	ReadFile(head2, f2, 2);
	ReadFile(head3, f3, 3);

	printf("\nPRINT 3 INITIAL LISTS:\n");
	printf("\nLIST 1:\n");
	PrintList(head1);
	printf("\nLIST 2:\n");
	PrintList(head2);
	printf("\nLIST 3:\n");
	PrintList(head3);
	
	MergeLists(headMerge, head1, 1);
	MergeLists(headMerge, head2, 2);
	MergeLists(headMerge, head3, 3);
	printf("\nPRINT MERGED LIST:\n");
	PrintList(headMerge);

	MergeLists2(headMerge2, head1, 1);
	MergeLists2(headMerge2, head2, 2);
	MergeLists2(headMerge2, head3, 3);
	printf("\nPRINT SORTED MERGED LIST:\n");
	PrintList2(headMerge2);

//	DeleteChosenStud(headMerge);

//	MoveToFront(headMerge);

	DeleteList(head1);
	DeleteList(head2);
	DeleteList(head3);
	DeleteList(headMerge);
	DeleteList(headMerge2);
	
	return EXIT_SUCCESS;
}

StudentP InitializeStud() {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (NULL == new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	strcpy(new->firstName, "");
	strcpy(new->lastName, "");
	new->subject1 = 1;
	new->subject2 = 1;
	new->subject3 = 1;
	new->avg = 0.0;
	new->next = NULL;

	return new;
}

int ReadFile(StudentP head, char* file, int whichList) {
	FILE* fp = NULL;
	char firstName[MAX_NAME_LEN] = { 0 };
	char lastName[MAX_NAME_LEN] = { 0 };
	int grade = 1;
	StudentP new = NULL;

	fp = fopen(file, "r");
	if (NULL == fp) {
		printf("\nReading file error!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", lastName, firstName, &grade);
		new = InitializeStud();
		new = CreateStud(firstName, lastName, grade, whichList);
		AddToFront(head, new);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

StudentP CreateStud(char* firstName, char* lastName, int grade, int whichList) {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (!new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	new = InitializeStud();
	strcpy(new->firstName, firstName);
	strcpy(new->lastName, lastName);
	new->next = NULL;

	if (whichList == 1) 
		new->subject1 = grade;
	else if (whichList == 2)
		new->subject2 = grade;
	else if (whichList == 3)
		new->subject3 = grade;

	return new;
}

int AddToFront(StudentP head, StudentP new) {
	StudentP temp = head;
	new->next = temp->next;
	temp->next = new;

	return EXIT_SUCCESS;
}

int PrintList(StudentP head) {
	StudentP temp = head->next;
	while (NULL != temp) {
		printf("\t- %s %s (%d, %d, %d)\n", temp->lastName, temp->firstName, temp->subject1, temp->subject2, temp->subject3);
		temp = temp->next;
	}
	
	return EXIT_SUCCESS;
}

int DeleteList(StudentP head) {
	StudentP temp = NULL;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

StudentP FindStud(StudentP head, char* firstName, char* lastName) {
	StudentP p = head->next;
	while (NULL != p) {
		if (strcmp(p->lastName, lastName) == 0 && strcmp(p->firstName, firstName) == 0)
			return p;
		p = p->next;
	}

	return NULL;
}

StudentP MergeLists(StudentP head, StudentP toMerge, int whichList) {
	StudentP p = NULL;
	StudentP findStud = NULL;

	for (p = toMerge->next; p != NULL; p = p->next) {
		
		if (whichList == 1) {
			if (p->subject1 > 1) {
				findStud = CreateStud(p->firstName, p->lastName, p->subject1, 1);
				AddToFront(head, findStud);
			}
		}

		else if (whichList == 2) {
			if (p->subject2 > 1) {
				findStud = FindStud(head, p->firstName, p->lastName);

				if (NULL != findStud)
					findStud->subject2 = p->subject2;
				else {
					findStud = CreateStud(p->firstName, p->lastName, p->subject2, 2);
					AddToFront(head, findStud);
				}
			}
		}
			
		else if (whichList == 3) {
			if (p->subject3 > 1) {
				findStud = FindStud(head, p->firstName, p->lastName);

				if (NULL != findStud)
					findStud->subject3 = p->subject3;
				else {
					findStud = CreateStud(p->firstName, p->lastName, p->subject3, 3);
					AddToFront(head, findStud);
				}
			}
		}
	}

	return head;
}

double Avg(StudentP stud) {
	double avg = 1. * (stud->subject1 + stud->subject2 + stud->subject3) / 3;
	return avg;
}

int InsertAfter(StudentP head, StudentP new) {
	new->next = head->next;
	head->next = new;

	return EXIT_SUCCESS;
}

//**************
int Cmp(StudentP head, StudentP new) {
	int equal = 0;
	int res = 0;
	
	if (fabs(head->avg - new->avg) < 0.00001)
		equal = 1;
	if ((head->avg < new->avg) || ( equal == 1 && strcmp(head->lastName, new->lastName) < 0))
		res = 1;

	return res;
}
//**************

int InsertSorted(StudentP head, StudentP new) {
	StudentP p = head;
	
	while (NULL != p->next && Cmp(p->next, new) == 1)
		p = p->next;
	InsertAfter(p, new);

	return EXIT_SUCCESS;
}

StudentP MergeLists2(StudentP head, StudentP toMerge, int whichList) {
	StudentP p = NULL;
	StudentP findStud = NULL;

	for (p = toMerge->next; p != NULL; p = p->next) {

		if (whichList == 1) {
			if (p->subject1 > 1) {
				findStud = CreateStud(p->firstName, p->lastName, p->subject1, 1);
				InsertSorted(head, findStud);
			}
		}

		else if (whichList == 2) {
			if (p->subject2 > 1) {
				findStud = FindStud(head, p->firstName, p->lastName);

				if (NULL != findStud)
					findStud->subject2 = p->subject2;
				else {
					findStud = CreateStud(p->firstName, p->lastName, p->subject2, 2);
					InsertSorted(head, findStud);
				}
			}
		}

		else if (whichList == 3) {
			if (p->subject3 > 1) {
				findStud = FindStud(head, p->firstName, p->lastName);

				if (NULL != findStud)
					findStud->subject3 = p->subject3;
				else {
					findStud = CreateStud(p->firstName, p->lastName, p->subject3, 3);
					InsertSorted(head, findStud);
				}
			}
		}
	}

	return head;
}

int PrintList2(StudentP head) {
	StudentP temp = head->next;
	double avg = 0;
	while (NULL != temp) {
		avg = Avg(temp);
		printf("\t- %s %s (%d, %d, %d) -\t\t%.3f\n", temp->lastName, temp->firstName, temp->subject1, temp->subject2, temp->subject3, avg);

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

StudentP FindStud2(StudentP head, char* firstName) {
	StudentP p = head->next;
	while (NULL != p) {
		if (strcmp(p->firstName, firstName) == 0)
			return p;
		p = p->next;
	}

	return NULL;
}


//**********************
int DeleteStud(StudentP head, StudentP stud) {
	StudentP temp = head;
	StudentP toDelete = NULL;

	if (NULL == temp) {
		head = head->next;
		temp->next = NULL;
		free(temp);
	}
	else
		for (temp = head->next; NULL != temp; temp = temp->next) {
			toDelete = temp->next;
			if (strcmp(toDelete->firstName, stud->firstName) == 0) {
				temp->next = temp->next->next;
				toDelete->next = NULL;
				free(toDelete);
			}
		}

	return EXIT_SUCCESS;
}

int DeleteChosenStud(StudentP head) {
	printf("\n\nDelete student(s): NAME\n");
	char* name[MAX_NAME_LEN] = { 0 };
	StudentP t = NULL;
	printf("\nDelete student(s): ");
	scanf("%s", name);
	t = FindStud2(head, name);
//
	printf("****FOUND STUD: %s\n", t->firstName);
//
	if(NULL == t)
		printf("\nStudent with name %s doesn't exist!\n", name);
	else {
		for (t = head->next; t != NULL; t = t->next) {
			if (strcmp(t->firstName, name) == 0) {
				DeleteStud(head, t);
			}
		}
		printf("\nStudent(s) with name: %s successfully deleted!\n");
		printf("LIST AFTER DELETING:\n");
		PrintList(head);
		}

	return EXIT_SUCCESS;
}

int GenerateRand(int lower, int upper) {
	int n;
	n = (rand() % (upper - lower + 1)) + lower;

	return n;
}

int MoveStudToFront(StudentP head, StudentP toMove) {
	StudentP p = NULL;
	p = toMove;
	p->next = head->next;
	head->next = p;
	toMove->next = NULL;
	free(toMove);

	return EXIT_SUCCESS;
}

int MoveToFront(StudentP head) {
	int grade;
	StudentP t = NULL;

	grade = GenerateRand(1, 5);
	printf("\nGENERATED GRADE: %d\n", grade);
	for (t = head->next; NULL != t; t = t->next)
		if (t->subject1 == grade || t->subject2 == grade || t->subject3 == grade)
			MoveStudToFront(head, t);

	printf("\nPRINT FINAL LIST: ");
	PrintList(head);

	return EXIT_SUCCESS;
}