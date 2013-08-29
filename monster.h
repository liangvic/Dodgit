#ifndef MONSTER_H
#define MONSTER_H

#include "bullet.h"
#include <vector>
#include "fireball.h"

class Monster: public Bullet            //Subclass of Bullet
{
    protected:
        char hdirection;     //horizontal direction that monster is moving in
        std::vector <fireball*> fireballs; //projectiles for the monsters!
    public:
        Monster();      //default monster
        Monster(char);   //monster by type (for now just firespitter)
        void moveDown();

};

#endif // MONSTER_H
