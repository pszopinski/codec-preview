#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "libx265";
}

H265Manager::~H265Manager() {}

/*CommonParametersWidget* H265Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void H265Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
