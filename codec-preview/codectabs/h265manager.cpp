#include "h265manager.h"
#include "ui_h265manager.h"

H265Manager::H265Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H265Manager) {
    streamingParameters = "-c:v libx265 -preset ultrafast -f matroska";
    ui->setupUi(this);
}

H265Manager::~H265Manager() { delete ui; }
