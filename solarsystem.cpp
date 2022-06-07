#include "solarsystem.h"
#include "ui_solarsystem.h"
#include <QObjectPicker>
#include <Qt3DRender>
#include <QPhongMaterial>
#include <Qt3DExtras>



SolarSystem::SolarSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SolarSystem)
{
    ui->setupUi(this);
    rootEntity = new Qt3DCore::QEntity;//главная сущность;

    view = new Qt3DExtras::Qt3DWindow();
//    ui->widget->resize(ui->widget->maximumSize());
//    ui->widget->resize(QGuiApplication::screens().at(0)->geometry().width(),QGuiApplication::screens().at(0)->geometry().height());
    QWidget *container  = QWidget::createWindowContainer(view,ui->centralwidget);
    QGridLayout *lay = new QGridLayout(ui->widget);
    lay->addWidget(container);
    ui->widget->setLayout(lay);
//    container->resize(ui->widget->width(),ui->widget->height());

    qDebug()<<container->size()<<ui->centralwidget->size()<<view->size();

    camera = view->camera();
    camera->setPosition(QVector3D(0,0.0,3000.0));
    camera->lens()->setPerspectiveProjection(45,(float)view->width()/(float)view->height(),0.1f,100000.0f);

//    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController = new customCameraController(rootEntity);


    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0);
    cameraController->setLinearSpeed(50.0);

    universe = new Qt3DCore::QEntity(rootEntity);
    universeSphere = new Qt3DExtras::QSphereMesh(universe);
    universeSphere->setRadius(-25000);
    universeSphere->setRings(200);

    //текстура космоса
    universeTexture = new Qt3DExtras::QTextureMaterial(universe);
    imageUniverseTexture = new Qt3DRender::QTextureImage(universe);
    imageUniverseTexture->setSource(QUrl("qrc:/Textures/8k_stars_milky_way.jpg"));
    texture2D = new Qt3DRender::QTexture2D(universeTexture);
    texture2D->addTextureImage(imageUniverseTexture);
    texture2D->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    universeTexture->setTexture(texture2D);



    entitySun = new Qt3DCore::QEntity(universe);
    transformSun = new Qt3DCore::QTransform(entitySun);
    sunSphere = new Qt3DExtras::QSphereMesh(entitySun);
    sunSphere->setRadius(700);
    sunSphere->setRings(100);
    sunSphere->setSlices(50);



    sunTextureLoader = new Qt3DRender::QTextureLoader(entitySun);
    sunTextureMaterial = new Qt3DExtras::QTextureMaterial(entitySun);
    sunTextureLoader->setSource(QUrl("qrc:/Textures/8k_sun.jpg"));
    sunTextureMaterial->setTexture(sunTextureLoader);
    sunTransform=new Qt3DCore::QTransform(entitySun);

    entitySun->addComponent(sunSphere);
    entitySun->addComponent(sunTextureMaterial);
    entitySun->addComponent(sunTransform);
    entitySun->addComponent(transformSun);

    sunAnimation.setStartValue(QVariant(0.0));
    sunAnimation.setEndValue(QVariant(360.0));
    sunAnimation.setDuration(600*100);
    sunAnimation.setLoopCount(-1);
    QObject::connect(&sunAnimation,&QVariantAnimation::valueChanged,sunTransform, [this](const QVariant & value){
                     transformSun->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0,1,0),value.toFloat()));
    });
    sunAnimation.start();


    Mercury = new planeta   (universe,QUrl("qrc:/Textures/2k_mercury.jpg"),         sunSphere->radius()+58,  sunSphere->radius()/285,   1407,   88,     46,     70,     0.205);
    Venus = new planeta     (universe,QUrl("qrc:/Textures/2k_venus_atmosphere.jpg"),sunSphere->radius()+108, sunSphere->radius()/115,   5832,   224,    107,    108,    0.007);
    Earth = new planeta     (universe,QUrl("qrc:/Textures/Tierra2k.jpg"),           sunSphere->radius()+150, sunSphere->radius()/109,   23,     365,    147,    152,    0.017);
    Mars = new planeta      (universe,QUrl("qrc:/Textures/2k_mars.jpg"),            sunSphere->radius()+228, sunSphere->radius()/205,   24,     686,    207,    249,    0.093);
    Jupiter = new planeta   (universe,QUrl("qrc:/Textures/2k_jupiter.jpg"),         sunSphere->radius()+778, sunSphere->radius()/10,    10,     4380,   741,    816,    0.048);
    Saturn = new planeta    (universe,QUrl("qrc:/Textures/2k_saturn.jpg"),          sunSphere->radius()+1429,sunSphere->radius()/12,    11,     10585,  1350,   1503,   0.055);
    Uran = new planeta      (universe,QUrl("qrc:/Textures/2k_uranus.jpg"),          sunSphere->radius()+2875,sunSphere->radius()/27,    17,     30660,  2735,   3006,   0.046);
    Neptune = new planeta   (universe,QUrl("qrc:/Textures/2k_neptune.jpg"),         sunSphere->radius()+4497,sunSphere->radius()/28,    16,     59860,  4460,   4537,   0.009);

    Luna = new planeta      (Earth->getEntity(),QUrl("qrc:/Textures/8k_moon.jpg"),Earth->getRadius()+(Earth->getRadius()/3.67)+0.384,Earth->getRadius()/3.67,24,27,0.36,0.4,0.055);





    Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(Saturn->getEntity());
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh(torusEntity);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform(torusEntity);


    torusMesh->setRadius(Saturn->getRadius()+80);
    torusMesh->setMinorRadius(57.5);
    torusMesh->setSlices(2);
    torusMesh->setRings(2000);
    torusMesh->setEnabled(true);

    Qt3DRender::QTextureLoader *torusTextureLoader = new Qt3DRender::QTextureLoader(torusEntity);
    Qt3DExtras::QTextureMaterial *torusTextureMaterial = new Qt3DExtras::QTextureMaterial(torusEntity);


    Qt3DCore::QTransform *torusMaterialTransform = new Qt3DCore::QTransform(torusTextureLoader);
    torusMaterialTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),90));
    torusTextureLoader->setSource(QUrl("qrc:/Textures/8k_saturn_ring_alpha.png"));

    torusTextureMaterial->setAlphaBlendingEnabled(true);
    torusTextureMaterial->setTexture(torusTextureLoader);
    torusTextureLoader->setSamples(22);
    torusTextureMaterial->setTextureOffset(QVector2D(1,0));


    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusTransform);
    torusEntity->addComponent(torusMaterialTransform);
    torusEntity->addComponent(torusTextureMaterial);

    universe->addComponent(universeSphere);
    universe->addComponent(universeTexture);

    view->setRootEntity(rootEntity);

}

SolarSystem::~SolarSystem()
{
    delete ui;
}

void SolarSystem::focusEarth()
{
    camera->setViewCenter(QVector3D(sunTransform->translation()));
    camera->viewSphere(Earth->getTranslation(),Earth->getRadius()+50);
    camera->setUpVector(QVector3D(0.0,1.0,0.0));
}

void SolarSystem::focusMars()
{
    camera->viewSphere(Mars->getTranslation(),Mars->getRadius()+50);
}

void SolarSystem::focusJupiter()
{
    camera->viewSphere(Jupiter->getTranslation(),Jupiter->getRadius()+100);
}

void SolarSystem::focusSaturn()
{
    camera->viewSphere(Saturn->getTranslation(),Saturn->getRadius()+100);
}


void SolarSystem::focusUran()
{
    camera->viewSphere(Uran->getTranslation(),Uran->getRadius()+50);

}


void SolarSystem::focusNeptune()
{
    camera->viewSphere(Neptune->getTranslation(),Neptune->getRadius()+50);

}





void SolarSystem::focusMerc()
{
    camera->viewSphere(Mercury->getTranslation(),Mercury->getRadius()+50);

}


void SolarSystem::focusVenus()
{
    camera->viewSphere(Venus->getTranslation(),Venus->getRadius()+50);

}

void SolarSystem::focusSun()
{
    camera->setViewCenter(QVector3D(transformSun->translation()));
}






void SolarSystem::on_rB_Sun_toggled(bool checked)
{

//        disconnect(Earth->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusEarth()));
//        disconnect(Mars->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMars()));
//        disconnect(Jupiter->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusJupiter()));
//        disconnect(Saturn->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusSaturn()));
//        disconnect(Uran->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusUran()));
//        disconnect(Neptune->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusNeptune()));
//        disconnect(Mercury->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMerc()));
//        disconnect(Venus->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusVenus()));
        camera->setViewCenter(QVector3D(0.0,0.0,0.0));
        camera->setPosition(QVector3D(0,0.0,3000.0));


}

void SolarSystem::on_rB_Merc_toggled(bool checked)
{
    if(checked==true)
    {

        connect(Mercury->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMerc()));
    }
    else
    {
        disconnect(Mercury->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMerc()));
    }
}

void SolarSystem::on_rB_Venus_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Venus->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusVenus()));
    }
    else
    {
        disconnect(Venus->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusVenus()));
    }
}



void SolarSystem::on_rB_Earth_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Earth->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusEarth()));



    }
    else
    {
        disconnect(Earth->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusEarth()));
    }
}

void SolarSystem::on_rB_Mars_toggled(bool checked)
{
    if(checked==true)
    {
//        focusPlanet(Mars);
        connect(Mars->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMars()));

    }
    else
    {
        disconnect(Mars->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusMars()));
    }
}

void SolarSystem::on_rB_Jupiter_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Jupiter->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusJupiter()));
    }
    else
    {
        disconnect(Jupiter->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusJupiter()));
    }
}

void SolarSystem::on_rB_Saturn_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Saturn->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusSaturn()));

    }
    else
    {
        disconnect(Saturn->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusSaturn()));
    }
}

void SolarSystem::on_rB_Uran_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Uran->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusUran()));
    }
    else
    {
        disconnect(Uran->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusUran()));
    }
}

void SolarSystem::on_rB_Neptune_toggled(bool checked)
{
    if(checked==true)
    {
        connect(Neptune->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusNeptune()));
    }
    else
    {
        disconnect(Neptune->animationMovie,SIGNAL(valueChanged(QVariant)),this,SLOT(focusNeptune()));
    }
}
