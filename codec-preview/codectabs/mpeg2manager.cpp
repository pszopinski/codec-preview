#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "mpeg2video";
}

MPEG2Manager::~MPEG2Manager() {}

void MPEG2Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
