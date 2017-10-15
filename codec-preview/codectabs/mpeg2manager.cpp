#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent, "mpeg2video") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    //addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");



    QMap<QString, QString> profiles;
    profiles.insert("422", "0");
    profiles.insert("HIGH", "1");
    profiles.insert("SS", "2");
    profiles.insert("SNR_SCALABLE", "3");
    profiles.insert("MAIN", "4");
    profiles.insert("SIMPLE", "5");
    addParameter("Profile", "profile:v", profiles);

    QMap<QString, QString> levels;
    levels.insert("422 main", "5");
    levels.insert("422 high", "2");
    levels.insert("main", "8");
    levels.insert("high 1440", "6");
    levels.insert("high", "4");
    addParameter("Level", "level:v", levels);
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
