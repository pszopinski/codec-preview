#include "h265manager.h"
#include "ui_h265manager.h"

H265Manager::H265Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H265Manager) {
    parameters.insert("c:v", "libx265");

    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

H265Manager::~H265Manager() { delete ui; }

/*CommonParametersWidget* H265Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void H265Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);
}
