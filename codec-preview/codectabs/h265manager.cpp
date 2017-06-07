#include "h265manager.h"
#include "ui_h265manager.h"

H265Manager::H265Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H265Manager) {
    encoderParameter = "libx265";
    ui->setupUi(this);
}

H265Manager::~H265Manager() { delete ui; }
