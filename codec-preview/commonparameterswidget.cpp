#include "commonparameterswidget.h"
#include "ui_commonparameterswidget.h"

CommonParametersWidget::CommonParametersWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CommonParametersWidget) {
    ui->setupUi(this);

    parameterFields.insert("crf", this->ui->crf);
    parameterFields.insert("r", this->ui->frameRate);
    parameterFields.insert("s", this->ui->scale);
}

CommonParametersWidget::~CommonParametersWidget() { delete ui; }


void CommonParametersWidget::setCodecTabs(CodecTabsWidget *widget) {
    this->codecTabs = widget;
    connect(codecTabs, &CodecTabsWidget::settingsChanged, this,
            &CommonParametersWidget::retrieveAllParameters);
}

void CommonParametersWidget::setCodecManager(CodecManager *widget) {
    this->codecManager = widget;
}

void CommonParametersWidget::retrieveParameter(QString parameter) {
    parameterFields.value(parameter)->setText(codecManager->getParameter(parameter));
}

void CommonParametersWidget::on_crf_returnPressed() {
    setParameter("crf");
}

void CommonParametersWidget::on_frameRate_returnPressed()
{
    setParameter("r");
}

void CommonParametersWidget::on_scale_returnPressed()
{
    setParameter("s");
}

void CommonParametersWidget::retrieveAllParameters() {
    QMap<QString, QLineEdit*>::iterator i;
    for (i = parameterFields.begin(); i != parameterFields.end(); ++i) {
        retrieveParameter(i.key());
    }

}

void CommonParametersWidget::setField(QString parameter) {
    codecTabs->setParameter(parameter, parameterFields.value(parameter)->text());
    codecTabs->settingsChanged();
}
