
#include <stdlib.h>
#include <iostream>
#include "bullet.h"
#include <QTime>

Bullet::Bullet()
	{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int setrole = qrand()%100;

    if (setrole >= 10)              //90% chance of points
       { image.load("images/score_up.jpg");
        shotType = 'P';
    }

    if (setrole < 10)               //10% chance of extra life
    {    image.load("images/HP_up.jpg");
        shotType = '+';
    }
    rect = image.rect();
    x = rand()%370 + 200;
    y = 1;
    speed = qrand()%2+1;            //speed of bullet
    rect.moveTo(x, y);

	}


Bullet::~Bullet()
{
    std::cout<<"Bullet Deleted"<<std::endl;
}

char Bullet::getShotType()
{return shotType;}
QImage& Bullet::getImage(){
    return image;
}

QRect Bullet::getRect(){
    return rect;
}

void Bullet::moveDown()  //moves bullet 1 space if bullet is turned on
{
    y+=speed;
    rect.moveBottom(y);
}


std::vector<fireball*>* Bullet::getFireballs() const
{}


void Bullet::spitFireballs()
{}

int Bullet::getLives()
{}

void Bullet::setLives(int)
{}
	 
int Bullet::getx(){
return x;
}

int Bullet::gety(){
return y;
}

void Bullet::setx(int newx){
x = newx;
}

void Bullet::sety(int newy){
y = newy;
}

