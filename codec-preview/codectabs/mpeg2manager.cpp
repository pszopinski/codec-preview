#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent) : CodecManager(parent, "mpeg2video") {
    QString codecName = "mpeg2";

    Codec *codec = CodecManager::getCodec(codecName);

    QList<QString> parameterNames = codec->getParameterKeys();
    QList<QString> comboBoxNames = codec->getComboBoxKeys();
    QList<QString> checkBoxNames = codec->getCheckBoxKeys();

    for (int i = 0; i < parameterNames.size(); i++) {
        QString paramName = parameterNames.at(i);
        QMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameterWidget(paramName, paramMap.value("value"), paramMap.value("default"));
    }

    for (int i = 0; i < comboBoxNames.size(); i++) {
        QString paramName = comboBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getComboBox(paramName);
        QString paramValue = paramMap.value("value");

        paramMap.remove("value");

        addParameterWidget(paramName, paramValue, paramMap);
    }

    for (int i = 0; i < checkBoxNames.size(); i++) {
        QString paramName = checkBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getCheckBox(paramName);
        QString command = paramMap.value("command");
        bool state = paramMap.value("state") != ""; // empty string for false, anything else for true

        addParameterWidget(paramName, command, state);
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
