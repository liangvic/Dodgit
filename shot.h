#ifndef SHOT_H
#define SHOT_H

#include<QImage>
#include<QRect>
#include "fireball.h"


class shot: public fireball
{
    public:
        ~shot();
        shot(int, int);
        void moveDown();
};

#endif // shot_H
