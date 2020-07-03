#include "cameracontroller.h"
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QFile>
#include <QCameraInfo>
#include <windows.h>
#include <Vfw.h>
#pragma comment(lib,"Vfw32.lib")
#include <iostream>
#include <QDebug>
#include <QTime>

#include <QDebug>
#include <atlbase.h>
#include <string>
#include <Windows.h>
#include <dshow.h>

CameraController::CameraController(CameraControllerBase* parent):
    CameraControllerBase(parent),m_pCameraData(&m_pMutex)
{
    initCameraDivice(m_deviceList);
}

CameraController::~CameraController()
{
    close();
}

bool CameraController::open()
{
#if 0

    QString videoName;
    for(auto& item:m_deviceList){
        if(item.type == Video_devices){
            videoName = item.name;
            break;
        }
    }
#if 0  //直接调用ffmpeg内置播放器打开摄像头
    if(!videoName.isEmpty()){
        QProcess process;
        QString cmd = QString("%1/ffplay.exe -f dshow -i video=\"%2\"")
                .arg(qApp->applicationDirPath())
                .arg(videoName);
        process.startDetached(cmd);
    }
#endif
    //https://blog.csdn.net/leixiaohua1020/article/details/38284961
    //参考大佬指令，直接发送指令
//    ffmpeg -f dshow -i video="Integrated Camera" -vcodec libx264 -preset:v ultrafast -tune:v zerolatency -f h264 udp://233.233.233.223:6666
    if(!videoName.isEmpty()){
        QProcess process;
        QString cmd = QString("%1/ffmpeg -f dshow -i video=\"%2\" -vcodec libx264 -preset:v ultrafast -tune:v zerolatency -f h264 udp://http://127.0.0.1:10001")
                .arg(qApp->applicationDirPath())
                .arg(videoName);
//        process.startDetached(cmd);
    }
#endif
    QString videoName;
    for(auto& item:m_deviceList){
        if(item.type == Video_devices){
            videoName = item.name;
            break;
        }
    }

    if(!videoName.isEmpty()){
        m_OpenState = OpenInput(videoName);
//        if(m_OpenState){
//            char *file= (QString("%1/%2.txt")
//                    .arg(qApp->applicationDirPath())
//                    .arg(QTime::currentTime().toString("hhmmss")))
//                    .toLocal8Bit().data();
//            m_filePtr = fopen(file,"wb");
//            m_OpenState = (m_filePtr != nullptr);
//        }
    }

    if(m_OpenState){
        m_isRunning = true;
        start();
    }
    return m_OpenState;
}

void CameraController::close()
{

    if(this->isRunning()){
         m_isRunning = false;
         this->wait();
         this->quit();

    }

    if(m_pCaptureContext){
        avcodec_close(m_pCaptureContext);
        m_pCaptureContext = nullptr;
    }

    if(m_pSwsContext){
       sws_freeContext(m_pSwsContext);
       m_pSwsContext = nullptr;
    }

    if(m_pFormatContent){
        avformat_close_input(&m_pFormatContent);
        m_pFormatContent = nullptr;
    }

    if(m_avFrame){
        av_frame_free(&m_avFrame);
        m_avFrame = nullptr;
    }

    if(m_pRGBFrame)
    {
        av_frame_free(&m_pRGBFrame);
        m_pRGBFrame = nullptr;
    }

    if(m_filePtr){
        fclose(m_filePtr);
        m_filePtr = nullptr;
    }
}

void CameraController::setCameSize(CameraControllerBase::CameraResolution type)
{

}

int CameraController::cameraCount()
{
    int count = 0;
    for(auto& item:m_deviceList){
        if(item.type == Video_devices){
            count++;
        }
    }
    return count;
}


void RGB2Image(char *srcBuf, int w, int h, QImage *pDistImage)
{
//m_pCameraData.m_cameraData.append((char*)m_pRGBFrame->data[0], m_pRGBFrame->width * m_pRGBFrame->height * 3);
 int i;
 int r, g, b;
 QRgb *point;
 uchar *bit;
 i = 0;
 bit = (uchar *)(srcBuf);

 for(int y = 0; y < h; y ++){
    for ( int x = 0; x < w; x ++ ){
     /* Please attion the Littile-Edian and Big-Edian,
      * The Order maybe R-G-B.
      */
        b = (int)bit[i];
        g = (int)bit[i+1];
        r = (int)bit[i+2];
#if 0
        point = (QRgb *)(pDistImage->scanLine(y) + x);
        *point = qRgb(r, g, b);
#else
        pDistImage->setPixel(x,y,qRgb(r, g, b));
#endif
        i += 3;
     }
 }
// return 0;
}


void CameraController::run()
{
    while (m_isRunning && m_OpenState)
    {
         // 获取摄像头数据
        if(capture())
        {
            // 同步通知显示
#if 0
            emit sigNeedUpdate(m_pCameraData.getCameraData());

#else
        //fwrite(m_pCameraData.getCameraData().data(),m_pCameraData.getCameraData().size(),1,m_filePtr);

         QImage* img = new QImage(QSize(m_pCaptureContext->width,m_pCaptureContext->height),QImage::Format_RGB32);
         RGB2Image(m_pCameraData.getCameraData().data(),img->width(),img->height(),img);
         emit sigFFmpegSigGetOneFramePtr(img);
#endif


        }
        QThread::msleep(1);
    }
}

bool CameraController::OpenInput(QString deviceName)
{
//    av_register_all();
    avdevice_register_all();
    m_avFrame = av_frame_alloc();
    AVInputFormat *inputFormat = av_find_input_format("dshow");

    AVDictionary *format_opts =  nullptr;
    av_dict_set_int(&format_opts, "rtbufsize", 3041280 * 10, 0);
    av_dict_set(&format_opts, "avioflags", "direct", 0);
    av_dict_set(&format_opts, "video_size", "1280x720", 0);
    av_dict_set(&format_opts, "framerate", "30", 0);
    av_dict_set(&format_opts, "vcodec", "mjpeg", 0);

    m_pFormatContent = avformat_alloc_context();
    QString urlString = QString("video=") + deviceName;
    // 打开输入
    int result = avformat_open_input(&m_pFormatContent, urlString.toLocal8Bit().data(), inputFormat, &format_opts);
    if (result < 0)
    {
//        Chicony USB2.0 Camera
        qDebug() << "AVFormat Open Input Error!" << urlString;
        return false;
    }

    result = avformat_find_stream_info(m_pFormatContent, nullptr);
    if (result < 0)
    {
        qDebug() << "AVFormat Find Stream Info Error!";
        return false;
    }

    // find Video Stream Index
    int count = m_pFormatContent->nb_streams;
    for (int i=0; i<count; ++i)
    {
        if (m_pFormatContent->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_nVideoStreamIndex = i;
            break;
        }
    }

    if (m_nVideoStreamIndex < 0)
        return false;

    // 查找解码器
    m_pCaptureContext = m_pFormatContent->streams[m_nVideoStreamIndex]->codec;
    AVCodec* codec = avcodec_find_decoder(m_pCaptureContext->codec_id);
    if (codec == nullptr)
        return false;

    // 打开解码器
    if (avcodec_open2(m_pCaptureContext, codec, nullptr) != 0)
        return false;

    // 设置尺寸、格式等信息
    m_pCameraData.m_nWidth = m_pCaptureContext->width;
    m_pCameraData.m_nHeight = m_pCaptureContext->height;
    AVPixelFormat format = m_pCaptureContext->pix_fmt;
    format = convertDeprecatedFormat(format);

    if (m_isUsedSwsScale)
        return true;

    m_isUsedSwsScale = false;
    if (format == AV_PIX_FMT_YUV420P)
        m_pCameraData.m_pixelFormat = CameraData::PIXFORMAT_YUV420P;
    else if (format == AV_PIX_FMT_YUV422P)
        m_pCameraData.m_pixelFormat = CameraData::PIXFORMAT_YUV422P;
    else if (format == AV_PIX_FMT_YUV444P)
        m_pCameraData.m_pixelFormat = CameraData::PIXFORMAT_YUV444P;
    else {
        m_pCameraData.m_pixelFormat = CameraData::PIXFORMAT_RGB24;
        m_isUsedSwsScale = true;
    }

    return true;
}

void CameraController::initCameraDivice(QList<Device> &deviceList)
{
    QProcess process;
    QString fileName = "device.txt";
    QString cmd = QString("%1/ffmpeg.exe -list_devices true -f dshow -i dummy 2>%2 \n")
            .arg(qApp->applicationDirPath())
            .arg(fileName);

    cmd = cmd.replace("/","\\");
    process.start("cmd");
    process.waitForStarted();
    process.write(cmd.toLocal8Bit());
    process.closeWriteChannel();
    process.waitForFinished();

    QFile device(qApp->applicationDirPath() + "/" + fileName);
    if(device.exists()){
        if(device.open(QIODevice::ReadOnly)){
            Device_type flag;
            while(!device.atEnd()){
                QString line = device.readLine();
                if(!line.contains("[dshow @")) continue;

                if (line.contains("DirectShow video devices"))
                {
                    flag = Video_devices;
                    continue;
                }

                if (line.contains("DirectShow audio devices"))
                {
                    flag = Audio_devices;
                    continue;
                }

                if (!line.contains("Alternative name"))
                {
                    int index = line.indexOf("\"");
                    line = line.remove(0,index);
                    line = line.remove("\"");
                    line = line.remove("\n");
                    line = line.remove("\r");

                    Device d;
                    d.type = flag;
                    d.name = line;
                    deviceList.push_back(d);
                }


            }
            device.close();
        }
        device.remove();
    }

//    下述代码实际上相当于输入了下面一条命令： ffmpeg -list_devices true -f dshow -i dummy
//    av_register_all();
//    avdevice_register_all();
//    AVFormatContext *pFormatCtx = avformat_alloc_context();
//    AVDictionary* options = NULL;
//    av_dict_set(&options,"list_devices","true",0);
//    AVInputFormat *iformat = av_find_input_format("dshow");
//    avformat_open_input(&pFormatCtx,"video=dummy",iformat,&options);

    //下述指令用qt自带
#if 0
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        // 获取摄像头的名称
        QString cameraName = cameraInfo.description();
        // 添加到ComboBox中
        qDebug() << "================================" << cameraName;
    }
#endif

}

AVPixelFormat CameraController::convertDeprecatedFormat(enum AVPixelFormat format)
{
    switch (format)
    {
    case AV_PIX_FMT_YUVJ420P:
        return AV_PIX_FMT_YUV420P;
    case AV_PIX_FMT_YUVJ422P:
        return AV_PIX_FMT_YUV422P;
    case AV_PIX_FMT_YUVJ444P:
        return AV_PIX_FMT_YUV444P;
    case AV_PIX_FMT_YUVJ440P:
        return AV_PIX_FMT_YUV440P;
    default:
        return format;
    }
}

// 获取一帧数据
bool CameraController::capture()
{
    AVPacket pkt;
    // 获取一帧数据
    int result = av_read_frame(m_pFormatContent, &pkt);

    if (result){
         return false;
    }

    if (pkt.stream_index != m_nVideoStreamIndex)
    {
        av_packet_unref(&pkt);
        return false;
    }

    // 解码视频数据
    result = avcodec_send_packet(m_pCaptureContext, &pkt);

    if (result)
    {
        av_packet_unref(&pkt);
        return false;
    }

    result = avcodec_receive_frame(m_pCaptureContext, m_avFrame);
    if (result)
    {
        av_packet_unref(&pkt);
        return false;
    }

    // 转换成RGB24
    if (m_isUsedSwsScale)
    {
        // 设置RGBFrame
        if (m_pRGBFrame == nullptr)
        {
            m_pRGBFrame = av_frame_alloc();
            m_pRGBFrame->width = m_avFrame->width;
            m_pRGBFrame->height = m_avFrame->height;
            m_pRGBFrame->linesize[0] = m_pRGBFrame->width * m_pRGBFrame->height * 3;
            av_image_alloc(m_pRGBFrame->data, m_pRGBFrame->linesize,
                m_pRGBFrame->width, m_pRGBFrame->height, AV_PIX_FMT_RGB24, 1);
        }

        // 转化为RGB24
        frameToRgbImage(m_pRGBFrame, m_avFrame);

        // 设置数据
        m_pMutex.lock();
        m_pCameraData.m_cameraData.clear();
        m_pCameraData.m_cameraData.append((char*)m_pRGBFrame->data[0], m_pRGBFrame->width * m_pRGBFrame->height * 3);
        m_pCameraData.m_pixelFormat = CameraData::PIXFORMAT_RGB24;
        m_pMutex.unlock();
    }
    else
    {
        disposeYUVData();
    }

    av_packet_unref(&pkt);

    return true;
}

void CameraController::frameToRgbImage(AVFrame* pDest, AVFrame* frame)
{
    // 创建SWS上下文
    if (m_pSwsContext == nullptr)
    {
        m_pSwsContext = sws_getContext(frame->width, frame->height, convertDeprecatedFormat((AVPixelFormat)(frame->format)), \
            frame->width, frame->height, AV_PIX_FMT_RGB24,
            SWS_BILINEAR, nullptr, nullptr, nullptr);
    }

    //avpicture_fill( )
    sws_scale(m_pSwsContext, frame->data, frame->linesize, 0, frame->height, \
        pDest->data, pDest->linesize);
}

void CameraController::disposeYUVData()
{
    QMutexLocker locker(&m_pMutex);
    m_pCameraData.m_cameraData.clear();

    AVPixelFormat pixFormat = convertDeprecatedFormat((AVPixelFormat)m_avFrame->format);
    // 设置Y的数据
    if (m_avFrame->linesize[0] == m_avFrame->width)
    {
        m_pCameraData.m_cameraData.append((char*)m_avFrame->data[0], \
                m_avFrame->linesize[0] * m_avFrame->height);
    }
    else
    {
        for (int i=0; i<m_avFrame->height; ++i)
        {
            m_pCameraData.m_cameraData.append((char*)m_avFrame->data[0], m_avFrame->width);
        }
    }

    // 设置U的数据
    int uDataWidth = m_avFrame->width;
    int uDataHeight = m_avFrame->height;
    if (pixFormat == AV_PIX_FMT_YUV420P)
    {
        uDataWidth = uDataWidth / 2;
        uDataHeight = uDataHeight / 2;
    }
    else if (pixFormat == AV_PIX_FMT_YUV422P)
        uDataWidth = uDataWidth / 2;

    if (m_avFrame->linesize[1] == uDataWidth)
    {
        m_pCameraData.m_cameraData.append((char*)m_avFrame->data[1], \
                m_avFrame->linesize[1] * uDataHeight);
    }
    else
    {
        for (int i=0; i<uDataHeight; ++i)
        {
            m_pCameraData.m_cameraData.append((char*)m_avFrame->data[1], uDataWidth);
        }
    }

    // 设置V的数据
    int vDataWidth = uDataWidth;
    int vDataHeight = uDataHeight;
    if (m_avFrame->linesize[1] == vDataWidth)
    {
        m_pCameraData.m_cameraData.append((char*)m_avFrame->data[2], \
                m_avFrame->linesize[2] * vDataHeight);
    }
    else
    {
        for (int i=0; i<vDataHeight; ++i)
        {
            m_pCameraData.m_cameraData.append((char*)m_avFrame->data[2], vDataWidth);
        }
    }
}

void CameraController::yuv420_toRGB(int width, int height, unsigned char *buf,unsigned char* RGBBuffer)
{
        unsigned char *YBuffer = buf;
        unsigned char *UBuffer = buf + height * width;
        unsigned char *VBuffer = buf + (int)(height*width*1.25);
        int Y, U, V, R, G, B;
        int writePos = 0;
        int i = 0, j = 0;
        int k = 0;
        for(i=0; i<height; i++)
        {
                for(j=0; j<width; j++)
                {
                        Y = YBuffer[j]-16;
                        k = (int)(j/2);
                        U = UBuffer[k]-128;
                        V = VBuffer[k]-128;
                        R = ((298*Y + 409*V + 128)>>8);
                        G = ((298*Y - 100*U - 208*V + 128)>>8);
                        B = ((298*Y + 516*U + 128)>>8);
                        RGBBuffer[writePos++] = (B<0) ? 0 : ((B>255) ? 255 : B);
                        RGBBuffer[writePos++] = (G<0) ? 0 : ((G>255) ? 255 : G);
                        RGBBuffer[writePos++] = (R<0) ? 0 : ((R>255) ? 255 : R);
                        RGBBuffer[writePos++] = 0xff;
                }

                YBuffer += width;
                if(i%2==1)
                {
                        UBuffer += width/2;
                        VBuffer += width/2;
                }
        }

}

