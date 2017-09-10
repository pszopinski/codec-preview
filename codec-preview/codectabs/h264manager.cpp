#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent, "libx264") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Costant Rate Factor", "crf", "");
    addParameter("Resolution", "s", "");
}

QMap<QString, QString> *H264Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");
    return parameters;
}

H264Manager::~H264Manager() {}
