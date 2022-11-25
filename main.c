#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6262)

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <string.h>

enum ColorType {
	BLACK,  	//0
	darkBLUE,	//1
	Dark_Green,	//2
	darkSkyBlue, //3
	DarkRed,  	//4
	DarkPurple,	//5
	DarkYellow,	//6
	GRAY,		//7
	DarkGray,	//8
	BLUE,		//9
	GREEN,		//10
	SkyBlue,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;

void setWindowSize(int cols, int lows);
void gotoxy(int x, int y);
void clear();

void textColor(int colorCode);
void hideCS();

int getColorBit(int background, int bright, int red, int green, int blue);

void closeTab(int level, int height, int weight, char house[30], char status[30]);

void printTitle();
int processInput();
int processTutorial();
int processMovePlace();

int makeNextTutorial();
int ingameStart();

int checkWall(int a);
void writeGj();

int chapter1();
int chapter2();
int chapter3();


extern int COLS;
extern int LOWS;
extern int COLS = 50;
extern int LOWS = 20;

int first_gj= 0;
int count = 0;

void setWindowSize(int cols, int lows) {
	char buffer[128];

	COLS = cols;
	LOWS = lows;

	sprintf(buffer, "mode con:cols=%d lines=%d", cols, lows);

	system(buffer);
}

void gotoxy(int x, int y) {
	// 실행할 프로그램의 기본 출력 장치 (console의 핸들을 가지고 올 것)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };

	// 커서 위치 바꾸기
	SetConsoleCursorPosition(hOut, pos);
}

void clear() {
	unsigned long dw;
	COORD pos = { 0, 0 };

	FillConsoleOutputCharacter(
		GetStdHandle(STD_OUTPUT_HANDLE), ' ', COLS * LOWS, pos, &dw
	);
	FillConsoleOutputAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), getColorBit(0, 1, 1, 1, 1), COLS * LOWS, pos, &dw
	);
	gotoxy(0, 0);
	textColor(getColorBit(0, 1, 1, 1, 1));
}

void textColor(int colorCode) {
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		colorCode
		// 앞 네 비트는 순서대로 배경색, 글씨색 비트임
	);
}

void hideCS() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int getColorBit(int background, int bright, int red, int green, int blue) {
	return (
		bright << 3 |
		red << 2 |
		green << 1 |
		blue
		) << background * 4;
}

void closeTab(int level, int height, int weight, char house[30], char status[30]) {
	FILE* fp;
	fp = fopen("userInfo.txt", "w");

	fprintf(fp, "%d\n", level);
	fprintf(fp, "%d\n", height);
	fprintf(fp, "%d\n", weight);
	fprintf(fp, "%s\n", house);
	fprintf(fp, "%s\n", status);

	fclose(fp);
}

void printTitle() {
	printf(".----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n");
	printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf("| |    ______    | || |      __      | || | ____    ____ | || |     _____    | || |      __      | |\n");
	printf("| |  .' ___  |   | || |     /  \\     | || ||_   \\  /   _|| || |    |_   _|   | || |     /  \\     | |\n");
	printf("| | / .'   \\_|   | || |    / /\\ \\    | || |  |   6\\/   |  | || |      | |     | || |    / /\\ \\    | |\n");
	printf("| | | |    ____  | || |   / ____ \\   | || |  | |\\  /| |  | || |   _  | |     | || |   / ____ \\   | |\n");
	printf("| | \\ `.___]  _| | || | _/ /    \\ \\_ | || | _| |_\\/_| |_ | || |  | |_' |     | || | _/ /    \\ \\_ | |\n");
	printf("| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || |  `.___.'     | || ||____|  |____|| |\n");
	printf("| |              | || |              | || |              | || |              | || |              | |\n");
	printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n");
}

int processInput() {
	if (kbhit()) {
		char c = getch();
		if (c == ' ') {
			makeNextTutorial();
		}
	}
	return 0;
}

int processTutorial() {
	if (kbhit()) {
		char c = getch();
		if (c == ' ') {
			return 1;
		}
	}
	return 0;
}

int makeNextTutorial() {
	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 감자밭");
	int exit;

	gotoxy(2, 4);
	printf("스페이스 눌러서 스토리 보기...\n\n");
	char list[1000][1000] = {
		"기원전 4,000년...\n\n",
		"병점의 작은 감자밭에서 한 아이가 태어난다.\n\n",
		"그의 이름은 석찬우...\n\n",
		"태어날 때부터 감자를 캐야하는 운명이다.\n\n",
		"과연 감자를 많이 캐 감자의 왕이 될 수 있을까?\n\n"
	};
	while (1) {
		exit = processTutorial();
		if (exit == 1) {
			if (count == 5) {
				Sleep(100);
				ingameStart();
			}
			gotoxy(2, 4 + ((count + 2) * 2));
			for (int j = 0; j < sizeof(list[count]) / sizeof(char); j++) {
				printf("%c", list[count][j]);
			}
			count++;
		}
	}
}

int now_x, now_y;

int processMoveKey() {
	if (kbhit()) {
		char c = getch();
		switch (c) {
		case 'D':
			return 1;
		case 'A':
			return 2;
		case 'W':
			return 3;
		case 'S':
			return 4;
		case 'd':
			return 1;
		case 'a':
			return 2;
		case 'w':
			return 3;
		case 's':
			return 4;
		}
	}
	return 0;
}

int isWall() {
	// 좌표값으로 벽인지 판단하기
}

char textInfo[100][100] = {
	"아래 보이는 게 당신입니다. WASD로 움직여서 감자를 먹어보세요. (0/4)",
	"다음 감자를 먹어보세요. (1/4)",
	"다음 감자를 먹어보세요. (2/4)",
	"다음 감자를 먹어보세요. (3/4)"
};

int chapter1() {
	
	int exit;
	now_x = 2;
	now_y = 7;
	gotoxy(now_x, now_y);

	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 찬우네 텃밭");

	gotoxy(30, 1);
	printf("1 - 집으로 들어가기");

	gotoxy(50, 1);
	printf("2 - 마트에 가기");

	while (1) {
		exit = processMoveKey();
		switch (exit) {
		case 1:
			now_x += 2; break;
		case 2:
			now_x -= 2; break;
		case 3:
			now_y -= 1; break;
		case 4:
			now_y += 1; break;
		case 5:
			break;
		case 6:
			break;
		}

	}
}


int chapter2() {
	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 찬우네 집");

	gotoxy(30, 1);
	printf("1 - 텃밭으로 나가기");

	gotoxy(50, 1);
	printf("2 - 마트에 가기");
}


int chapter3() {
	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 편의점 포도씨유");

	gotoxy(30, 1);
	printf("1 - 집으로 들어가기");

	gotoxy(50, 1);
	printf("2 - 텃밭으로 나가기");
}

int processMovePlace() {
	if (kbhit()) {
		char c = getch();
		switch (c) {
		case 'D':
			return 1;
		case 'A':
			return 2;
		case 'W':
			return 3;
		case 'S':
			return 4;
		case 'd':
			return 1;
		case 'a':
			return 2;
		case 'w':
			return 3;
		case 's':
			return 4;
		case '1':
			return 5;
		case '2':
			return 6;
		}
	}
	return 0;
}

int ingameStart() {

	int exit;

	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 찬우네 집");

	gotoxy(2, 4);
	for (int i = 0; i < 100; i++) {
		printf("%c", textInfo[first_gj][i]);
	}

	writeGj();

	now_x = 2;
	now_y = 7;
	gotoxy(2, 7);

	hideCS();
	textColor(GRAY);

	printf("◎");

	while (1) {
		exit = processMoveKey();
		if (now_x == 70 && now_y == 20) {
			if (first_gj == 0) {
				first_gj += 1;
				ingameStart();
			}
		}
		else if (now_x == 20 && now_y == 14) {
			if (first_gj == 1) {
				first_gj += 1;
				ingameStart();
			}
		}
		else if (now_x == 80 && now_y == 16) {
			if (first_gj == 2) {
				first_gj += 1;
				ingameStart();
			}
		}
		else if (now_x == 20 && now_y == 26) {
			if (first_gj == 3) {
				chapter1();
				return 0;
			}
		}
		gotoxy(2, 30);
		switch (exit) {
		case 1:
			checkWall(1); break;
		case 2:
			checkWall(2); break;
		case 3:
			checkWall(3); break;
		case 4:
			checkWall(4); break;
		}
	}
}

void writeGj() {
	textColor(YELLOW);

	if (first_gj == 0) {
		gotoxy(70, 20);
	}
	else if (first_gj == 1) {
		gotoxy(20, 14);
	}
	else if (first_gj == 2) {
		gotoxy(80, 16);
	}
	else if (first_gj == 3) {
		gotoxy(20, 26);
	}
	printf("▣");
}

int checkWall(int a) {
	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 찬우네 집");

	gotoxy(2, 4);
	for (int i = 0; i < 100; i++) {
		printf("%c", textInfo[first_gj][i]);
	}

	writeGj();

	hideCS();
	textColor(GRAY);

	switch (a) {
		case 1:
			now_x += 2; break;
		case 2:
			now_x -= 2; break;
		case 3:
			now_y -= 1; break;
		case 4:
			now_y += 1; break;
	}
	gotoxy(now_x, now_y);
	printf("◎");

	return 1;
}

struct SeokChanwoo {
	int level;
	int height;
	int weight;
	char house[30];
	char status[30];
}user;

struct Status {
	int year;
	int month;
	int day;
	int weather;
}today;

int main() {
	int exit;
	gotoxy(0, 18);
	struct SeokChanwoo user = { 1, 180, 50, "병점역", "안녕하세요" };
	setWindowSize(100, 30);
	printTitle();

	gotoxy(40, 26);
	printf_s("스페이스 눌러 시작하기");

	while (1) {
		exit = processInput();
		if (exit == 1) {
			break;
		}
	}
	ingameStart();
	closeTab(user.level, user.height, user.weight, user.house, user.status);
	return 0;
}
