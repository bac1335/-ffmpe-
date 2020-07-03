#ifndef CAMERADISPLAY_H
#define CAMERADISPLAY_H

#include <QGraphicsWidget>
#include <QMutex>
/**
* @projectName   cameratest
* @brief         摄像头显示类
* @date          2020-06-20
*/
class CameraControllerBase;

class CameraDisplay : public QGraphicsWidget{
    Q_OBJECT
public:
    explicit CameraDisplay(int width,int height,QGraphicsWidget* parent = nullptr);
    void doPlayState(bool on);

private:
    void init();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private slots:
    void onNeedUpdate(QByteArray byte);
    void onMyFFmpegSigGetOneFrame(QImage img);
    void onsigFFmpegSigGetOneFramePtr(QImage*);

private:
    QSize                                    m_size;
    QSharedPointer<CameraControllerBase>     m_controller = nullptr;
    QImage                                   m_bg;
    QMutex                                   m_mutex;
    QThread*                                 m_pThread = nullptr;
};

#endif // CAMERADISPLAY_H
