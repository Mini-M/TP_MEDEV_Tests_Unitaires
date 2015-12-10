#pragma once

#include "joueur.h"
#include "structures_jeu.h"
#include <fstream>

bool case_libre (int x, int y, Goban plateau);
bool gestion_ko (int x, int y, Goban plateau);
bool suicide (int x, int y , Goban plateau);
bool coup_possible (int x, int y, Goban plateau);
