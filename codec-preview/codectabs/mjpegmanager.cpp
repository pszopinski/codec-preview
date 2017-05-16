#include "mjpegmanager.h"
#include "ui_mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent)
    : CodecManager(parent), ui(new Ui::MJPEGManager) {
    encoderParameter = "mjpeg";
    ui->setupUi(this);
}

MJPEGManager::~MJPEGManager() { delete ui; }
