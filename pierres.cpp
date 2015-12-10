/*==========================================================================
fichier : pierres.cpp
auteurs :   Côme & Irshad
derniere modif : 3/12/2015
description : Contient les méthodes de pierre et groupe
============================================================================*/

#include "structures_jeu.h"

/*==========================
        Struct Coord
==========================*/

/*==========================
        Classe Pierre
==========================*/

/* Constructeur */
Pierre::Pierre (Goban* jeu, int couleur, int x, int y){

this->couleur = couleur;
coord_pierre.x = x;
coord_pierre.y = y;
this->jeu = jeu;
grpAssoc = new Groupe(jeu,this);

}

/*Accesseur*/
coord Pierre::getCoord(){

return coord_pierre;

}

/*==========================
        Classe Groupe
==========================*/

/*constructeur*/
Groupe::Groupe (Goban* jeu,Pierre* maPierre ){

    this->jeu = jeu;
    pierres.clear();
    pierres.push_back(maPierre);

    //Récupère les libertés
    libertes.clear();
    coord pierre_coord = maPierre->getCoord();
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

//Fonction Fusionne deux groupes
void Groupe::fusionGroupe(Groupe* grp){

    vector<Pierre*> sndpierres = grp->getlistPierres();
    vector<coord> sndlibertes = grp->getlibertes();
    vector<coord> libertes_fusionnes(libertes.size()+sndlibertes.size());
    vector<coord>::iterator it;
    /* fusion des libertés*/
    sort(libertes.begin(),libertes.end());
    sort(sndlibertes.begin(),sndlibertes.end());

    it=set_union(libertes.begin(),libertes.end(),sndlibertes.begin(),sndlibertes.end(),libertes_fusionnes.begin());
    libertes_fusionnes.resize(it-libertes_fusionnes.begin());

    libertes = libertes_fusionnes;

    /*fusion des listes de pierres*/
    pierres.insert(pierres.end(),sndpierres.begin(), sndpierres.end());

    delete grp;


}

/*Accesseurs Groupe*/

vector<Pierre*> Groupe::getlistPierres(){
    return pierres;
}

vector<coord> Groupe::getlibertes(){
    return libertes;
}

void Groupe::miseAJourLibertes(){

    vector<coord>::iterator it;
    for(it = libertes.begin();it<libertes.end();it++){
        if (jeu->getPierre(*it)){ //S'il y a une pierre
            libertes.erase(it); // Ce n'est plus une liberte
        }

    }
}

/*==========================
        Classe Goban
==========================*/

Goban::Goban (){
}

void Goban::MiseAJour(Pierre* maPierre){


}

Pierre* Goban::getPierre(coord case_pierre){
    return NULL;
}

