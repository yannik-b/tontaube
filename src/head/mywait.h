void mywait(int);
void mywait(int d) {
	struct time t, tneu;
	int loop;
	
	for (loop=0; loop<d; loop++) {
		gettime(&t);
		gettime(&tneu);
		while (t.ti_hund == tneu.ti_hund) gettime(&tneu);
	}
}
