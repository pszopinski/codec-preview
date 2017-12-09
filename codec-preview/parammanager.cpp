#include "parammanager.h"

ParamManager::ParamManager() { initTooltips(); }

QString ParamManager::getHint(QString paramName) {
    // Make the default label the same as the name of the parameter
    return paramHints->value(paramName, paramName);
}

void ParamManager::setHint(QString paramName, QString tooltip) {
    paramHints->insert(paramName, tooltip);
}

void ParamManager::initTooltips() {
    paramHints = new OrderedMap<QString, QString>();
    setHint("FPS", FPS);
    setHint("Resolution", RESOLUTION);
    setHint("Quality", QUALITY);
    setHint("Motion vectors", MOTION_VECTORS);
    setHint("GOP size", GOP_SIZE);
    setHint("B frames limit", B_FRAMES_LIMIT);
}
