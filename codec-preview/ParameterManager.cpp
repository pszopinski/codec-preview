#include "ParameterManager.h"

ParameterManager::ParameterManager() { initTooltips(); }

QString ParameterManager::getHint(QString paramName) {
    return paramHints->value(paramName, "not found");
}

void ParameterManager::setHint(QString paramName, QString tooltip) {
    paramHints->insert(paramName, tooltip);
}

void ParameterManager::initTooltips() {
    paramHints = new QMap<QString, QString>();
    setHint("FPS", FPS);
    setHint("Minrate", MINRATE);
    setHint("Maxrate", MAXRATE);
    setHint("Aspect ratio", ASPECTRATIO);
    setHint("Costant Rate Factor", CONSTANTRATEFACTOR);
    setHint("Resolution", RESOLUTION);
    setHint("Buffer size", BUFFERSIZE);
    setHint("Scale", SCALE);
    setHint("Qscale", QSCALE);
    setHint("Bitrate", BITRATE);
    setHint("Quantization", QUANTIZATION);
}
