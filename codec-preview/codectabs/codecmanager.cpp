#include "codecmanager.h"

CodecManager::CodecManager(QWidget *parent) : QWidget(parent) {
    crfParameter = "38";
    pixelFormatParameter = "yuv420p";
    filterParameter = "";
    presetParameter = "ultrafast";
    formatParameter = "matroska";
}

QString CodecManager::getStreamingParameters() {
    QStringList list;
    if (!encoderParameter.isEmpty())
        list << "-c:v" << encoderParameter;
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
    list << "-an";


    //list << "-rtbufsize 10M"; changing buffer

    QString parameters = list.join(" ");
    return parameters;
}
