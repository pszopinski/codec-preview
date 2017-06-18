#include "commonparameterswidget.h"
#include "ui_commonparameterswidget.h"

CommonParametersWidget::CommonParametersWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CommonParametersWidget) {
    ui->setupUi(this);
}

CommonParametersWidget::~CommonParametersWidget() { delete ui; }

void CommonParametersWidget::on_crf_returnPressed() {
    codecTabs->setCRF(ui->crf->text());
    codecTabs->settingsChanged();
}

void CommonParametersWidget::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    connect(codecTabs, &CodecTabsWidget::settingsChanged, this,
            &CommonParametersWidget::retrieveCRF);
}

void CommonParametersWidget::setCodecManager(CodecManager *widget) {
    this->codecManager = widget;
}

void CommonParametersWidget::retrieveCRF() {
    this->ui->crf->setText(codecManager->getCRF());
}
