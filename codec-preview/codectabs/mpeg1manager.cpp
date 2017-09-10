#include "mpeg1manager.h"

MPEG1Manager::MPEG1Manager(QWidget *parent)
    : CodecManager(parent, "mpeg1video") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}

QMap<QString, QString> *MPEG1Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");

    return parameters;
}

MPEG1Manager::~MPEG1Manager() {}
