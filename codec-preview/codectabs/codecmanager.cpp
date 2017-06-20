#include "codecmanager.h"

CodecManager::CodecManager(QWidget *parent) : QWidget(parent) {
    crfParameter = "38";
    pixelFormatParameter = "yuv420p";
    filterParameter = "";
    presetParameter = "ultrafast";
    formatParameter = "matroska";
}

QMap<QString, QString> CodecManager::getStreamingParameters() {
    QMap<QString, QString> parameters;

    if (!encoderParameter.isEmpty())
        parameters.insert("c:v", encoderParameter);
    if (!crfParameter.isEmpty())
        parameters.insert("crf", crfParameter);
    if (!pixelFormatParameter.isEmpty())
        parameters.insert("pix_fmt", pixelFormatParameter);
    if (!filterParameter.isEmpty())
        parameters.insert("vf", filterParameter);
    if (!presetParameter.isEmpty())
        parameters.insert("preset", presetParameter);
    if (!formatParameter.isEmpty())
        parameters.insert("f", formatParameter);

    return parameters;
}

void CodecManager::setCodecTabs(CodecTabsWidget *widget) {
    qDebug() << "===============this SHOULDNT run======================"; // WTF?

    (void)widget;
}
