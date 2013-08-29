#include "fireball.h"
#include <iostream>

fireball::~fireball(){
std::cout<<"fireball Deleted"<<std::endl;
}

fireball::fireball(int xpos, int ypos)
{
    image.load("images/fireball.jpg");
    rect = image.rect();
    x = xpos;
    y = ypos;
    rect.moveTo(x, y);
    speed = 3;
    shotType= 'f';
}

void fireball::move(int newx, int newy)
{

}

void fireball::moveDown()
{
    y+= speed;
    rect.moveTo(x, y);
}
