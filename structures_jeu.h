/*==========================================================================
fichier : structure_jeu.h
auteurs :   Côme & Irshad
derniere modif : 3/12/2015
description : Contient les définitions des classes Pierre, Groupe et Goban
============================================================================*/
#ifndef STRUCTURE_JEU_H_INCLUDED
#define STRUCTURE_JEU_H_INCLUDED

#include <algorithm>
#include <vector>

using namespace std;

struct coord {

int x;
int y;

bool operator <(const coord& a) const
{
    if (x<a.x) {
        return true;
    }
    else if (x>a.x){
        return false;
    }
    else{
        if(y<a.y){
            return true;
        }
        else{
            return false;
        }
    }
}

};

//Pré-déclaration

class Groupe;
class Goban;

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
    void fusionGroupe (Groupe* grp);
    void miseAJourLibertes ();

    //accesseur
    vector<Pierre*> getlistPierres();
    vector<coord> getlibertes();
};

class Goban {
private :
    int taille; // ne sert à rien ?
    Pierre* pierres_en_jeu[5][5];

public :
    Goban ();
    void MiseAJour (Pierre* maPierre); //Pose d'une pierre sur le Goban
    Pierre* getPierre(coord case_pierre); // Récupère la pierre de la case

};

#endif // STRUCTURE_JEU_H_INCLUDED
