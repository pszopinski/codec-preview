#include "selectcodecs.h"
#include "ui_selectcodecs.h"

SelectCodecs::SelectCodecs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCodecs)
{
    count = 2;
    ui->setupUi(this);
    c1 = ui->MPEG1;
    c2 = ui->MPEG2;
    c3 = ui->MJPEG;
    c4 = ui->H261;
    c5 = ui->H264;
    c6 = ui->H265;
}

SelectCodecs::~SelectCodecs()
{
    delete ui;
}

void SelectCodecs::on_MPEG1_clicked()
{
    bMpeg1 = !bMpeg1;
}

void SelectCodecs::on_MPEG2_clicked()
{
    bMpeg2 = !bMpeg2;
}

void SelectCodecs::on_MJPEG_clicked()
{
    bMjpeg = !bMjpeg;
}

void SelectCodecs::on_H261_clicked()
{
    bH261 = !bH261;
}

void SelectCodecs::on_H264_clicked()
{
    bH264 = !bH264;
}

void SelectCodecs::on_H265_clicked()
{
    bH265 = !bH265;
}

void SelectCodecs::on_buttonBox_accepted()
{
    bool b[] = {bMjpeg, bH261, bMpeg1, bMpeg2, bH264, bH265};
    ccw->setSelectedCodecs(b);
}

void SelectCodecs::setMainWindowHandler(CodecComparisonWindow* ccw)
{
    qDebug() << "setMain!\n";
    this->ccw = ccw;
}
