#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent, "mpeg2video") {
    QString codecName = "mpeg2";

    Codec* codec = CodecManager::getCodec(codecName);

    QList<QString> parameterNames = codec->getParamKeys();
    QList<QString> comboNames = codec->getComboKeys();

    for(int i = 0; i < parameterNames.size(); i++) {
        QString paramName = parameterNames.at(i);
        QMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameter(paramName, paramMap.value("value"), paramMap.value("default"));
    }

    for(int i = 0; i < comboNames.size(); i++) {
        QString paramName = comboNames.at(i);
        QMap<QString, QString> paramMap = codec->getCombo(paramName);
        QString paramValue = paramMap.value("value");

        paramMap.remove("value");

        addParameter(paramName, paramValue, paramMap);

    }
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
