
#include <string>
#include "structures_jeu.h"

class Joueur
{
private :
    int couleur;
    int captures;
    float points;
public :
    Joueur(int color);
    ~Joueur();
    void jouer (Goban plateau);

    //Fonctions de récupération
    int getColor();


};
