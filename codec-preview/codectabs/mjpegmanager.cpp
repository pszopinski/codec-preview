#include "mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent) : CodecManager(parent, "mjpeg") {
    addParameter("Scale", "s", "");
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}

QMap<QString, QString> *MJPEGManager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "matroska");
    return parameters;
}

MJPEGManager::~MJPEGManager() {}
