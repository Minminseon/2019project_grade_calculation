#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct student {
	int number;
	char name[20];
	double total;
	char grade;
	int ranking;
} Student;

void menu() {
	printf("==============[Grade Calculation Program]==============\n");
	printf("\n");
	printf("   1. All student grades\n");
	printf("   2. Search for student ID\n");
	printf("   3. End\n");
	printf("\n");
	printf(" > ");
}

void print_student(Student* sp, int menu) {
	int i;
	if (menu == 1) {
		printf("\n");
		printf(" STUDENT ID\tNAME\t  CORE\t GRADE\tRANK\n");
		for (i = 0; i < 15; i++) {
			printf("  %d \t%s\t  %.2lf\t%4c %6d\n", sp->number, sp->name, sp->total, sp->grade, sp->ranking);
			sp++;
		}
		printf("\n\n\n");
	}
	else {
		int num;
		printf("The student ID to search for is : ");
		scanf("%d", &num);
		getchar();
		printf("\n");

		for (i = 0; i < 15; i++) {
			if (sp->number == num) {
				printf(" STUDENT ID\tNAME\t  CORE\t GRADE\tRANK\n");
				printf("  %d \t%s\t  %.2lf\t%4c %6d\n", sp->number, sp->name, sp->total, sp->grade, sp->ranking);
				printf("\n\n\n");
				return;
			}
			sp++;

		}
	}

}

int compare(void* st1, void* st2) {
	Student** a = (Student**)st1;
	Student** b = (Student**)st2;

	double num1 = (*a)->total;
	double num2 = (*b)->total;

	if (num1 < num2) return 1;
	if (num1 > num2) return -1;
	return 0;
}

int main() {

	FILE* fp;
	Student std[15] = { 0 };
	int i, j;
	int menu_num;
	int rank = 1;

	fp = fopen("C:\\std_info.txt", "r");		// 파일 경로 입력 , 파일 읽어오기

	if (fp == NULL) {
		printf("Failed to read the information.\n");
		return 0;
	}

	for (i = 0; i < 15; i++) {
		int absence = 0;
		int mid;
		int final;

		fscanf(fp, "%d %s", &std[i].number, std[i].name); // 파일 데이터를 읽어 std[i].number, std[i].name에 저장

		for (j = 0; j < 15; j++) {
			fgetc(fp);	//파일에서 문자 하나하나 읽어내기
			if (fgetc(fp) == '1') absence++;
		}

		fgetc(fp);

		fscanf(fp, "%d %d", &mid, &final);
		std[i].total = (100 - 5 * absence) * 0.2 + mid * 0.4 + final * 0.4;

		if (absence >= 4 || std[i].total < 60) {
			std[i].grade = 'F';
			std[i].ranking = -1;
		}

		fgetc(fp);
	}

	fclose(fp);

	Student* sp[15] = { 0 };

	for (i = 0; i < 15; i++) {
		sp[i] = &std[i];
	}


	qsort(sp, sizeof(sp) / sizeof(sp[0]), sizeof(sp[0]), compare);

	int limit = floor(sizeof(sp) / sizeof(sp[0]) * 0.3); //floor() : 반올림 함수


	for (i = 0; i < limit; i++) {
		if (sp[i]->grade != 'F') {
			sp[i]->grade = 'A';
			sp[i]->ranking = rank++;
		}
		else
			limit++;
	}

	limit = floor(sizeof(sp) / sizeof(sp[0]) * 0.7);
	for (; i < limit; i++) {
		if (sp[i]->grade != 'F') {
			sp[i]->grade = 'B';
			sp[i]->ranking = rank++;
		}
		else limit++;
	}

	for (; i < sizeof(sp) / sizeof(sp[0]); i++) {
		if (sp[i]->grade != 'F') {
			sp[i]->grade = 'C';
			sp[i]->ranking = rank++;
		}
	}

	while (1) {
		menu();
		menu_num = getchar();
		getchar();

		switch (menu_num) {
		case '1': print_student(std, 1); break;
		case '2': print_student(std, 2); break;
		case '3': return 0;
		}
	}

}
