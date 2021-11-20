#include "initsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    InitSystem w;
    return app.exec();
}
