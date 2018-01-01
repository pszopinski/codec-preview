#include "Codec.h"

Codec::Codec() { parameterOrder = new QList<QString>(); }

void Codec::addParameter(QString paramName, QString paramValue, QString paramDefault) {
    QMap<QString, QString> param;
    param.insert("value", paramValue);
    param.insert("default", paramDefault);
    parameters->insert(paramName, param);
    parameterOrder->append(paramName);
}

void Codec::addComboBox(QString paramName, QString paramValue, QMap<QString, QString> paramMap, QString paramDefault) {
    QMap<QString, QString> comboCopy = QMap<QString, QString>(paramMap);
    comboCopy.insert("value", paramValue);
    comboCopy.insert("default", paramDefault);
    comboBoxes->insert(paramName, comboCopy);
}

void Codec::addCheckBox(QString paramName, QString command, bool state) {
    QMap<QString, QString> param;
    param.insert("command", command);
    param.insert("state", state ? "enabled" : ""); // empty string for false, anything else for true
    checkBoxes->insert(paramName, param);
}

void Codec::addSlider(QString paramName, QString paramValue, QString paramDefault, QString paramMin, QString paramMax) {
    QMap<QString, QString> param;
    param.insert("value", paramValue);
    param.insert("default", paramDefault);
    param.insert("min", paramMin);
    param.insert("max", paramMax);
    sliders->insert(paramName, param);
}

void Codec::addStat() {}

QMap<QString, QString> Codec::getParameter(QString paramName) { return parameters->value(paramName); }

QMap<QString, QString> Codec::getComboBox(QString &paramName) { return comboBoxes->value(paramName); }

QMap<QString, QString> Codec::getCheckBox(QString paramName) { return checkBoxes->value(paramName); }

QMap<QString, QString> Codec::getSlider(QString paramName) { return sliders->value(paramName); }

QList<QString> Codec::getParameterKeys() { return parameters->keys(); }

QList<QString> Codec::getComboBoxKeys() { return comboBoxes->keys(); }

QList<QString> Codec::getCheckBoxKeys() { return checkBoxes->keys(); }

QList<QString> Codec::getSliderKeys() { return sliders->keys(); }

QList<QString> *Codec::getParameterOrder() { return parameterOrder; }
