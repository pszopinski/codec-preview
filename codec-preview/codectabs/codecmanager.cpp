#include "codecmanager.h"

CodecManager::CodecManager(QWidget *parent) : QWidget(parent) {
    crfParameter = "38";
    pixelFormatParameter = "yuv420p";
    filterParameter = "";
    presetParameter = "";
    formatParameter = "matroska";
}

QString CodecManager::getStreamingParameters() {
    QStringList list;
    if (!crfParameter.isEmpty())
        list << "-crf" << crfParameter;
    if (!pixelFormatParameter.isEmpty())
        list << "-pix_fmt" << pixelFormatParameter;
    if (!filterParameter.isEmpty())
        list << "-vf" << filterParameter;
    if (!presetParameter.isEmpty())
        list << "-preset" << presetParameter;
    if (!formatParameter.isEmpty())
        list << "-f" << formatParameter;

    QString parameters = list.join(" ");
    return parameters;
}
