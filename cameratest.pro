#-------------------------------------------------
#
# Project created by QtCreator 2020-06-20T00:25:58
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = logo.ico
include($$PWD/ffmpeg/ffmpeg.pri)

TARGET = cameratest
TEMPLATE = app

OBJECTS_DIR = ./obj
DESTDIR = ./bin

INCLUDEPATH += $$PWD/button

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        button/animationbutton.cpp \
        button/camerabutton.cpp \
        cameracontrolbar.cpp \
        cameracontroller.cpp \
        cameradisplay.cpp \
        camerawindow.cpp \
        general.cpp \
        main.cpp

HEADERS += \
    $$PWD/button/animationbutton.h \
    button/camerabutton.h \
    cameracontrolbar.h \
    cameracontroller.h \
    cameracontrollerbase.h \
    cameradata.h \
    cameradisplay.h \
    cameradisplaydef.h \
    camerawindow.h \
    general.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
