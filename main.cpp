#include "solarsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SolarSystem w;
    w.showMaximized();

    return a.exec();
}
