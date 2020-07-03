#include <QApplication>
#include "camerawindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CameraWindow camera;
    camera.show();

    return a.exec();
}
