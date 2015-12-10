#include "regles.h"

bool case_libre(int x, int y, Goban plateau)
{
    bool estLibre;
    coord totest;
    totest.x = x;
    totest.y= y;

    if (plateau.getPierre(totest))
    {
        estLibre= false;
    }
    else
    {
        estLibre= true;
    }
    return estLibre;
}

bool suicide (int x, int y, Goban plateau)
{
    bool estValide=false;
    //poser la pierre
    //pour chaque groupe autour tester libertes
    //si groupe tue return true
    //sinon tester libertes pierre posee
        //si liberte >0 return true
        //sinon return false
    return estValide;
}

bool gestion_ko(int x, int y, Goban plateau)
{
    bool estValide=false;

    //jouer coup
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
    return estValide;
}


bool coup_possible(int x, int y, Goban plateau)
{
    return (case_libre(x,y, plateau)&&gestion_ko(x,y,plateau)&&(suicide(x,y,plateau)));
}
