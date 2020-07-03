#include "cameradisplay.h"
#include "cameracontroller.h"
#include <QPainter>
#include <QDebug>

CameraDisplay::CameraDisplay(int width,int height,QGraphicsWidget *parent):
    QGraphicsWidget(parent)
{
    m_size = QSize(width,height);
    this->resize(m_size);
    init();
}

void CameraDisplay::doPlayState(bool on)
{
    if(on){
         m_controller->open();
    }
    else{
         m_controller->close();
    }
}

void CameraDisplay::init()
{
    m_bg = QImage(m_size, QImage::Format_RGB32);
    m_controller = QSharedPointer<CameraControllerBase>(new CameraController);
    connect(m_controller.data(),SIGNAL(sigNeedUpdate(QByteArray)),this,SLOT(onNeedUpdate(QByteArray)));
    connect(m_controller.data(),SIGNAL(MyFFmpegSigGetOneFrame(QImage)),this,SLOT(onMyFFmpegSigGetOneFrame(QImage)));
    connect(m_controller.data(),SIGNAL(sigFFmpegSigGetOneFramePtr(QImage*)),this,SLOT(onsigFFmpegSigGetOneFramePtr(QImage*)));

//    m_pThread = new QThread;
//    this->moveToThread(m_pThread);
//    m_pThread->start();
}

void CameraDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(this->rect(),m_bg,m_bg.rect());
}

void CameraDisplay::onNeedUpdate(QByteArray byte)
{
    m_mutex.lock();
//    qDebug() << "============================" << byte;
//    m_bg.loadFromData(byte.data());
   // qDebug() << "============================" << m_bg.isNull();
//    RGB2Image(byte.data(),m_bg.width(),m_bg.height(),&m_bg);
    m_mutex.unlock();
    this->update();
}

void CameraDisplay::onMyFFmpegSigGetOneFrame(QImage img)
{
    m_mutex.lock();
//    qDebug() << "============================" << byte;
    m_bg = img;

    m_mutex.unlock();
    this->update();
}

void CameraDisplay::onsigFFmpegSigGetOneFramePtr(QImage *img)
{
    m_bg = *img;
    delete img;
    this->update();
}
