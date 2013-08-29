#include <stdlib.h>
#include <QPainter>
#include <QApplication>
#include <QFont>
#include <QImage>
#include <vector>
#include <iostream>
#include "Dodger.h"


using namespace std;


//constructor for Dodger class
Dodger::Dodger(QWidget *parent): QWidget(parent)
{

gameNew = true;         //if first instance of game
gameStarted = false;
gamePaused = false;
gameOver = false;
gameWon = false;
hitbox = new HitBox();
bullets.push_back(new Bullet);

bulletCooldown = 0;
score = 500; //score is equivalent to energy
gameTimer = 0;

keepLeft = false;
keepRight = false;
keepDown = false;
keepUp = false;
boss = false;


}

Dodger::~Dodger()
{
    delete hitbox;

for (int i = 0; i < bullets.size(); i++)        //clear out vector of npcs
    delete bullets[i];
  bullets.clear();

}

void Dodger::paintEvent(QPaintEvent *event)    //makes display
{
    QPainter painter(this);
    QColor pencolor("steelblue");
    QPen pen;
    pen.setColor(pencolor);
    pen.setWidth(8);
    painter.setPen(pen);

    if (gameOver){                                                //if game over
        QFont font("Arial", 15, QFont::AllUppercase);
        QFontMetrics text(font);

        if (gameWon){                                         //if boss is dead
        int textWidth = text.width("GJ, you win. You beat the Boss.");

        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint (w/2, h/2));
        painter.drawText(-textWidth/2, 0, "GJ, you win. You beat the Boss.");

        }
        else                //if boss is still alive or you died before the boss
        {

            int textWidth = text.width("Game Over. You Lose. Sucks.");

            font.setPixelSize(10);
            int h = height();
            int w = width();

            painter.translate(QPoint (w/2, h/2));
            painter.drawText(-textWidth/2, 0, "Game Over. You Lose. Sucks");
        }
        QString str;
        str.setNum(score);
        painter.drawText(-100, 30, "Final Score: ");                            //prints final score
        painter.drawText(25, 30,  str);
        painter.drawText(-110, 90, "Press 'Space' to Restart");

    }
    else {                                          //if game still going on, draw sidebar
                   //draw sidebar
        QImage MonsterIcon;
        MonsterIcon.load("images/Monster.jpg");
        QPoint MonsterPoint(15, 120);

        QImage Health;
        Health.load("images/HP_up.jpg");
        QPoint HealthPoint(30, 175);

        QImage Coin;
        Coin.load("images/score_up.jpg");
        QPoint CoinPoint(35, 205);

        QRect statusBox(5, 5, 190, 690);
        painter.drawRect(statusBox);

        QFont font("Arial", 15, QFont::AllUppercase);
        setFont(font);
        painter.drawText(25, 40, "How to Play:");
        painter.drawText(25, 70, "1) Collect Points");
        painter.drawText(25, 90, "2) Don't Die");

        painter.drawImage(MonsterPoint, MonsterIcon);
        painter.drawImage(CoinPoint, Coin);
        painter.drawImage(HealthPoint, Health);
        painter.drawText(70, 150, "Avoid These!");
        painter.drawText(80, 190, "HP UP");
        painter.drawText(70, 220, "+50 Energy");

        painter.drawLine(5, 270, 192, 270);

        painter.drawText(25, 300, "Controls:");
        painter.drawText(25, 330, "Up, Down, Left");
        painter.drawText(25, 350, "Right Keys");
        painter.drawText(25, 380, "'Z' to shoot");
        painter.drawText(20, 400, "(Uses 100 Energy)");
        painter.drawText(25, 450, "'P' to Pause");
  //      painter.drawText(25, 420, "'Space' to Restart");
        painter.drawText(25, 470, "'Q' to Quit");

        QString str;
        str.setNum(score);
        painter.drawText(25, 600, "Energy:");
        painter.drawText(95, 600, str);
        painter.drawText(25, 630, "HP Left:");
        str.setNum(hitbox->getHP());
        painter.drawText(110, 630, str);

        if (gameNew)
        {
            painter.drawText(300, 400, "Press 'Space' to Start");           //if first instance of game
        }
        else
        {
        painter.drawImage(hitbox->getRect(), hitbox->getImage());           //draw user
        for (int i=0; i< bullets.size(); i++)
        {
        painter.drawImage(bullets[i]->getRect(), bullets[i]->getImage());       //draw npcs
        if (bullets[i]->getShotType() == 'B')
        {
            Boss* boss = static_cast<Boss*>(bullets.at(i));
            vector<fireball*>* projectiles = boss->getFireballs();            //draw fireballs
            for (int i = 0; i < (*projectiles).size(); i++)
                painter.drawImage((*projectiles)[i]->getRect(), (*projectiles)[i]->getImage());
        }
        }

        if(hitbox->getShots() > 0)                                                  //draw shots
        {
            vector <shot*>* projectiles = hitbox->getShots();
            for (int i=0; i < projectiles->size(); i++)
                painter.drawImage((*projectiles)[i]->getRect(), (*projectiles)[i]->getImage());
        }
    }

}
}

void Dodger::level1()
{
    if (gameTimer%100 == 0){                 //creates new bullet every 100 run-throughs
        int setrole = qrand()%100;
        if (setrole < 80)       //80% chance of Monster
            bullets.push_back(new Monster());
        if (setrole >= 70 && setrole < 100)  //15% chance of points or hp
            bullets.push_back(new Bullet);
    }

}

void Dodger::level2()
{
    if (gameTimer%100 == 0){                   //creates new bullet every 100 run-throughs
        int setrole = qrand()%100;
        if (setrole < 70)       //80% chance of Monster
            bullets.push_back(new Monster());
        if (setrole >= 70 && setrole < 100)      //30% chance of points or hp
            bullets.push_back(new Bullet);                                   
    }
    if (gameTimer%500 == 0){
        bullets.push_back(new Monster('Z'));
    }

}

void Dodger::level3(){

    if (boss== false)
       {
        boss = true;                           //creates new boss
        bullets.push_back(new Boss());
        }
    if (gameTimer%100 == 0){                   //creates new bullet every 100 run-throughs
        int setrole = qrand()%100;
        if (setrole < 70)       //80% chance of Monster
            bullets.push_back(new Monster());
        if (setrole >= 70 && setrole < 100)      //30% chance of points or hp
            bullets.push_back(new Bullet);
    }

    if (gameTimer%150 == 0)                   //boss spits fireballs ever 150 cycles
    {
        for (int i = 0; i <bullets.size(); i++)
        {
            if (bullets[i]->getShotType() == 'B')
                bullets[i]->spitFireballs();
        }
    }
}



void Dodger::timerEvent(QTimerEvent *event){        //for 1 loop of the game
    gameTimer++;
    if (gameTimer < 3000)                    //game progresses depending on score
    level1();
    else
        if (gameTimer > 3000 && gameTimer < 6000 )
            level2();
        else
            if (gameTimer > 6000)
                level3();

    for(int i=0; i <bullets.size(); i++)
    {
        if (bullets[i]->getShotType() == 'B')       //moves boss and his bullets -checks if he's still alive
        {
            Boss* boss = static_cast<Boss*>(bullets.at(i));

            if(boss->getLives() > 0)
            {
            if (gameTimer%5 == 0)
            {
                boss->moveDown();                 //move the boss and all of his fireballs
                vector<fireball*>* projectiles = boss->getFireballs();
                for (int i = 0; i < projectiles->size(); i++)
                    (*projectiles)[i]->moveDown();
            }
            }
            else                //if boss's lives reaches 0
            {
                boss = false;
                gameWon = true;
                endGame();
            }

        }
        else
         bullets[i]->moveDown();            //moves all other npcs ("automove")

    }

    if (keepLeft)
        hitbox->moveLeft();

    if (keepRight)
        hitbox->moveRight();

    if (keepUp)
        hitbox->moveUp();

    if (keepDown)
        hitbox->moveDown();

    if(hitbox->getShots() > 0)
    {
         vector <shot*>* projectiles = hitbox->getShots();
        for (int i=0; i < projectiles->size(); i++)
                    (*projectiles)[i]->moveDown();
    }

    checkCollisionBullets();

    if ((hitbox->getHP())== 0 || (gameWon))          //if you lost all HP, game ends or if boss is dead and game is won
        endGame();

    if (gameTimer% 100 == 0)          //point increment timer
        score++;

    if (bulletCooldown > 0)
        bulletCooldown--;
    repaint();
}

//aids in making smoother movements
void Dodger::keyReleaseEvent(QKeyEvent *event){

    if(!event->isAutoRepeat())
    {
    switch(event->key()){
    case Qt::Key_Left:
    {
        keepLeft = false;
        break;
    }
    case Qt::Key_Right:
    {
       keepRight = false;
       break;
    }
    case Qt::Key_Up:
    {
        keepUp = false;
        break;
    }
    case Qt::Key_Down:
    {
        keepDown = false;
        break;
    }
    }
    }
}

//basic movement and game-functions
void Dodger::keyPressEvent(QKeyEvent *event){

    if (!gamePaused){
        switch(event->key()){
        case Qt::Key_Left:
        {
            keepLeft = true;
            break;
        }
        case Qt::Key_Right:
        {
           keepRight = true;
            break;
        }
        case Qt::Key_Up:
        {
            keepUp = true;
            break;
        }
        case Qt::Key_Down:
        {
            keepDown = true;
            break;
             }
         case Qt::Key_Z:
        {
            if (score >= 100 && bulletCooldown == 0){
            hitbox->fireShot();
            bulletCooldown = 25;
            score-=100;
            }
        }
            break;
       case Qt::Key_Space:
       {startGame();
           gameNew= false;
       }
       break;
       case Qt::Key_P:
       {pauseToggle();
       }
           break;
       case Qt::Key_Q:
       {
       qApp->exit();
       }
       break;
      default:
           QWidget::keyPressEvent(event);
    }
   }
    else                //prevents user from "teleporting" while game paused
    {
        switch(event->key())
        {
        case Qt::Key_P:
        {pauseToggle();
        }
            break;
        case Qt::Key_Q:
        {
        qApp->exit();
        }
        break;
        default:
            QWidget::keyPressEvent(event);
        }
    }
}

void Dodger::startGame(){
    if (!gameStarted){
        if (gameOver)       //if the game reset, reset the game properties
        {
            gameTimer = 0;
            score = 500;
             hitbox->reset();                           //reset hitbox hp and position
        for (int i = 0; i < bullets.size(); i++)        //clear out vector of npcs
            delete bullets[i];
        bullets.clear();
        bullets.push_back(new Bullet);
        }

        gameOver = false;   //reset game status
        gameWon = false;
        gameStarted = true;
        boss = false;
        timerId=startTimer(5);   //start looping
    }
}

void Dodger::pauseToggle(){
    if (gamePaused){                    //unpauses game
        timerId = startTimer(5);
        gamePaused = false;
    }
        else{                       //pauses game
     gamePaused = true;
    killTimer(timerId);
    }
    }

void Dodger::endGame(){
    killTimer(timerId);         //ends loop
    gameOver = true;
    gameStarted = false;
    gameNew = true;
}

bool Dodger::checkCollisionBullets(){
    for (int i = 0; i <bullets.size(); i++)         //checks if hitbox and bullets collide
		{
        if (hitbox->getShots()->size() > 0)                //check hitbox's vector of shots for collisions
        {
            vector<shot*>* shotsfired = hitbox->getShots();
            for (int h = 0; h < shotsfired->size(); h++)
            {

                if (bullets[i]->getRect().intersects((*shotsfired)[h]->getRect()))
                    if((bullets[i]->getShotType() != '+') && (bullets[i]->getShotType() != 'P'))      //if shot collides with monster
                {

                    if (bullets[i]->getShotType() == 'B')
                    {
                          std::cout<<"hit boss!"<<std::endl;
                        bullets[i]->setLives(bullets[i]->getLives()-1);
                    }
                    else
                    {
                    delete bullets[i];
                    bullets[i] = bullets[bullets.size()-1];
                    bullets.pop_back();
                    }
                    delete (*shotsfired)[h];                                        //delete fireball
                    (*shotsfired)[h] = (*shotsfired)[shotsfired->size()-1];
                    (*shotsfired).pop_back();

                    std::cout<<"shot hit!"<<std::endl;
                    return true;
                }
            }
            }

        if ((hitbox->getRect()).intersects(bullets[i]->getRect()))
            {
        if ((bullets[i]->getShotType()) == 'V' || (bullets[i]->getShotType()) == 'Z')     //lose 1 HP if collides with normal Monsters
            hitbox->setHP((hitbox->getHP())-1);
		else
        if ((bullets[i]->getShotType()) == '+')     //gain 1 HP
            hitbox->setHP((hitbox->getHP())+1);
		else
        if ((bullets[i]->getShotType()) == 'P')     //gains 50 points
			score+=50;
        else
            if  ((bullets[i])->getShotType() == 'B')                    //auto-lose if collides with boss
            {
                 hitbox->setHP(0);
                 gameOver = true;
                 gameWon = false;
                 break;

            }

        delete bullets[i];
        bullets[i] = bullets[bullets.size()-1];
        bullets.pop_back();
        std::cout<<"hit!"<<std::endl;
        return true;
    }

        if (bullets[i]->getShotType() == 'B')                //check boss-type's vector of fireball for collisions
        {
            Boss* boss = static_cast<Boss*>(bullets.at(i));
            vector<fireball*>* shotsfired = boss->getFireballs();
            for (int i = 0; i < shotsfired->size(); i++)
            {
                if (hitbox->getRect().intersects((*shotsfired)[i]->getRect()))      //if user collides with fireball
                {
                    hitbox->setHP((hitbox->getHP())-1);                         //decrease HP

                    delete (*shotsfired)[i];                                        //delete fireball
                    (*shotsfired)[i] = (*shotsfired)[shotsfired->size()-1];
                    (*shotsfired).pop_back();

                    std::cout<<"bulletshot hit!"<<std::endl;
                    return true;


                }
            if(((*shotsfired)[i]->getRect().top()) > 700)    //if fireball at bottom of screen, delete it
              {
                delete (*shotsfired)[i];
                (*shotsfired)[i] = (*shotsfired)[shotsfired->size()-1];
                  (*shotsfired).pop_back();
              }
            }

        }

    }

        for(int i = 0; i <bullets.size(); i++)
         if((bullets[i]->getRect().top()) > 700)    //if bullet at bottom of screen, delete it
           {
             delete bullets[i];
             bullets[i] = bullets[bullets.size()-1];
               bullets.pop_back();

         }

        vector<shot*>* shotsfired = hitbox->getShots();
          for(int i = 0; i < shotsfired->size(); i++)
         if(((*shotsfired)[i]->getRect().bottom()) < 0)    //if shot at top of screen, delete it
           {
             delete (*shotsfired)[i];
             (*shotsfired)[i] = (*shotsfired)[shotsfired->size()-1];
               (*shotsfired).pop_back();
         }


	return false;	
}

