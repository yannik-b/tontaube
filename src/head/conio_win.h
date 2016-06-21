/*
Copyright 2015 Yannik Buerkle

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
