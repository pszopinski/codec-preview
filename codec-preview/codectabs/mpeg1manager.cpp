#include "mpeg1manager.h"
#include "ui_mpeg1manager.h"

MPEG1Manager::MPEG1Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MPEG1Manager) {
    streamingParameters = "-c:v mpeg1video -preset ultrafast -f matroska";
    ui->setupUi(this);
}

MPEG1Manager::~MPEG1Manager() { delete ui; }
