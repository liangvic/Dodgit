#include <QDesktopWidget>
#include <QApplication>
#include "Dodger.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth, screenHeight;

    int WIDTH = 600;
    int HEIGHT = 700;

    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;
    widget.setGeometry(x, y, WIDTH, HEIGHT);
    widget.setFixedSize(WIDTH, HEIGHT);

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Dodger GameEx;

    GameEx.setWindowTitle("Genbulhel");
    GameEx.show();
    center(GameEx);

    return app.exec();


}
