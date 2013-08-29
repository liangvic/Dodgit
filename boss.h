#ifndef BOSS_H
#define BOSS_H

#include "monster.h"
#include "fireball.h"

class Boss: public Monster
{
    public:
        Boss();
        ~Boss();
        void moveDown();
        int getLives();
        void setLives(int);
        std::vector<fireball*>* getFireballs();  //return pointer to vector

    private:
        int lives; //boss lives
        char vdirection;    //vertical direction
        int bulletspawnx;
        void spitFireballs();               //add fireball to vector

};

#endif // BOSS_H
