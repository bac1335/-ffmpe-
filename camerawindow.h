#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H
#include <QWidget>
class CameraDisplay;
class QGraphicsView;
class CameraControllerBar;

class CameraWindow : public QWidget{
   Q_OBJECT
public:
    explicit CameraWindow(QWidget* parent = nullptr);

private:
    void init();

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void onPlayState(bool on);

private:
    CameraDisplay*              m_pCameraDisplay = nullptr;
    CameraControllerBar*        m_playBar = nullptr;
};


#endif // CAMERAWINDOW_H
