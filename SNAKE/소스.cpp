#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


void Boarder();
void Food();
void load();
void Print();
void record();
int Score(); 
int Scoreonly();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Delay(long double k);
void Move();
void Bend();
void Up();
void Down();
void Right();
void Left();
void ExitGame();
void RestartGame();
void EndGame();


int length;
int bend_no;
int len;
int life;
char key;

struct coordinate
{
	int x, y, direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500], food, body[30];

int main()
{

	Print(); // 처음 화면 출력

	system("cls");

	load(); // loading 출력

	length = 5; // 머리+몸통 길이 = 5

	head.x = 25; // 처음 머리 x 좌표
	head.y = 20; // 처음 머리 y 좌표

	head.direction = RIGHT; //처음 머리 방향

	Boarder(); // 경계 생성

	Food(); // 음식 생성

	life = 3; // 처음 life 수

	bend[0] = head;

	Move();

	return 0;


}


void Boarder()
{
	system("cls");
	GotoXY(food.x, food.y);
	printf("@");
	int i;
	for (i = 10; i < 71; i++)
	{
		GotoXY(i, 10);
		printf("!");
		GotoXY(i, 30);
		printf("!");
	}
	for (i = 10; i < 31; i++)
	{
		GotoXY(10, i);
		printf("!");
		GotoXY(70, i);
		printf("!");
	}
}

void Food()
{
	if (head.x == food.x && head.y == food.y)
	{
		length++;
		time_t a;
		a = time(0);
		srand(a);
		food.x = rand() % 70;
		if (food.x <= 10)
			food.x += 11;
		food.y = rand() % 30;
		if (food.y <= 10)

			food.y += 11;
	}
	else if (food.x == 0)
	{
		food.x = rand() % 70;
		if (food.x <= 10)
			food.x += 11;
		food.y = rand() % 30;
		if (food.y <= 10)
			food.y += 11;
	}
}

void load()
{
	gotoxy(36, 14);
	printf("L o a d i n g...");
	gotoxy(30, 15);
	//Sleep(5000);
	//printf("%c", "~");
	
}

void Print()
{
	printf("\tWelcome to the mini Snake Game. (press any key to continue)\n");
	getch();
	system("cls");
	printf("\tGame Instructions: \n");
	printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
	printf("\n\nPress any key to play game...");
}

void record()
{
	char changedplname[20], plname[20], cha, c;
	int i, j, px;
	FILE* info;

	info = fopen("record.txt", "a+");


	system("cls");
	printf("Enter your name\n");
	scanf("%[^\n]", plname);

	changedplname[0] = toupper(plname[0]);

	for (i = 1 ; plname[i] != NULL; i++)
	{
		changedplname[i] = tolower(plname[i]);
	}
	i += 1;
	changedplname[i] = toupper(plname[i]);
	for (; plname[i] != '\0'; i++)
	{
		changedplname[i] = plname[i];
	}

	fprintf(info, "Player Name :%s\n", changedplname);

	time_t mytime;
	mytime = time(NULL);
	fprintf(info, "Played Date:%s", ctime(&mytime));
	fprintf(info, "Score:%d\n", px = Scoreonly());
	


	for (i = 0; i <= 50; i++)
		fprintf(info, "%c", '_');
	fprintf(info, "\n");
	fclose(info);
	printf("Wanna see past records press 'y'\n");
	cha = getch();
	system("cls");
	if (cha == 'y')
	{
		info = fopen("record.txt", "r");
		do
		{
			putchar(c = getc(info));
		} while (c != EOF);
	}
	fclose(info);
}



int Score()
{
	int score;
	GotoXY(20, 8);
	score = length - 5;
	printf("SCORE : %d", score);
	GotoXY(50, 8);
	printf("Life : %d", life);
	return score;
}

int Scoreonly()
{
	system("cls");
	return Score();
}

void gotoxy(int x, int y) // 커서 위치 옮기기
{
	COORD coord; // COORD 구조체에 선언된 x y 값 저장
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void GotoXY(int x, int y)
{
	HANDLE a;
	COORD b;
	fflush(stdout);
	b.X = x;
	b.Y = y;
	a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, b);
}

void Delay(long double k)
{
	Score();
	long double i;
	for (i = 0; i <= (10000000); i++);
}


void Move()
{
	int a, i;

	do
	{

		Food();
		fflush(stdin);

		len = 0;

		for (i = 0; i < 30; i++)

		{

			body[i].x = 0;

			body[i].y = 0;

			if (i == length)

				break;

		}

		Delay(length);

		Boarder();

		if (head.direction == RIGHT)

			Right();

		else if (head.direction == LEFT)

			Left();

		else if (head.direction == DOWN)

			Down();

		else if (head.direction == UP)

			Up();

		ExitGame();


	} while (GetAsyncKeyState(VK_UP) & 0x8001);


	a = getch();

	if (a == 27) // ascii 27 == esc

	{

		system("cls");

		exit(0);

	}
	key = getch();

	if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN))

	{

		bend_no++;

		bend[bend_no] = head;

		head.direction = key;

		if (key == UP)

			head.y--;

		if (key == DOWN)

			head.y++;

		if (key == RIGHT)

			head.x++;

		if (key == LEFT)

			head.x--;

		Move();

	}

	else if (key == 27)

	{

		system("cls");

		exit(0);

	}

	else

	{

		printf("\a"); // 방향키, esc 제외 누르면 알람 울림

		Move();

	}
}


void Bend()
{
	int i, j;

	for (i = bend_no; i >= 0 && len < length; i--)
	{
		int diff_x = bend[i].x - bend[i - 1].x;
		int diff_y = bend[i].y - bend[i - 1].y;

		if (diff_x == 0)
		{
			int step = (diff_y < 0) ? -1 : 1;

			for (j = 1; j <= abs(diff_y) && len < length; j++)
			{
				body[len].x = bend[i].x;
				body[len].y = bend[i].y + step * j;

				GotoXY(body[len].x, body[len].y);
				printf("*");

				len++;
			}
		}
		else if (diff_y == 0)
		{
			int step = (diff_x < 0) ? -1 : 1;

			for (j = 1; j <= abs(diff_x) && len < length; j++)
			{
				body[len].x = bend[i].x + step * j;
				body[len].y = bend[i].y;

				GotoXY(body[len].x, body[len].y);
				printf("*");

				len++;
			}
		}
	}
}
void Up()
{
	int i;
	for (i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++)
	{
		GotoXY(head.x, head.y + i);
		{
			if (len == 0)
				printf("^");
			else
				printf("*");
		}
		body[len].x = head.x;
		body[len].y = head.y + i;
		len++;
	}
	Bend();
	if (!kbhit())
		head.y--;
}

void Down()
{
	int i;
	for (i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++)
	{
		GotoXY(head.x, head.y - i);
		{
			if (len == 0)
				printf("v");
			else
				printf("*");
		}
		body[len].x = head.x;
		body[len].y = head.y - i;
		len++;
	}

	Bend();
	if (!kbhit())
		head.y++;
}

void Left()
{
	int i;
	for (i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++)
	{
		GotoXY((head.x + i), head.y);
		{
			if (len == 0)
				printf("<");
			else
				printf("*");
		}
		body[len].x = head.x + i;
		body[len].y = head.y;
		len++;
	}
	Bend();
	if (!kbhit())
		head.x--;

}
void Right()
{
	int i;
	for (i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++)
	{
		//GotoXY((head.x-i),head.y);
		body[len].x = head.x - i;
		body[len].y = head.y;
		GotoXY(body[len].x, body[len].y);
		{
			if (len == 0)
				printf(">");
			else
				printf("*");
		}
		/*body[len].x=head.x-i;
		body[len].y=head.y;*/
		len++;
	}
	Bend();
	if (!kbhit())
		head.x++;
}

void ExitGame()
{
	int i, check = 0;

	for (i = 1; i < length; i++) {
		if (body[0].x == body[i].x && body[0].y == body[i].y) {
			check++;
			break;
		}
	}

	if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30) {
		check++;
	}

	if (check > 0) {
		life--;

		if (life > 0) {
			// Restart the game with a new life
			RestartGame();
		}
		else {
			// End the game
			EndGame();
		}
	}
}


void RestartGame() {
	// Reset snake position and direction
	head.x = 25;
	head.y = 20;
	bend_no = 0;
	head.direction = RIGHT;

	// Continue the game
	Move();
}

void EndGame() {
	system("cls");
	printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");

	// Record game information
	record();

	exit(0);
}