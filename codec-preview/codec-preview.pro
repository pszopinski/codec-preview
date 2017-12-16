SQT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec-preview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    CodecComparisonWindow.cpp \
    MainWindow.cpp \
    CodecParametersWidget.cpp \
    VideoPlaybackWidget.cpp \
    VideoStatisticsWidget.cpp \
    ParameterManager.cpp \
    ParameterValidator.cpp \
    FFmpegCommand.cpp \
    codecs/AnyCodec.cpp \
    codecs/Codec.cpp \
    codecs/H261Codec.cpp \
    codecs/H264Codec.cpp \
    codecs/H265Codec.cpp \
    codecs/MjpegCodec.cpp \
    codecs/Mpeg1Codec.cpp \
    codecs/Mpeg2Codec.cpp \
    StreamingProcess.cpp \
    CodecSelectorWindow.cpp



HEADERS  += constants.h \
    CodecComparisonWindow.h \
    MainWindow.h \
    CodecParametersWidget.h \
    VideoPlaybackWidget.h \
    VideoStatisticsWidget.h \
    ParameterManager.h \
    ParameterValidator.h \
    FFmpegCommand.h \
    codecs/AnyCodec.h \
    codecs/Codec.h \
    codecs/H261Codec.h \
    codecs/H264Codec.h \
    codecs/H265Codec.h \
    codecs/Mpeg2Codec.h \
    codecs/Mpeg1Codec.h \
    codecs/MjpegCodec.h \
    StreamingProcess.h \
    CodecSelectorWindow.h


FORMS    += \
    CodecComparisonWindow.ui \
    MainWindow.ui \
    CodecParametersWidget.ui \
    VideoPlaybackWidget.ui \
    VideoStatisticsWidget.ui \
    CodecSelectorWindow.ui

	
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

RC_FILE = myapp.rc

