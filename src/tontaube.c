#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mywait.h>

#if __linux__
#include "conio_linux.h"
#elif _WIN32 || _MSC_VER || __MINGW32__
#include "conio_win.h"
#elif __TURBOC__ || __BORLANDC__
#include <conio.h>
#endif

#define TRUE 1
#define FALSE 0
#define KEY_FIRE ' '
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

// [Globale Variablen]
int pos_fk_x, pos_fk_y;    			   		// Position des Fadenkreuzes
int pos_tt_x, pos_tt_y;				   		// Aktuelle Position der Tontaube
int ofs_x=4, ofs_y=3, siz_x=74, siz_y=21; 	// Größe und Position des Spielfeldes
int level=1, schuesse=7;

// [Funktionsprototypen]
void resetParameter();
void resetBildschirm();
int bewegeFadenkreuz();
void zeichneFadenkreuz();
void zeichneTontaube();
void zeichneBildschirm();
void bewegeTontaube();
int feuern();
void schreibeMeldung();
void schreibeSpielMeldung(char*, char*);


/**
 * Setzt die Positionen von Fadenkreuz und Tontaube nach einer Runde zurück
 */
void resetParameter() {
	pos_fk_x = 4;	// Position des Fadenkreuzes
	pos_fk_y = 4;
	pos_tt_x = 14;  // Position der Tontaube
	pos_tt_y = 13;
	schuesse = 7;
}

/**
 * Spielfeld leeren und Tontaube und Fadenkreuz neu zeichnen
 */
void resetBildschirm() {
	int x, y;
	for (y=0; y < siz_y; y++) {
    	gotoxy(ofs_x, ofs_y + y);
		for (x=0; x < siz_x; x++) {
			printf(" ");
        }
	}
	zeichneTontaube();
	zeichneFadenkreuz();
}

/**
 * Bewegt das Fadenkreuz, wenn W/A/S/D gedrückt
 * <p>Wenn SPACE gedrückt, führe feuern() aus</p> 
 * @return boolean Bewegung durchgeführt / Taste gedrückt
 */
int bewegeFadenkreuz() {
	int done = FALSE;
	if(kbhit()) {
    	done = TRUE;
		switch (getch()) {
			case KEY_FIRE:
				done = feuern() / -1;  // Bei -1 wird zum nächsten Level gewechselt
				break;
			case KEY_UP:
				if (pos_fk_y > 2) pos_fk_y--;
				break;
			case KEY_DOWN:
				if (pos_fk_y < (siz_y-3)) pos_fk_y++;
				break;
			case KEY_LEFT:
				if (pos_fk_x > 4) pos_fk_x-=2;
				break;
			case KEY_RIGHT:
				if (pos_fk_x < (siz_x-4)) pos_fk_x+=2;
				break;
			default:
            	done=FALSE;
		}
		if (done==TRUE) {
			resetBildschirm();
			zeichneFadenkreuz();
			zeichneTontaube();
		}
	}
	return done;
	
}

/**
 * Zeichnet das Fadenkreuz auf aktueller Position
 * @return boolean TRUE
 */
void zeichneFadenkreuz() {
	int x = ofs_x + pos_fk_x - 3;
    int y = ofs_y + pos_fk_y;
	gotoxy(x, y-2);
	printf("*******");
	gotoxy(x, y-1);
	printf("*     *");
	gotoxy(x, y);
	printf("*  +  *");
	gotoxy(x, y+1);
	printf("*     *");
	gotoxy(x, y+2);
	printf("*******");
}

/**
 * Zeichnet die Tontaube auf aktueller Position
 * @return boolean TRUE
 */
void zeichneTontaube() {
	gotoxy(ofs_x + pos_tt_x - 1, ofs_y + pos_tt_y);
    printf("~*~");
}

/**
 * Zeichnet den Rahmen für das Spielfeld
 * @return boolean TRUE
 */
void zeichneBildschirm() {
	int i;
	char s[2]="°"; // Zeichen für die Rahmendarstellung
	// Horizontale Linie über Spielfeld zeichnen
	gotoxy(ofs_x-1, ofs_y-1);
	for (i=0; i <= siz_x+1; i++) {
		printf(s);
	}         
	// Horizontale Linie unter Spielfeld zeichnen
	gotoxy(ofs_x-1, ofs_y+siz_y);
	for (i=0; i <= siz_x+1; i++) {
		printf(s);
	}
	// Vertikale Linie links und rechts neben Spielfeld zeichnen
	for (i=0; i <= siz_y; i++) {
		gotoxy(ofs_x-1, ofs_y+i);
		printf(s);
		gotoxy(ofs_x+siz_x, ofs_y+i);
		printf(s);
	}
}                 

/**
 * Bewegt die Tontaube zufällig auf dem Bildschirm
 * @return boolean TRUE
 */
void bewegeTontaube() {
	srand(time(NULL));
	pos_tt_x+=(rand()%3-1);
	pos_tt_y+=(rand()%3-1);  // -1 oder +0 oder +1
	if (pos_tt_x > siz_x) pos_tt_x = siz_x;
	if (pos_tt_x < 0) pos_tt_x = 0;
	if (pos_tt_y > siz_y) pos_tt_y = siz_y;
	if (pos_tt_y < 0) pos_tt_y = 0;
	resetBildschirm();
	zeichneTontaube();
}

/**
 * Prüft auf Position von Tontaube und Fadenkreuz
 * @return boolean getroffen
 */
int feuern() {
	int getroffen = FALSE;
    // Variablen für Schleife auf Minimalwerte setzen
	int fx, fy, t;
	// Schleife für Fadenkreuzpunkte
	for (fx=-2; fx<=2; fx++) {
		for (fy=-1; fy<=1; fy++) {
			// Alle Positionen der Tontaube berücksichtigen
			for (t=-1; t<=1; t++) {
				if ((pos_fk_x + fx) == (pos_tt_x + t) && (pos_fk_y + fy) == pos_tt_y) {
					getroffen = TRUE;
				}
            }
        }
	}
	schuesse--;
    schreibeMeldung();
	return getroffen;
}

void schreibeMeldung() {
	gotoxy(1,1);
	printf("Level %2i von 10 | noch %1i Schüsse übrig", level, schuesse);
}

void schreibeSpielMeldung(char* headline, char* text) {
	clrscr();
	gotoxy(1,2);
	printf(" *********************************************************\n");
	printf(" * #####   ###   #   #  #####    #    #   #  ###   ##### *\n");
	printf(" *   #    #   #  ##  #    #     # #   #   #  #  #  #     *\n");
	printf(" *   #    #   #  # # #    #    #   #  #   #  ###   ###   *\n");
	printf(" *   #    #   #  #  ##    #    # # #  #   #  #  #  #     *\n");
	printf(" *   #     ###   #   #    #    #   #   ###   ###   ##### *\n");
	printf(" *********************************************************");
	gotoxy(12,10);
	printf(headline);
    gotoxy(12,12);
	printf(text);
	getch();
	gotoxy(1,2);
	int i;
	for (i=0; i<7; i++) {
		printf("                                                          \n");
	}
}

void main() {
	schreibeSpielMeldung("WILLKOMMEN", "Drücke Enter um zu starten");
	int play=TRUE; // Wenn Level erfolglos beendet, wird diese auf FALSE gesetzt => Spiel endet
	int durchlauf;
	// einzelne Levels

	while(level < 11 && play == TRUE) {
		durchlauf=1;
		resetParameter();
        resetBildschirm();
		zeichneBildschirm();
		schreibeMeldung();
        while (schuesse > 0 && schuesse < 100) {
			mywait(1);
			if(durchlauf == 10) {   // Alle 10 Durchläufe Tontaube bewegen
				bewegeTontaube();
        	    durchlauf = 1;
			}
			if (bewegeFadenkreuz() == -1) {
				// Wenn Taube getroffen, setze schuesse auf 999 um nächstes Level zu erreichen
                schuesse=999;
			}
			durchlauf++;
		}
		if (schuesse==0) {
			play=FALSE;
            schreibeSpielMeldung("GAME OVER", "Du hast die Taube nicht mit deinen 7 Schüssen getroffen");
		}
		else {
			schuesse=7;
			level++;
        }
	}
    if (play) {
		schreibeSpielMeldung("HERZLICHEN GLÜCKWUNSCH", "Du hast Tontauben-Schießen durchgespielt");
    }
}
