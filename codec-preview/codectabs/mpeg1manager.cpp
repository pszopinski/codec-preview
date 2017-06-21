#include "mpeg1manager.h"

MPEG1Manager::MPEG1Manager(QWidget *parent)
    : CodecManager(parent, "mpeg1video") {
    addParameter("Resolution", "s", "640:360");
}

MPEG1Manager::~MPEG1Manager() {}
