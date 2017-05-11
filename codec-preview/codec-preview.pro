#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T16:23:19
#
#-------------------------------------------------

QT       += core gui concurrent multimedia

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
    codectab.cpp \
    h261tab.cpp \
    h264tab.cpp \
    h265tab.cpp \
    mjpegtab.cpp \
    mpeg1tab.cpp \
    mpeg2tab.cpp

HEADERS  += codeccomparisonwindow.h \
    codectab.h \
    h261tab.h \
    h264tab.h \
    h265tab.h \
    mjpegtab.h \
    mpeg1tab.h \
    mpeg2tab.h

FORMS    += codeccomparisonwindow.ui



	
win32 {
VLCQT_PATH = D:\programming-tools\vlc-qt

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

