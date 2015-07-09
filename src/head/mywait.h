void mywait(int);
/**
 * Verzoegert den Ablauf des Programmes
 * @param int Verzoegerung in Millisekunden
 */
void mywait(int d) {
    struct time t, tneu;
    int loop;
	
    for (loop=0; loop<d; loop++) {
        gettime(&t);
        gettime(&tneu);
        while (t.ti_hund == tneu.ti_hund) gettime(&tneu);
    }
}
