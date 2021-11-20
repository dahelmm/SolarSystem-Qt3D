#include "initsystem.h"


void InitSystem::setCameraPosition()
{
    return camera->setPosition(QVector3D(transformEarth->translation()));
}
//**************************************************************************************************************
Qt3DCore::QEntity *InitSystem::initUniverse()
{
    //создание сущности и сферы космоса
    universe = new Qt3DCore::QEntity(rootEntity);
    universeSphere = new Qt3DExtras::QSphereMesh(universe);
    universeSphere->setRadius(-3000);
    universeSphere->setRings(200);

    //текстура космоса
    universeTexture = new Qt3DExtras::QTextureMaterial(universe);
    imageUniverseTexture = new Qt3DRender::QTextureImage(universe);
    imageUniverseTexture->setSource(QUrl("qrc:/Textures/2k_stars+milky_way.jpg"));
    texture2D = new Qt3DRender::QTexture2D(universeTexture);
    texture2D->addTextureImage(imageUniverseTexture);
    texture2D->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));

    universeTexture->setTexture(texture2D);

    universeTransform = new Qt3DCore::QTransform();
    universe->addComponent(universeSphere);
    universe->addComponent(universeTexture);
    universe->addComponent(universeTransform);


    return universe;
}
//**************************************************************************************************************
Qt3DCore::QEntity *InitSystem::initSun()
{

    entitySun = new Qt3DCore::QEntity(rootEntity);
    sphereSun = new Qt3DExtras::QSphereMesh(entitySun);
    sphereSun->setRadius(500);
    sphereSun->setRings(100);

    //применение текстуры к сфере солнца
    textureSun = new Qt3DRender::QTextureLoader(entitySun);
    textureMaterialSun = new Qt3DExtras::QTextureMaterial(entitySun);
    textureSun->setSource(QUrl("qrc:/Textures/2k_sun.jpg"));
    textureMaterialSun->setTexture(textureSun);

    //модуль для управления сферой
    transformSun = new Qt3DCore::QTransform(entitySun);

    entitySun->addComponent(sphereSun);
    entitySun->addComponent(textureMaterialSun);
    entitySun->addComponent(transformSun);

    //настройка вращения солцна вокруг своей оси
    animationSun.setStartValue(QVariant(0.0));
    animationSun.setEndValue(QVariant(360.0));
    animationSun.setDuration(5*10000);
    animationSun.setLoopCount(-1);

    QObject::connect(&animationSun,&QVariantAnimation::valueChanged,transformSun, [this](const QVariant & value){
                     transformSun->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0,1,0),value.toFloat()));
    });
    animationSun.start();

    return entitySun;
}
//**************************************************************************************************************
Qt3DCore::QEntity *InitSystem::initEarth()
{
    //создание Земли
    earthEntity = new Qt3DCore::QEntity(rootEntity);
    sphereEarth= new Qt3DExtras::QSphereMesh(earthEntity);
    sphereEarth->setRadius(sphereSun->radius()/109);
//    sphereEarth->setRings(100);

    textureEarth= new Qt3DRender::QTextureLoader(earthEntity);
    textureMaterialEarth= new Qt3DExtras::QTextureMaterial(earthEntity);
    textureEarth->setSource(QUrl("qrc:/Textures/Tierra2k.jpg"));
    textureMaterialEarth->setTexture(textureEarth);

    //модуль для управления сферой
    transformEarth = new Qt3DCore::QTransform/*(earthEntity)*/;
    transformEarth->setTranslation(QVector3D(800.0,0.0,0.0));

    animationEarth.setStartValue(QVariant(0.0));
    animationEarth.setEndValue(QVariant(360.0));
    animationEarth.setDuration(1000);
    QObject::connect(&animationEarth,&QVariantAnimation::valueChanged,transformEarth,[this](const QVariant & value){
        transformEarth->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,0.0,value.toFloat())));
    });
    animationEarth.start();
//    transformEarth->setTranslation(QVector3D(800.0,0.0,0.0));
//    controllerEarth = new OrbitTransformController(transformEarth);
//    controllerEarth->setTarget(transformEarth);
//    controllerEarth->setRadius(800.0f);
//    controllerEarth->setViewCenter(transformSun->translation());

//    movieEarth = new QPropertyAnimation(transformEarth);
//    movieEarth->setTargetObject(controllerEarth);
//    movieEarth->setPropertyName("angle");
//    movieEarth->setStartValue(QVariant::fromValue(0));
//    movieEarth->setEndValue(QVariant::fromValue(360));
//    movieEarth->setDuration(10000);
//    movieEarth->setLoopCount(-1);
//    movieEarth->start();

    earthEntity->addComponent(sphereEarth);
    earthEntity->addComponent(transformEarth);
    earthEntity->addComponent(textureMaterialEarth);

    return earthEntity;
}
//**************************************************************************************************************
Qt3DCore::QEntity * InitSystem::initObj()
{
    //прочитать и отобразить obj файл
    voyadjerEntity = new Qt3DCore::QEntity(rootEntity);
    voyadjer = new Qt3DRender::QSceneLoader(voyadjerEntity);
    voyadjer->setSource(QUrl("qrc:/SpaceCraft/Voyager.obj"));

    //управление вояджером
    voyaTransform = new Qt3DCore::QTransform/*(voyadjerEntity)*/;

    controllerVoyadjer = new OrbitTransformController(voyaTransform);
    controllerVoyadjer->setTarget(voyaTransform);
    controllerVoyadjer->setViewCenter(transformEarth->translation());
    controllerVoyadjer->setRadius(100.0f);

    movieVoyadjer = new QPropertyAnimation(voyaTransform);
    movieVoyadjer->setTargetObject(controllerVoyadjer);
    movieVoyadjer->setPropertyName("angle");
    movieVoyadjer->setStartValue(QVariant::fromValue(0));
    movieVoyadjer->setEndValue(QVariant::fromValue(360));
    movieVoyadjer->setDuration(10000);
    movieVoyadjer->setLoopCount(-1);
    movieVoyadjer->start();

    voyadjerEntity->addComponent(voyadjer);
    voyadjerEntity->addComponent(voyaTransform);

    return voyadjerEntity;
}
//**************************************************************************************************************
InitSystem::InitSystem()
{
    rootEntity = new Qt3DCore::QEntity;//главная сущность

    initUniverse();

    initSun();

    initEarth();

    initObj();

    camera = view.camera();
    camera->lens()->setPerspectiveProjection(90,(float)view.width()/(float)view.height(),0.1f,10000.0f);
    camera->setViewCenter(QVector3D(0.0,0.0,0.0));
//    camera->setViewCenter(QVector3D(0.0,0.0,0.0));
    camera->setPosition(QVector3D(0.0,0.0,1500.0));

//    Qt3DCore::QTransform *cameraTransform = new Qt3DCore::QTransform(rootEntity);
//    cameraTransform->setTranslation(transformEarth->translation());
//    camera->addComponent(cameraTransform);

    cameraController = new customCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0);
    cameraController->setLinearSpeed(50.0);

    view.setRootEntity(rootEntity);
    view.show();
}
