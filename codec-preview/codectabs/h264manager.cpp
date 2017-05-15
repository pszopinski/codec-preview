#include "h264manager.h"
#include "ui_h264manager.h"

H264Manager::H264Manager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::H264Manager) {
    streamingParameters = "-c:v libx264 -preset ultrafast -f matroska";
    ui->setupUi(this);
}

H264Manager::~H264Manager() { delete ui; }
