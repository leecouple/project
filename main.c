#include "tools.h"

struct SeockChanwoo {
	int level;
	int height;
	int weight;
}user;

int main() {
	user.level = 1;
	user.height = 180;
	user.weight = 230;

	closeTab(user.level, user.height, user.weight, "", "");
	return 0;
}