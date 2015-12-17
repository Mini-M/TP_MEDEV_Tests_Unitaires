#include "regles.h"

/* Teste si une case est libre*/
bool case_libre(int x, int y, Goban* plateau)
{
    bool estLibre;
    coord totest;
    totest.x = x;
    totest.y= y;
    int taille = plateau->get_taille();
    if ((x>=0)&&(x<taille)&&(y>=0)&&(y<taille)){

        if (plateau->getPierre(totest))
        {
            estLibre= false;
        }
        else{
            estLibre= true;
        }

    }
    else{
        estLibre = false;

    }
    return estLibre;
}

/* Teste si la pierre posée est un suicide (coup invalide)
ou si elle capture un groupe (coup valide) */

bool suicide (int couleur, int x, int y, Goban* plateau)
{
    bool estValide=false;
    Pierre* pierre = new Pierre(plateau, 0, x,y);
    vector<coord> libertes = pierre->getGroupe()->getlibertes();
    if (sizeof(libertes)>0)
        {
        estValide=true;
        }
    else
        {
        coord pierre_coord;
        pierre_coord.x=x;
        pierre_coord.y=y;
        coord case_droite = pierre_coord;
        coord case_gauche = pierre_coord;
        coord case_haut = pierre_coord;
        coord case_bas = pierre_coord;
        case_droite.x++;
        case_gauche.x--;
        case_haut.y--;
        case_bas.y++;
        if(sizeof(plateau->getPierre(case_droite)->getGroupe()->getlibertes())==0)
            {
            estValide=true;

            }
        if(sizeof(plateau->getPierre(case_gauche)->getGroupe()->getlibertes())==0)
            {
            estValide=true;
            }
        if(sizeof(plateau->getPierre(case_haut)->getGroupe()->getlibertes())==0)
            {
            estValide=true;
            }
        if(sizeof(plateau->getPierre(case_bas)->getGroupe()->getlibertes())==0)
            {
            estValide=true;
            }

        }
    return estValide;
}

bool gestion_ko(Goban* plateau)
{
    bool estValide=false;
    std::ofstream ofs;
    ofs.open("tour.txt", ofstream::out | ofstream::trunc);//efface le contenu du texte
    //ecrire nouveau texte (boucle for)
    ofs.close();

    ifstream nouveau("tour.txt");
    ifstream vieux("tour_2.txt");
    while((!nouveau.eof())&&(!vieux.eof()))
    {
        string line, line2;
        getline(nouveau,line);
        getline(vieux,line2);
        if(line==line2)
        {
        estValide=true;
        }
        else
        {
        estValide=false;
        }
    }
    nouveau.close();
    vieux.close();
    return estValide;
}

//on teste le suicide puis le ko
bool coup_possible(int couleur,int x, int y, Goban* plateau)
{
    bool estValide;

    if (suicide(couleur,x,y,plateau))
        {
        estValide=true;
        }
    else
        {
        if (gestion_ko(plateau))
            {
            estValide=true;
            }
        else
            {
            estValide=false;
            }
        }

    if(!estValide)
    {
    //recreer le Goban selon l etat precedent
    }
    return estValide;
}
