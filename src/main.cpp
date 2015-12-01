#include "GravityMainWindow.h"
#include <QApplication>

/*

Tutorial Reference:
https://www.youtube.com/watch?v=8ntEQpg7gck

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GravityMainWindow w;
    w.show();

    return a.exec();
}
