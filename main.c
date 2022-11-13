#include "tool.h"

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
