#include "animationbutton.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QTime>
#include <QDebug>
#define ANINUM 20
AnimationButton::AnimationButton(QWidget *parent):
    QWidget (parent)
{
    init();
}

AnimationButton::AnimationButton(int w, int h, QWidget *parent):
    QWidget (parent)
{
    this->resize(w,h);
    init();
}

void AnimationButton::setBgPixmap(QPixmap &pix)
{
    m_bg = pix;
    update();
}

void AnimationButton::enterEvent(QEvent *event)
{
    if(m_btnAnimation->state() == QAbstractAnimation::Running){
        m_btnAnimation->stop();
    }

    reInitAni();
    m_btnAnimation->start();
}

void AnimationButton::leaveEvent(QEvent *event)
{

}

void AnimationButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(),m_bg,m_bg.rect());
}

void AnimationButton::mousePressEvent(QMouseEvent *event)
{
    m_clickedPoint = event->screenPos();
    m_clickState = true;
}

void AnimationButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_clickState){
        m_clickState = false;
        if(qAbs(event->screenPos().manhattanLength() - m_clickedPoint.manhattanLength()) < 20){
            emit sigClicked();
        }
    }
}

void AnimationButton::init()
{
    m_btnAnimation = new QPropertyAnimation(this,"pos",this);
    m_btnAnimation->setDuration(200);
}

void AnimationButton::reInitAni()
{
    if(m_oriPoint.isNull()) m_oriPoint = this->pos();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    m_btnAnimation->setKeyValueAt(0,m_oriPoint);

    for(int i = 0; i< 10;i++){
        int k1 = qrand()%ANINUM > ANINUM/2?1:-1;
        int k2 = qrand()%ANINUM > ANINUM/2?1:-1;
        m_btnAnimation->setKeyValueAt(i*1.0/ANINUM,
                                      m_oriPoint + QPoint(qrand()%ANINUM*k1,rand()%ANINUM*k2));
    }

    m_btnAnimation->setKeyValueAt(1,m_oriPoint);
}
