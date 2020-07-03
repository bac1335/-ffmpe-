#ifndef CAMERACONTROLLERBASE_H
#define CAMERACONTROLLERBASE_H
#include <QThread>
/**
* @projectName   cameratest
* @brief         控制器接口
* @date          2020-06-20
*/
#include <QImage>

class CameraControllerBase : public QThread{
    Q_OBJECT
public:
    enum CameraResolution{
        Camera_ordinary,
        CameRa_HD
    };
    CameraControllerBase(QObject* parent = nullptr):QThread(parent){}
    virtual ~CameraControllerBase(){}

    /**
    * @brief  打开摄像头
    */
    virtual bool open() = 0;
    /**
    * @brief  关掉摄像头
    */
    virtual void close() = 0;
    /**
    * @brief  设置摄像头分辨率
    * @parame type分辨率类型
    */
    virtual void setCameSize(CameraControllerBase::CameraResolution type) = 0;
    /**
    * @projectName   cameratest
    * @brief         获取设备摄像头个数
    * @date          2020-06-20
    */
    virtual int cameraCount() = 0;

signals:
    /**
    * @projectName   cameratest
    * @brief         更新数据
    * @date          2020-06-21
    */
    void sigNeedUpdate(QByteArray);
    void MyFFmpegSigGetOneFrame(QImage);
    void sigFFmpegSigGetOneFramePtr(QImage*);

protected:
    bool        m_isRunning = false;
    bool        m_OpenState = false;

};
#endif // CAMERACONTROLLERBASE_H
