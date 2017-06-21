#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager(QWidget *parent)
    : CodecManager(parent, "mpeg2video") {
    addParameter("Resolution", "s", "640:360");
}

MPEG2Manager::~MPEG2Manager() {}
