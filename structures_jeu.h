/*==========================================================================
fichier : structure.h
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
Pierre (int couleur, int x, int y);
};

class Groupe {
private :
int couleur;
vector<Pierre*> pierres;
vector<coord> libertes;
Goban* jeu;

public :
Groupe (Pierre* maPierre );
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

};
