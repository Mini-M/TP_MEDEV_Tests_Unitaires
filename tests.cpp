#include "structures_jeu.h"
#include "gtest/gtest.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
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
*/
/* Premières séries de tests : libertes basiques*/

class gobanTest1 : public ::testing::Test {
protected :
Goban* jeu;
Pierre* maPierre_centre,*maPierre_bord,*maPierre_coin;
int taille_centre, taille_bord, taille_coin;
virtual void SetUp () {
    jeu = new Goban();

    maPierre_centre = new Pierre (jeu,0,2,2);
    maPierre_bord = new Pierre (jeu,0,0,3);
    maPierre_coin = new Pierre (jeu,0,4,4);

    taille_centre = maPierre_centre->getGroupe()->getlibertes().size();
    taille_bord = maPierre_bord->getGroupe()->getlibertes().size();
    taille_coin = maPierre_coin->getGroupe()->getlibertes().size();


}


};


Pierre* maPierre_centre,*maPierre_bord,*maPierre_coin;
int taille_centre, taille_bord, taille_coin;

/*Une pierre posee au centre a 4 libertes*/
TEST_F(gobanTest1, TestLibertes1) {

    EXPECT_EQ (4,taille_centre);

}

/*Une pierre posee au bord a 3 libertes*/

TEST_F(gobanTest1, TestLibertes2) {

    EXPECT_EQ (3,taille_bord);

}

/*Une pierre posee dans le coin a 2 libertes*/
TEST_F(gobanTest1, TestLibertes3) {

    EXPECT_EQ (2,taille_coin);

}



int main(int argc, char **argv) {


::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
