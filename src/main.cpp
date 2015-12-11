#include "GravityMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GravityMainWindow w;
    w.show();

    return a.exec();
}
