#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent, "libx265") {
    addParameter("Scale", "s", "640:360");
}

H265Manager::~H265Manager() {}
