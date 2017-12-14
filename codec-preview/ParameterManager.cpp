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
    setHint("Resolution", RESOLUTION);
    setHint("Buffer size", BUFFERSIZE);
    setHint("Quantization", QUANTIZATION);
    setHint("Bitrate", BITRATE);
    setHint("Motion vectors", MOTION_VECTORS);
    setHint("GOP size", GOP_SIZE);
    setHint("B frames limit", B_FRAMES_LIMIT);
}
