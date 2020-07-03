#ifndef CARAMECONTROLBAR_H
#define CARAMECONTROLBAR_H
#include <QWidget>

class CameraButton;
class CameraControllerBar : public QWidget{
    Q_OBJECT
public:
    explicit CameraControllerBar(int width,int height,QWidget* parent = nullptr);

private:
    void init();
    CameraButton* creatBtn();

private slots:
    void onButtonClicked();

signals:
    void sigPlayState(bool);

private:
    QList<CameraButton*>            m_btnList;

};

#endif // CARAMECONTROLBAR_H
