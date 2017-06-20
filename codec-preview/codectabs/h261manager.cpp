#include "h261manager.h"

H261Manager::H261Manager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "h261";
    filterParameter =
        "scale=352:288:force_original_aspect_ratio=decrease,pad=352:288:(ow-iw)/2:(oh-ih)/2";
}

H261Manager::~H261Manager() {}

void H261Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
