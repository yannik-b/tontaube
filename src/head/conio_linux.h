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
