#include "monster.h"

Monster::Monster()              //base monster
{

        image.load("images/Monster.jpg");

    shotType='V';
    rect = image.rect();
    rect.moveTo(x, y);
    speed = 1;
}

Monster::Monster(char stype)        //only 1 other type implemented so far
{
    shotType = stype;

    if (shotType == 'Z')
    image.load("images/zigzagger.jpg");

    rect = image.rect();
    rect.moveTo(x, y);
    speed = 1;
    if (x > 400)
        hdirection = 'r';
    else
        hdirection = 'l';

}

void Monster::moveDown()
{
    if (shotType == 'V')            //for base monsters
    {
    y+=speed;
    rect.moveBottom(y);             //just move down
    }
    else
    {
        if (shotType == 'Z')          //for zigzagging monsters
        {
        if (rect.left() <=202 )     //set random left/right direction
            hdirection = 'r';
        if (rect.right() > 600 )
            hdirection = 'l';

        if (hdirection == 'r')                  //move in that direction
            rect.moveTo((++x), rect.top());
        if (hdirection == 'l')
            rect.moveTo((--x), rect.top());


        y+=speed;
        rect.moveBottom(y);             //move down 1
    }
}
}

