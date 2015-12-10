#include "joueur.h"

using namespace std;

Joueur :: Joueur(int color)
{
    couleur=color;
    captures=0;
    points=0.0;
}

int Joueur :: getColor()
{
    return couleur;
}

void Joueur :: jouer (Goban* plateau)
{
    bool aJoue=false;
    while(!aJoue)
    {
    string action ;
    cin >> action;

    if (action=="jouer")
    {
        int x,y;
        cout<<"Entrer les coordonnees de la pierre"<<endl;
        cin>>x>>y;

        if (case_libre(x,y,plateau))
        {
            if(coup_possible(couleur,x,y,plateau))
            {
            cout<<"Le coup ("<<x<<","<<y<<") a ete joue"<<endl;
            aJoue=true;
            }
            else
            {
            cout<<"Le coup ("<<x<<","<<y<<") est invalide"<<endl;
            }
        }
    }
    else if (action=="passer")
        {
        aJoue=true;
        }
    else
        {
        cout<<"Action inconnue"<<endl;
        }
    }
}
