#include "regles.h"
#include <fstream>

using namespace std;

//Creation du fichier historique des coups

ofstream outfile("historique.txt");

//Creation des fichiers necessaires a la gestion du ko

ofstream outfile2("tour_2.txt");
ofstream outfile1("tour_1.txt");
ofstream outfile0("tour.txt");

Joueur Noir = new Joueur(0);
Joueur Blanc = new Joueur(1);



int main ()
{
    int tour=0;

    bool partiefinie=false;

    while(!partiefinie)//boucle de jeu
    {
    if(tour%2) {Blanc.jouer;}
    else {Noir.jouer;}
    tour++;
    }
    return 0;
}
