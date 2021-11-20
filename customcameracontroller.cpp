#include "customcameracontroller.h"


customCameraController::customCameraController(Qt3DCore::QNode *parent) :
    Qt3DCore::QEntity(parent)
{
    //признак нажатия кнопки
//    m_key1Pressed = false;
//    m_key2Pressed = false;
//    m_key3Pressed = false;
//    m_key4Pressed = false;
//    m_key5Pressed = false;
//    m_key6Pressed = false;
//    m_key7Pressed = false;
//    m_key8Pressed = false;
//    m_key9Pressed = false;

    m_keyUpPressed = false;
    m_leftButtonPressed = false;
    m_keyMinPressed = false;
    m_keyPlusPressed = false;
    m_dx = 0;
    m_dy = 0;
    m_lookSpeed = 180.0;
    m_linearSpeed = 50.0;
    m_camera = 0;

    m_keyboardDevice = new Qt3DInput::QKeyboardDevice(this);
    m_mouseDevice = new Qt3DInput::QMouseDevice(this);
    m_logicalDevice = new Qt3DInput::QLogicalDevice(this);
    m_leftButtonAction = new Qt3DInput::QAction(this);
    m_keyUpAction = new Qt3DInput::QAction(this);
    m_keyUpInput = new Qt3DInput::QActionInput(this);

    m_keyMinInput = new Qt3DInput::QActionInput(this);
    m_keyPlusInput = new Qt3DInput::QActionInput(this);
    m_keyMinAction = new Qt3DInput::QAction(this);
    m_keyPlusAction = new Qt3DInput::QAction(this);

    m_leftButtonInput = new Qt3DInput::QActionInput(this);
    m_xAxis = new Qt3DInput::QAxis(this);
    m_yAxis = new Qt3DInput::QAxis(this);
    m_mouseXInput = new Qt3DInput::QAnalogAxisInput(this);
    m_mouseYInput = new Qt3DInput::QAnalogAxisInput(this);
    m_frameAction = new Qt3DLogic::QFrameAction(this);
    m_camera =  new Qt3DRender::QCamera(this);

    m_keyUpInput->setButtons(QVector<int>() << Qt::Key_W);
    m_keyUpInput->setSourceDevice(m_keyboardDevice);
    m_keyUpAction->addInput(m_keyUpInput);
    m_keyUpAction->setObjectName("Key_Up");

    //левая кнопка мыши
    m_leftButtonInput->setButtons(QVector<int>() << Qt::LeftButton);
    m_leftButtonInput->setSourceDevice(m_mouseDevice);
    m_leftButtonAction->addInput(m_leftButtonInput);
    m_leftButtonAction->setObjectName("Left_button");

    //кнопка настройки камеры на Меркурий
//    m_key1Input->setButtons(QVector<int>()<<Qt::Key_1);
//    m_key1Input->setSourceDevice(m_keyboardDevice);
//    m_key1Action->addInput(m_key1Input);
//    m_key1Action->setObjectName("CameraMerc");

    //кнопка настройки камеры на Землю
//    m_key3Input->setButtons(QVector<int>()<<Qt::Key_3);
//    m_key3Input->setSourceDevice(m_keyboardDevice);
//    m_key3Action->addInput(m_key3Input);
//    m_key3Action->setObjectName("CameraEarth");

    m_mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
    m_mouseXInput->setSourceDevice(m_mouseDevice);
    m_xAxis->addInput(m_mouseXInput);
    m_xAxis->setObjectName("Axis_x");

    m_mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
    m_mouseYInput->setSourceDevice(m_mouseDevice);
    m_yAxis->addInput(m_mouseYInput);
    m_yAxis->setObjectName("Axis_y");

    m_keyMinInput->setButtons(QVector<int>() <<Qt::Key_Up);
    m_keyMinInput->setSourceDevice(m_keyboardDevice);
    m_keyMinAction->addInput(m_keyMinInput);
    m_keyMinAction->setObjectName("Key_Down");

    m_keyPlusInput->setButtons(QVector<int>() <<Qt::Key_Down);
    m_keyPlusInput->setSourceDevice(m_keyboardDevice);
    m_keyPlusAction->addInput(m_keyPlusInput);
    m_keyPlusAction->setObjectName("Key_Plus");

    m_logicalDevice->addAction(m_leftButtonAction);
    m_logicalDevice->addAction(m_keyUpAction);
    m_logicalDevice->addAction(m_keyMinAction);
    m_logicalDevice->addAction(m_keyPlusAction);
    m_logicalDevice->addAxis(m_xAxis);
    m_logicalDevice->addAxis(m_yAxis);

    connect(m_xAxis,SIGNAL(valueChanged(float)),this, SLOT(valueChanged(float)));
    connect(m_yAxis,SIGNAL(valueChanged(float)),this, SLOT(valueChanged(float)));
    connect(m_leftButtonAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChenged(bool)));
    connect(m_keyUpAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChenged(bool)));
    connect(m_keyPlusAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChenged(bool)));
    connect(m_keyMinAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChenged(bool)));

    connect(m_frameAction, SIGNAL(triggered(float)), this, SLOT(frameActionTriggered(float)));

}

void customCameraController::setCamera(Qt3DRender::QCamera *camera)
{
    m_camera = camera;
}

float customCameraController::lookSpeed() const
{
    return m_lookSpeed;
}

void customCameraController::setLookSpeed(float lookSpeed)
{
    m_lookSpeed = lookSpeed;
}

float customCameraController::linearSpeed() const
{
    return m_linearSpeed;
}

void customCameraController::setLinearSpeed(float linearSpeed)
{
    m_linearSpeed = linearSpeed;
}



void customCameraController::activeChenged(bool isActive)
{
    if((sender()->objectName()) == "Left_button")
    {
        m_leftButtonPressed = isActive;
    } else if ((sender()->objectName()) == "Key_Down")
    {
        m_keyMinPressed = isActive;
    }
    else if (sender()->objectName() == "Key_Plus") {
        m_keyPlusPressed = isActive;
    }
//    else if(sender()->objectName()=="CameraEarth")
//    {
//        m_key3Pressed = isActive;
//    }
}

void customCameraController::valueChanged(float value)
{
    if(sender()->objectName() == "Axis_x")
    {
        m_dx = value;
    }
    else if (sender()->objectName() == "Axis_y")
    {
        m_dy = value;
    }
}

void customCameraController::frameActionTriggered(float dt)
{    
    if(m_camera == 0) return;


    if(m_leftButtonPressed == true)
    {
        m_camera->panAboutViewCenter(-m_dx * m_lookSpeed * dt);
        m_camera->tiltAboutViewCenter(-m_dy * m_lookSpeed * dt);
    }
    QVector3D posCamera = m_camera->position();
    float cX = posCamera.x();
    float cY = posCamera.y();
    float cZ = posCamera.z();
    if (m_keyMinPressed ==true)
    {
        if((cX>0.0)||(cY>0.0)||(cZ>0.0))
        {
            posCamera.setX(cX - dt*100);
            posCamera.setY(cY - dt*100);
            posCamera.setZ(cZ - dt*100);
            if(cX<=0.0)
            {
                posCamera.setX(cX + dt*100);
            }
            if(cY<=0.0)
            {
                posCamera.setY(cY + dt*100);
            }
            if(cZ<=0.0)
            {
                posCamera.setZ(cZ + dt*100);
            }
        }
        m_camera->setPosition(posCamera);
    }

    if (m_keyPlusPressed == true)
    {
        if((cX>0.0)||(cY>0.0)||(cZ>0.0))
        {
            posCamera.setX(cX + dt*100);
            posCamera.setY(cY + dt*100);
            posCamera.setZ(cZ + dt*100);
            if(cX<=0.0)
            {
                posCamera.setX(cX - dt*100);
            }
            if(cY<=0.0)
            {
                posCamera.setY(cY - dt*100);
            }
            if(cZ<=0.0)
            {
                posCamera.setZ(cZ - dt*100);
            }
        }
        m_camera->setPosition(posCamera);

    }


}
