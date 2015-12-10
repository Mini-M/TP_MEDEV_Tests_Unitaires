#include "regles.h"

bool case_libre(int x, int y, Goban* plateau)
{
    bool estLibre;
    coord totest;
    totest.x = x;
    totest.y= y;

    if (plateau->getPierre(totest))
    {
        estLibre= false;
    }
    else
    {
        estLibre= true;
    }
    return estLibre;
}

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

        }

        //pour chaque groupe autour tester libertes
            //si groupe tue return true
            //sinon return false
    return estValide;
}

bool gestion_ko(Goban* plateau)
{
    bool estValide=false;
    std::ofstream ofs;
    ofs.open("tour.txt", ofstream::out | ofstream::trunc);
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
