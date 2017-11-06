#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent, "libx264") {
    QString codecName = "h264";

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

QMap<QString, QString> *H264Manager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", "mpegts");
    return parameters;
}

H264Manager::~H264Manager() {}
