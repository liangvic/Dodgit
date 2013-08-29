#include "shot.h"
#include <iostream>

shot::~shot(){
std::cout<<"shot Deleted"<<std::endl;
}

shot::shot(int xpos, int ypos):fireball(xpos, ypos)
{
    image.load("images/shot.jpg");
    rect = image.rect();
    x = xpos;
    y = ypos;
    rect.moveTo(x, y);
    speed = 3;
    shotType= 's';
}

/*
void shot::move(int newx, int newy)
{
}
*/
void shot::moveDown()
{
    y-= speed;
    rect.moveTo(x, y);
}

