#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <QWidget>

class Sidebar: public QWidget
{
    Q_OBJECT

private:
    int score;
    int HP;

public:
    Sidebar(QWidget* parent);
    ~Sidebar();

    void paintEvent(QPaintEvent *event);
    void setScore(int newscore);
    void setHP(int newHP);
};

#endif
