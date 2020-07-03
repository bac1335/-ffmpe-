#ifndef ANIMATIONBUTTON_H
#define ANIMATIONBUTTON_H
#include <QWidget>

class QPropertyAnimation;
class AnimationButton : public QWidget{
    Q_OBJECT
public:
    explicit AnimationButton(QWidget* parent = nullptr);
    explicit AnimationButton(int w,int h,QWidget* parent = nullptr);
    void setBgPixmap(QPixmap& pix);
    void reInitAni();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void init();

signals:
    void sigClicked();

protected:
    QPixmap                 m_bg;
//    QRect                   m_oriRect;
    QPoint                  m_oriPoint;
    QPointF                 m_clickedPoint;
    bool                    m_clickState = false;
    QPropertyAnimation*     m_btnAnimation = nullptr;

};


#endif // ANIMATIONBUTTON_H
