#include "h264manager.h"
#include "ui_h264manager.h"

H264Manager::H264Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H264Manager) {
    parameters.insert("c:v", "libx264");

    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

H264Manager::~H264Manager() { delete ui; }

/*CommonParametersWidget* H264Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void H264Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);
}
