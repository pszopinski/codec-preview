SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    codeccomparewindow.cpp \
    codecselector.cpp \
    codectabswidget.cpp \
    ffmpegcommand.cpp \
    mainwindow.cpp \
    parammanager.cpp \
    videoinfowidget.cpp \
    videoplaybackwidget.cpp \
    codecs/codec.cpp \
    codecs/h261.cpp \
    codecs/h264.cpp \
    codecs/mjpeg.cpp \
    codecs/mpeg1.cpp \
    codecs/mpeg2.cpp \
    codectabs/codecmanager.cpp \
    codectabs/h261manager.cpp \
    codectabs/h264manager.cpp \
    codectabs/h265manager.cpp \
    codectabs/mjpegmanager.cpp \
    codectabs/mpeg1manager.cpp \
    codectabs/mpeg2manager.cpp \
    codecs/h265.cpp \
    codecs/allcodecs.cpp \
    codectabs/paramsvalidator.cpp \
    statistics.cpp



HEADERS  += constants.h \
    codeccomparewindow.h \
    codecselector.h \
    codectabswidget.h \
    ffmpegcommand.h \
    mainwindow.h \
    parammanager.h \
    videoinfowidget.h \
    videoplaybackwidget.h \
    codecs/codec.h \
    codecs/h261.h \
    codecs/h264.h \
    codecs/mjpeg.h \
    codecs/mpeg1.h \
    codecs/mpeg2.h \
    codectabs/codecmanager.h \
    codectabs/h261manager.h \
    codectabs/h264manager.h \
    codectabs/h265manager.h \
    codectabs/mjpegmanager.h \
    codectabs/mpeg1manager.h \
    codectabs/mpeg2manager.h \
    codecs/h265.h \
    codecs/allcodecs.h \
    codectabs/paramsvalidator.h \
    statistics.h


FORMS    += \
    codeccomparewindow.ui \
    codecselector.ui \
    codectabswidget.ui \
    mainwindow.ui \
    videoinfowidget.ui \
    videoplaybackwidget.ui \
    codectabs/codecmanager.ui

	
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

