#include "codecmanager.h"

CodecManager::CodecManager(QWidget *parent)
    : QWidget(parent), streamingParameters() {}

QString CodecManager::getStreamingParameters() { return streamingParameters; }
