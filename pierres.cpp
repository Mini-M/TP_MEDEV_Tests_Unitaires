/*==========================================================================
fichier : structures_jeu.cpp
auteurs :   Côme & Irshad
derniere modif : 3/12/2015
description : Contient les méthodes de pierre et groupe
============================================================================*/

#include "structures_jeu.h"
#include <iostream>
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

Groupe* Pierre::getGroupe(){
return grpAssoc;
}

int Pierre::getCouleur(){
    return couleur;
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


    int taille = jeu->get_taille();

    if ((pierre_coord.x == 0)&&(pierre_coord.y==0)){
            test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,0,1);
    }
    else if((pierre_coord.x == taille-1)&&(pierre_coord.y==0)){

            test_case_adjacent(maPierre,-1,0);
            test_case_adjacent(maPierre,0,1);
    }
    else if((pierre_coord.x == 0)&&(pierre_coord.y==taille-1)){

            test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,0,-1);
    }
    else if((pierre_coord.x == taille-1)&&(pierre_coord.y==taille-1)){

            test_case_adjacent(maPierre,-1,0);
            test_case_adjacent(maPierre,0,-1);
    }
    else if (pierre_coord.x == 0){

             test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,0,-1);
            test_case_adjacent(maPierre,0,1);


    }
    else if (pierre_coord.x == taille-1){

             test_case_adjacent(maPierre,-1,0);
            test_case_adjacent(maPierre,0,-1);
            test_case_adjacent(maPierre,0,1);

    }
    else if (pierre_coord.y == 0){

            test_case_adjacent(maPierre,0,1);
            test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,-1,0);

    }
    else if (pierre_coord.y == taille-1){

            test_case_adjacent(maPierre,0,-1);
            test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,-1,0);

    }
    else{
            test_case_adjacent(maPierre,0,1);
            test_case_adjacent(maPierre,0,-1);
            test_case_adjacent(maPierre,1,0);
            test_case_adjacent(maPierre,-1,0);

    }


}

void Groupe::test_case_adjacent(Pierre* maPierre,int decal_x,int decal_y){
    coord case_pierre_adjacente = maPierre->getCoord();
    case_pierre_adjacente.x += decal_x;
    case_pierre_adjacente.y += decal_y;
    Pierre* case_adjacente = jeu->getPierre(case_pierre_adjacente);

    if (!case_adjacente){ // Si la case est vide
        libertes.push_back(case_pierre_adjacente);
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

    grp = this;


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

/*Accesseur*/
Goban::Goban (){
}

void Goban::MiseAJour(Pierre* maPierre){
    coord pierre_coord = maPierre->getCoord();
    goban[pierre_coord.x][pierre_coord.y]= maPierre;

    //Cette pierre appartient-elle a un groupe! Ou bien réduit-elle les libertes d'un groupe adverse.
    if ((pierre_coord.x == 0)&&(pierre_coord.y==0)){
            test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,0,1);
    }
    else if((pierre_coord.x == taille-1)&&(pierre_coord.y==0)){

            test_adjacent(maPierre,-1,0);
            test_adjacent(maPierre,0,1);
    }
    else if((pierre_coord.x == 0)&&(pierre_coord.y==taille-1)){

            test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,0,-1);
    }
    else if((pierre_coord.x == taille-1)&&(pierre_coord.y==taille-1)){

            test_adjacent(maPierre,-1,0);
            test_adjacent(maPierre,0,-1);
    }
    else if (pierre_coord.x == 0){

             test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,0,-1);
            test_adjacent(maPierre,0,1);


    }
    else if (pierre_coord.x == taille-1){

             test_adjacent(maPierre,-1,0);
            test_adjacent(maPierre,0,-1);
            test_adjacent(maPierre,0,1);

    }
    else if (pierre_coord.y == 0){

            test_adjacent(maPierre,0,1);
            test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,-1,0);

    }
    else if (pierre_coord.y == taille-1){

            test_adjacent(maPierre,0,-1);
            test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,-1,0);

    }
    else{
            test_adjacent(maPierre,0,1);
            test_adjacent(maPierre,0,-1);
            test_adjacent(maPierre,1,0);
            test_adjacent(maPierre,-1,0);

    }
}

void Goban::test_adjacent(Pierre* maPierre,int decal_h, int decal_v){

    coord pierre_coord = maPierre->getCoord();
    int couleur_pierre = maPierre->getCouleur();
    Pierre* case_adjacente = goban[pierre_coord.x+decal_h][pierre_coord.y+decal_v];
    int couleur_pierre_adjacente = case_adjacente->getCouleur();

    if (case_adjacente){ // Si la case n'est pas vide
        if(couleur_pierre==couleur_pierre_adjacente){ // Meme groupe
            case_adjacente->getGroupe()->fusionGroupe(maPierre->getGroupe());
        }
        else{ // Sinon on touche une groupe adversaire
            case_adjacente->getGroupe()->miseAJourLibertes();
        }
    }

}

/*fonction getPierre*/
Pierre* Goban::getPierre(coord case_pierre){
    return goban[case_pierre.x][case_pierre.y];
}

/*fonction getTaille*/
int Goban::get_taille(){
    return taille;
}

/*fonction d'affichage du goban*/
void Goban::affichage(){

    cout <<"================="<<endl;
    for (int i=0; i<5;i++){
        for(int j=0; j<5;j++){
            if(goban[i][j]){
                if (goban[i][j]->getCouleur() ==0){
                    cout <<" B ";
                }
                else{
                    cout <<" N ";
                }
            }
            else{
                cout <<" . ";
            }
        }
        cout <<endl;
    }
    cout<<"=================";


}

