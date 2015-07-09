#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void clrscr() {
	printf("\e[1;1H\e[2J");
}

void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y, x);
}

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

int getche() {
	int c = getch();
	putchar(c);
	return c;
}
