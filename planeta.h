#ifndef PLANETA_H
#define PLANETA_H

#include <QString>
#include <math.h>
#include "initsystem.h"



class Planeta
{
public:

    InitSystem initSystem;

    float radio = 100.0;
    QString nameP;
    double aphelionP;
    double perihelionP;
    double periodOrbitalP;
    double rotationP;
    double moodXP;
    double moodZP;
    double sizeP;
    double deltaTime;

    double currentLocation;
    double currentPositionSystem;

    double pX,pY,pZ;

    QString texturePath;
    Planeta *sateliteOf;

    Planeta(QString name, double aphelion, double perihelion, double peroidOrbital, double periodRotation,
            QString texturePath, double size, double mood,
            Planeta *sateliteOf = NULL);

    void Painter();

    void Orbita(double grad,double escalaRotationEje);


};

#endif // PLANETA_H
