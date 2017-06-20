#include "mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent) : CodecManager(parent) {
    encoderParameter = "mjpeg";
}

MJPEGManager::~MJPEGManager() {}

/*CommonParametersWidget* MJPEGManager::getCommonParams() {
    return ui->commonParameters;
}*/

void MJPEGManager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
}
