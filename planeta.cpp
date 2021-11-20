#include "planeta.h"


Planeta::Planeta(QString name, double aphelion, double perihelion,
                 double peroidOrbital, double periodRotation,
                 QString texturePath, double size, double mood,
                 Planeta *sateliteOf):
    nameP(name),
    aphelionP(aphelion),
    perihelionP(perihelion),
    periodOrbitalP(peroidOrbital),
    rotationP(periodRotation),
    texturePath(texturePath),
    sizeP(size),
    moodZP(mood),
    moodXP(rand()%180),
    sateliteOf(sateliteOf)
{

}

void Planeta::Painter()
{

}

void Planeta::Orbita(double grad, double escalaRotationEje)
{
    const float pi = 3.1416;
    const float gradusToRadian = 57.29577951;
    double translateSistemaX = 0.05 * (aphelionP + perihelionP);
    double translateSistemaZ = 0.05 * (aphelionP + perihelionP);

    if(nameP == "Sun")
        pX = -2;
    else
        pX = -cos((double)(currentPositionSystem/gradusToRadian + pi))*translateSistemaX;
    pY = 0;

    if(sateliteOf == NULL)
        pZ = sin((double)(currentPositionSystem/gradusToRadian + pi)) * translateSistemaZ;
    else
        pZ = sin((double)(currentPositionSystem/gradusToRadian + pi)) * translateSistemaX;

    if(sateliteOf != NULL)
    {
        Qt3DCore::QEntity *loon = new Qt3DCore::QEntity(initSystem.rootEntity);
        Qt3DExtras::QSphereMesh *loonSphere = new Qt3DExtras::QSphereMesh(loon);
        loonSphere->setRadius(sizeP);

        Qt3DRender::QTextureLoader *loonTexture = new Qt3DRender::QTextureLoader(loon);
        Qt3DExtras::QTextureMaterial *loonTextureMaterial = new Qt3DExtras::QTextureMaterial(loon);
        loonTexture->setSource(texturePath);
        loonTextureMaterial->setTexture(loonTexture);

        Qt3DCore::QTransform *loonTransform = new Qt3DCore::QTransform(loon);
        loonTransform->setTranslation(QVector3D(sateliteOf->pX,sateliteOf->pY,sateliteOf->pZ));
        loonTransform->rotateAround(loonTransform->translation(),40,QVector3D(0,1,0));

        loon->addComponent(loonSphere);
        loon->addComponent(loonTransform);
        loon->addComponent(loonTextureMaterial);
        loon->setObjectName(nameP);
    }

    if(sateliteOf == NULL && nameP != "Sun")
    {
        Qt3DCore::QEntity *planets = new Qt3DCore::QEntity(initSystem.rootEntity);
        Qt3DExtras::QSphereMesh *planetSphere = new Qt3DExtras::QSphereMesh(planets);
        planetSphere->setRadius(sizeP);

        Qt3DRender::QTextureLoader *planetTexture = new Qt3DRender::QTextureLoader(planets);
        Qt3DExtras::QTextureMaterial *planetTextureMaterial = new Qt3DExtras::QTextureMaterial(planets);
        planetTexture->setSource(texturePath);
        planetTextureMaterial->setTexture(planetTexture);

        Qt3DCore::QTransform *planetTransform = new Qt3DCore::QTransform(planets);
        planetTransform ->setTranslation(QVector3D(-(translateSistemaX+translateSistemaZ)/3,0.0,0.0));
        planetTransform->setScale3D(QVector3D(1,1,translateSistemaZ/translateSistemaX));
        Qt3DRender::QGeometryRenderer *trassa = new Qt3DRender::QGeometryRenderer(initSystem.rootEntity);

        //НУжно понять, как передать transformSun параметры для установки местоположения, вращения и увеличения размера
    }

}
