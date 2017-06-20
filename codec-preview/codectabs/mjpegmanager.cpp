#include "mjpegmanager.h"
#include "ui_mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MJPEGManager) {
    parameters.insert("c:v", "mjpeg");
    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

MJPEGManager::~MJPEGManager() { delete ui; }

/*CommonParametersWidget* MJPEGManager::getCommonParams() {
    return ui->commonParameters;
}*/

void MJPEGManager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);
}
