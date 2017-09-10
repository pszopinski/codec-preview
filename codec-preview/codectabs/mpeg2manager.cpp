#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent, "mpeg2video") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}

QMap<QString, QString> *MPEG2Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");

    return parameters;
}

MPEG2Manager::~MPEG2Manager() {}
