#pragma once

#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define getch() _getch()
#define getche() _getche()
#define sleep(x) Sleep(x)

void randomize() {
	srand(time(NULL));
}

int random(int x) {
	return rand() % x;
}

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void clrscr() {
	system("cls");
}

