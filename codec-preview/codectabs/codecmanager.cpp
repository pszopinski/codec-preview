#include "codecmanager.h"


CodecManager::CodecManager(QWidget *parent) : QWidget(parent) {
    parameters.insert("crf", "38");
    parameters.insert("pix_fmt", "yuv420p");
    parameters.insert("preset", "ultrafast");
    parameters.insert("vf", "");
    parameters.insert("f", "matroska");
    parameters.insert("r", "30");
    parameters.insert("s", "120:60");


}

QMap<QString, QString> CodecManager::getStreamingParameters() {
    return parameters;
}




void CodecManager::setParameter(QString parameter, QString value) {
    parameters.insert(parameter, value);
}

QString CodecManager::getParameter(QString parameter) {
    return parameters.value(parameter);
}


/*CommonParametersWidget* CodecManager::getCommonParams() {
    qDebug() << "this SHOULDNT run";
    return NULL;
}*/


void CodecManager::setField(QString parameter) {
    codecTabs->setParameter(parameter, parameterFields.value(parameter)->text());
    codecTabs->settingsChanged();
}
