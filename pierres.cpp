/*==========================================================================
fichier : pierres.cpp
auteurs :   Côme & Irshad
derniere modif : 3/12/2015
description : Contient les méthodes de pierre et groupe
============================================================================*/

#include "structures_jeu.h"

/*==========================
        Classe Pierre
==========================*/

/* Constructeur */
Pierre::Pierre (Goban* jeu, int couleur, int x, int y){

this->couleur = couleur;
coord.x = x;
coord.y = y;
this->jeu = jeu;
grpAssoc = new Groupe(this);

}

/*Accesseur*/
coord getCoord(){

return coord_pierre;

}

/*==========================
        Classe Groupe
==========================*/

Groupe::Groupe (Goban* jeu,Pierre* maPierre ){

    this->jeu = jeu;
    pierres.clear();
    pierres.push_back(maPierre);

    //Récupère les libertés
    libertes.clear();
    coord pierre_coord = maPierre.getCoord();
    Pierre* case_adjacente;

    coord case_droite = pierre_coord;
    coord case_gauche = pierre_coord;
    coord case_haut = pierre_coord;
    coord case_bas = pierre_coord;
    case_droite.x++;
    case_gauche.x--;
    case_haut.y--;
    case_bas.y++;

    case_adjacente = jeu->getPierre(case_droite);

    if (!case_adjacente){ // Si la case est vide
        libertes.push_back(case_droite);
    }

    case_adjacente = jeu->getPierre(case_gauche);

    if (!case_adjacente){ // Si la case est vide
        libertes.push_back(case_gauche);
    }

    case_adjacente = jeu->getPierre(case_haut);

    if (!case_adjacente){ // Si la case est vide
        libertes.push_back(case_haut);
    }

    case_adjacente = jeu->getPierre(case_bas);

    if (!case_adjacente){ // Si la case est vide
        libertes.push_back(case_bas);
    }



}
