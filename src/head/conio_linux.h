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

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/**
 * Leert den Inhalt der Konsole
 */
void clrscr() {
	printf("\e[1;1H\e[2J");
}

/**
 * Setzt den Cursor auf eine bestimmte Bildschirmposition
 * @param int X-Wert
 * @param int Y-Wert
 */
void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y, x);
}

/**
 * Wartet auf eine Tastatureingabe und gibt den entsprechenden Keycode zurück
 * @return int Keycode
 */
int getch() {
	int ch;
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

/**
 * Wartet auf eine Tastatureingabe, gibt den Keycode zurück und zeigt die Taste auf dem Bildschirm
 * @return int Keycode
 */
int getche() {
	int c = getch();
	putchar(c);
	return c;
}
