
#include <string>

Class Joueur
{
private :
    int couleur;
    int captures;
    float points;
public :
    Joueur(int color);
    ~Joueur();
    void jouer ();
    //Board* plateau;

};
