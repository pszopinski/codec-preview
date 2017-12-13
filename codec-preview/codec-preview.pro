SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    codecs/codec.cpp \
    codecs/h261.cpp \
    codecs/h264.cpp \
    codecs/mjpeg.cpp \
    codecs/mpeg1.cpp \
    codecs/mpeg2.cpp \
    codecs/h265.cpp \
    codecs/allcodecs.cpp \
    CodecComparisonWindow.cpp \
    CodecSelector.cpp \
    CodecTabsWidget.cpp \
    MainWindow.cpp \
    CodecParametersWidget.cpp \
    VideoPlaybackWidget.cpp \
    VideoStatisticsWidget.cpp \
    ParameterManager.cpp \
    ParameterValidator.cpp \
    FFmpegCommand.cpp



HEADERS  += constants.h \
    codecs/codec.h \
    codecs/h261.h \
    codecs/h264.h \
    codecs/mjpeg.h \
    codecs/mpeg1.h \
    codecs/mpeg2.h \
    codecs/h265.h \
    codecs/allcodecs.h \
    CodecComparisonWindow.h \
    CodecSelector.h \
    CodecTabsWidget.h \
    MainWindow.h \
    CodecParametersWidget.h \
    VideoPlaybackWidget.h \
    VideoStatisticsWidget.h \
    ParameterManager.h \
    ParameterValidator.h \
    FFmpegCommand.h


FORMS    += \
    CodecComparisonWindow.ui \
    CodecSelector.ui \
    CodecTabsWidget.ui \
    MainWindow.ui \
    CodecParametersWidget.ui \
    VideoPlaybackWidget.ui \
    VideoStatisticsWidget.ui

	
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

