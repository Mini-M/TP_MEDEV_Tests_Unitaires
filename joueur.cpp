#include "joueur.h"

Joueur :: Joueur(string color)
{
    couleur=color;
    captures=0;
    points=0.0;
}

int Joueur :: getColor()
{
    return couleur;
}

void Joueur :: jouer (Goban plateau)
{
    string action ;
    cin >> action;

    if (action=="jouer")
    {
    //a completer
    }
    else if (action=="passer")
    {
    //a completer
    }
    else
    {
    cout<<"Action inconnue"<<endl;
    }
}
