#include "regles.h"

bool case_libre(int x, y, Goban plateau)
{
    if (sizeof(plateau[x][y])==1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool coup_possible(int x,y, Goban plateau)
{
    return (case_libre(x,y, plateau)&&gestion_ko(x,y,plateau)&&(suicide(x,y,plateau)));
}
