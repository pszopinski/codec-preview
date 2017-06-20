#include "commonparameterswidget.h"
#include "ui_commonparameterswidget.h"

CommonParametersWidget::CommonParametersWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CommonParametersWidget) {
    ui->setupUi(this);
}

CommonParametersWidget::~CommonParametersWidget() { delete ui; }


void CommonParametersWidget::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    connect(codecTabs, &CodecTabsWidget::settingsChanged, this,
            &CommonParametersWidget::retrieveCRF);
    connect(codecTabs, &CodecTabsWidget::settingsChanged, this,
            &CommonParametersWidget::retrieveFrameRate);
    connect(codecTabs, &CodecTabsWidget::settingsChanged, this,
            &CommonParametersWidget::retrieveScale);
}

void CommonParametersWidget::setCodecManager(CodecManager *widget) {
    this->codecManager = widget;
}

void CommonParametersWidget::retrieveCRF() {
    this->ui->crf->setText(codecManager->getParameter("crf"));
}

void CommonParametersWidget::retrieveFrameRate() {
    this->ui->frameRate->setText(codecManager->getParameter("r"));
}


void CommonParametersWidget::retrieveScale() {
    this->ui->scale->setText(codecManager->getParameter("s"));
}

void CommonParametersWidget::on_crf_returnPressed() {
    codecTabs->setCRF(ui->crf->text());
    codecTabs->settingsChanged();
}

void CommonParametersWidget::on_frameRate_returnPressed()
{
    codecTabs->setFrameRate(ui->frameRate->text());
    codecTabs->settingsChanged();
}

void CommonParametersWidget::on_scale_returnPressed()
{
    codecTabs->setScale(ui->scale->text());
    codecTabs->settingsChanged();
}
