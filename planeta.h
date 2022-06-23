#ifndef PLANETA_H
#define PLANETA_H

#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QParallelAnimationGroup>

#include "customcameracontroller.h"

class planeta
{
public:
    planeta(Qt3DCore::QEntity *parent, QUrl path, float distance, float radius, float periodRotationAxis,  float periodRotaion, double perig, double apog, double excentr, Qt3DCore::QTransform *targetRotation = nullptr);


    Qt3DCore::QEntity *parentEntity;
    Qt3DCore::QTransform *transformParent;
    Qt3DCore::QTransform *transformEntity;
    Qt3DCore::QTransform *transformMovie;
    Qt3DRender::QCamera *camera();
    Qt3DExtras::QSphereMesh *entitySphere;
    Qt3DCore::QEntity *entity;

    Qt3DRender::QGeometry *geometry;
    Qt3DRender::QBuffer *buf;
    Qt3DRender::QAttribute *positionAttribute;
    Qt3DRender::QGeometryRenderer *line;
    Qt3DExtras::QPhongMaterial *materialLine;
    Qt3DCore::QEntity *entityGeometry;


    QByteArray bufferBytes;
    QByteArray indexBytes;

    bool signalOfActivation;


    QPropertyAnimation *animationEntity;
    QPropertyAnimation *animationMovie;

    float getRadius();
    float getAngle();
    Qt3DCore::QEntity *getEntity();
    QVector3D getTranslation();
    float getPeriod();
    Qt3DCore::QTransform *getTransform();
    int countPoint = 0;

private:
    float m_peroidRotation;
    double x;
    double y;
    double z;
    float angle;
};

#endif // PLANETA_H
