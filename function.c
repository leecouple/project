#include "tools.h" 

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