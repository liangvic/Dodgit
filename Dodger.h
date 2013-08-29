#ifndef DODGER_H
#define DODGER_H

#include "hitbox.h"
#include "boss.h"
#include "monster.h"
//#include "sidebar.h"
#include <vector>
#include <QWidget>
#include <QKeyEvent>

class Dodger: public QWidget
{
    Q_OBJECT

public:
    Dodger(QWidget *parent = 0);
    ~Dodger();
protected:
    void paintEvent(QPaintEvent *event);        //paints scene
    void timerEvent(QTimerEvent *event);        //loops game
    void keyReleaseEvent(QKeyEvent *);          //helps for smoother movement
    void keyPressEvent(QKeyEvent *event);       //to determine movement

    void level1();
    void level2();
    void level3();
    void startGame();                           //resets game and starts it
    void pauseToggle();                         //pauses timer
    void endGame();                             //sets game status
    bool checkCollisionBullets();               //check collisions between objects
private:
    HitBox* hitbox;                             //player
    std::vector<Bullet*> bullets;               //npc objects

    int timerId;                            //timer for loop
    int gameTimer, bulletCooldown;                        //game timer
    int score;
    bool gameOver, gameWon, gameStarted, gamePaused, gameNew;
    bool boss;                              //checks if boss has been summoned
    bool keepLeft, keepRight, keepDown, keepUp;

};

#endif
