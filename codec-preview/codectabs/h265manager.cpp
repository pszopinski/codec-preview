#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent, "libx265") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Costant Rate Factor", "crf", "");
    addParameter("Resolution", "s", "");
}

QMap<QString, QString> *H265Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");
    return parameters;
}

H265Manager::~H265Manager() {}
