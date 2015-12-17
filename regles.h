#pragma once

#include "joueur.h"
#include "structures_jeu.h"
#include <fstream>

void ecriture_texte (string txtname,Goban* plateau);
bool case_libre (int x, int y, Goban* plateau);
bool suicide (int couleur, int x, int y , Goban* plateau);
bool gestion_ko (Goban* plateau);
bool coup_possible (int couleur, int x, int y, Goban* plateau);

