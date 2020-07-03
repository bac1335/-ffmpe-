#include "camerawindow.h"
#include "general.h"
#include <QPainter>
#include <QKeyEvent>
#include <QThread>
#include <QApplication>
#include "cameradisplay.h"
#include <QGraphicsView>
#include "cameracontrolbar.h"

CameraWindow::CameraWindow(QWidget *parent):
    QWidget (parent)
{
    init();
}

void CameraWindow::init()
{
    this->resize(Uti->getScreenSize());
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    QGraphicsView* CameViewport = new QGraphicsView(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    m_pCameraDisplay = new CameraDisplay(this->width() * 3/5,this->height()*4/5);

    CameViewport->setRenderHint(QPainter::Antialiasing, false);
    CameViewport->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    CameViewport->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    CameViewport->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    CameViewport->setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);
    CameViewport->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CameViewport->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CameViewport->setAttribute(Qt::WA_TranslucentBackground);
    CameViewport->setStyleSheet("background-color:transparent;border:0px");
    CameViewport->setScene(scene);
    CameViewport->resize(m_pCameraDisplay->size().toSize());
    scene->addItem(m_pCameraDisplay);
    CameViewport->move((this->width() -CameViewport->width())/2.,0);

    m_playBar = new CameraControllerBar(this->width(),this->height()*1/5,this);
    connect(m_playBar,&CameraControllerBar::sigPlayState,this,&CameraWindow::onPlayState);
    m_playBar->move(0,this->height() - m_playBar->height());
}

void CameraWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),"#242424");
}

void CameraWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:

        for(int i = 100;i>0;i--)
        {
            this->setWindowOpacity(i*1./100);
            QThread::msleep(10);
        }
        qApp->quit();

        break;
        default:{

        }
    }
}

void CameraWindow::onPlayState(bool on)
{
    m_pCameraDisplay->doPlayState(on);
}
