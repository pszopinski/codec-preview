#include "mpeg1manager.h"

MPEG1Manager::MPEG1Manager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "mpeg1video";
}

MPEG1Manager::~MPEG1Manager() {}

/*CommonParametersWidget* MPEG1Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void MPEG1Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
