#include "h261manager.h"
#include "ui_h261manager.h"

H261Manager::H261Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H261Manager) {
    parameters.insert("c:v", "h261");
    parameters.insert("vf", "scale=352:288:force_original_aspect_ratio=decrease,pad=352:288:(ow-iw)/2:(oh-ih)/2");

    ui->setupUi(this);

    ui->commonParameters->setCodecManager(this);
}

H261Manager::~H261Manager() { delete ui; }


/*CommonParametersWidget* H261Manager::getCommonParams() {
    return ui->commonParameters;
}*/

void H261Manager::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    ui->commonParameters->setCodecTabs(codecTabs);

}
