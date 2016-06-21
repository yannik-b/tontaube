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
