#include "h261manager.h"
#include "ui_h261manager.h"

H261Manager::H261Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H261Manager) {
    encoderParameter = "h261";
    filterParameter = "scale=352:288:force_original_aspect_ratio=decrease,pad=352:288:(ow-iw)/2:(oh-ih)/2";
    ui->setupUi(this);
}

H261Manager::~H261Manager() { delete ui; }
