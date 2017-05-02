#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T16:23:19
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        codeccomparisonwindow.cpp \
    mjpeg.cpp \
    h261.cpp \
    mpeg1.cpp \
    mpeg2.cpp \
    h264.cpp \
    avc.cpp \
    h265.cpp \
    codec.cpp

HEADERS  += codeccomparisonwindow.h \
    codec.h \
    mjpeg.h \
    h261.h \
    mpeg1.h \
    mpeg2.h \
    h264.h \
    avc.h \
    h265.h

FORMS    += codeccomparisonwindow.ui



	
win32 {
VLCQT_PATH = C:\vlc-qt

INCLUDEPATH += $$VLCQT_PATH\include

LIBS += \
    -L$$VLCQT_PATH\lib \
    -lVLCQtCored.dll \
    -lVLCQtQmld.dll \
    -lVLCQtWidgetsd.dll
}


unix {
LIBS += \
    -lVLCQtCore \
    -lVLCQtQml \
    -lVLCQtWidgets
}

