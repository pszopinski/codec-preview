#include "mjpegmanager.h"

MJPEGManager::MJPEGManager(QWidget *parent) : CodecManager(parent, "mjpeg") {
    addParameter("Scale", "s", "640:360");
}

MJPEGManager::~MJPEGManager() {}
