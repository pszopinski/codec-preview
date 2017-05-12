SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        codeccomparisonwindow.cpp \
    codectabs/codecmanager.cpp \
    codectabs/h261manager.cpp \
    codectabs/h264manager.cpp \
    codectabs/mjpegmanager.cpp \
    codectabs/mpeg1manager.cpp \
    codectabs/mpeg2manager.cpp \
    codectabs/h265manager.cpp

HEADERS  += codeccomparisonwindow.h \
    constants.h \
    codectabs/h261manager.h \
    codectabs/codecmanager.h \
    codectabs/h264manager.h \
    codectabs/h265manager.h \
    codectabs/mjpegmanager.h \
    codectabs/mpeg2manager.h \
    codectabs/mpeg1manager.h

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

