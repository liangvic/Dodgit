#include "hitbox.h"
#include <iostream>


HitBox::HitBox() //constructors and deconstructors
    {
    x = 350;
    y = 600;
    image.load("images/hitbox.jpg");
    rect = image.rect();
    rect.moveTo(x, y);
    HP = 5;

}

HitBox::~HitBox()
{
    for (int i=0; i < shots.size(); i++)
        delete shots[i];

    std::cout <<"hitbox deleted"<<std::endl;
}

//move character 1 space
    void HitBox::reset(){
        HP = 3;
        x = 350;
        y = 600;
        rect.moveTo(x, y);
        if (shots.size() > 0)
        clearShots();
         }

    void HitBox::moveLeft(){
        if (rect.left() >=202 )
            rect.moveTo((--x), rect.top());
        }
    void HitBox::moveRight(){
        if (rect.right() <=600 )
             rect.moveTo((++x), rect.top());
        }
    void HitBox::moveUp(){
        if (rect.top() >=2 )
            rect.moveTo(rect.left(), (--y));
        }
    void HitBox::moveDown(){
        if (rect.bottom() <= 700 )
            rect.moveTo(rect.left(), (++y));
        }
	
//getters
	int HitBox::getHP()
	{ return HP;}
    int HitBox::getx()
    { return x;}
    int HitBox::gety()
    { return y;}
    QRect HitBox::getRect()
    {return rect;}
    QImage& HitBox::getImage()
    {return image;}
//setters
	void HitBox::setHP(int h)
	{ HP = h;}
    void HitBox::setx(int newx)
    {x = newx;}
    void HitBox::sety(int newy)
    {y = newy;}



    void HitBox::fireShot()
    {
        shots.push_back(new shot(x, y));         //add shots!
        shots.push_back(new shot(x+30, y));
    }

    std::vector<shot*>* HitBox::getShots()
    {
        return &shots;                  //return pointer to shots vector
    }

    void HitBox::clearShots()
    {
        for (int i=0; i < shots.size(); i++)
            delete shots[i];
    }
