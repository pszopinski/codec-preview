#include "mpeg2manager.h"
#include "ui_mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MPEG2Manager) {
    streamingParameters = "-c:v mpeg2video -preset ultrafast -f matroska";
    ui->setupUi(this);
}

MPEG2Manager::~MPEG2Manager() { delete ui; }
