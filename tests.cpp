#include "structures_jeu.h"
#include "gtest/gtest.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomPlateauGen (int nbPierres,int t,Goban* jeu) {
    if (2*nbPierres<t*t)
    {

    srand (time(NULL));
    int x = rand()%t;
    int y = rand()%t;
  //  int taille = jeu->get_taille();

    for (int i=0; i<nbPierres;i++)
    {
        coord cp;
        cp.x =x;
        cp.y =y;
        while (jeu->getPierre(cp))
        {
            cp.x = rand()%t;
            cp.y = rand()%t;
        }

        jeu->MiseAJour(new Pierre (jeu,0,x,y));

        cp.x =rand()%t;
        cp.y =rand()%t;
        while (jeu->getPierre(cp))
        {
            cp.x = rand()%t;
            cp.y = rand()%t;
        }

        jeu->MiseAJour(new Pierre (jeu,0,x,y));

    }
    }
    return 0;
}



class gobanTest1 : public ::testing::Test {
protected :
Goban* jeu;
Pierre* maPierre;
vector<coord> libertes;
virtual void SetUp () {
    jeu = new Goban();
    //jeu->MiseAJour(new Pierre (jeu,0,2,2));
    maPierre = new Pierre (jeu,0,2,2);
    libertes = maPierre->getGroupe()->getlibertes();
}


};


TEST_F(gobanTest1, TestLibertes1) {

    EXPECT_EQ (4,libertes.size());

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
