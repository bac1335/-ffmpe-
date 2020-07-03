#ifndef CAMERADATA_H
#define CAMERADATA_H
#include <QMutex>
#include <QByteArray>

class CameraData
{
public:
    enum PixelFormat
    {
        PIXFORMAT_YUV420P,
        PIXFORMAT_YUV422P,
        PIXFORMAT_YUV444P,
        PIXFORMAT_RGB24
    };

public:
    CameraData(QMutex *mutex)
        :m_pMutex(mutex){
        //qRegisterMetaType<CameraData>("CameraData");
    }
    ~CameraData(){}

    int getWidth(void) const {return m_nWidth;}
    int getHeight(void) const {return m_nHeight;}
    QByteArray getCameraData(void) {
        QMutexLocker locker(m_pMutex);
        return m_cameraData;
    }
    PixelFormat getPixelFormat(void) const {return m_pixelFormat;}

private:
    friend class CameraController;
    QByteArray         m_cameraData;
    std::atomic<int>   m_nWidth;
    std::atomic<int>   m_nHeight;
    PixelFormat        m_pixelFormat;

    QMutex*            m_pMutex = nullptr;
};

#endif // CAMERADATA_H
