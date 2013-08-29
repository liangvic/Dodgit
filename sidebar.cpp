#include "sidebar.h"
#include <QImage>
#include <QPainter>
#include <QApplication>

Sidebar::Sidebar(QWidget *parent)
{
    HP = 0;
    score = 0;
}

Sidebar::~Sidebar()
{
}

void Sidebar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor pencolor("steelblue");
    QPen pen;
    pen.setColor(pencolor);
    pen.setWidth(8);
    painter.setPen(pen);

    QRect statusBox(5, 5, 190, 690);
    painter.drawRect(statusBox);

}

void Sidebar::setScore(int newscore){
    score = newscore;
}

void Sidebar::setHP(int newHP){
    HP = newHP;
}
