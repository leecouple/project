#include "tool.h"

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
	FILE* fp;
	fp = fopen("title.txt", "r");
	char buffer[3000] = { 0, };

	fread(buffer, 1, 3000, fp);
	printf("%s", buffer);

	fclose(fp);
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
			if (count == 6) {
				Sleep(500);
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
