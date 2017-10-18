SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    codectabs/codecmanager.cpp \
    codectabs/h261manager.cpp \
    codectabs/h264manager.cpp \
    codectabs/h265manager.cpp \
    codectabs/mjpegmanager.cpp \
    codectabs/mpeg1manager.cpp \
    codectabs/mpeg2manager.cpp \
    videoinfowidget.cpp \
    codectabswidget.cpp \
    videoplaybackwidget.cpp \
    mainwindow.cpp \
    parammanager.cpp \
    codeccomparewindow.cpp \
    codecselector.cpp \
    ffmpegcommand.cpp



HEADERS  += constants.h \
    codectabs/codecmanager.h \
    codectabs/h261manager.h \
    codectabs/h264manager.h \
    codectabs/h265manager.h \
    codectabs/mjpegmanager.h \
    codectabs/mpeg1manager.h \
    codectabs/mpeg2manager.h \
    videoinfowidget.h \
    codectabswidget.h \
    videoplaybackwidget.h \
    mainwindow.h \
    parammanager.h \
    codeccomparewindow.h \
    codecselector.h \
    ffmpegcommand.h


FORMS    += \
    videoinfowidget.ui \
    videoplaybackwidget.ui \
    codectabswidget.ui \
    mainwindow.ui \
    codectabs/codecmanager.ui \
    codeccomparewindow.ui \
    codecselector.ui
	
win32 {
VLCQT_PATH = $$_PRO_FILE_PWD_\vlc-qt

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

