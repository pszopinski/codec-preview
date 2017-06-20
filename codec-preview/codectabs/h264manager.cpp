#include "h264manager.h"

H264Manager::H264Manager(QWidget *parent) : CodecManager(parent, "libx264") {
    // addParameter(...);
}

H264Manager::~H264Manager() {}
