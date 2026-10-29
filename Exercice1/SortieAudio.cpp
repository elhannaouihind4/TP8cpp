
#include "SortieAudio.hpp"

void HautParleur::ouvrir() {
    cout << "Haut-parleur ouvert." << endl;
}

void HautParleur::jouer(const string& son) {
    cout << "Haut-parleur joue : " << son << endl;
}

void HautParleur::fermer() {
    cout << "Haut-parleur ferme." << endl;
}

void CasqueBT::ouvrir() {
    cout << "Casque Bluetooth connecte." << endl;
}

void CasqueBT::jouer(const string& son) {
    cout << "Casque Bluetooth joue : " << son << endl;
}

void CasqueBT::fermer() {
    cout << "Casque Bluetooth deconnecte." << endl;
}

void SortieHDMI::ouvrir() {
    cout << "Sortie HDMI ouverte." << endl;
}

void SortieHDMI::jouer(const string& son) {
    cout << "Sortie HDMI joue : " << son << endl;
}

void SortieHDMI::fermer() {
    cout << "Sortie HDMI fermee." << endl;
}





