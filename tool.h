#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

extern int COLS;
extern int LOWS;

void setWindowSize(int cols, int lows);
void gotoxy(int x, int y);
void clear();

void textColor(int colorCode);

int getColorBit(int background, int bright, int red, int green, int blue);

void closeTab(int level, int height, int weight, char house[30], char status[30]);

char printTitle();

void makeNextTutorial();
