#ifndef CAMERABUTTON_H
#define CAMERABUTTON_H
#include "animationbutton.h"

class CameraButton : public AnimationButton{
    Q_OBJECT
public:
    enum ButtonType{
        Btn_Undefine,
        Btn_play,
    };
    enum ButtonState{
       Btn_state_on,
       Btn_state_off
    };

    explicit CameraButton(QWidget* parent = nullptr);
    explicit CameraButton(int w,int h,QWidget* parent = nullptr);
    void setBtnState(ButtonState state);
    ButtonState btnState(){return m_button_state;}
    void setBtnType(ButtonType type){m_button_type = type;}
    ButtonType btnType(){return m_button_type;}
    void setBtnPix(QString p1,QString p2);

private:
    void updatePixState();

private:
   ButtonState  m_button_state = Btn_state_off;
   ButtonType   m_button_type = Btn_Undefine;

   QPixmap      m_btnStateOnPix;
   QPixmap      m_btnStateOffPix;

};

#endif // CAMERABUTTON_H
