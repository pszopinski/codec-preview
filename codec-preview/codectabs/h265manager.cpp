#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent, "libx265") {
    QString codecName = "h265";

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

QMap<QString, QString> *H265Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");
    return parameters;
}

H265Manager::~H265Manager() {}
