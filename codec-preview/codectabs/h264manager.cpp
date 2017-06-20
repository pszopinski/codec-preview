#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent, "libx264") {
    addParameter("Scale", "s", "640:360");
}

H264Manager::~H264Manager() {}
