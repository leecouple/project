#include "tool.h"

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

	gotoxy(2, 3);
	printf("아래 보이는 게 당신입니다. WASD로 움직여보세요.");

	now_x = 2;
	now_y = 5;
	gotoxy(2, 5);
	
	while (1) {
		exit = processMoveKey();
		switch (exit) {
			case 1:
				gotoxy(now_x + 1, now_y);
				now_x += 1;
			case 2:
				gotoxy(now_x - 1, now_y);
				now_x -= 1;
			case 3:
				gotoxy(now_x, now_y + 1);
				now_y += 1;
			case 4:
				gotoxy(now_x, now_y - 1);
				now_y -= 1;
		}
		Sleep(50);
	}
}
