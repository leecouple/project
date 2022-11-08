#include "tools.h"

struct SeockChanwoo {
	int level;
	int height;
	int weight;
	char house[30];
	char status[30];
}user;

int main() {
	struct SeockChanwoo user = { 1, 180, 50, "병점역", "안녕하세요" };
	closeTab(user.level, user.height, user.weight, user.house, user.status);
	return 0;
}
