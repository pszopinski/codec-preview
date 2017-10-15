#include "h261manager.h"

H261Manager::H261Manager(QWidget *parent) : CodecManager(parent, "h261") {


    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    //addParameter("Qscale", "qscale:v", "");

    QMap<QString, QString> resolutions;
    resolutions.insert("176:144", "176x144");
    resolutions.insert("352:288", "352x288");
    addParameter("Resolution", "s", resolutions);
}

QMap<QString, QString> *H261Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "matroska");
    return parameters;
}

H261Manager::~H261Manager() {}
