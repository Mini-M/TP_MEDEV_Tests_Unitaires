#pragma once

#include <iostream>
#include <string>
#include "structures_jeu.h"
#include "regles.h"



class Joueur
{
private :
    int couleur;
    int captures;
    float points;
    bool aPasse;
public :
    Joueur(int color);
    ~Joueur();
    void jouer (Goban* plateau);

    //Fonctions de récupération
    int getColor();
    bool getPasse();


};
