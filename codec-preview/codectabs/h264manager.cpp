#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent, "libx264") {
    QString codecName = "h264";

    Codec* codec = CodecManager::getCodec(codecName);

    QList<QString> parameterNames = codec->getParamKeys();
    QList<QString> comboNames = codec->getComboKeys();

    for(int i = 0; i < parameterNames.size(); i++) {
        QString paramName = parameterNames.at(i);
        QMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameterWidget(paramName, paramMap.value("value"), paramMap.value("default"));
    }

    for(int i = 0; i < comboNames.size(); i++) {
        QString paramName = comboNames.at(i);
        QMap<QString, QString> paramMap = codec->getCombo(paramName);
        QString paramValue = paramMap.value("value");

        paramMap.remove("value");

        addParameterWidget(paramName, paramValue, paramMap);

    }
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
