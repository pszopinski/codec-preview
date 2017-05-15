#include "mjpegmanager.h"
#include "ui_mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MJPEGManager) {
    streamingParameters = "-c:v mjpeg -preset ultrafast -f matroska";
    ui->setupUi(this);
}

MJPEGManager::~MJPEGManager() { delete ui; }
