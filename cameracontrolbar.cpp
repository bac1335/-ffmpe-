#include "cameracontrolbar.h"
#include <QApplication>
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>
#include "camerabutton.h"

CameraControllerBar::CameraControllerBar(int width,int height,QWidget *parent):
    QWidget (parent)
{
    this->resize(width,height);
    init();
}

void CameraControllerBar::init()
{
    CameraButton *btn = creatBtn();
    btn->setBtnType(CameraButton::Btn_play);
    btn->setBtnPix(QApplication::applicationDirPath() + "/skin/btn/btn_stop.png",
                             QApplication::applicationDirPath() + "/skin/btn/btn_play.png");
    btn->move(this->width()/2. - btn->width()/2.,
              this->height()/2. - btn->height()/2.);
    btn->reInitAni();

}

CameraButton *CameraControllerBar::creatBtn()
{
    CameraButton *btn = new CameraButton(this->height()/2,this->height()/2,this);
    m_btnList.push_back(btn);
    connect(btn,&AnimationButton::sigClicked,this,&CameraControllerBar::onButtonClicked);
    return btn;
}


void CameraControllerBar::onButtonClicked()
{
    CameraButton* btn = qobject_cast<CameraButton*>(sender());
    switch (btn->btnType()) {
        case CameraButton::Btn_play:
        {
            if(btn->btnState() == CameraButton::Btn_state_on){
                 btn->setBtnState(CameraButton::Btn_state_off);
            }
            else{
                 btn->setBtnState(CameraButton::Btn_state_on);
            }
            emit sigPlayState(btn->btnState() == CameraButton::Btn_state_on);
        }
        break;
        default:{

        }
    }


}
