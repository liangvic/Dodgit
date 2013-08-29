#include "boss.h"


Boss::Boss()
{
    lives = 10;           //10 lives!
    shotType='B';
    image.load("images/fireboss.jpg");
    x = 400;
    vdirection = 'd';               //starts moving downwards
    rect = image.rect();
    rect.moveTo(x, y);
    speed = 1;
    int choosedir = rand()%370 + 200;
    if (choosedir > 400)                //left or right starting direction
        hdirection = 'r';
    else
        hdirection = 'l';
    bulletspawnx= 0;
}

Boss::~Boss(){
    if (fireballs.size()>0)
    for (int i=0; i<fireballs.size(); i++)
        delete fireballs[i];
}

void Boss::moveDown(){

    if (rect.left() <=202 )             //if hits wall, changes direction
        hdirection = 'r';
    if (rect.right() > 600 )
        hdirection = 'l';

    if (hdirection == 'r')                  //moves left or right depending on currently set direction
        rect.moveTo((++x), rect.top());
    if (hdirection == 'l')
        rect.moveTo((--x), rect.top());

    if (rect.top() < 1 )                //doesn't move past 200 pixels down
        vdirection = 'd';
    if (rect.bottom() > 200 )
        vdirection = 'u';

    if (vdirection == 'u')                  //moves up or down depending
        rect.moveTo(rect.left(), --y);
    if (vdirection == 'd')
        rect.moveTo(rect.left(), ++y);
}

int Boss::getLives(){
    return lives;
}

void Boss::setLives(int newl){
        lives = newl;
}

void Boss::spitFireballs()
{
    fireballs.push_back(new fireball(x+50-bulletspawnx, y+30));         //add fireballs!
    fireballs.push_back(new fireball(x+70+bulletspawnx, y+30));
    fireballs.push_back(new fireball(x, y+30));         //add fireballs!
    fireballs.push_back(new fireball(x+120, y+30));
    bulletspawnx+=2;
}

std::vector<fireball*>* Boss::getFireballs()
{
    return &fireballs;                  //return pointer to fireballs vector
}
