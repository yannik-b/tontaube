#pragma once

#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define getch() _getch()
#define getche() _getche()
#define sleep(x) Sleep(x)

/**
 * Zufallsgenerator initialisieren
 */
void randomize() {
	srand(time(NULL));
}

/**
 * Generiert eine zufällige Ganzzahl
 * @param int Höchstwert
 */
int random(int x) {
	return rand() % x;
}

/**
 * Setzt den Cursor auf eine bestimmte Bildschirmposition
 * @param int X-Wert
 * @param int Y-Wert
 */
void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

/**
 * Leert den Inhalt der Konsole
 */
void clrscr() {
	system("cls");
}

