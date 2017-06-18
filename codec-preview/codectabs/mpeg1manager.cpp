#include "mpeg1manager.h"
#include "ui_mpeg1manager.h"

MPEG1Manager::MPEG1Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MPEG1Manager) {
    encoderParameter = "mpeg1video";
    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

MPEG1Manager::~MPEG1Manager() { delete ui; }

/*CommonParametersWidget* MPEG1Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void MPEG1Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);
}
