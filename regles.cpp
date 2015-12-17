#include "regles.h"


void ecriture_texte(string txtname, Goban* plateau)
{
    ofstream ofs;
    ofs.open(txtname,ofstream::out(ofstream::trunc));
    coord towrite;
    for(int j=0;j<plateau->get_taille();j++)
    {
        for(int i=0; i<plateau->get_taille();i++)
        {
            towrite.x=i;
            towrite.y=j;
            if(sizeof(plateau->getPierre(towrite))==0)
            {
                ofs<<".";
            }
            else
            {
                ofs<<plateau->getPierre(towrite)->getCouleur();
            }

        }
    }
    ofs.close();
}

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
            cout<<"La case ("<<x<<","<<y<<") est deja occupee"<<endl;
            estLibre= false;
        }
        else{
            estLibre= true;
        }


    if (plateau->getPierre(totest))
    {
        estLibre= false;

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
    if (estValide==false){cout<<"Ne vous suicidez pas !"<<endl;}
    return estValide;
}

bool gestion_ko(Goban* plateau)
{
    bool estValide=false;
    //Actualisation du fichier actuel du plateau
    ecriture_texte("tour.txt");
    //Comparaison du fichier actuel avec celui de deux tours avant
    ifstream nouveau("tour.txt");
    ifstream vieux("tour_2.txt");
    while((!nouveau.eof())&&(!vieux.eof()))
    {
        string line, line2;
        getline(nouveau,line);
        getline(vieux,line2);
        if(line==line2)
        {
        estValide=false;//2 fichiers identiques : c'est un ko
        cout<<"Ce coup est un ko"<<endl;
        }
        else
        {
        estValide=true;//fichiers differents donc coup valide
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
