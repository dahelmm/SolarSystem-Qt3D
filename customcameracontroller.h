#ifndef CUSTOMCAMERACONTROLLER_H
#define CUSTOMCAMERACONTROLLER_H

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DLogic>
#include <QApplication>

class customCameraController : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    customCameraController(Qt3DCore::QNode *parent = Q_NULLPTR);

    void setCamera(Qt3DRender::QCamera *camera);
    float lookSpeed() const;
    void setLookSpeed(float lookSpeed);
    float linearSpeed() const;
    void setLinearSpeed(float linearSpeed);

//    void moveCamera();



protected  slots:
    void activeChenged(bool isActive);
    void valueChanged(float value);
    void frameActionTriggered(float dt);

private:
    //подключение девайсов
    Qt3DInput::QKeyboardDevice *m_keyboardDevice;
    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QLogicalDevice *m_logicalDevice;

    //левая кнопка и кнопка вверх
    Qt3DInput::QAction *m_leftButtonAction;
    Qt3DInput::QAction *m_keyUpAction;
    Qt3DInput::QActionInput *m_leftButtonInput;
    Qt3DInput::QActionInput *m_keyUpInput;

    //кнопки приближения и отдаления камеры
    Qt3DInput::QActionInput *m_keyMinInput;
    Qt3DInput::QActionInput *m_keyPlusInput;
    Qt3DInput::QAction *m_keyMinAction;
    Qt3DInput::QAction *m_keyPlusAction;

    //кнопки переключения камеры на планеты
//    Qt3DInput::QAction *m_key1Action;
//    Qt3DInput::QAction *m_key2Action;
//    Qt3DInput::QAction *m_key3Action;
//    Qt3DInput::QAction *m_key4Action;
//    Qt3DInput::QAction *m_key5Action;
//    Qt3DInput::QAction *m_key6Action;
//    Qt3DInput::QAction *m_key7Action;
//    Qt3DInput::QAction *m_key8Action;
//    Qt3DInput::QAction *m_key9Action;
//    Qt3DInput::QActionInput *m_key1Input;
//    Qt3DInput::QActionInput *m_key2Input;
//    Qt3DInput::QActionInput *m_key3Input;
//    Qt3DInput::QActionInput *m_key4Input;
//    Qt3DInput::QActionInput *m_key5Input;
//    Qt3DInput::QActionInput *m_key6Input;
//    Qt3DInput::QActionInput *m_key7Input;
//    Qt3DInput::QActionInput *m_key8Input;
//    Qt3DInput::QActionInput *m_key9Input;

    //для перемещения при движении мышью
    Qt3DInput::QAxis *m_xAxis;
    Qt3DInput::QAxis *m_yAxis;
    Qt3DInput::QAnalogAxisInput *m_mouseXInput;
    Qt3DInput::QAnalogAxisInput *m_mouseYInput;

    Qt3DLogic::QFrameAction *m_frameAction;

    Qt3DRender::QCamera *m_camera;
    float m_lookSpeed;
    float m_linearSpeed;

//    bool m_key1Pressed;
//    bool m_key2Pressed;
//    bool m_key3Pressed;
//    bool m_key4Pressed;
//    bool m_key5Pressed;
//    bool m_key6Pressed;
//    bool m_key7Pressed;
//    bool m_key8Pressed;
//    bool m_key9Pressed;

    bool m_keyUpPressed;
    bool m_leftButtonPressed;
    bool m_keyMinPressed;
    bool m_keyPlusPressed;

    float m_dx;
    float m_dy;
};

#endif // CUSTOMCAMERACONTROLLER_H
