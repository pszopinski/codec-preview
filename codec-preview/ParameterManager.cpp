#include "ParameterManager.h"

ParameterManager::ParameterManager() { initTooltips(); }

QString ParameterManager::getHint(QString paramName) {
    // Use paramName as the default tooltip
    return paramHints->value(paramName, paramName);
}

void ParameterManager::setHint(QString paramName, QString tooltip) { paramHints->insert(paramName, tooltip); }

void ParameterManager::initTooltips() {
    paramHints = new QMap<QString, QString>();
    setHint("FPS", "Frames per second\n"
                   "Format: integer\n"
                   "Example: 30");
    setHint("Bitrate", "Bits per second\n"
                       "Format: integer\n"
                       "Example: 500");
    setHint("Minrate", "Minimum bit rate\n"
                       "Format: integer\n"
                       "Example: 300");
    setHint("Maxrate", "Maximum bit rate\n"
                       "Format: integer\n"
                       "Example: 600");
    setHint("Buffer size", "Buffer size for bitrate management\n"
                           "Format: integer\n"
                           "Example: 1500");
    setHint("Resolution", "Resultion of the video\n"
                          "Format: interger:integer\n"
                          "Example: 1920:1080");
    setHint("Aspect ratio correction", "Contener-level aspect ratio correction.");
    setHint("Quantization", "Quantization factor\n"
                            "Format: integer\n"
                            "Range: 1-31 (the lower the better quality)\n"
                            "Example: 15");
    setHint("Motion vectors", "Draw motion vectors on the encoded video\n"
                              "This has no effect for camera input.");
    setHint("GOP size", "Group of frames size.\n"
                        "The distance between I frames. Defaults to 12.");
    setHint("B frames limit", "The maximum number of consecutive B frames.\n"
                              "Enter 0 to disable B frames altogether.");
}
