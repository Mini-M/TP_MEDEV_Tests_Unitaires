#include "regles.h"
#include <fstream>

using namespace std;

//Creation du fichier historique des coups

ofstream outfile("historique.txt");

//Creation des fichiers necessaires a la gestion du ko

ofstream outfile2("tour_2.txt");
ofstream outfile1("tour_1.txt");
ofstream outfile0("tour.txt");

Joueur* Noir = new Joueur(0);
Joueur* Blanc = new Joueur(1);
Goban* plateau = new Goban();



int main ()
{
    int tour=0;
   /* int taille_groupe,taille_groupe2,taille_groupe3,taille_groupe4, nb_libertes ;
    Pierre *maPierre1 = new Pierre (plateau,0,2,2);
    Pierre *maPierre2 = new Pierre (plateau,0,2,3);
    Pierre *maPierre3 = new Pierre (plateau,0,3,3);
    Pierre *maPierre4 = new Pierre (plateau,0,4,3);

    plateau->MiseAJour(maPierre1);
    plateau->MiseAJour(maPierre2);
    plateau->MiseAJour(maPierre3);
    plateau->MiseAJour(maPierre4);
    plateau->MiseAJour(new Pierre (plateau,1,4,4));

    taille_groupe = maPierre1->getGroupe()->getlistPierres().size();
    taille_groupe2 = maPierre2->getGroupe()->getlistPierres().size();
    taille_groupe3 = maPierre3->getGroupe()->getlistPierres().size();
    taille_groupe4 = maPierre4->getGroupe()->getlistPierres().size();

    nb_libertes = maPierre1->getGroupe()->getlibertes().size();

    cout << "taille_groupe=" << taille_groupe << "  taille_groupe2=" << taille_groupe2 << "  taille_groupe3=" << taille_groupe3 <<"  taille_groupe4=" << taille_groupe4 << endl;
    cout << "nb libertes = " << nb_libertes <<endl;*/
    bool partiefinie=false;

    while(!partiefinie)//boucle de jeu
    {
    plateau->affichage();

    if(tour%2) {Noir->jouer(plateau);}
    else {Blanc->jouer(plateau);}
    tour++;
    }
    return 0;
}
