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

/*Setters*/

void Pierre::setGroupe(Groupe* grp){
        grpAssoc = grp;
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

    /* fusion des libertés*/
    sort(libertes.begin(),libertes.end());
    sort(sndlibertes.begin(),sndlibertes.end());

    /*On élimine les pierres du premier groupe dans la liste des libertés du second groupe*/
    for(vector<Pierre*>::iterator itpierre1 = pierres.begin();itpierre1<pierres.end();itpierre1++) {
        coord c =(*itpierre1)->getCoord();
        vector<coord>::iterator pos = find(sndlibertes.begin(),sndlibertes.end(),c);
        if (pos != sndlibertes.end()) sndlibertes.erase(pos);
    }

    /*On élimine les pierres du second groupe dans la liste des libertés du premier groupe*/
    for(vector<Pierre*>::iterator itpierre2 = sndpierres.begin();itpierre2<sndpierres.end();itpierre2++) {
        coord c =(*itpierre2)->getCoord();
        vector<coord>::iterator pos = find(libertes.begin(),libertes.end(),c);
        if (pos != libertes.end()) libertes.erase(pos);
    }

    /* on fusionne les libertés*/
    vector<coord>::iterator it;
    it=set_union(libertes.begin(),libertes.end(),sndlibertes.begin(),sndlibertes.end(),libertes_fusionnes.begin());
    libertes_fusionnes.resize(it-libertes_fusionnes.begin());

    libertes = libertes_fusionnes;

    /*fusion des listes de pierres*/
    pierres.insert(pierres.end(),sndpierres.begin(), sndpierres.end());

    grp->updateGroup(this);


}

void Groupe::updateGroup(Groupe* grp){

    for(vector<Pierre*>::iterator itpierre = pierres.begin();itpierre<pierres.end();itpierre++) {
        (*itpierre)->setGroupe(grp);
    }
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

    if (case_adjacente){ // Si la case n'est pas vide
        int couleur_pierre_adjacente = case_adjacente->getCouleur();
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
    cout <<"  0  1  2  3  4  "<<endl;
    for (int i=0; i<5;i++){
        cout << i;
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
    cout<<"================="<< endl;;


}

