#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QMainWindow>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QParallelAnimationGroup>

#include "customcameracontroller.h"
#include <QMainWindow>
#include "planeta.h"
#include <QRadioButton>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class SolarSystem; }
QT_END_NAMESPACE

class SolarSystem : public QMainWindow
{
    Q_OBJECT

public:
    SolarSystem(QWidget *parent = nullptr);
    ~SolarSystem();

    Qt3DCore::QEntity *rootEntity;//РіР»Р°РІРЅР°СЏ СЃСѓС‰РЅРѕСЃС‚СЊ
    Qt3DExtras::Qt3DWindow *view; //РіР»Р°РІРЅРѕРµ РѕРєРЅРѕ

    planeta *Mercury;
    planeta *Venus;
    planeta *Earth;
    planeta *Mars;
    planeta *Jupiter;
    planeta *Saturn;
    planeta *Uran;
    planeta *Neptune;

    planeta *Luna;




    //РљРћРЎРњРћРЎ
    Qt3DCore::QEntity *universe; //СЃСѓС‰РЅРѕСЃС‚СЊ РєРѕСЃРјРѕСЃР°
    Qt3DExtras::QSphereMesh *universeSphere; //СЃС„РµСЂР° РґР»СЏ РєРѕСЃРјРѕСЃР°
    //РїСЂРёРјРµРЅРµРЅРёРµ С‚РµРєСЃС‚СѓСЂС‹
    Qt3DExtras::QTextureMaterial *universeTexture;
    Qt3DRender::QTextureImage *imageUniverseTexture;
    Qt3DRender::QTexture2D *texture2D;

    //РЎРћР›РќР¦Р•
    Qt3DCore::QEntity *entitySun;
    Qt3DCore::QTransform *transformSun;
    Qt3DExtras::QSphereMesh *sunSphere;
    Qt3DRender::QTextureLoader *sunTextureLoader;
    Qt3DExtras::QTextureMaterial *sunTextureMaterial;
    Qt3DCore::QTransform *sunTransform;
    QVariantAnimation sunAnimation;

    void focusPlanet(planeta *activePlanet);


    Qt3DRender::QCamera *camera;
    customCameraController *cameraController;


    bool testt;
public slots:
    void focusSun();
    void focusMerc();
    void focusVenus();
    void focusEarth();
    void focusMars();
    void focusJupiter();
    void focusSaturn();
    void focusUran();
    void focusNeptune();

private slots:
    void on_rB_Sun_toggled(bool checked);
    void on_rB_Merc_toggled(bool checked);
    void on_rB_Venus_toggled(bool checked);


    void on_rB_Earth_toggled(bool checked);

    void on_rB_Mars_toggled(bool checked);

    void on_rB_Jupiter_toggled(bool checked);

    void on_rB_Saturn_toggled(bool checked);

    void on_rB_Uran_toggled(bool checked);

    void on_rB_Neptune_toggled(bool checked);

private:
    Ui::SolarSystem *ui;
};
#endif // SOLARSYSTEM_H
