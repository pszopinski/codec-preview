#include "parammanager.h"

ParamManager::ParamManager() { initTooltips(); }

QString ParamManager::getHint(QString paramName) {
    return paramHints->value(paramName, "not found");
}

void ParamManager::setHint(QString paramName, QString tooltip) {
    paramHints->insert(paramName, tooltip);
}

void ParamManager::initTooltips() {
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
