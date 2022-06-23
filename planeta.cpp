#include "planeta.h"
#include <math.h>

const double PI = 3.1416;
const double gradToRad = 57.29577951;
const double radToGrad = 0.0174533;

planeta::planeta(Qt3DCore::QEntity *parent,
                 QUrl path,
                 float distance,
                 float radius,
                 float periodRotationAxis,
                 float periodRotaion,
                 double perig,
                 double apog,
                 double excentr,
                 Qt3DCore::QTransform *targetRotation)
    :m_peroidRotation(periodRotaion)
{
    geometry = new Qt3DRender::QGeometry(parent);

    bufferBytes.resize(4*360*sizeof(float));
    float *positions = reinterpret_cast<float*>(bufferBytes.data());

    apog+=distance;
    perig+=distance;

    double A = apog+perig;
    double a = A/2;
    double b = a * sqrt(1-(excentr*excentr));

    parentEntity = new Qt3DCore::QEntity(parent);
    transformMovie = new Qt3DCore::QTransform(parentEntity);
    transformParent = new Qt3DCore::QTransform(parentEntity);
    animationMovie = new QPropertyAnimation(parentEntity);
    animationMovie->setTargetObject(transformMovie);
    animationMovie->setStartValue(QVariant(0.0));
    animationMovie->setEndValue(QVariant(360.0));
    animationMovie->setDuration(periodRotaion*10000);
    animationMovie->setLoopCount(-1);

    animationMovie->start();

    QObject::connect(animationMovie,&QPropertyAnimation::valueChanged,transformMovie,[=](const QVariant & value){

        double fi = atan2(a*(sin(value.toFloat()*radToGrad)*gradToRad),b*(cos(value.toFloat()*radToGrad)*gradToRad))*gradToRad;

        x = (double) (a*((cos(fi))));
        z = (double) (b*((sin(fi))));
        transformMovie->setTranslation(QVector3D(x,0,z));
        if(countPoint <= (360*3))
        {
//            *positions = transformMovie->translation().x();
//            *positions = transformMovie->translation().y();
//            *positions = transformMovie->translation().z();
            countPoint++;
        }
    });
    *positions = 1000;
    *positions = 0;
    *positions = 0;


    buf = new Qt3DRender::QBuffer(geometry);
    buf->setData(bufferBytes);

    positionAttribute = new Qt3DRender::QAttribute(geometry);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buf);
    positionAttribute->setByteStride(3*sizeof(float));
    positionAttribute->setCount(2);
    geometry->addAttribute(positionAttribute);

    line = new Qt3DRender::QGeometryRenderer(parent);
    line->setGeometry(geometry);
    line->setPrimitiveType((Qt3DRender::QGeometryRenderer::Lines));

    materialLine = new Qt3DExtras::QPhongMaterial(parent);
    materialLine->setAmbient(Qt::white);

    entityGeometry = new Qt3DCore::QEntity(parent);
    entityGeometry->addComponent(line);
    entityGeometry->addComponent(materialLine);

    entity = new Qt3DCore::QEntity(parentEntity);
    transformEntity = new Qt3DCore::QTransform(entity);
    entitySphere = new Qt3DExtras::QSphereMesh(entity);
    entitySphere->setRadius(radius);
    entitySphere->setRings(1000);
    entitySphere->setSlices(50);

    Qt3DRender::QTextureLoader *textureLoaderEntity = new Qt3DRender::QTextureLoader(entity);
    Qt3DExtras::QTextureMaterial *textureMaterialEntity = new Qt3DExtras::QTextureMaterial(entity);
    textureLoaderEntity->setSource(path);
    textureMaterialEntity->setTexture(textureLoaderEntity);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial;
    material->setDiffuse(QVariant::fromValue<Qt3DRender::QAbstractTexture *>(textureLoaderEntity));
    material->setShininess(-100);
    material->setAmbient(QColor(70,70,70));

    animationEntity = new QPropertyAnimation(entity);
    animationEntity->setTargetObject(transformEntity);
    animationEntity->setStartValue(QVariant(0.0));
    animationEntity->setEndValue(QVariant(360.0));
    animationEntity->setDuration(periodRotationAxis*1000);
    animationEntity->setLoopCount(-1);

    animationEntity->start();

    QObject::connect(animationEntity,&QPropertyAnimation::valueChanged,transformEntity,[=](const QVariant & value){
                transformEntity->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,value.toFloat(),0.0)));
    });

    entity->addComponent(textureMaterialEntity);
    entity->addComponent(transformEntity);
    entity->addComponent(entitySphere);
    entity->addComponent(material);

    parentEntity->addComponent(transformMovie);


}



float planeta::getRadius()
{
    return entitySphere->radius();
}

float planeta::getAngle()
{
    return angle;
}

Qt3DCore::QEntity *planeta::getEntity()
{
    return entity;
}

QVector3D planeta::getTranslation()
{
    return transformMovie->translation();
}

float planeta::getPeriod()
{
    return m_peroidRotation;
}

Qt3DCore::QTransform * planeta::getTransform()
{
    return transformMovie;
}



