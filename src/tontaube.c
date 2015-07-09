#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <mywait.h>

#define true 1
#define false 0
#define KEY_FIRE ' '
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

// [Globale Variablen]
int POS_FK_X, POS_FK_Y;    			   		// Position des Fadenkreuzes
int POS_TT_X, POS_TT_Y;				   		// Aktuelle Position der Tontaube
int OFS_X=4, OFS_Y=3, SIZ_X=74, SIZ_Y=21; 	// Gr��e und Position des Spielfeldes
int LEVEL=1, SCHUESSE=7;

// [Funktionsprototypen]
int resetParameter();
int resetBildschirm();
int bewegeFadenkreuz();
int zeichneFadenkreuz();
int zeichneTontaube();
int zeichneBildschirm();
int bewegeTontaube();
int feuern();
int schreibeMeldung();
int schreibeSpielMeldung(char*, char*);


/**
 * Setzt die Positionen von Fadenkreuz und Tontaube nach einer Runde zur�ck
 * @return boolean true
 */
int resetParameter() {
	POS_FK_X = 4;	// Position des Fadenkreuzes
	POS_FK_Y = 4;
	POS_TT_X = 14;  // Position der Tontaube
	POS_TT_Y = 13;
	SCHUESSE = 7;
	return true;
}

/**
 * Spielfeld leeren und Tontaube und Fadenkreuz neu zeichnen
 * @return boolean true
 */
int resetBildschirm() {
	int x, y;
	for (y=0; y < SIZ_Y; y++) {
    	gotoxy(OFS_X, OFS_Y + y);
		for (x=0; x < SIZ_X; x++) {
			printf(" ");
        }
	}
	zeichneTontaube();
	zeichneFadenkreuz();
    return true;
}

/**
 * Bewegt das Fadenkreuz, wenn W/A/S/D gedr�ckt
 * <p>Wenn SPACE gedr�ckt, f�hre feuern() aus</p> 
 * @return boolean Bewegung durchgef�hrt / Taste gedr�ckt
 */
int bewegeFadenkreuz() {
	int done = false;
	if(kbhit()) {
    	done = true;
		switch (getch()) {
			case KEY_FIRE:
				done = feuern() / -1;  // Bei -1 wird zum n�chsten Level gewechselt
				break;
			case KEY_UP:
				if (POS_FK_Y > 2) POS_FK_Y--;
				break;
			case KEY_DOWN:
				if (POS_FK_Y < (SIZ_Y-3)) POS_FK_Y++;
				break;
			case KEY_LEFT:
				if (POS_FK_X > 4) POS_FK_X-=2;
				break;
			case KEY_RIGHT:
				if (POS_FK_X < (SIZ_X-4)) POS_FK_X+=2;
				break;
			default:
            	done=false;
		}
		if (done==true) {
			resetBildschirm();
			zeichneFadenkreuz();
			zeichneTontaube();
		}
	}
	return done;
	
}

/**
 * Zeichnet das Fadenkreuz auf aktueller Position
 * @return boolean true
 */
int zeichneFadenkreuz() {
	int x = OFS_X + POS_FK_X - 3;
    int y = OFS_Y + POS_FK_Y;
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
    return true;
}

/**
 * Zeichnet die Tontaube auf aktueller Position
 * @return boolean true
 */
int zeichneTontaube() {
	gotoxy(OFS_X + POS_TT_X - 1, OFS_Y + POS_TT_Y);
    printf("~*~");
    return true; 
}

/**
 * Zeichnet den Rahmen f�r das Spielfeld
 * @return boolean true
 */
int zeichneBildschirm() {
	int i;
	char s[2]="�"; // Zeichen f�r die Rahmendarstellung
	// Horizontale Linie �ber Spielfeld zeichnen
	gotoxy(OFS_X-1, OFS_Y-1);
	for (i=0; i <= SIZ_X+1; i++) {
		printf(s);
	}         
	// Horizontale Linie unter Spielfeld zeichnen
	gotoxy(OFS_X-1, OFS_Y+SIZ_Y);
	for (i=0; i <= SIZ_X+1; i++) {
		printf(s);
	}
	// Vertikale Linie links und rechts neben Spielfeld zeichnen
	for (i=0; i <= SIZ_Y; i++) {
		gotoxy(OFS_X-1, OFS_Y+i);
		printf(s);
		gotoxy(OFS_X+SIZ_X, OFS_Y+i);
		printf(s);
	}
	return true;
}                 

/**
 * Bewegt die Tontaube zuf�llig auf dem Bildschirm
 * @return boolean true
 */
int bewegeTontaube() {
	srand(time(NULL));
	POS_TT_X+=(rand()%3-1);
	POS_TT_Y+=(rand()%3-1);  // -1 oder +0 oder +1
	if (POS_TT_X > SIZ_X) POS_TT_X = SIZ_X;
	if (POS_TT_X < 0) POS_TT_X = 0;
	if (POS_TT_Y > SIZ_Y) POS_TT_Y = SIZ_Y;
	if (POS_TT_Y < 0) POS_TT_Y = 0;
	resetBildschirm();
	zeichneTontaube();
	return true;      // Wenn Taube das Feld verl�sst auf FALSE setzen, damit neue Taube genriert
}

/**
 * Pr�ft auf Position von Tontaube und Fadenkreuz
 * @return boolean getroffen
 */
int feuern() {
	int getroffen = false;
    // Variablen f�r Schleife auf Minimalwerte setzen
	int fx, fy, t;
	// Schleife f�r Fadenkreuzpunkte
	for (fx=-2; fx<=2; fx++) {
		for (fy=-1; fy<=1; fy++) {
			// Alle Positionen der Tontaube ber�cksichtigen
			for (t=-1; t<=1; t++) {
				if ((POS_FK_X + fx) == (POS_TT_X + t) && (POS_FK_Y + fy) == POS_TT_Y) {
					getroffen = true;
				}
            }
        }
	}
	SCHUESSE--;
    schreibeMeldung();
	return getroffen;
}

int schreibeMeldung() {
	gotoxy(1,1);
	printf("Level %2i von 10 | noch %1i Sch�sse �brig", LEVEL, SCHUESSE);
	return true;
}

int schreibeSpielMeldung(char* headline, char* text) {
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
	schreibeSpielMeldung("WILLKOMMEN", "Dr�cke Enter um zu starten");
	int PLAY=true; // Wenn Level erfolglos beendet, wird diese auf FALSE gesetzt => Spiel endet
	int durchlauf;
	// einzelne Levels

	while(LEVEL < 11 && PLAY == true) {
		durchlauf=1;
		resetParameter();
        resetBildschirm();
		zeichneBildschirm();
		schreibeMeldung();
        while (SCHUESSE > 0 && SCHUESSE < 100) {
			mywait(1);
			if(durchlauf == 10) {   // Alle 10 Durchl�ufe Tontaube bewegen
				bewegeTontaube();
        	    durchlauf = 1;
			}
			if (bewegeFadenkreuz() == -1) {
				// Wenn Taube getroffen, setze SCHUESSE auf 999 um n�chstes Level zu erreichen
                SCHUESSE=999;
			}
			durchlauf++;
		}
		if (SCHUESSE==0) {
			PLAY=false;
            schreibeSpielMeldung("GAME OVER", "Du hast die Taube nicht mit deinen 7 Sch�ssen getroffen");
		}
		else {
			SCHUESSE=7;
			LEVEL++;
        }
	}
    if (PLAY) {
		schreibeSpielMeldung("HERZLICHEN GL�CKWUNSCH", "Du hast Tontauben-Schie�en durchgespielt");
    }
}