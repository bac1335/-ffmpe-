#ifndef GENERAL_H
#define GENERAL_H
#include <QObject>
#define Uti General::getInstance()

class General : public QObject{
    Q_OBJECT
public:
    static General* getInstance();
    /**
    * @brief    获取屏幕尺寸
    * @parame   index为哪个屏幕，默认主屏
    */
    static QSize getScreenSize(int index = -1);
    /**
    * @brief  屏幕个数
    */
    static int getScreenNum();


};

#endif // GENERAL_H
