#ifndef HITBOX_H
#define HITBOX_H

#include <QImage>
#include <QRect>
#include "shot.h"

class HitBox
{
//Data Members
private:
	int HP;
    int x, y;
       QImage image;            //user image
        QRect rect;             //collision box
         std::vector <shot*> shots; //projectiles for the player!
//constructors
public: 
	HitBox();
	~HitBox();
//commands
public:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void reset();           //reset position and HP


//getters and setters
    int getHP();
	void setHP(int);
    int getx();
    int gety();
    QRect getRect();
    QImage& getImage();
    void setx(int);
    void sety(int);

    void fireShot();               //add fireball to vector - equivalent to monster's spitfireball function
    std::vector<shot*>* getShots();     //return pointer to vector
    void clearShots();          //clears shot vector
};

#endif
