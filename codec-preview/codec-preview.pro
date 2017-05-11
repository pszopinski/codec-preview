SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        codeccomparisonwindow.cpp \
    codectabs/codectab.cpp \
    codectabs/h261tab.cpp \
    codectabs/h264tab.cpp \
    codectabs/h265tab.cpp \
    codectabs/mjpegtab.cpp \
    codectabs/mpeg1tab.cpp \
    codectabs/mpeg2tab.cpp

HEADERS  += codeccomparisonwindow.h \
    codectabs/codectab.h \
    codectabs/h261tab.h \
    codectabs/h264tab.h \
    codectabs/h265tab.h \
    codectabs/mjpegtab.h \
    codectabs/mpeg1tab.h \
    codectabs/mpeg2tab.h \
    constants.h

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

