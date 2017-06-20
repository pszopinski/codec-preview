#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "libx264";
}

H264Manager::~H264Manager() {}

void H264Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
