#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6262)

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <string.h>

void setWindowSize(int cols, int lows);
void gotoxy(int x, int y);
void clear();

void textColor(int colorCode);

int getColorBit(int background, int bright, int red, int green, int blue);

void closeTab(int level, int height, int weight, char house[30], char status[30]);

void printTitle();
int processInput();
int processTutorial();

int makeNextTutorial();
int ingameStart();

int checkWall(int a);

extern int COLS;
extern int LOWS;

extern int COLS = 50;
extern int LOWS = 20;

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
	printf("| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || |    |_   _|   | || |     /  \     | |\n");
	printf("| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |      | |     | || |    / /\ \    | |\n");
	printf("| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   _  | |     | || |   / ____ \   | |\n");
	printf("| | \ `.___]  _| | || | _/ /    \ \_ | || | _| |_\/_| |_ | || |  | |_' |     | || | _/ /    \ \_ | |\n");
	printf("| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || |  `.___.'     | || ||____|  |____|| |\n");
	printf("| |              | || |              | || |              | || |              | || |              | |\n");
	printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
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

int ingameStart() {
	int exit;

	clear();
	gotoxy(2, 1);
	printf("현재 위치 | 찬우네 집");

	gotoxy(2, 4);
	printf("아래 보이는 게 당신입니다. WASD로 움직여보세요.");

	now_x = 2;
	now_y = 7;
	gotoxy(2, 7);

	while (1) {
		exit = processMoveKey();
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

int checkWall(int a) {
	if ((now_x >= 2 && now_x < 100) && (now_y >= 7 && now_y < 30)) {
		clear();
		gotoxy(2, 1);
		printf("현재 위치 | 찬우네 집");

		gotoxy(2, 4);
		printf("아래 보이는 게 당신입니다. WASD로 움직여보세요.");

		switch (a) {
		case 1:
			now_x += 1; break;
		case 2:
			now_x -= 1; break;
		case 3:
			now_y -= 1; break;
		case 4:
			now_y += 1; break;
		}
		gotoxy(now_x, now_y);
		printf("◎");
		return 1;
	}
	else {
		return 0;
	}
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
