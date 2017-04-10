QT += core network
QT += gui

CONFIG += c++11

TARGET = TcpReceiver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    server.h

win32 {
    # CHANGE OPENCV PATH HERE
    OPENCV_PATH = C:\opencv

    #CHANGE FFMPEG PATH HERE
    FFMPEG_PATH = C:\ffmpeg

    INCLUDEPATH += $$OPENCV_PATH\include

    LIBS += \
    -L$$OPENCV_PATH\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll \
    -lopencv_video320.dll \
    -lopencv_videoio320.dll \
    -lopencv_videostab320.dll

    INCLUDEPATH += $$FFMPEG_PATH\include

    LIBS += \
    -L$$FFMPEG_PATH\lib \
    -lavutil.dll \
    -lavfilter.dll  \
    -lavcodec.dll  \
    -lavdevice.dll  \
    -lavformat.dll  \
    -lswresample.dll  \
    -lswscale.dll
}

# to be tested on arch
unix {
    LIBS += \
    -lopencv_core  \
    -lopencv_highgui  \
    -lopencv_imgcodecs  \
    -lopencv_imgproc  \
    -lopencv_features2d  \
    -lopencv_calib3d  \
    -lopencv_video  \
    -lopencv_videoio  \
    -lopencv_videostab

    LIBS += \
    -lavutil \
    -lavfilter \
    -lavcodec \
    -lavdevice \
    -lavformat \
    -lswresample \
    -lswscale
}

