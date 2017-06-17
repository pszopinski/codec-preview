#include "codecmanager.h"

CodecManager::CodecManager(QWidget *parent) : QWidget(parent) {
    crfParameter = "38";
    pixelFormatParameter = "yuv420p";
    filterParameter = "";
    presetParameter = "ultrafast";
    formatParameter = "matroska";
}

QMap<QString, QString> CodecManager::getStreamingParameters() {

    if (!encoderParameter.isEmpty()) parameters.insert("c:v", encoderParameter);
    if (!crfParameter.isEmpty()) parameters.insert("crf", crfParameter);
    if (!pixelFormatParameter.isEmpty()) parameters.insert("pix_fmt", pixelFormatParameter);
    if (!filterParameter.isEmpty()) parameters.insert("vf", filterParameter);
    if (!presetParameter.isEmpty()) parameters.insert("preset", presetParameter);
    if (!formatParameter.isEmpty()) parameters.insert("f", formatParameter);

    /*QStringList list;
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
    */

    //list << "-rtbufsize 10M"; changing buffer

    //QString parameters = list.join(" ");
    return parameters;
}


void CodecManager::setCRF(QString value) {
    crfParameter = value;
}

QString CodecManager::getCRF() {
    return crfParameter;
}
