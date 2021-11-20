#ifndef INITSYSTEM_H
#define INITSYSTEM_H

#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QParallelAnimationGroup>

#include "customcameracontroller.h"
#include "orbittransformcontroller.h"
#include "math.h"
//#include "planeta.h"

class InitSystem
{
public:
    Qt3DCore::QEntity *rootEntity;//создание главной сущности
    Qt3DExtras::Qt3DWindow view; //создание главного окна

    //КОСМОС
    Qt3DCore::QEntity *universe; //сущность космоса
    Qt3DExtras::QSphereMesh *universeSphere; //сфера для космоса
    //применение текстуры
    Qt3DExtras::QTextureMaterial *universeTexture;
    Qt3DRender::QTextureImage *imageUniverseTexture;
    Qt3DRender::QTexture2D *texture2D;
    Qt3DCore::QTransform *universeTransform;//управление космосом

    //СОЛНЦЕ
    Qt3DCore::QEntity *entitySun; //сущность
    Qt3DExtras::QSphereMesh *sphereSun; //сфера
    Qt3DRender::QTextureLoader *textureSun; //загрузчик текстуры
    Qt3DExtras::QTextureMaterial *textureMaterialSun;
    Qt3DCore::QTransform *transformSun; //управление положением сферы
    QVariantAnimation animationSun;

    //СПУТНИК какого-либо объекта
    Qt3DCore::QEntity *sateliteEntity; //сущность будущего спутника
    Qt3DExtras::QSphereMesh *sateliteSphere; //сфера спутника
    Qt3DRender::QTextureLoader *sateliteTexture; //загрузчик текстур
    Qt3DExtras::QTextureMaterial *sateliteTextureMaterial;
    Qt3DCore::QTransform *sateliteTransform; //управление

    //ЗЕМЛЯ
    Qt3DCore::QEntity *earthEntity; //сущность
    Qt3DExtras::QSphereMesh *sphereEarth; //сфера
    Qt3DRender::QTextureLoader *textureEarth; //загрузчик текстур
    Qt3DExtras::QTextureMaterial *textureMaterialEarth;
    Qt3DCore::QTransform *transformEarth;
    OrbitTransformController *controllerEarth; //контроллер орбиты
    QPropertyAnimation *movieEarth; //анимация движения
    QVariantAnimation animationEarth;

    //Вояджер
    Qt3DCore::QEntity *voyadjerEntity;
    Qt3DRender::QSceneLoader *voyadjer;
    Qt3DCore::QTransform *voyaTransform;
    OrbitTransformController *controllerVoyadjer;
    QPropertyAnimation *movieVoyadjer;

    customCameraController *cameraController; //управление камерой
    Qt3DRender::QCamera *camera; //создание камеры

protected slots:
    void setCameraPosition(); //пробная

    Qt3DCore::QEntity *initUniverse(); //инициализация космоса
    Qt3DCore::QEntity *initSun(); //инициализация Солнца
    Qt3DCore::QEntity *initEarth(); //инициализация Земли
    Qt3DCore::QEntity *initObj(); //инициализация Вояджера

public:
    InitSystem(); //главная функция
};

#endif // INITSYSTEM_H
