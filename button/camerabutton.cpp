#include "camerabutton.h"

CameraButton::CameraButton(QWidget*parent):
    AnimationButton(parent)
{

}

CameraButton::CameraButton(int w, int h, QWidget *parent):
    AnimationButton (w,h,parent)
{

}

void CameraButton::setBtnState(CameraButton::ButtonState state)
{
    m_button_state = state;
    updatePixState();
}

void CameraButton::setBtnPix(QString p1, QString p2)
{
    m_btnStateOnPix = QPixmap(p1);
    m_btnStateOffPix = QPixmap(p2);
    updatePixState();
}

void CameraButton::updatePixState()
{
    switch (m_button_state){
        case Btn_state_on:
        m_bg = m_btnStateOnPix;
        break;
        default:{
        m_bg = m_btnStateOffPix;
        break;
        }
    }
    update();
}
