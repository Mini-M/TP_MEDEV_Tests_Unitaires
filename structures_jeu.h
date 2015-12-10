/*==========================================================================
fichier : structure_jeu.h
auteurs :   Côme & Irshad
derniere modif : 3/12/2015
description : Contient les définitions des classes Pierre, Groupe et Goban
============================================================================*/
#ifndef structures_jeu.h
#define structures_jeu.h

#include <vector>

struct coord {
int x;
int y;
};

class Pierre {

private :

    int couleur;//0 si blanc et 1 pour noir
    coord coord_pierre;
    Groupe* grpAssoc;
    Goban* jeu;

public :

    //Constructeur
    Pierre (Goban* jeu,int couleur, int x, int y);
    //Accesseur
    coord getCoord();


};

class Groupe {

private :
    int couleur;
    vector<Pierre*> pierres;
    vector<coord> libertes;
    Goban* jeu;

public :
    Groupe (Goban* jeu,Pierre* maPierre );
    void ajouterPierre (Pierre* maPierre);
    void miseAJourLibertes ();

};

class Goban {
private :
    int taille;
    vector <vector<Pierre*> >;

public :
    Goban (int taille);
    void MiseAJour (Pierre* maPierre);
    Pierre* getPierre(coord case_pierre); // Récupère la pierre de la case

};
