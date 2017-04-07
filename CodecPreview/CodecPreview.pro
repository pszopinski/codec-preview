QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodecPreview
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    codec_preview.cpp \
    frame_encoder.cpp \
    image_converter.cpp

HEADERS += \
    codec_preview.h \
    frame_encoder.h \
    image_converter.h

FORMS += \
    codec_preview.ui

# We use some mostly deprecated stuff (new functionality is poorly documented...),
# so we supress warnings (otherwise there is like 200 of those)
QMAKE_CXXFLAGS = -std=c++0x -Wno-deprecated-declarations -Wno-unused-result -static-libgcc -static-libstdc++


win32 {
    # CHANGE OPENCV PATH HERE
    OPENCV_PATH = C:\opencv

    #CHANGE FFMPEG PATH HERE
    FFMPEG_PATH = C:\ffmpeg1

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

