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
