#include "h264manager.h"
#include "ui_h264manager.h"

H264Manager::H264Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H264Manager) {
    encoderParameter = "libx264";
    ui->setupUi(this);
}

H264Manager::~H264Manager() { delete ui; }
