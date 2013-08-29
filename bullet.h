#ifndef BULLET_H
#define BULLET_H
#include <QImage>
#include <QRect>

class fireball; //temporary link to subclass

class Bullet
{
	public:
		Bullet();
		~Bullet();

    protected:
        QRect rect;
        QImage image;

    char shotType;          //type of npc
    int x, y, speed;        //position and speed

	public:
   QImage& getImage();          //returns bullet image
   QRect getRect();             //returns QRect for object

   virtual void moveDown(); //moves bullet down 1 space
   virtual std::vector<fireball*>* getFireballs() const;      //pointer to a vector of pointers to fireballs - virtual
   virtual int getLives();
   virtual void setLives(int);
    virtual void spitFireballs();                       //adds another fireball to the vector - virtual
    int getx();                 //return x position
    int gety();             //returns y position
    void setx(int);         //set xposition of bullet
    void sety(int);         //set yposition of bullet
    char getShotType();     //return shot type
};

#endif
