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
    codecTab.cpp \
    h261Tab.cpp \
    h264Tab.cpp \
    h265Tab.cpp \
    mjpegTab.cpp \
    mpeg1Tab.cpp \
    mpeg2Tab.cpp

HEADERS  += codeccomparisonwindow.h \
    codecTab.h \
    h261Tab.h \
    h264Tab.h \
    h265Tab.h \
    mjpegTab.h \
    mpeg1Tab.h \
    mpeg2Tab.h

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

