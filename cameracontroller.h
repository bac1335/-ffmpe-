#ifndef CAMERACOLLOR_H
#define CAMERACOLLOR_H

#include "cameracontrollerbase.h"
#include "ffmpeg/ffmpeginclude.h"
#include "cameradata.h"

/**
* @projectName   cameratest
* @brief         摄像头控制器。负责打开，关闭，调整摄像头
* @date          2020-06-20
*/

class CameraController : public CameraControllerBase{
    Q_OBJECT
public:

    enum Device_type{
        Audio_devices,
        Video_devices
    };

    struct Device{
        Device_type type;
        QString     name;
//        QString     alternativeName;
    };

    explicit CameraController(CameraControllerBase* parent = nullptr);
    ~CameraController();
    bool open();
    void close();
    void setCameSize(CameraControllerBase::CameraResolution type);
    int cameraCount();

protected:
    void run();

private:
    bool OpenInput(QString deviceName);
    void initCameraDivice(QList<Device>& deviceList);
    AVPixelFormat convertDeprecatedFormat(enum AVPixelFormat format);
    bool capture();
    void frameToRgbImage(AVFrame* pDest, AVFrame* frame);
    void disposeYUVData();
    void yuv420_toRGB(int width, int height, unsigned char *buf,unsigned char* RGBBuffer);

private:
    QList<Device>      m_deviceList;   //支持设备个数
    AVFrame *          m_avFrame = nullptr;
    AVFrame *          pFrameYUV = nullptr;
    AVFormatContext *  m_pFormatContent = nullptr;
    int                m_nVideoStreamIndex = -1;
    AVCodecContext *   m_pCaptureContext = nullptr;
    bool               m_isUsedSwsScale = true;
    CameraData         m_pCameraData;
    AVFrame *          m_pRGBFrame = nullptr;
    SwsContext         *m_pSwsContext = nullptr;
    QMutex             m_pMutex;
    FILE*              m_filePtr = nullptr;
};

#endif // CAMERACOLLOR_H
