
#include "SortieAudio.hpp"


void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique.mp3");
    sortie->fermer();
}

int main() {

    SortieAudio* sorties[3];


    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();


    for (int i = 0; i < 3; i++) {
        tester(sorties[i]);
        cout << "\n" << endl;
    }


    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}

