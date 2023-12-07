#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
int leap_year(int year);
int total_date(int year, int month);
int month_date(int year, int month);
int start_day(int year, int month);
void print_calender(int year, int month);
int print_class_list(void);
void print_color_changed_calender(int year, int month, int date);
int print_class_list(void);
int hw_date(void);
char* create_file(int year, int month, int date);
void write_hw(int year, int month, int date, char* filename, struct Homework* result);
void print_hw(char* filename);
void print_color_changed_calender(int year, int month, int date2);

#define MAX 1000
#define SIZE 1000

struct Homework 
{
	char hw_name[SIZE];
	char hw[SIZE];
};

int main(void)
{
	int year, month;
	printf("년도: ");
	scanf_s("%d", &year);
	printf("과제를 입력할 달을 입력하세요 : ");
	scanf_s("%d", &month);
	printf("과제를 입력할 일을 입력하세요 : ");
	int date = hw_date();

	print_calender(year, month);
	print_class_list();
	printf("\n\n\n");


	char* filename = create_file(year,month, date);

	struct Homework result;

	write_hw(year, month, date, filename, &result);
	printf("\n\n\n");
	print_color_changed_calender(year, month, date);
	print_hw(filename);

	free(filename);

	return 0;
}

int leap_year(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0))
		return 1;
	else
		return 0;
}

int total_date(int year, int month)
{
	int total = 0;
	for (int i = 1800; i < year; i++) {
		if (leap_year(i))
			total += 366;
		else
			total += 365;
	}
	for (int i = 1; i < month; i++)
		total = total + month_date(year, i);
	return total;
}

int month_date(int year, int month)
{
	if (leap_year(year))
	{
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: return 31;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
		case 2: return 29;
		}
	}
	else
	{
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: return 31;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
		case 2: return 28;
		}
	}
}

int start_day(int year, int month)
{
	int startday = 3;
	int total = total_date(year, month);
	return (startday + total) % 7;
}

void print_calender(int year, int month)
{
	printf("%d년 %d월\n", year, month);
	printf("-----------------------------\n");
	printf(" Sun Mon Tue Wed Thu Fri Sat\n");

	int startday = start_day(year, month);
	int count = 0, i;

	for (i = 0; i < startday; i++)
	{
		printf("    ");
		count++;
	}

	int date = month_date(year, month);

	for (i = 1; i <= date; i++)
	{
		printf("%4d", i);
		count++;
		if (count % 7 == 0)
			printf("\n");
	}

	printf("\n\n\n");

}

int print_class_list(void)
{
	FILE* fp = fopen("class_list.txt", "r");

	if (fp != NULL)
	{
		char line[MAX];
		while (fgets(line, MAX, fp) != NULL)
		{
			printf("%s", line);
		}
		fclose(fp);
	}
	else
	{
		return -1;
	}
	return 0;
}

int hw_date(void)
{
	int date;
	do
	{
		scanf_s("%d", &date);
		getchar();
	} while (date < 1 || date >32);
	return date;
}

char* create_file(int year, int month, int date) 
{
	char* filename = (char*)malloc(SIZE); // 동적 메모리 할당

	if (filename == NULL) {
		// 메모리 할당 실패
		fprintf(stderr, "메모리 할당 실패\n");
		exit(EXIT_FAILURE);
	}

	// 파일명 생성
	snprintf(filename, SIZE, "%d-%d-%d.txt", year, month, date);

	return filename;
}

void write_hw(int year, int month, int date, char* filename, struct Homework* result) 
{
	FILE* fp = fopen(filename, "a+");

	printf("수업 이름을 입력하세요 : ");
	fgets(result->hw_name, sizeof(result->hw_name), stdin);
	fflush(stdin);

	printf("과제 내용을 입력하세요: ");
	fgets(result->hw, sizeof(result->hw), stdin);
	fflush(stdin);

	fprintf(fp, "%s %s", result->hw_name, result->hw);
	fclose(fp);
}

void print_hw(char* filename) 
{
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(EXIT_FAILURE);
	}

	struct Homework myHomework;

	// 파일에서 데이터 읽어오기
	while (fscanf(fp, "%s %s", myHomework.hw_name, myHomework.hw) == 2) {
		// 읽어온 데이터 출력
		printf("수업 이름: %s\n", myHomework.hw_name);
		printf("과제 내용: %s\n", myHomework.hw);
	}

	fclose(fp);
}

void print_color_changed_calender(int year, int month, int date2)
{
	int colored_date = date2;
	printf("%d년 %d월\n", year, month);
	printf("-----------------------------\n");
	printf(" Sun Mon Tue Wed Thu Fri Sat\n");

	int startday = start_day(year, month);
	int count = 0, i;

	for (i = 0; i < startday; i++)
	{
		printf("    ");
		count++;
	}

	int date = month_date(year, month);

	for (i = 1; i <= date; i++)
	{
		if (i == colored_date)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%4d", i);
			count++;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else
		{
			printf("%4d", i);
			count++;
		}
		if (count % 7 == 0)
			printf("\n");
	}

	printf("\n\n\n");

}