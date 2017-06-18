#include "mpeg2manager.h"
#include "ui_mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MPEG2Manager) {
    encoderParameter = "mpeg2video";
    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

MPEG2Manager::~MPEG2Manager() { delete ui; }

/*CommonParametersWidget* MPEG2Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void MPEG2Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);
}
